import java.util.HashMap;
import java.util.Map;

public class EmailSplit {
    public static void main(String[] args) {
        String str = "aa@sohu.com,bb@163.com,cc@sina.com";
        Map<String, String> emailMap = new HashMap<>();

        String[] emails = str.split(",");
        for (String email : emails) {
            int i = email.indexOf('@', 0);
            emailMap.put(email.substring(0, i), email.substring(i + 1));
        }

        System.out.println(emailMap.toString());
    }
}
