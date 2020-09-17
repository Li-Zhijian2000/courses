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

public class ShapeFactory {
    public enum ShapeType {
        ELLIPSE, RECTANGLE, RHOMBUS;
    }

    public Shape makeShape(ShapeType type, double a, double b) {
        if (a < 0 || b < 0)
            return null;

        switch (type) {
            case ELLIPSE:
                return new Ellipse(a, b);
            case RECTANGLE:
                return new Rectangle(a, b);
            case RHOMBUS:
                return new Rhombus(a, b);
            default:
                return null;
        }
    }

    public Shape randomNextShape() {
        Random randon = new Random();

        double a = randon.nextDouble() * 10, b = randon.nextDouble() * 10;
        ShapeType[] values = ShapeType.values();
        ShapeType type = values[randon.nextInt(values.length)];

        return makeShape(type, a, b);
    }
}