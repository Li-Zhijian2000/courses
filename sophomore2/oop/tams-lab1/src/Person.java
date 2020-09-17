import java.text.*;
import java.util.*;

/**
 * Person
 */
public class Person {

    public void init(String name, String ID) throws IDFormatException {
        this.name = name;
        this.ID = new IDNum();

        this.ID.init(ID);
        parseID();
    }

    public static Person newPerson(String name, String ID) {
        Person person = new Person();
        try {
            person.init(name, ID);
        } 
        catch (IDFormatException e) {
            return null;
        }
        return person;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Name:" + name).append( System.getProperty("line.separator"));
        sb.append("IDNum:" + ID.toString()).append( System.getProperty("line.separator"));
        sb.append("Sex:" + sex).append( System.getProperty("line.separator"));
        sb.append("Birthday:" + birthday);
        return sb.toString();
    }

    private void parseID() {
        try {
            SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMdd");
            Date date = dateFormat.parse(ID.toString().substring(Constants.BIRTHDAY_BEGIN_INDEX, Constants.BIRTHDAY_END_INDEX));
            dateFormat.applyPattern("yyyy/MM/dd");
            this.birthday = dateFormat.format(date);
            
            char ch = ID.toString().charAt(Constants.SEX_INDEX);
            this.sex = (Character.getNumericValue(ch) % 2 == 1) ? 'M' : 'F';
        } 
        catch (ParseException e) { }
    }

    private String name;

    private IDNum ID;

    private String birthday;

    private char sex;

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

    public char getSex() {
        return this.sex;
    }

    public void setSex(char sex) {
        this.sex = sex;
    }
}