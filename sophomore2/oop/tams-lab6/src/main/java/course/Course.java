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
    private ClassTime classTime;

    private List<String> students = new ArrayList<>();
    private PersonList personList;

    public static class ClassTime {
        int fromWeek, toWeek, n, m;

        public ClassTime(int fromWeek, int toWeek, int n, int m) {
            this.fromWeek = fromWeek;
            this.toWeek = toWeek;
            this.n = n;
            this.m = m;
        }

        @Override
        public String toString() {
            return String.format("[%d-%d]%d,%d", fromWeek, toWeek, n, m);
        }

        boolean check() {
            return fromWeek <= toWeek && fromWeek > 0 && fromWeek <= 18 && toWeek > 0 && toWeek <= 18 && n >= 1
                    && n <= 7 && m >= 1 && m <= 10;
        }

        public boolean conflict(ClassTime classTime) {
            return this.n == classTime.n && this.m == classTime.m
                    && rangeOverlap(this.n, this.m, classTime.n, classTime.m);
        }

        private static boolean rangeOverlap(int n1, int m1, int n2, int m2) {
            if (n1 > n2)
                return rangeOverlap(n2, m2, n1, m1);

            return n2 <= m1;
        }
    }

    public Course(final String cid, final String title, List<String> teachers, int capacity, ClassTime classTime,
            PersonList personList) {
        this.cid = cid;
        this.title = title;
        this.teachers = teachers;
        this.capacity = capacity;
        this.classTime = classTime;
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

    public ClassTime getClassTime() {
        return this.classTime;
    }

    @Override
    public int compareTo(final Course o) {
        return cid.compareTo(o.cid);
    }

    @Override
    public String toString() {
        List<String> teachersName = new ArrayList<>();
        for (String tid : this.teachers) {
            Teacher teacher = (Teacher) personList.getPersonByCode(tid);
            if (teacher == null)
                teachersName.add(tid);
            else
                teachersName.add(teacher.getName());
        }
        return String.format("CID:%s,Name:%s,Teachers:%s,Capacity:%d/%d,Time:%s", this.cid, this.title,
                Arrays.toString(teachersName.toArray()).replace(" ", ""), this.students.size(), this.capacity,
                this.classTime);
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

    public static boolean checkClassTime(ClassTime classTime) {
        return classTime.check();
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