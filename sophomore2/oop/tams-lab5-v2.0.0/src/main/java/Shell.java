import static utils.Utils.shift;

import java.io.PrintStream;
import java.util.Arrays;
import java.util.Hashtable;
import java.util.LinkedList;
import java.util.Map;
import java.util.Optional;
import java.util.Scanner;

import course.CourseList;
import person.PersonList;
import person.Student;
import person.Teacher;
import utils.ExceptionSystem.ExceptionType;

/**
 * Shell
 */
class Shell {
    protected PrintStream out;
    protected Map<String, Action> commands = new Hashtable<>();

    public void register(String[] cmds, PrintStream out, Scanner scanner, CourseList courseList,
            PersonList personList) {
        try {
            this.out = out;
            for (String cmd : cmds) {
                String actionName = cmd.toLowerCase();
                actionName = Character.toUpperCase(actionName.charAt(0)) + actionName.substring(1) + "Action";
                Class<?> clazz = Class.forName(actionName);

                Action action = (Action) clazz.getDeclaredConstructor().newInstance();
                action.init(this, out, scanner, courseList, personList);
                this.command(cmd, action);
            }
        } catch (Exception e) {
            out.println(e);
        }
    }

    public Shell command(String command, Action action) {
        commands.put(command, action);
        return this;
    }

    public void parse(String line) {
        LinkedList<String> args = new LinkedList<>(Arrays.asList(line.split(" +")));
        String name = shift(args);
        Action action = commands.get(name);
        if (action == null) 
        out.println(ExceptionType.input_illegal);
    else    
        action.run(args);
    }
}

class TeacherShell extends Shell {
    private Teacher teacher;

    public void set(Teacher teacher) {
        this.teacher = teacher;
    }

    public Teacher get() {
        return this.teacher;
    }
}

class StudentShell extends Shell {
    private Student student;

    public void set(Student student) {
        this.student = student;
    }

    public Student get() {
        return this.student;
    }
}
