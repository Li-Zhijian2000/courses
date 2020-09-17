/**
 * UnicodeFormOf
 */
public class UnicodeFormOf {

    public static String unicodeFormOf(char c) {

        return String.format("\\u%4s", Integer.toHexString(c))
                     .replace(' ', '0');
    }

    public static void main(String[] args) {
        
        char a = 'a', b = '冲';

        System.out.println(unicodeFormOf(a));
        System.out.println(unicodeFormOf(b));
    }
}