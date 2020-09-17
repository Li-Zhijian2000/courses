/**
 * DefaultInit
 */
public class DefaultInit {

    byte a;
    short b;
    int c;
    long d;
    boolean e;
    char f;
    float g;
    double h;

    public static void main(String[] args) {
        
        DefaultInit di = new DefaultInit();

        System.out.println("byte: " + di.a);
        System.out.println("short: " + di.b);
        System.out.println("int: " + di.c);
        System.out.println("long: " + di.d);
        System.out.println("boolean: " + di.e);
        System.out.println("char: " + Integer.toHexString(di.f));
        System.out.println("float: " + di.g);
        System.out.println("double: " + di.h);

    }
}