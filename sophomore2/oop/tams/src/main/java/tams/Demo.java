package tams;

import java.util.Scanner;

import tams.course.CourseInfoException;

/**
 * Demo
 */
public class Demo {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextLine()) {
            try {
                String in = scanner.nextLine();
                if (in.equals("[]")) {
                    System.out.println("Update success.");
                    continue;
                }
                if (!in.matches("\\[[^,]+(,[^,]+)*\\]"))
                    throw new IllegalArgumentException();

                String[] teachers = in.substring(1, in.length() - 1).split(",");

                for (String teacher : teachers) {
                    if (!teacher.matches("[a-zA-Z]+"))
                        throw new CourseInfoException();
                }
                System.out.println("Update success.");
            } catch (IllegalArgumentException e) {
                System.out.println("Input illegal.");
            } catch (CourseInfoException e) {
                System.out.println("Update fail.");
            }
        }
        scanner.close();
    }
}