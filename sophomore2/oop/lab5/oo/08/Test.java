import java.util.Random;

abstract class Shape {
    protected double a;
    protected double b;

    public Shape() {
        this(0.0, 0.0);
    }

    public Shape(double a, double b) {
        this.a = a;
        this.b = b;
    }

    /**
     * calcArea 计算形状的面积
     * 
     * @return 面积
     */
    abstract public double calcArea();

    /* 其他必要的方法，比如getter和setter */
}

class Rhombus extends Shape {
    public Rhombus(double a, double b) {
        super(a, b);
    }

    @Override
    public double calcArea() {
        return a * b;
    }
}

class Ellipse extends Shape {
    public Ellipse(double a, double b) {
        super(a, b);
    }

    @Override
    public double calcArea() {
        return Math.PI * a * b;
    }
}

class Rectangle extends Shape {
    public Rectangle(double a, double b) {
        super(a, b);
    }

    @Override
    public double calcArea() {
        return a * b;
    }
}

interface IShapeFactory {
    Shape makeShape(double a, double b);
}

class RhomousFactory implements IShapeFactory {
    @Override
    public Shape makeShape(double a, double b) {
        if (a < 0 || b < 0)
            return null;
        return new Rhombus(a, b);
    }
}

class EllipseFactory implements IShapeFactory {
    @Override
    public Shape makeShape(double a, double b) {
        if (a < 0 || b < 0)
            return null;
        return new Ellipse(a, b);
    }
}

class RectangleFactory implements IShapeFactory {
    @Override
    public Shape makeShape(double a, double b) {
        if (a < 0 || b < 0)
            return null;
        return new Rectangle(a, b);
    }
}

public class Test {
    public static Shape makeShape(IShapeFactory factory, double a, double b) {
        return factory.makeShape(a, b);
    }

    public static void main(String[] args) {
        IShapeFactory[] factories = new IShapeFactory[] { new RhomousFactory(), new RectangleFactory(),
                new EllipseFactory() };
        for (IShapeFactory factory : factories) {
            Shape shape = makeShape(factory, 2, 2);
            System.out.println(shape.calcArea());
        }
    }
}