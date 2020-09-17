package tams;

import java.io.PrintStream;
import java.util.Scanner;

import tams.command.Cid;
import tams.command.Gc;
import tams.command.Nc;
import tams.command.Np;
import tams.command.Udc;
import tams.course.CourseList;

/**
 * PersonTest
 */
public class Test extends Shell {

    public static Scanner scanner = new Scanner(System.in);

    public static PrintStream out = System.out;

    public static CourseList courseList = new CourseList();

    public static void main(String[] args) {
        final Shell shell = new Test();
        while (scanner.hasNextLine()) {
            args = scanner.nextLine().split("\\s+");
            if (shell.run(args))
                break;
        }
        scanner.close();
    }

    @Override
    protected boolean run(final String[] args) {
        try {
            switch (getArg(args, 0)) {
                case "ls":
                    out.println(courseList);
                    break;
                case "QUIT":
                    return true;
                case "cid":
                    Cid.run(out, getArg(args, 1));
                    break;
                case "np":
                    Np.run(out, getArg(args, 1), getArg(args, 2));
                    break;
                case "gc":
                    switch (getArg(args, 1)) {
                        case "-id":
                            Gc.Id.run(out, courseList, getArg(args, 2));
                            break;
                        case "-key":
                            Gc.Key.run(out, courseList, getArg(args, 2),
                                    getArg(args, 3), getArg(args, 4));
                            break;
                        case "-all":
                            Gc.All.run(out, courseList, getArg(args, 2),
                                    getArg(args, 3));
                            break;
                        default:
                            throw new IllegalArgumentException();
                    }
                    break;

                case "udc":
                    Udc.run(out, courseList, getArg(args, 1), getArg(args, 2),
                            getArg(args, 3));
                    break;

                case "nc":
                    Nc.run(out, courseList, getArg(args, 1), getArg(args, 2),
                            getArg(args, 3), getArg(args, 4));
                    break;
                default:
                    throw new IllegalArgumentException();
            }
        } catch (final IllegalArgumentException e) {
            out.println(FailType.Input_illegal);
        }
        return false;
    }
}