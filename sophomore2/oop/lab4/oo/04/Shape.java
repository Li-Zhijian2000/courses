public abstract class Shape {
    protected double a;
    protected double b;

    public Shape() {
        this(0.0, 0.0);
    }

    public Shape(double a, double b) throws IllegalArgumentException {
        if (a < 0 || b < 0)
            throw new IllegalArgumentException("length could not be negative");
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
