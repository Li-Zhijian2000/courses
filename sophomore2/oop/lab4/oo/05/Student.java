
public class Student extends Person {
    protected String code;

    public Student(String name, Sex sex, String birthday, String code) {
        super(name, sex, birthday);
        this.code = code;
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder("\n" + this.code);
        return super.toString() + stringBuilder.toString();
    }
}