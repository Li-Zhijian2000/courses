
enum Sex {
    MALE, FEMALE;
}

public class Person {

    protected String name;
    protected Sex sex;
    protected String birthday;

    public Person(String name, Sex sex, String birthday) {
        this.name = name;
        this.sex = sex;
        this.birthday = birthday;
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder(this.name);
        stringBuilder.append("\n" + this.sex).append("\n" + this.birthday);
        return stringBuilder.toString();
    }
}