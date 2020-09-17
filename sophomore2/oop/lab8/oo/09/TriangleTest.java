public class TriangleTest {
    
    public static void main(String[] args) {
        try {
            Triangle triangle = new Triangle(1.0, 2.0, 3.0);
            System.out.println(triangle.getArea());
            triangle.showInfo();
        } catch (NotTriangleException e) {
            System.out.println("this is not a triangle");
        }

        System.out.println("\n---------------\n");

        try {
            Triangle triangle = new Triangle(2.0, 2.0, 3.0);
            System.out.println(triangle.getArea());
            triangle.showInfo();
        } catch (NotTriangleException e) {
            System.out.println("this is not a triangle");
        }
    }
}