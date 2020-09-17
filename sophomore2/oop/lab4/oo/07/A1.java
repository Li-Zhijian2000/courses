
// 证明先完成父类的加载，之后再执行本类的静态初始化
class Parent {
    static int a1 = f1();

    static int f1() {
        System.out.println("this is parent class");
        return 0;
    }
}

class Sub extends Parent {
    static int a2 = f2();

    static int f2() {
        System.out.println("this is subclass");
        return 1;
    }
}

public class A1 {
    public static void main(String[] args) {
        Sub sub = new Sub();
    }
}