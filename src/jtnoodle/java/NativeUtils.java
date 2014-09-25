//<<<package cz.adamh.utils;
 
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.HashMap;
 
/**
 * Simple library class for working with JNI (Java Native Interface)
 * Changes for cross platform and cross architecture added by Jeremy
 * Fleischman.
 * 
 * @see http://frommyplayground.com/how-to-load-native-jni-library-from-jar
 *
 * @author Adam Heirnich <adam@adamh.cz>, http://www.adamh.cz
 * @author Jeremy Fleischman <jeremyfleischman@gmail.com>
 */
public class NativeUtils {
 
    /**
     * Private constructor - this class will never be instanced
     */
    private NativeUtils() {
    }
 
    /**
     * Loads library from current JAR archive
     * 
     * The file from JAR is copied into system temporary directory and then loaded. The temporary file is deleted after exiting.
     * Method uses String as filename because the pathname is "abstract", not system-dependent.
     * 
     * @param filename The filename inside JAR as absolute path (beginning with '/'), e.g. /package/File.ext
     * @throws IOException If temporary file creation or read/write operation fails
     * @throws IllegalArgumentException If source file (param path) does not exist
     * @throws IllegalArgumentException If the path is not absolute or if the filename is shorter than three characters (restriction of {@see File#createTempFile(java.lang.String, java.lang.String)}).
     */
    public static void loadLibraryFromJar(String path) throws IOException {
 
        if (!path.startsWith("/")) {
            throw new IllegalArgumentException("The path has to be absolute (start with '/').");
        }
 
        // Obtain filename from path
        String[] parts = path.split("/");
        String filename = (parts.length > 1) ? parts[parts.length - 1] : null;
 
        // Split filename to prexif and suffix (extension)
        String prefix = "";
        String suffix = null;
        if (filename != null) {
            parts = filename.split("\\.", 2);
            prefix = parts[0];
            suffix = (parts.length > 1) ? "."+parts[parts.length - 1] : null; // Thanks, davs! :-)
        }
 
        // Check if the filename is okay
        if (filename == null || prefix.length() < 3) {
            throw new IllegalArgumentException("The filename has to be at least 3 characters long.");
        }
 
        // Prepare temporary file
        File temp = File.createTempFile(prefix, suffix);
        temp.deleteOnExit();
 
        if (!temp.exists()) {
            throw new FileNotFoundException("File " + temp.getAbsolutePath() + " does not exist.");
        }
 
        // Prepare buffer for data copying
        byte[] buffer = new byte[1024];
        int readBytes;
 
        // Open and check input stream
        InputStream is = NativeUtils.class.getResourceAsStream(path);
        if (is == null) {
            throw new FileNotFoundException("File " + path + " not found by getResourceAsStream.");
        }
 
        // Open output stream and copy data between source file in JAR and the temporary file
        OutputStream os = new FileOutputStream(temp);
        try {
            while ((readBytes = is.read(buffer)) != -1) {
                os.write(buffer, 0, readBytes);
            }
        } finally {
            // If read/write fails, close streams safely before throwing an exception
            os.close();
            is.close();
        }
 
        // Finally, load the library
        System.out.println("About to load " + temp.getAbsolutePath());//<<<
        System.load(temp.getAbsolutePath());
        System.out.println("Successfully loaded " + temp.getAbsolutePath());//<<<
    }


    // **** Begin custom changes ****

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

    public static void loadLibrary(String name) throws IOException {
        // Well, this stinks
        //  https://community.oracle.com/thread/1550056?start=0&tstart=0
        // also http://stackoverflow.com/a/2734652
        //  https://github.com/rholder/gradle-one-jar

        // Determining which file to load is tricky. See
        //  https://github.com/xerial/snappy-java/issues/6
        // and
        //  https://github.com/xerial/snappy-java/blob/develop/src/main/java/org/xerial/snappy/SnappyLoader.java#L288
        String libFilename = System.mapLibraryName(name);
        if(libFilename.endsWith("jnilib")) {
            // mapLibraryName on JDK 7 on OS X started returning *.dylib
            // instead of the older *.jnilib. We're hip with the times,
            // so normalize the name to *.dylib.
            libFilename = libFilename.replace("jnilib", "dylib");
        }

        String libFileFullName = getNativeLibraryFolderName() + "/" + libFilename;

        System.out.println("About to load " + libFileFullName + " ... ");//<<<
        NativeUtils.loadLibraryFromJar(libFileFullName);
        System.out.println("Successfully loaded: " + libFileFullName);//<<<
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
}
