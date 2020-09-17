package person;

import java.util.Hashtable;
import java.util.Map;

/**
 * PersonList
 */
public final class PersonList {

    private Map<String, Person> idNumberKeyPersons = new Hashtable<>();
    private Map<String, Person> codeKeyPersons = new Hashtable<>();

    private static PersonList personList = new PersonList();

    private PersonList() {
    }

    public static PersonList getInstance() {
        return personList;
    }

    public Person add(Person person) {
        String idNumber = person.idNum.toString();
        Person res = idNumberKeyPersons.get(idNumber);
        if (res == null) {
            idNumberKeyPersons.put(idNumber, person);
            if (person instanceof Teacher) {
                Teacher teacher = (Teacher) person;
                codeKeyPersons.put(teacher.getTid(), person);
            }
            if (person instanceof Student) {
                Student student = (Student) person;
                codeKeyPersons.put(student.getSid(), person);
            }
            return null;
        }
        return res;
    }

    public void remove(Person person) {
        idNumberKeyPersons.remove(person.idNum.toString());
        if (person instanceof Teacher) {
            Teacher teacher = (Teacher) person;
            codeKeyPersons.remove(teacher.getTid());
        }
        if (person instanceof Student) {
            Student student = (Student) person;
            codeKeyPersons.remove(student.getSid());
        }
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder();
        idNumberKeyPersons.values().stream().sorted().forEach(x -> stringBuilder.append(x).append("\n"));
        return stringBuilder.toString();
    }

    public Person getPersonByIdNumber(String idNumber) {
        return idNumberKeyPersons.get(idNumber);
    }

    public Person getPersonByCode(String Code) {
        return codeKeyPersons.get(Code);
    }

    public boolean containIdNumber(String idNumber) {
        return idNumberKeyPersons.containsKey(idNumber);
    }

    public boolean containCode(String code) {
        return codeKeyPersons.containsKey(code);
    }
}