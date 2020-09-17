package tams.course;

import java.util.Arrays;

/**
 * Course
 */
public class Course implements Comparable<Course> {

    private String CID;

    private String title;

    private String[] teachers;

    private int capacity;

    public void init(final String CID, final String title, final String[] teachers, final int capacity)
            throws CourseInfoException {
        setCID(CID);
        setTitle(title);
        setTeachers(teachers);
        setCapacity(capacity);
    }

    @Override
    public String toString() {
        return String.format("CID:%s,Name:%s,Teachers:%s,Capacity:%d", CID, title,
                Arrays.toString(teachers).replaceAll(" ", ""), capacity);
    }

    @Override
    public int compareTo(final Course o) {
        return CID.compareTo(o.CID);
    }

    public String getCID() {
        return this.CID;
    }

    public String getTitle() {
        return this.title.toUpperCase();
    }

    public void setCID(final String CID) {
        this.CID = CID.toUpperCase();
    }

    public void setTitle(final String title) throws CourseInfoException {
        if (!title.matches("[a-zA-Z0-9]+"))
            throw new CourseInfoException();
        this.title = title;
    }

    public void setTeachers(final String[] teachers) throws CourseInfoException {
        for (final String teacher : teachers) {
            if (!teacher.matches("[a-zA-Z]+"))
                throw new CourseInfoException();
        }
        this.teachers = teachers;
    }

    public void setCapacity(int capacity) throws CourseInfoException {
        if (capacity < 0) {
            throw new CourseInfoException();
        }
        this.capacity = capacity;
    }
}