package course;

import java.util.ArrayList;
import java.util.Hashtable;
import java.util.List;
import java.util.Map;

/**
 * CourseList
 */
public final class CourseList {

    private Map<String, Course> courses = new Hashtable<>();

    private static CourseList courseList = new CourseList();

    private CourseList() {
    }

    public static CourseList getInstance() {
        return courseList;
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder();
        courses.values().stream().sorted().forEach(x -> stringBuilder.append(x).append("\n"));
        return stringBuilder.toString();
    }

    public int size() {
        return courses.size();
    }

    public boolean containId(String cid) {
        return courses.containsKey(cid);
    }

    public Course getCourseById(String cid) {
        for (Course course : this.courses.values()) {
            if (course.getCid().toUpperCase().equals(cid.toUpperCase()))
                return course;
        }
        return null;
    }

    public List<Course> getCourseByKeyword(String keyword) {
        List<Course> ret = new ArrayList<>();
        for (Course course : this.courses.values()) {
            if (course.getTitle().toUpperCase().contains(keyword.toUpperCase())) {
                ret.add(course);
            }
        }
        return ret;
    }

    public List<Course> getCourseByTid(String tid) {
        List<Course> res = new ArrayList<>();
        for (Course course : this.courses.values()) {
            if (course.getTeachers().contains(tid))
                res.add(course);
        }
        return res;
    }

    public List<Course> getCourseBySid(String sid) {
        List<Course> res = new ArrayList<>();
        for (Course course : this.courses.values()) {
            if (course.getStudents().contains(sid)) {
                res.add(course);
            }
        }
        return res;
    }

    public void add(Course course) {
        courses.put(course.getCid(), course);
    }
}