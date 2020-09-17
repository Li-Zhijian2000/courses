package person;

import course.CourseList;

/**
 * Person
 */
public class Person {

    protected String name;
    protected IDNum idNum;
    protected String password;
    protected CourseList courseList;

    public Person(String name, String idNumber, String password, CourseList courseList) {
        this.name = name;
        this.idNum = new IDNum(idNumber);
        this.password = password;
        this.courseList = courseList;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("Name:" + this.name);
        sb.append("\nIDNum:" + this.idNum);
        sb.append("\nSex:" + this.idNum.getSex());
        sb.append("\nBirthday:" + this.idNum.getBirthday());
        sb.append("\nPassword:" + this.password);
        return sb.toString();
    }

    public static boolean checkName(String name) {
        return name.matches("[a-zA-Z]+");
    }

    public static boolean checkIdNumber(String idNumber) {
        return IDNum.checkIDNum(idNumber);
    }

    public static boolean checkPassword(String password) {
        return password.matches(// 33 - 126
                "^(?![A-Z]*$)(?![a-z]*$)(?![0-9]*$)(?![^a-zA-Z0-9]*$)[\\x21-\\x7e]{6,18}$");
    }

    public String getName() {
        return this.name;
    }

    public String getPassword() {
        return this.password;
    }

    public void updatePassword(String password) {
        this.password = password;
    }

    // 以下代码为测试接口
    // public static Person newPerson(String nameAndIdNumberAndPassword) {
    // String[] s = nameAndIdNumberAndPassword.split("\\s+");
    // return newPerson(s[0], s[1], s[2]);
    // }

    // public static Person newPerson(String name, String idNumber, String password)
    // {
    // if (checkName(name) && checkIdNumber(idNumber) && checkPassword(password)) {
    // return new Person(name, idNumber, password);
    // }
    // return null;
    // }
}