import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * Person
 */
public class Person {

    private String name;

    private IDNum ID;

    private String birthday;

    private Sex sex;

    public enum Sex {
        F, M;
    }

    public void init(String name, String ID) throws IDFormatException {
        this.name = name;
        this.ID = new IDNum();

        this.ID.init(ID);
        parseID();
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Name:" + name).append("\n");
        sb.append("IDNum:" + ID.toString()).append("\n");
        sb.append("Sex:" + sex).append("\n");
        sb.append("Birthday:" + birthday);
        return sb.toString();
    }

    // 以下代码为测试接口
    public static Person newPerson(String nameAndID) {
        String[] s = IDAndName.split("\\s+");
        return newPerson(s[0], s[1]);
    }

    public static Person newPerson(String name, String ID) {
        Person person = new Person();
        try {
            person.init(name, ID);
        } catch (IDFormatException e) {
            return null;
        }
        return person;
    }

    public String getName() {
        return this.name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public IDNum getID() {
        return this.ID;
    }

    public void setID(IDNum ID) {
        this.ID = ID;
    }

    public String getBirthday() {
        return this.birthday;
    }

    public void setBirthday(String birthday) {
        this.birthday = birthday;
    }

    public Sex getSex() {
        return this.sex;
    }

    public void setSex(Sex sex) {
        this.sex = sex;
    }

    private void parseID() {
        try {
            SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMdd");
            Date date = dateFormat
                    .parse(ID.toString().substring(Constants.BIRTHDAY_BEGIN_INDEX, Constants.BIRTHDAY_END_INDEX));
            dateFormat.applyPattern("yyyy/MM/dd");
            this.birthday = dateFormat.format(date);

            char ch = ID.toString().charAt(Constants.SEX_INDEX);
            this.sex = (Character.getNumericValue(ch) % 2 == 1) ? Sex.M : Sex.F;
        } catch (ParseException e) {
        }
    }
}