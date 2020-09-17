package tams.command;

import java.io.PrintStream;

import tams.Shell.FailType;
import tams.Shell.SuccessType;
import tams.course.Course;
import tams.course.CourseInfoException;
import tams.course.CourseList;

/**
 * UDC
 */
public class Udc {

    public static void run(PrintStream out, CourseList courseList, String cid, String option, String para)
            throws IllegalArgumentException {
        Course course = courseList.getCourseById(cid);
        if (course == null) {
            out.println(FailType.Course_does_not_exist);
            return;
        }
        try {
            switch (option) {
                case "-n": {
                    courseList.update(course, "Title", para, String.class);
                    out.println(SuccessType.Update_success);
                    break;
                }
                case "-c": {
                    courseList.update(course, "Capacity", Integer.parseInt(para), Integer.class);
                    out.println(SuccessType.Update_success);
                    break;
                }
                case "-t": {
                    courseList.update(course, "Teachers", splitTeachers(para), String[].class);
                    out.println(SuccessType.Update_success);
                    break;
                }
                default:
                    throw new IllegalArgumentException();
            }
        } catch (CourseInfoException e) {
            out.println(FailType.Update_fail);
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