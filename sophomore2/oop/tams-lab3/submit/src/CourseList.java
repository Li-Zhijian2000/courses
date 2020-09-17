
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

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder();
        courses.values().stream().sorted()
                .forEach(x -> stringBuilder.append(x).append("\n"));
        return stringBuilder.deleteCharAt(stringBuilder.length() - 1)
                .toString();
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
            if (course.getTitle().contains(keyword.toUpperCase())) {
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
}