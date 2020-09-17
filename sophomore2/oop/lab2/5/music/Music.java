package music;

public class Music {

    private String name;

    private Style style;

    public Music(String name, Style style) {
        this.name = name;
        this.style = style;
    }

    public enum Style {
        JAZZ, LATIN, HIPHOP, COUNTRY
    };

    @Override
    public String toString() {
        return "name: " + name + "\n" + "Style: " + style.toString().toLowerCase();
    }
}