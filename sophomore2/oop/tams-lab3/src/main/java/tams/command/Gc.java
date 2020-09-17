package tams.command;

import java.io.PrintStream;
import java.util.Arrays;
import java.util.Optional;

import tams.Shell.FailType;
import tams.Test;
import tams.course.Course;
import tams.course.CourseList;

/**
 * GC
 */
public class Gc {

    public static class Id {
        public static void run(PrintStream out, CourseList courseList,
                String id) {
            final Course res = courseList.getCourseById(id);
            Optional.ofNullable(res).ifPresentOrElse((x) -> out.println(x),
                    () -> out.println(FailType.Course_does_not_exist));
        }
    }

    public static class Key {
        public static void run(PrintStream out, CourseList courseList,
                String keyword, String n, String m) {
            final Course[] res = courseList.getCourseByKeyword(keyword);
            Arrays.sort(res);

            gcShell(out, res, Integer.parseInt(n), Integer.parseInt(m));
        }
    }

    public static class All {
        public static void run(PrintStream out, CourseList courseList, String n,
                String m) {
            Key.run(out, courseList, "", n, m);
        }
    }

    private static void gcShell(PrintStream out, Course[] res, int n, int m) {
        boolean flag = true;
        while (flag) {
            final int fromIndex = (n - 1) * m,
                    toIndex = Math.min(n * m, res.length);
            if (fromIndex >= toIndex || fromIndex < 0) {
                out.println(FailType.Course_does_not_exist);
                flag = false;
            } else {
                out.println("Page:" + n);
                for (int i = fromIndex; i < toIndex; i++) {
                    out.format("%d.%s\n", i - fromIndex + 1, res[i]);
                }
                out.println("n-next page, l-last page, q-quit");
                if (Test.scanner.hasNextLine())
                    switch (Test.scanner.nextLine()) {
                        case "n":
                            n++;
                            break;
                        case "l":
                            n--;
                            break;
                        case "q":
                            flag = false;
                            break;
                        default:
                            out.println(FailType.Input_illegal);
                    }
                else
                    flag = false;
            }
        }
    }
}
