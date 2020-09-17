import java.io.PrintStream;
import java.util.Scanner;

/**
 * PersonTest
 */
public class CourseTest extends Shell {

    public static PrintStream out = System.out;

    public static CourseList courseList = new CourseList();

    public static void main(String[] args) {
        Shell shell = new CourseTest();
        shell.run(args);
    }

    @Override
    protected void run(String[] args) {
        try {
            switch (getArg(args, 0)) {
                case "gc":
                    switch (getArg(args, 1)) {
                        case "-id":
                            Gc.Id.run(out, courseList, getArg(args, 2));
                            break;
                        case "-key":
                            Gc.Key.run(out, courseList, getArg(args, 2));
                            break;
                        default:
                            throw new IllegalArgumentException();
                    }
                    break;

                case "udc":
                    Udc.run(out, courseList, getArg(args, 1), getArg(args, 2), getArg(args, 3));
                    break;

                case "nc":
                    Nc.run(out, courseList, getArg(args, 1), getArg(args, 2), getArg(args, 3), getArg(args, 4));
                    break;
                default:
                    throw new IllegalArgumentException();
            }
        } catch (IllegalArgumentException e) {
            out.println(FailType.Input_illegal);
        }
    }
}