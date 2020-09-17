package tams;

import java.util.Arrays;

import tams.course.Course;
import tams.course.CourseList;

/**
 * PersonTest
 */
public class CourseTest extends Shell {
    public static void main(String[] args) {
        CourseList courseList = new CourseList();
        // Course course = new Course();
        // try {
        // course.init("bh000000", "oop", new String[] { "zhijian" }, 100);
        // } catch (Exception e) {
        // }
        try {
            switch (getArg(args, 0)) {
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

    protected static void gc(String[] args, CourseList courseList)
            throws IllegalArgumentException {
        switch (getArg(args, 1)) {
            case "-id":
                gcId(getArg(args, 2), courseList);
                break;
            case "-key":
                gcKey(getArg(args, 2), courseList);
                break;
            default:
                throw new IllegalArgumentException();
        }
    }

    protected static void gcKey(String keyword, CourseList courseList) {
        final Course[] res = courseList.getCourseByKeyword(keyword);
        Arrays.sort(res);
        System.out.println("Total:" + res.length);
        for (int i = 0; i < res.length; i++) {
            System.out.format("%d.%s\n", i + 1, res[i]);
        }
    }
}