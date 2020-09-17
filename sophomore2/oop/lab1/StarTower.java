/**
 * StarTower
 */
public class StarTower {

    public static void main(String[] args) {
        
        final int n = Integer.parseInt(args[0]);

        for (int i = 1; i <= n; i += 2) {
            System.out.printf("%s%s%s\n", " ".repeat((n-i)/2),  "*".repeat(i), " ".repeat((n-i)/2));
        }

        for (int i = n-2; i >= 0; i -= 2) {
            System.out.printf("%s%s%s\n", " ".repeat((n-i)/2),  "*".repeat(i), " ".repeat((n-i)/2));
        }
    }
}