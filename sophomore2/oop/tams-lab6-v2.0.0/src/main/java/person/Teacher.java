package person;

import java.util.List;

import course.Course;
import course.CourseList;

public class Teacher extends Person implements Comparable<Teacher> {

    protected String tid;

    public Teacher(String name, String idNumber, String tid, CourseList courseList) {
        super(name, idNumber, "a12345", courseList);
        this.tid = tid;
    }

    public String getTid() {
        return this.tid;
    }

    public List<Course> getCourses() {
        return this.courseList.getCourseByTid(this.tid);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("Name:" + this.name);
        sb.append("\nIDNum:" + this.idNum);
        sb.append("\nTID:" + this.tid);
        sb.append("\nSex:" + this.idNum.getSex());
        sb.append("\nBirthday:" + this.idNum.getBirthday());
        return sb.toString();
    }

    @Override
    public int compareTo(Teacher o) {
        return tid.compareTo(o.tid);
    }

    public static boolean checkTid(String tid) {
        return tid.matches("\\d{5}");
    }
}