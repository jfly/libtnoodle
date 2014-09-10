
public class JTNoodle {
    static {
        // Well, this stinks
        // https://community.oracle.com/thread/1550056?start=0&tstart=0
        // also http://stackoverflow.com/a/2734652
        // https://github.com/rholder/gradle-one-jar
        System.out.println(System.getProperty("java.library.path"));//<<<
        System.out.println(System.mapLibraryName("tnoodlejni"));//<<<
        System.loadLibrary("tnoodlejni");
    }

    public static native int summer();
}
