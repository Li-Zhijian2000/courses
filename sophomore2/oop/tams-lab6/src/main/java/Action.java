import static utils.Utils.shift;

import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Optional;
import java.util.Scanner;

import course.Course;
import course.Course.ClassTime;
import course.CourseList;
import person.Person;
import person.PersonList;
import person.Student;
import person.Teacher;
import utils.ExceptionSystem.ExceptionType;
import utils.ExceptionSystem.InterruptType;
import utils.ExceptionSystem.TamsException;
import utils.ExceptionSystem.TamsInterrupt;
import utils.Utils.interObject;

abstract class Action {
    protected Shell shell;

    protected Scanner scanner;
    protected PrintStream out;
    protected CourseList courseList;
    protected PersonList personList;

    public void init(Shell shell, PrintStream out, Scanner scanner, CourseList courseList, PersonList personList) {
        this.shell = shell;
        this.scanner = scanner;
        this.out = out;
        this.courseList = courseList;
        this.personList = personList;
    }

    public abstract void run(LinkedList<String> args);

    public void interShell(List<? extends interObject> res, int n, int m, ExceptionType type) {
        boolean flag = true;
        while (flag) {
            final int fromIndex = (n - 1) * m, toIndex = Math.min(n * m, res.size());
            if (fromIndex >= toIndex || fromIndex < 0)
                throw new TamsException(type);

            out.println("Page:" + n);
            for (int i = fromIndex; i < toIndex; i++) {
                out.format("%d.%s\n", i - fromIndex + 1, res.get(i).interToString());
            }
            out.println("n-next page, l-last page, q-quit");
            if (scanner.hasNextLine())
                switch (this.scanner.nextLine()) {
                    case "n":
                        n++;
                        break;
                    case "l":
                        n--;
                        break;
                    case "q":
                        flag = false;
                        break;
                    default:
                        out.println(ExceptionType.input_illegal);
                }
            else
                flag = false;
        }
    }

    public static List<String> splitTeachers(String teachers) {
        if ("[]".equals(teachers)) {
            return new ArrayList<>();
        }
        if (!teachers.matches("\\[[^,\\[\\]]+(,[^,\\[\\]]+)*\\]")) {
            throw new TamsException(ExceptionType.input_illegal);
        }
        return Arrays.asList(teachers.substring(1, teachers.length() - 1).split(","));
    }

    public static ClassTime splitClassTime(String arg) {
        if (!arg.matches("\\[[^\\[-\\]]+-[^\\[-\\]]+\\][^,]+,[^,]+"))
            throw new TamsException(ExceptionType.input_illegal);

        int i1 = arg.indexOf('['), i2 = arg.indexOf('-'), i3 = arg.indexOf(']'), i4 = arg.indexOf(',');

        int fromWeek = Integer.parseInt(arg.substring(i1 + 1, i2)),
                toWeek = Integer.parseInt(arg.substring(i2 + 1, i3)), n = Integer.parseInt(arg.substring(i3 + 1, i4)),
                m = Integer.parseInt(arg.substring(i4 + 1));

        return new ClassTime(fromWeek, toWeek, n, m);
    }
}

class CidAction extends Action {
    @Override
    public void run(LinkedList<String> args) {
        try {
            String idNumber = shift(args).replace('x', 'X');
            out.println(Person.checkIdNumber(idNumber) ? "true" : "false");
        } catch (TamsException e) {
            out.println(e.getType());
        }
    }
}

class NpAction extends Action {
    @Override
    public void run(LinkedList<String> args) {
        try {
            final String op = shift(args), name = shift(args), idNumber = shift(args).replace('x', 'X'),
                    code = shift(args);

            boolean isStudent;
            if ("-t".equals(op))
                isStudent = false;
            else if ("-s".equals(op))
                isStudent = true;
            else
                throw new TamsException(ExceptionType.input_illegal);

            if (!Person.checkIdNumber(idNumber))
                throw new TamsException(ExceptionType.id_illegal);

            if (personList.containIdNumber(idNumber))
                throw new TamsException(ExceptionType.id_exists);

            if (!Person.checkName(name))
                throw new TamsException(ExceptionType.name_illegal);

            if (isStudent) {
                if (!Student.checkSid(code))
                    throw new TamsException(ExceptionType.sid_illegal);

                if (personList.containIdNumber(idNumber) || personList.containCode(code))
                    throw new TamsException(ExceptionType.sid_exists);

                personList.add(new Student(name, idNumber, code, courseList));
                throw new TamsException(ExceptionType.add_student_success);

            } else {
                if (!Teacher.checkTid(code))
                    throw new TamsException(ExceptionType.tid_illegal);
                if (personList.containIdNumber(idNumber) || personList.containCode(code))
                    throw new TamsException(ExceptionType.tid_exists);

                personList.add(new Teacher(name, idNumber, code, courseList));
                throw new TamsException(ExceptionType.add_teacher_success);
            }
        } catch (TamsException e) {
            out.println(e.getType());
        }
    }
}

