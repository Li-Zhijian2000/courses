import java.util.Scanner;

public class Solver {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();

        boolean isNum = true;
        for (char ch : input.toCharArray()) {
            if (!Character.isDigit(ch)) {
                isNum = false;
            }
        }
        if (!isNum || input != removePreZero(input)) {
            System.out.println(input + "不是没有前导0的无符号整数");
            return;
        } else {
            System.out.println(input + "是没有前导0的无符号整数");
        }
        String reverseInput = removePreZero(new StringBuilder(input).reverse().toString());
        if (reverseInput.equals(input)) {
            System.out.println(input + "是回文数");
        } else {
            System.out.println(input + "不是回文数");
        }
    }

    static String removePreZero(String s) {
        if (s.length() == 1)
            return s;

        int i = 0;
        while (i < s.length() && s.charAt(i) == '0') {
            i++;
        }
        return s.substring(i);
    }
}