import java.io.PrintStream;
import java.util.Scanner;

import course.CourseList;
import person.PersonList;
import person.Student;
import person.Teacher;
import utils.ExceptionSystem.TamsInterrupt;

/**
 * PersonTest
 */
public class Test {

    public Scanner scanner = new Scanner(System.in);

    public PrintStream out = System.out;

    public CourseList courseList = CourseList.getInstance();

    public PersonList personList = PersonList.getInstance();

    public Shell currentShell;
    public Shell userShell = new Shell();
    public Shell rootShell = new Shell();
    public StudentShell studentShell = new StudentShell();
    public TeacherShell teacherShell = new TeacherShell();

    public boolean exit = false;

    public static void main(String[] args) {
        Test program = new Test();

        program.init();
        program.run();

        program.scanner.close();
    }

    public void init() {

        userShell.register(
            new String[] { "SUDO", "login", "QUIT" }, 
            out, scanner, courseList, personList);

        rootShell.register(
            new String[] { "np", "nc", "udc", "clist", "back", "QUIT" }, 
            out, scanner, courseList, personList);

        teacherShell.register(
            new String[] { "gc", "chgpw", "myinfo", "myc", "clist", "back", "QUIT" }, 
            out, scanner, courseList, personList);

        studentShell.register(
                new String[] { "gc", "chgpw", "myinfo", "getc", "dropc", "myc", "dropout", "back", "QUIT" }, 
                out, scanner, courseList, personList);
    }

    public void run() {
        currentShell = userShell;
        while (!exit && scanner.hasNextLine()) {
            try {
                String nameAndArgs = scanner.nextLine();
                if (nameAndArgs.isEmpty()) continue;
                currentShell.parse(nameAndArgs);
            } catch (TamsInterrupt e) {
                switch (e.getType()) {
                    case quit:
                        this.exit = true;
                        break;
                    case switchToRoot:
                        this.currentShell = this.rootShell;
                        break;
                    case switchToUser:
                        this.currentShell = this.userShell;
                        break;
                    case switchToStudent:
                        this.currentShell = this.studentShell;
                        this.studentShell.set((Student) e.getObj());
                        break;
                    case switchToTeacher:
                        this.currentShell = this.teacherShell;
                        this.teacherShell.set((Teacher) e.getObj());
                        break;
                    default:
                }
            }

        }
    }
}