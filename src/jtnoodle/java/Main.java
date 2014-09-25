
public class Main {
    public static void main(String[] args) {
        String shortName = jtnoodle.tnoodle_getShortPuzzleName(0);
        String scramble = jtnoodle.tnoodle_generateScramble(0);
        System.out.println(shortName + " scramble: " + scramble);
    }
}
