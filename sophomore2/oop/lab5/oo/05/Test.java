import java.util.List;
import java.util.ArrayList;

public class Test {
    public static void main(String[] args) {
        ShapeFactory shapeFactory = new ShapeFactory();
        List<Shape> shapes = new ArrayList<>();
        for (int i = 0; i < 5; i++) {
            shapes.add(shapeFactory.randomNextShape());
        }
        for (Shape shape : shapes) {
            System.out.println(shape.calcArea());
        }
    }
}