class NcAction extends Action {
    @Override
    public void run(LinkedList<String> args) {
        try {
            if (args.size() != 4)
                throw new TamsException(ExceptionType.input_illegal);
            String cid = shift(args);

            Course res = courseList.getCourseById(cid);
            if (res != null)
                throw new TamsException(ExceptionType.course_exists);

            String title = shift(args);
            List<String> teachers = splitTeachers(shift(args));
            int capacity = Integer.parseInt(shift(args));
            ClassTime classTime = splitClassTime(shift(args));

            if (Course.checkCid(cid) && Course.checkTitle(title) && Course.checkCapacity(capacity)
                    && Course.checkTeachers(teachers) && Course.checkClassTime(classTime)) {
                Course course = new Course(cid, title, teachers, capacity, classTime, personList);
                courseList.add(course);
            } else {
                throw new TamsException(ExceptionType.course_add_illegal);
            }
        } catch (NumberFormatException e) {
            out.println(ExceptionType.input_illegal);
        } catch (TamsException e) {
            out.println(e.getType());
        }

    }
}

class UdcAction extends Action {
    @Override
    public void run(LinkedList<String> args) {
        try {
            String cid = shift(args), op = shift(args);
            Course course = courseList.getCourseById(cid);

            if (course == null)
                throw new TamsException(ExceptionType.course_does_not_exist);

            if ("-n".equals(op)) {
                String title = shift(args);
                if (Course.checkTitle(title)) {
                    course.updateTitle(title);
                    throw new TamsException(ExceptionType.update_success);
                }
                throw new TamsException(ExceptionType.update_fail);
            } else if ("-c".equals(op)) {
                int capacity = Integer.parseInt(shift(args));
                if (Course.checkCapacity(capacity)) {
                    course.updateCapacity(capacity);
                    throw new TamsException(ExceptionType.update_success);
                }
                throw new TamsException(ExceptionType.update_fail);
            } else if ("-t".equals(op)) {
                List<String> teachers = splitTeachers(shift(args));
                if (Course.checkTeachers(teachers)) {
                    course.updateTeachers(teachers);
                    throw new TamsException(ExceptionType.update_success);
                }
                throw new TamsException(ExceptionType.update_fail);
            } else {
                throw new TamsException(ExceptionType.input_illegal);
            }
        } catch (NumberFormatException e) {
            out.println(ExceptionType.input_illegal);
        } catch (TamsException e) {
            out.println(e.getType());
        }
    }
}

class ClistAction extends Action {
    @Override
    public void run(LinkedList<String> args) {
        try {
            if (args.size() != 3)
                throw new TamsException(ExceptionType.input_illegal);
            String cid = shift(args);
            Course course = courseList.getCourseById(cid);
            if (course == null)
                throw new TamsException(ExceptionType.course_does_not_exist);

            int n = Integer.parseInt(shift(args)), m = Integer.parseInt(shift(args));

            List<Student> students = new ArrayList<>();
            for (String sid : course.getStudents()) {
                students.add((Student) personList.getPersonByCode(sid));
            }

            Collections.sort(students);
            interShell(students, n, m, ExceptionType.record_does_not_exist);
        } catch (NumberFormatException e) {
            out.println(ExceptionType.input_illegal);
        } catch (TamsException e) {
            out.println(e.getType());
        }
    }
}

class LoginAction extends Action {
    @Override
    public void run(LinkedList<String> args) {
        try {
            String op = shift(args), idNumber = shift(args).replace('x', 'X'), password = shift(args);
            Person res = personList.getPersonByIdNumber(idNumber);

            if ("-t".equals(op)) {
                if (res != null && res instanceof Teacher && res.getPassword().equals(password)) {
                    out.println(ExceptionType.login_success);
                    throw new TamsInterrupt(InterruptType.switchToTeacher, res);
                }
                throw new TamsException(ExceptionType.login_failed);

            } else if ("-s".equals(op)) {
                if (res != null && res instanceof Student && res.getPassword().equals(password)) {
                    out.println(ExceptionType.login_success);
                    throw new TamsInterrupt(InterruptType.switchToStudent, res);
                }
                throw new TamsException(ExceptionType.login_failed);
            } else
                throw new TamsException(ExceptionType.input_illegal);

        } catch (TamsException e) {
            out.println(e.getType());
        }
    }
}

class GcAction extends Action {
    public void run(LinkedList<String> args) {
        try {
            String op = shift(args);
            if ("-id".equals(op)) {
                String id = shift(args);
                final Course res = courseList.getCourseById(id);
                Optional.ofNullable(res).ifPresentOrElse((x) -> out.println(x),
                        () -> out.println(ExceptionType.course_does_not_exist));
            } else if ("-key".equals(op)) {
                String keyword = shift(args);
                int n = Integer.parseInt(shift(args)), m = Integer.parseInt(shift(args));
                gcKey(keyword, n, m);
            } else if ("-all".equals(op)) {
                int n = Integer.parseInt(shift(args)), m = Integer.parseInt(shift(args));
                gcKey("", n, m);
            } else {
                throw new TamsException(ExceptionType.input_illegal);
            }
        } catch (NumberFormatException e) {
            out.println(ExceptionType.input_illegal);
        } catch (TamsException e) {
            out.println(e.getType());
        }
    }

