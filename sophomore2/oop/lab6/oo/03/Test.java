public class Test {
    public static Shape makeShape(IShapeFactory factory, double a, double b) {
        return factory.makeShape(a, b);
    }

    public static void main(String[] args) {
        IShapeFactory[] factories = new IShapeFactory[] { Rhombus.getFactory(), Rectangle.getFactory(),
                Ellipse.getFactory() };
        for (IShapeFactory factory : factories) {
            Shape shape = makeShape(factory, 2, 2);
            System.out.println(shape.calcArea());
        }
    }
}