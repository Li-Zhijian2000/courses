/**
 * Strscat
 */
public class Strscat {

   public static String strscat(String ...args) {

      String ret = "";
      for (String str: args) {
         ret += str;
      }
      return ret;
   }

   public static void main(String[] args) {
      
      System.out.println(strscat("a", "b", "c", "d"));
      System.out.println(strscat("str"));
   }
}