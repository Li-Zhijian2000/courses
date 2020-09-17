package utils;

public class ExceptionSystem {

    public static class TamsInterrupt extends RuntimeException {

        private static final long serialVersionUID = 1L;

        InterruptType type;
        Object obj;

        public TamsInterrupt(InterruptType type) {
            this.type = type;
        }

        public TamsInterrupt(InterruptType type, Object obj) {
            this.type = type;
            this.obj = obj;
        }

        public InterruptType getType() {
            return this.type;
        }

        public Object getObj() {
            return this.obj;
        }
    }

    public static enum InterruptType {
        quit, switchToRoot, switchToUser, switchToTeacher, switchToStudent;
    }

    public static class TamsException extends RuntimeException {

        private static final long serialVersionUID = 1L;

        ExceptionType type;

        public TamsException(ExceptionType type) {
            this.type = type;
        }

        public ExceptionType getType() {
            return this.type;
        }
    }

    public static enum ExceptionType {
        input_illegal,
        // login
        login_success, login_failed,
        // np
        id_illegal, id_exists, name_illegal,
        // np-teacher
        tid_illegal, tid_exists, add_teacher_success,
        // np-student
        sid_illegal, sid_exists, add_student_success,
        // nc
        course_exists, add_success, course_add_illegal,
        // udc
        course_does_not_exist, update_success, update_fail,
        // clist
        record_does_not_exist,
        // chgpw
        password_illegal, password_diffrent, password_changed,
        // getc
        course_has_been_selected, course_full, course_chosen_success, course_time_conflict,
        // dropc
        course_has_not_been_selected, drop_course_successful,
        // dropout
        dropout_successfully, password_must_be_same;

        @Override
        public String toString() {
            switch (this) {
                // login
                case login_success:
                    return "Login success.";
                case login_failed:
                    return "Login Error. Your ID or password maybe wrong.";

                // np
                case id_illegal:
                    return "ID illegal.";
                case id_exists:
                    return "ID exists.";
                case name_illegal:
                    return "Name illegal.";
                case tid_illegal:
                    return "TID illegal.";
                case tid_exists:
                    return "TID exists.";
                case add_teacher_success:
                    return "Add teacher success.";
                case sid_illegal:
                    return "SID illegal.";
                case sid_exists:
                    return "SID exists.";
                case add_student_success:
                    return "Add student success.";

                // nc
                case course_exists:
                    return "Course exists.";
                case add_success:
                    return "Add success.";
                case course_add_illegal:
                    return "Course add illegal.";

                // udc
                case course_does_not_exist:
                    return "Course does not exist.";
                case update_success:
                    return "Update success.";
                case update_fail:
                    return "Update fail.";

                // clist
                case record_does_not_exist:
                    return "Record does not exist.";
                // chgpw
                case password_illegal:
                    return "Password illegal.";
                case password_diffrent:
                    return "The password you entered must be the same as the former one.";
                case password_changed:
                    return "Password changed successfully.";

                // getc
                case course_has_been_selected:
                    return "The course has been selected.";
                case course_full:
                    return "The course is full.";
                case course_chosen_success:
                    return "Course chosen success.";
                case course_time_conflict:
                    return "Course time conflict.";

                // dropc
                case course_has_not_been_selected:
                    return "The course has not been selected.";
                case drop_course_successful:
                    return "Drop out successful.";

                // dropout
                case dropout_successfully:
                    return "Congratulations, drop out successfully.";

                case password_must_be_same:
                    return "The password you entered must be the same as the former one.";
                case input_illegal:
                default:
                    return "Input illegal.";
            }
        }
    }

}