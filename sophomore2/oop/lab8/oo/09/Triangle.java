public class Triangle {
    
    private double a;
    private double b;
    private double c;

    public Triangle(double a, double b, double c) {
        this.a = a;
        this.b = b;
        this.c = c;
    }

    public double getArea() {
        if (!check())
            throw new NotTriangleException();

        double p = (a + b + c) / 2;

        double area = Math.sqrt(p * (p-a) * (p-b) * (p-c));

        return area;
    }

    public void showInfo() {
        if (!check())
            throw new NotTriangleException();

        System.out.format("a = %f, b = %f, c = %f\n", a, b, c);
    }

    private boolean check() {
        return a + b > c && b + c > a && c + a > b;
    }
}