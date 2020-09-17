
import java.io.PrintStream;

/**
 * UDC
 */
public class Udc {

    public static void run(PrintStream out, CourseList courseList, String cid,
            String option, String para) throws IllegalArgumentException {
        Course course = courseList.getCourseById(cid);
        if (course == null) {
            out.println(FailType.Course_does_not_exist);
            return;
        }
        try {
            switch (option) {
                case "-n": {
                    course.setTitle(para);
                    out.println(SuccessType.Update_success);
                    break;
                }
                case "-c": {
                    course.setCapacity(Integer.parseInt(para));
                    // courseList.update(course, "Capacity",
                    // Integer.parseInt(para), Integer.class);
                    out.println(SuccessType.Update_success);
                    break;
                }
                case "-t": {
                    course.setTeachers(splitTeachers(para));
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

    private static String[] splitTeachers(String para)
            throws IllegalArgumentException {
        if ("[]".equals(para)) {
            return new String[] {};
        }
        if (!para.matches("\\[[a-zA-Z]+(,[a-zA-z]+)*\\]")) {
            throw new IllegalArgumentException();
        }
        return para.substring(1, para.length() - 1).split(",");
    }
}