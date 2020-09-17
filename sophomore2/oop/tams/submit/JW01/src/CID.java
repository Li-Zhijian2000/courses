
import java.io.PrintStream;

/**
 * CID
 */
public class CID {
    public static void cid(PrintStream out, String ID) {
        out.println(IDNum.checkIDNum(ID) ? "true" : "false");
    }
}