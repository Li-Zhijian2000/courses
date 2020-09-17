package music;

import music.Music.Style;

public class MusicTest {
    public static void main(String[] args) {
        Music music = new Music("500 miles", Style.COUNTRY);
        System.out.println(music);
    }
}