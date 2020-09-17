import java.util.Scanner;
import java.util.InputMismatchException;

public class CalculateTest {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        try {
            int a = scanner.nextInt();
            String op = scanner.next();
            int b = scanner.nextInt();
            
            if ("+".equals(op)) 
                System.out.format("%d %s %d = %d\n", a, op, b, Calculate.add(a, b));
            else if ("-".equals(op)) 
                System.out.format("%d %s %d = %d\n", a, op, b, Calculate.minus(a, b));
            else System.out.println("input illegal");

        } catch (InputMismatchException e) {
            System.out.println("input illegal");
        } catch (RuntimeException e) {
            System.out.println(e.getMessage());
        }
    }
}