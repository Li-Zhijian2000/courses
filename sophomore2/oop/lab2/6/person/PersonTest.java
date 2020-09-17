package person;

import person.Person.Sex;

public class PersonTest {
    public static void main(String[] args) {
        try {
            Person zhangSan = new Person("zhang san", 25, Sex.MALE);
            zhangSan.setAge(50);
            System.out.println(zhangSan.getage());

            Person liSi = new Person("li si", 50, Sex.FEMALE);
            liSi.showAge();
            liSi.work();
        } catch (IllegalArgumentException e) {
            System.err.println("Wrong age");
        }
    }
}