package tams;

import java.io.PrintStream;
import java.util.Scanner;

import tams.command.Gc;
import tams.command.Nc;
import tams.command.Udc;
import tams.course.CourseList;

/**
 * PersonTest
 */
public class CourseTest extends Shell {

    public static PrintStream out = System.out;

    public static CourseList courseList = new CourseList();

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Shell shell = new CourseTest();
        while (scanner.hasNextLine()) {
            args = scanner.nextLine().split("\\s+");
            shell.run(args);
        }
        scanner.close();
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