package utils;

import java.util.LinkedList;

import utils.ExceptionSystem.ExceptionType;
import utils.ExceptionSystem.TamsException;

public class Utils {

    public static <T> T shift(LinkedList<T> args) {
        if (args.size() == 0)
            throw new TamsException(ExceptionType.input_illegal);
        return args.removeFirst();
    }

    public interface interObject {
        String interToString();
    }
}