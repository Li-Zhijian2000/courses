
public class MasterStudent extends Student {
    protected String major;
    protected String tutor;

    public MasterStudent(String name, Sex sex, String birthday, String code, String major, String tutor) {
        super(name, sex, birthday, code);
        this.major = major;
        this.tutor = tutor;
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder("\n" + this.major);
        stringBuilder.append("\n" + this.tutor);
        return super.toString() + stringBuilder.toString();
    }
}