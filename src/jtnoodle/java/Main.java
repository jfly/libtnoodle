
public class Main {
    public static void main(String[] args) {
        String shortName = jtnoodle.getShortPuzzleName(0);
        String scramble = jtnoodle.generateScramble(0);
        System.out.println(shortName + " scramble: " + scramble);
    }
}
