import java.io.File;
import java.io.IOException;
import java.util.HashMap;

public class JTNoodle {
    private static HashMap<String, String> archMapping = new HashMap<String, String>();
    private static final String X86 = "x86";
    private static final String X86_64 = "x86_64";

    static {
        // Copied from
        // https://github.com/xerial/snappy-java/blob/develop/src/main/java/org/xerial/snappy/OSInfo.java
        // x86 mappings
        archMapping.put(X86, X86);
        archMapping.put("i386", X86);
        archMapping.put("i486", X86);
        archMapping.put("i586", X86);
        archMapping.put("i686", X86);
        archMapping.put("pentium", X86);

        // x86_64 mappings
        archMapping.put(X86_64, X86_64);
        archMapping.put("amd64", X86_64);
        archMapping.put("em64t", X86_64);
        archMapping.put("universal", X86_64); // Needed for openjdk7 in Mac
    }

    static {
        // Well, this stinks
        //  https://community.oracle.com/thread/1550056?start=0&tstart=0
        // also http://stackoverflow.com/a/2734652
        //  https://github.com/rholder/gradle-one-jar

        // Determining which file to load is tricky. See
        //  https://github.com/xerial/snappy-java/issues/6
        // and
        //  https://github.com/xerial/snappy-java/blob/develop/src/main/java/org/xerial/snappy/SnappyLoader.java#L288
        String libFilename = System.mapLibraryName("jnitnoodle");
        if(libFilename.endsWith("jnilib")) {
            // mapLibraryName on JDK 7 on OS X started returning *.dylib
            // instead of the older *.jnilib. We're hip with the times,
            // so normalize the name to *.dylib.
            libFilename = libFilename.replace("jnilib", "dylib");
        }

        String libFileFullName = getNativeLibraryFolderName() + "/" + libFilename;

        System.out.println("About to load " + libFileFullName + " ... ");//<<<
        try {
            NativeUtils.loadLibraryFromJar(libFileFullName);
            System.out.println("Successfully loaded: " + libFileFullName);//<<<
        } catch(IOException e) {
            e.printStackTrace();//<<<
        }
    }

    // Same basic idea as https://github.com/xerial/snappy-java/blob/develop/src/main/java/org/xerial/snappy/OSInfo.java#L139
    private static String getTranslatedOsName() {
        String osName = System.getProperty("os.name");
        if(osName.contains("Windows")) {
            return "windows";
        } else if(osName.contains("Mac")) {
            return "osx";
        } else if(osName.contains("Linux")) {
            return "linux";
        } else {
            // No idea what OS we're running on =(.
            return osName.replaceAll("\\W", "");
        }
    }

    private static String getTranslatedArchName() {
        String osArch = System.getProperty("os.arch");
        String translatedArch = archMapping.get(osArch);
        if(translatedArch == null) {
            return osArch.replaceAll("\\W", "");
        }
        return translatedArch;
    }

    private static String getNativeLibraryFolderName() {
        return "/native/" + getTranslatedOsName() + "_" + getTranslatedArchName();
    }

    public static native String getShortPuzzleName(int puzzleId);
    public static native String generateScramble(int puzzleId);
}
