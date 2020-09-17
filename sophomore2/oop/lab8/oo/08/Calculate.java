public class Calculate {

    private static class NumberRangeException extends RuntimeException {

        private static final long serialVersionUID = 1L;

        public NumberRangeException(String message) {
            super(message);
        }
    }

    public static int add(int a, int b) {

        if (Math.abs(a) > 10 || Math.abs(b) > 10)
            throw new NumberRangeException("整数绝对值需不大于10");

        return a + b;
    }

    public static int minus(int a, int b) {

        if (Math.abs(a) > 10 || Math.abs(b) > 10)
            throw new NumberRangeException("整数绝对值需不大于10");

        return a - b;
    }
}