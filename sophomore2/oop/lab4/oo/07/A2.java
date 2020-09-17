class Parent {
    public Parent() {
        System.out.println("this is Parent class constructor");
    }
}

class Sub extends Parent {
    public int a = f();

    public int f() {
        System.out.println("this is Subclass member");
        return 1;
    }

    public Sub() {
        System.out.println("this is Subclass constructor");
    }
}

public class A2 {
    public static void main(String[] args) {
        Sub sub = new Sub();
    }
}