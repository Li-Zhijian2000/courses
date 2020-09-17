
public class Test {
    public static void main(String[] args) {
        Rectangle rectangle = new Rectangle(3.0, 4.0);
        System.out.println("rectangle area: " + rectangle.calcArea());

        Ellipse ellipse = new Ellipse(2.0, 1.0);
        System.out.println("ellipse area: " + ellipse.calcArea());

        Rhombus rhombus = new Rhombus(2.0, 1.0);
        System.out.println("rhombus area: " + rhombus.calcArea());

        Rectangle error = new Rectangle(-1, 0);
    }
}