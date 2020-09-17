package tams.command;

import java.io.PrintStream;
import java.util.Arrays;
import java.util.Optional;

import tams.Shell.FailType;
import tams.course.Course;
import tams.course.CourseList;

/**
 * GC
 */
public class Gc {

    public static class Id {
        public static void run(PrintStream out, CourseList courseList, String id) {
            final Course res = courseList.getCourseById(id);
            Optional.ofNullable(res).ifPresentOrElse((x) -> out.println(x),
                    () -> out.println(FailType.Course_does_not_exist));
        }
    }

    public static class Key {
        public static void run(PrintStream out, CourseList courseList, String keyword) {
            final Course[] res = courseList.getCourseByKeyword(keyword);
            Arrays.sort(res);
            System.out.println("Total:" + res.length);
            for (int i = 0; i < res.length; i++) {
                out.format("%d.%s\n", i + 1, res[i]);
            }
        }
    }
}
