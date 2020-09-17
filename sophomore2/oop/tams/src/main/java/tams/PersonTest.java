package tams;

/**
 * CourseTest
 */
public class PersonTest extends Shell {
    public static void main(String[] args) {
        try {
            switch (getArg(args, 0)) {
                case "cid":
                    cid(getArg(args, 1));
                    break;
                case "np":
                    np(getArg(args, 1), getArg(args, 2));
                    break;
            }
        } catch (IllegalArgumentException e) {
            System.out.println(FailType.Input_illegal);
        }
    }
}