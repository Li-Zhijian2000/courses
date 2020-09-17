
import java.io.PrintStream;


/**
 * CID
 */
public class Cid {
    public static void run(PrintStream out, String ID) {
        out.println(IDNum.checkIDNum(ID) ? "true" : "false");
    }
}