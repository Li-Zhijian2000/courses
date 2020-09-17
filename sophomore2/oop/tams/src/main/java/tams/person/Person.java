package tams.person;

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

    private void parseID() {
        try {
            SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMdd");
            Date date = dateFormat.parse(
                    ID.toString().substring(Constants.BIRTHDAY_BEGIN_INDEX,
                            Constants.BIRTHDAY_END_INDEX));
            dateFormat.applyPattern("yyyy/MM/dd");
            this.birthday = dateFormat.format(date);

            char ch = ID.toString().charAt(Constants.SEX_INDEX);
            this.sex = (Character.getNumericValue(ch) % 2 == 1) ? Sex.M : Sex.F;
        } catch (ParseException e) {
        }
    }
}