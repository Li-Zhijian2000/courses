
/**
 * Shell
 */
enum FailType {
    Input_illegal, ID_illegal, Course_does_not_exist, Update_fail, Course_exists, Course_add_illegal;

    @Override
    public String toString() {
        return name().replace('_', ' ') + ".";
    }
}

enum SuccessType {
    Update_success, Add_success;

    @Override
    public String toString() {
        return name().replace('_', ' ') + ".";
    }
}

public abstract class Shell {

    protected static String getArg(String[] args, int i) throws IllegalArgumentException {
        if (args.length <= i) {
            throw new IllegalArgumentException();
        }
        return args[i];
    }

    protected abstract void run(String[] args);
}