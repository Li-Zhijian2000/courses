package person;

public class Person {
    private String name;

    private int age;

    private Sex sex;

    public enum Sex {
        FEMALE, MALE
    }

    public Person(String name, int age, Sex sex) throws IllegalArgumentException {
        this.name = name;
        this.sex = sex;
        setAge(age);
    }

    public void setAge(int age) throws IllegalArgumentException {
        if (age < 0 || age > 130) {
            throw new IllegalArgumentException();
        }

        this.age = age;
    }

    public int getage() {
        return this.age;
    }

    public void work() {
        System.out.println("work");
    }

    public void showAge() {
        System.out.println(this.age);
    }
}