    private void gcKey(String keyword, int n, int m) {
        final List<Course> res = courseList.getCourseByKeyword(keyword);
        Collections.sort(res);

        interShell(res, n, m, ExceptionType.course_does_not_exist);
    }
}

class ChgpwAction extends Action {
    @Override
    public void run(LinkedList<String> args) {
        try {
            String newPassword = shift(args), confirmPassword = shift(args);
            Person person;
            if (this.shell instanceof TeacherShell)
                person = ((TeacherShell) this.shell).get();
            else
                person = ((StudentShell) this.shell).get();

            if (!Person.checkPassword(newPassword))
                throw new TamsException(ExceptionType.password_illegal);
            if (!newPassword.equals(confirmPassword))
                throw new TamsException(ExceptionType.password_diffrent);

            person.updatePassword(newPassword);
            throw new TamsException(ExceptionType.password_changed);
        } catch (TamsException e) {
            out.println(e.getType());
        }
    }
}

class MyinfoAction extends Action {
    @Override
    public void run(LinkedList<String> args) {
        if (this.shell instanceof TeacherShell) {
            Teacher teacher = ((TeacherShell) this.shell).get();
            out.println(teacher);
        } else {
            Student student = ((StudentShell) this.shell).get();
            out.println(student);
        }
    }
}

class MycAction extends Action {
    @Override
    public void run(LinkedList<String> args) {
        try {
            if (args.size() != 2)
                throw new TamsException(ExceptionType.input_illegal);

            int n = Integer.parseInt(shift(args)), m = Integer.parseInt(shift(args));

            if (this.shell instanceof TeacherShell) {
                Teacher teacher = ((TeacherShell) this.shell).get();
                List<Course> res = teacher.getCourses();
                Collections.sort(res);
                interShell(res, n, m, ExceptionType.course_does_not_exist);
            }
            if (this.shell instanceof StudentShell) {
                Student student = ((StudentShell) this.shell).get();
                List<Course> res = student.getCourses();
                Collections.sort(res);
                interShell(res, n, m, ExceptionType.course_does_not_exist);
            }

        } catch (NumberFormatException e) {
            out.println(ExceptionType.input_illegal);
        } catch (TamsException e) {
            out.println(e.getType());
        }
    }
}

class GetcAction extends Action {
    @Override
    public void run(LinkedList<String> args) {
        try {
            String cid = shift(args);
            Course course = courseList.getCourseById(cid);
            if (course == null)
                throw new TamsException(ExceptionType.course_does_not_exist);

            Student student = ((StudentShell) this.shell).get();
            List<Course> res = student.getCourses();
            for (Course c : res) {
                if (c.equals(course))
                    throw new TamsException(ExceptionType.course_has_been_selected);
                if (c.getClassTime().conflict(course.getClassTime()))
                    throw new TamsException(ExceptionType.course_time_conflict);
            }
            if (course.full())
                throw new TamsException(ExceptionType.course_full);

            course.addStudent(student.getSid());
            out.println(ExceptionType.course_chosen_success);
        } catch (TamsException e) {
            out.println(e.getType());
        }
    }
}

class DropcAction extends Action {
    @Override
    public void run(LinkedList<String> args) {
        try {
            String cid = shift(args);
            Course course = courseList.getCourseById(cid);
            if (course == null)
                throw new TamsException(ExceptionType.course_does_not_exist);

            Student student = ((StudentShell) this.shell).get();
            List<Course> res = student.getCourses();
            for (Course c : res) {
                if (c.equals(course)) {
                    course.dropStudent(student.getSid());
                    throw new TamsException(ExceptionType.drop_out_successful);
                }
            }
            throw new TamsException(ExceptionType.course_has_not_been_selected);
        } catch (TamsException e) {
            out.println(e.getType());
        }
    }
}

class DropoutAction extends Action {
    @Override
    public void run(LinkedList<String> args) {
        try {
            String password = shift(args), passwordRepeat = shift(args);
            if (!password.equals(passwordRepeat))
                throw new TamsException(ExceptionType.password_must_be_same);

            Student student = ((StudentShell) this.shell).get();

            for (Course course : student.getCourses()) {
                course.dropStudent(student.getSid());
            }
            personList.remove(student);

        } catch (TamsException e) {
            out.println(e.getType());
        }
    }
}

class SudoAction extends Action {
    @Override
    public void run(LinkedList<String> args) {
        throw new TamsInterrupt(InterruptType.switchToRoot);
    }
}

class BackAction extends Action {
    @Override
    public void run(LinkedList<String> args) {
        throw new TamsInterrupt(InterruptType.switchToUser);
    }
}

class QuitAction extends Action {
    @Override
    public void run(LinkedList<String> args) {
        throw new TamsInterrupt(InterruptType.quit);
    }
}