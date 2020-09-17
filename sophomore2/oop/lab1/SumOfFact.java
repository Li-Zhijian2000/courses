/**
 * SumOfFact
 */
public class SumOfFact {

    public static long fact(int n) {
        
        long sum = 1;

        for (int i = 1; i <= n; i++) sum *= i;
        
        return sum;
    }

    public static void main(String[] args) {
        
        final int maxn = 20;
        int n; double sum;

        n = maxn; sum = 0;
        while (n != 0) sum += 1.0 / fact(n--);
        System.out.println(sum);

        n = maxn; sum = 0;
        do sum += 1.0 / fact(n--); while (n != 0);
        System.out.println(sum);

    }
}