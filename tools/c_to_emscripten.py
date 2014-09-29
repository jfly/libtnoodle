#!/usr/bin/env python2

import json
import argparse
import collections
import clang.cindex
from clang.cindex import TypeKind
from clang.cindex import CursorKind

Function = collections.namedtuple('Function', ['name', 'returnType', 'argumentTypes'])

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

def getFunctions(node):
    if node.kind == CursorKind.FUNCTION_DECL:
        args = []
        for arg in node.get_arguments():
            jsType = getJavascriptType(arg.type)
            args.append(jsType)
        jsReturnType = getJavascriptType(node.result_type)
        return [ Function( node.spelling, jsReturnType, args ) ]

    # Recurse for children of this node
    funcs = []
    for c in node.get_children():
        funcs += getFunctions(c)
    return funcs

def main():
    parser = argparse.ArgumentParser(description='Produce Emscripten wrapper code for a C header file.')
    parser.add_argument('file', type=argparse.FileType('r'), help='C header file to parse')
    parser.add_argument('action', choices=[ "exported", "cwrap" ])
    args = parser.parse_args()

    index = clang.cindex.Index.create()
    tu = index.parse(args.file.name)
    funcs = getFunctions(tu.cursor)
    if args.action == "cwrap":
        prefixes = set()
        js = ""
        for f in funcs:
            prefix, shortName = f.name.split("_")
            prefixes.add(prefix)
            funcData = {}
            funcData['prefix'] = prefix
            funcData['shortName'] = shortName
            funcData['name'] = f.name
            funcData['returnType'] = f.returnType
            funcData['argumentTypes'] = json.dumps(f.argumentTypes)
            js += '{prefix}.{shortName} = Module.cwrap("{name}", "{returnType}", {argumentTypes});\n'.format(**funcData)
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
