import java.io.PrintStream;

/**
 * PersonTest
 */
public class PersonTest extends Shell {

    static boolean DEBUG = true;

    public static void main(String[] args) {
        Shell shell = new Shell();
        shell.run(args, System.out);
    }

    @Override
    protected void run(String[] args, PrintStream out) {
        switch (getArg(args, 0)) {
            case "cid":
                CID.cid(out, getArg(args, 1));
                break;
            case "np":
                NP.np(out, getArg(args, 1), getArg(args, 2));
                break;
            default:
                throw new IllegalArgumentException();
        }
    }
}