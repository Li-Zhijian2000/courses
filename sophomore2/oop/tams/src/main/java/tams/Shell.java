package tams;

import java.util.Arrays;
import java.util.Optional;

import tams.course.Course;
import tams.course.CourseList;
import tams.course.CourseInfoException;
import tams.person.IDFormatException;
import tams.person.IDNum;
import tams.person.Person;

/**
 * Shell
 */
public class Shell {
    public enum FailType {
        Input_illegal, ID_illegal, Course_does_not_exist, Update_fail,
        Course_exists, Course_add_illegal;

        @Override
        public String toString() {
            return name().replace('_', ' ') + ".";
        }
    }

    public enum SuccessType {
        Update_success, Add_success;

        @Override
        public String toString() {
            return name().replace('_', ' ') + ".";
        }
    }

    protected static String getArg(String[] args, int i)
            throws IllegalArgumentException {
        if (args.length <= i) {
            throw new IllegalArgumentException();
        }
        return args[i];
    }

    protected static void cid(String ID) {
        System.out.println(IDNum.checkIDNum(ID) ? "true" : "false");
    }

    protected static void np(String name, String ID) {
        try {
            Person person = new Person();
            person.init(name, ID);
            System.out.println(person);
        } catch (IDFormatException e) {
            System.out.println(FailType.ID_illegal);
        }

    }

    protected static void gcId(String id, CourseList courseList) {
        final Course res = courseList.getCourseById(id);
        Optional.ofNullable(res).ifPresentOrElse((x) -> System.out.println(x),
                () -> System.out.println(FailType.Course_does_not_exist));
    }

    protected static void gcKey(String keyword, int n, int m,
            CourseList courseList) {
        getCourseByKeyword(keyword, courseList, n, m);
    }

    protected static void gcAll(int n, int m, CourseList courseList) {
        getCourseByKeyword("", courseList, n, m);
    }

    protected static void gc(String[] args, CourseList courseList)
            throws IllegalArgumentException {
        switch (getArg(args, 1)) {
            case "-id": {
                final String id = getArg(args, 2);
                gcId(id, courseList);
                break;
            }
            case "-key": {
                final String keyword = getArg(args, 2);
                int n = Integer.parseInt(getArg(args, 3)),
                        m = Integer.parseInt(getArg(args, 4));
                gcKey(keyword, n, m, courseList);
                break;
            }
            case "-all": {
                int n = Integer.parseInt(getArg(args, 2)),
                        m = Integer.parseInt(getArg(args, 3));
                gcAll(n, m, courseList);
                break;
            }
            default:
                throw new IllegalArgumentException();
        }
    }

    protected static void udc(String[] args, CourseList courseList)
            throws IllegalArgumentException {
        final String cid = getArg(args, 1), option = getArg(args, 2),
                para = getArg(args, 3);
        Course course = courseList.getCourseById(cid);
        if (course == null) {
            System.out.println(FailType.Course_does_not_exist);
            return;
        }
        try {
            switch (option) {
                case "-n": {
                    courseList.update(course, "Title", para, String.class);
                    System.out.println(SuccessType.Update_success);
                    break;
                }
                case "-c": {
                    courseList.update(course, "Capacity",
                            Integer.parseInt(para), Integer.class);
                    System.out.println(SuccessType.Update_success);
                    break;
                }
                case "-t": {
                    if (!para.equals("[]") && !para.matches("[[^,]+{,.}*]]")) {
                        throw new IllegalArgumentException();
                    }
                    courseList.update(course, "teachers", splitteachers(para),
                            String[].class);
                    System.out.println(SuccessType.Update_success);
                    break;
                }
                default:
                    throw new IllegalArgumentException();
            }
        } catch (CourseInfoException e) {
            System.out.println(FailType.Update_fail);
        }

    }

    protected static void nc(String[] args, CourseList courseList) {
        final String cid = args[1], title = args[2];
        final String[] teachers = splitteachers(args[3]);
        final int capacity = Integer.parseInt(args[4]);

        try {
            Course course = courseList.getCourseById(cid);
            if (course == null) {
                Course c = new Course();
                c.init(cid, title, teachers, capacity);
                courseList.add(c);
                System.out.println(SuccessType.Add_success);
            } else {
                System.out.println(FailType.Course_exists);
            }
        } catch (CourseInfoException e) {
            System.out.println(FailType.Course_add_illegal);
        }

    }

    private static void getCourseByKeyword(String keyword,
            CourseList courseList, int n, int m) {
        final Course[] res = courseList.getCourseByKeyword(keyword);
        Arrays.sort(res);

        boolean flag = true;
        while (flag) {
            final int fromIndex = (n - 1) * m,
                    toIndex = Math.min(n * m, res.length);
            if (fromIndex >= toIndex || fromIndex < 0) {
                System.out.println(FailType.Course_does_not_exist);
                flag = false;
            } else {
                System.out.println("Page:" + n);
                for (int i = fromIndex; i < toIndex; i++) {
                    System.out.format("%d.%s\n", i - fromIndex + 1, res[i]);
                }
                System.out.println("n-next page, l-last page, q-quit");
                if (Test.scanner.hasNextLine())
                    switch (Test.scanner.nextLine()) {
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
                            System.out.println(FailType.Input_illegal);
                    }
                else
                    flag = false;
            }
        }
    }

    private static String[] splitteachers(String str) {
        return str.substring(1, str.length() - 1).split(",");
    }
}