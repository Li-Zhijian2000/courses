/**
 * StarTower
 */
public class NumberBox {

    public static void main(String[] args) {
        
        final int n = Integer.parseInt(args[0]);

        for (int i = 1; i <= n * n; i++) {

            System.out.printf("%d ", i);

            if (i % n == 0) System.out.println("");
        }
    }
}