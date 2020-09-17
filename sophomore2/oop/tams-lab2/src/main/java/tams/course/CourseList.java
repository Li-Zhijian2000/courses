package tams.course;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.List;
import java.util.Map;

/**
 * CourseList
 */
public class CourseList {

    private Map<String, Course> courses;

    public CourseList() {
        courses = new Hashtable<>();
    }

    public int size() {
        return courses.size();
    }

    public Course getCourseById(String cid) {
        return courses.get(cid.toUpperCase());
    }

    public Course[] getCourseByKeyword(String keyword) {
        List<Course> ret = new ArrayList<>();
        for (Course course : courses.values()) {
            if (course.getTitle().contains(keyword)) {
                ret.add(course);
            }
        }
        return ret.toArray(new Course[0]);
    }

    public Course add(Course course) {
        Course res = getCourseById(course.getCID());
        if (res == null) {
            courses.put(course.getCID(), course);
            return null;
        }
        return res;
    }

    public <T> void update(Course course, String field, T arg, Class<T> type) throws CourseInfoException {
        try {
            Method setter = Course.class.getMethod("set" + field, type);
            setter.invoke(course, arg);
        } catch (NoSuchMethodException e) {
            System.out.println("No such method");
        } catch (IllegalAccessException e) {
        } catch (InvocationTargetException e) {
            throw (CourseInfoException) e.getCause();
        }
    }
}