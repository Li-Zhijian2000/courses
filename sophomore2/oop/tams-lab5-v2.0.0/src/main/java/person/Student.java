package person;

import java.util.List;

import course.Course;
import course.CourseList;
import utils.Utils.interObject;

/**
 * Student
 */
public class Student extends Person implements Comparable<Student>, interObject {

    protected String sid;

    public Student(String name, String idNumber, String sid, CourseList courseList) {
        super(name, idNumber, "a12345", courseList);
        this.sid = sid;
    }

    public String getSid() {
        return this.sid;
    }

    public List<Course> getCourses() {
        return this.courseList.getCourseBySid(this.sid);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("Name:" + this.name);
        sb.append("\nIDNum:" + this.idNum);
        sb.append("\nSID:" + this.sid);
        sb.append("\nSex:" + this.idNum.getSex());
        sb.append("\nBirthday:" + this.idNum.getBirthday());
        return sb.toString();
    }

    @Override
    public String interToString() {
        return String.format("%s,%s", this.sid, this.name);
    }

    @Override
    public int compareTo(Student o) {
        return sid.compareTo(o.sid);
    }

    public static boolean checkSid(String sid) {
        return sid.matches("\\d{8}");
    }
}