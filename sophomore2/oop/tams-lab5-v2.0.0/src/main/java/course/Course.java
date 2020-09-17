package course;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import person.PersonList;
import person.Teacher;
import utils.Utils.interObject;

/**
 * Course
 */
public final class Course implements Comparable<Course>, interObject {

    private String cid;
    private String title;
    private List<String> teachers;
    private int capacity;

    private List<String> students = new ArrayList<>();
    private PersonList personList;

    public Course(final String cid, final String title, List<String> teachers, int capacity, PersonList personList) {
        this.cid = cid;
        this.title = title;
        this.teachers = teachers;
        this.capacity = capacity;
        this.personList = personList;
    }

    public boolean full() {
        return students.size() == capacity;
    }

    public String getCid() {
        return this.cid;
    }

    public String getTitle() {
        return this.title;
    }

    public List<String> getTeachers() {
        return this.teachers;
    }

    public void addStudent(String sid) {
        students.add(sid);
    }

    public void dropStudent(String sid) {
        students.remove(sid);
    }

    public List<String> getStudents() {
        return this.students;
    }

    @Override
    public int compareTo(final Course o) {
        return cid.compareTo(o.cid);
    }

    @Override
    public String toString() {
        List<String> teachersName = new ArrayList<>();
        Collections.sort(this.teachers);
        for (String tid : this.teachers) {
            Teacher teacher = (Teacher) personList.getPersonByCode(tid);
            if (teacher == null)
                teachersName.add(tid);
            else
                teachersName.add(teacher.getName());
        }
        return String.format("CID:%s,Name:%s,Teachers:%s,Capacity:%d/%d", this.cid, this.title,
                Arrays.toString(teachersName.toArray()).replace(" ", ""), this.students.size(), this.capacity);
    }

    @Override
    public String interToString() {
        return this.toString();
    }

    public static boolean checkCid(String cid) {
        return cid.matches("[bB][hH]\\d{8}");
    }

    public static boolean checkTitle(String title) {
        return title.matches("[a-zA-Z0-9]+");
    }

    public static boolean checkTeachers(List<String> teachers) {
        Set<String> unique = new HashSet<>(teachers);
        if (unique.size() != teachers.size())
            return false;
        for (String teacher : teachers) {
            if (!Teacher.checkTid(teacher))
                return false;
        }
        return true;
    }

    public static boolean checkCapacity(int capacity) {
        return capacity >= 0;
    }

    public void updateTitle(String title) {
        this.title = title;
    }

    public void updateCapacity(int capacity) {
        this.capacity = capacity;
    }

    public void updateTeachers(List<String> teachers) {
        Collections.sort(teachers);
        this.teachers = teachers;
    }
}