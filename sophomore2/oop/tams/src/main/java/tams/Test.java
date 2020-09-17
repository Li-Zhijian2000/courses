package tams;

import java.io.FileInputStream;
import java.util.Arrays;
import java.util.Scanner;

import tams.course.CourseList;

/**
 * Test
 */
public class Test extends Shell {
    private static boolean DEBUG = true;
    protected static Scanner scanner;

    public static void main(String[] args) {
        if (DEBUG) {
            try {
                System.setIn(new FileInputStream(
                        "/home/zhijian/fourth/oop/tams/src/main/java/tams/input.txt"));
            } catch (Exception e) {
                System.out.println("file not found");
            }
        }
        scanner = new Scanner(System.in);
        CourseList courseList = new CourseList();
        boolean flag = true;
        while (flag && scanner.hasNextLine()) {
            try {
                args = scanner.nextLine().split("\\s+");
                switch (getArg(args, 0)) {
                    case "ls":
                        Arrays.stream(courseList.getCourseByKeyword(""))
                                .forEach(System.out::println);
                        break;
                    case "QUIT":
                        flag = false;
                        break;
                    case "cid":
                        cid(getArg(args, 1));
                        break;
                    case "np":
                        np(getArg(args, 1), getArg(args, 2));
                        break;
                    case "gc":
                        gc(args, courseList);
                        break;
                    case "udc":
                        udc(args, courseList);
                        break;
                    case "nc":
                        nc(args, courseList);
                        break;
                    default:
                        throw new IllegalArgumentException();
                }
            } catch (IllegalArgumentException e) {
                System.out.println(FailType.Input_illegal);
            }
        }
        scanner.close();
    }
}