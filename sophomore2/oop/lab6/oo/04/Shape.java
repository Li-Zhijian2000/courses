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

interface IShapeFactory {
    Shape makeShape(double a, double b);
}

class Rhombus extends Shape {
    private static IShapeFactory factory = new IShapeFactory() {
        @Override
        public Shape makeShape(double a, double b) {
            if (a < 0 || b < 0)
                return null;
            return new Rhombus(a, b);
        }
    };

    public static IShapeFactory getFactory() {
        return factory;
    }

    public Rhombus(double a, double b) {
        super(a, b);
    }

    @Override
    public double calcArea() {
        return a * b;
    }
}

class Ellipse extends Shape {
    private static IShapeFactory factory = new IShapeFactory() {
        @Override
        public Shape makeShape(double a, double b) {
            if (a < 0 || b < 0)
                return null;
            return new Ellipse(a, b);
        }
    };

    public static IShapeFactory getFactory() {
        return factory;
    }

    public Ellipse(double a, double b) {
        super(a, b);
    }

    @Override
    public double calcArea() {
        return Math.PI * a * b;
    }
}

class Rectangle extends Shape {
    private static IShapeFactory factory = new IShapeFactory() {
        @Override
        public Shape makeShape(double a, double b) {
            if (a < 0 || b < 0)
                return null;
            return new Rectangle(a, b);
        }
    };

    public static IShapeFactory getFactory() {
        return factory;
    }

    public Rectangle(double a, double b) {
        super(a, b);
    }

    @Override
    public double calcArea() {
        return a * b;
    }
}
