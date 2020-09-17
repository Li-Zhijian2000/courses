class MyPrintStream {

    public void println() {
        System.out.println();
    }

    public void println(String x) {
        System.out.println(x);
    }
}

class MySystem {

    public static final MyPrintStream out = new MyPrintStream();
}

public class SystemOutDemo {
    public static void main(String[] args) {
        MySystem.out.println("hello");
    }
}