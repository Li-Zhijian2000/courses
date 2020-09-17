package tams.course;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Course
 */
public class Course implements Comparable<Course> {

    private String CID;

    private String title;

    private String[] teachers;

    private int capacity;

    /**
     * 初始化{@code Course}类
     * 
     * @param CID      课程编号
     * @param title    课程名称
     * @param teachers 上课教师
     * @param capacity 最大容量
     * @throws CourseInfoException 当出现非法数据（课程名中含有除英文字母和数字以外的字符，
     *                             教师名称中含有英⽂字⺟以外的字符，课程容量为负数）时
     */
    public void init(final String CID, final String title,
            final String[] teachers, final int capacity)
            throws CourseInfoException {
        setCID(CID);
        setTitle(title);
        setteachers(teachers);
        setCapacity(capacity);
    }

    /**
     * 以以下格式输出{@code Course}类
     * 
     * <pre>
     * {@code CID:BH20200307,Name:OOP,Teachers:[S,L,P,G],Capacity:200}
     * </pre>
     * 
     * 其中CID全大写
     */
    @Override
    public String toString() {
        return String.format("CID:%s,Name:%s,teacherss:%s,Capacity:%d", CID,
                title, Arrays.toString(teachers).replaceAll(" ", ""), capacity);
    }

    @Override
    public int compareTo(final Course o) {
        return CID.compareTo(o.CID);
    }

    public String getCID() {
        return this.CID;
    }

    /**
     * 
     * @return 返回大写形式的课程名称
     */
    public String getTitle() {
        return this.title.toUpperCase();
    }

    public void setCID(final String CID) {
        this.CID = CID.toUpperCase();
    }

    public void setTitle(final String title) throws CourseInfoException {
        if (title.matches("[a-zA-Z0-9]+"))
            throw new CourseInfoException();
        this.title = title;
    }

    public void setteachers(final String[] teachers)
            throws CourseInfoException {
        for (final String teacher : teachers) {
            if (!teacher.matches("[a-zA-Z]+"))
                throw new CourseInfoException();
        }
        this.teachers = teachers;
    }

    public void setCapacity(final int capacity) throws CourseInfoException {
        if (capacity < 0) {
            throw new CourseInfoException();
        }
        this.capacity = capacity;
    }
}