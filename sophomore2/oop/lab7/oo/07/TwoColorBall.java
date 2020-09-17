import java.util.HashSet;
import java.util.Random;
import java.util.Set;

public class TwoColorBall {
    public static void main(String[] args) {
        Set<Integer> existBall = new HashSet<>();
        Random random = new Random();
        boolean hasBlue = false;

        while (existBall.size() != 7) {
            int x = random.nextInt(48) + 1;
            if (x >= 34) {
                if (!hasBlue) {
                    existBall.add(x);
                    System.out.println("蓝球 " + (x - 33));
                    hasBlue = true;
                } else
                    continue;
            }

            if (!existBall.contains(x)) {
                existBall.add(x);
                System.out.println("红球 " + x);
            }
        }
    }
}
