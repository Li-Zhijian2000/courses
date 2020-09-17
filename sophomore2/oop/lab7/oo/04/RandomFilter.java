import java.util.Arrays;
import java.util.Random;

public class RandomFilter {
    public static void main(String[] args) {
        Random random = new Random();

        int[] randoms = new int[10];
        for (int i = 0; i < 10; i++)
            randoms[i] = random.nextInt(100) + 1;

        Arrays.stream(randoms).filter(x -> x > 50).forEach(System.out::println);
    }
}