#!/usr/bin/env python2

import json
import argparse
import collections
import clang.cindex
from clang.cindex import TypeKind
from clang.cindex import CursorKind

Function = collections.namedtuple('Function', ['name', 'returnType', 'argumentTypes'])
Constant = collections.namedtuple('Constant', ['name', 'value'])

def getJavascriptType(t):
    if t.kind == TypeKind.TYPEDEF:
        return getJavascriptType(t.get_canonical())
    elif t.kind == TypeKind.POINTER:
        pointee = t.get_pointee()
        if pointee.kind == TypeKind.CHAR_S:
            return "string"
        else:
            assert False # unrecognized pointer type
    elif t.kind in [ TypeKind.INT, TypeKind.UINT, TypeKind.LONG ]:
        return "number"
    else:
        assert False # unrecognized type

def getFunctionsAndConstants(node, filename):
    if node.kind == CursorKind.FUNCTION_DECL:
        args = []
        for arg in node.get_arguments():
            jsType = getJavascriptType(arg.type)
            args.append(jsType)
        jsReturnType = getJavascriptType(node.result_type)
        return [ Function( node.spelling, jsReturnType, args ) ], []
    elif node.kind == CursorKind.MACRO_DEFINITION:
        if node.location.file is not None and node.location.file.name == filename:
            tokens = list(node.get_tokens())
            # We're only interested in stuff like
            #  #define PI 3.14
            # not
            #  #define CNOODLE_H
            if len(tokens) == 3:
                identifier, literal, hsh = tokens
                return [], [ Constant(identifier.spelling, literal.spelling) ]

    # Recurse for children of this node
    funcs = []
    consts = []
    for c in node.get_children():
        fs, cs = getFunctionsAndConstants(c, filename)
        funcs += fs
        consts += cs
    return funcs, consts

def main():
    parser = argparse.ArgumentParser(description='Produce Emscripten wrapper code for a C header file.')
    parser.add_argument('file', type=argparse.FileType('r'), help='C header file to parse')
    parser.add_argument('action', choices=[ "exported", "cwrap" ])
    args = parser.parse_args()

    index = clang.cindex.Index.create()
    tu = index.parse(args.file.name, options=clang.cindex.TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD)
    funcs, consts = getFunctionsAndConstants(tu.cursor, args.file.name)
    if args.action == "cwrap":
        prefixes = set()
        js = ""
        for f in funcs:
            prefix, shortName = f.name.split("_", 1)
            prefixes.add(prefix)
            funcData = {}
            funcData['prefix'] = prefix
            funcData['shortName'] = shortName
            funcData['name'] = f.name
            funcData['returnType'] = f.returnType
            funcData['argumentTypes'] = json.dumps(f.argumentTypes)
            js += '{prefix}.{shortName} = Module.cwrap("{name}", "{returnType}", {argumentTypes});\n'.format(**funcData)
        for c in consts:
            prefix, shortName = c.name.split("_", 1)
            prefix = prefix.lower()
            constData = {
                'prefix': prefix,
                'shortName': shortName,
                'value': c.value,
            }
            js += "{prefix}.{shortName} = {value};\n".format(**constData)
        for prefix in prefixes:
            js = "var {0} = {0} || {{}};\n".format(prefix) + js
        print js,
    elif args.action == "exported":
        funcNames = [ "_%s" % f.name for f in funcs ]
        exported = 'EXPORTED_FUNCTIONS=%s' % json.dumps( funcNames )
        print exported
    else:
        assert False

if __name__ == "__main__":
    main()
