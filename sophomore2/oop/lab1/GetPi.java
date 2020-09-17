/**
 * GetPi
 */
public class GetPi {

    public static double getPi(int n) {

        double sum = 0;

        for (int i = 0; i <= n; i++) {
            sum += Math.pow(-1, i) / (2*i + 1);
        }

        sum *= 4;
        return sum;
    }
    public static void main(String[] args) {
        
        System.out.println(getPi(Integer.parseInt(args[0])));
    }
}