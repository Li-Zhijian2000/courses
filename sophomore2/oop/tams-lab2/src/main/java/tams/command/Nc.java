package tams.command;

import java.io.PrintStream;

import tams.Shell.FailType;
import tams.Shell.SuccessType;
import tams.course.Course;
import tams.course.CourseInfoException;
import tams.course.CourseList;

/**
 * Nc
 */
public class Nc {

    public static void run(PrintStream out, CourseList courseList, String cid, String title, String teachers,
            String capacity) throws IllegalArgumentException {
        try {
            Course course = courseList.getCourseById(cid);
            if (course == null) {
                Course c = new Course();
                c.init(cid, title, splitTeachers(teachers), Integer.parseInt(capacity));
                courseList.add(c);
                out.println(SuccessType.Add_success);
            } else {
                out.println(FailType.Course_exists);
            }
        } catch (CourseInfoException e) {
            out.println(FailType.Course_add_illegal);
        }
    }

    private static String[] splitTeachers(String para) throws IllegalArgumentException {
        if ("[]".equals(para)) {
            return new String[] {};
        }
        if (!para.matches("\\[[^,]+(,[^,]+)*\\]")) {
            throw new IllegalArgumentException();
        }
        return para.substring(1, para.length() - 1).split(",");
    }
}