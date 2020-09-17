package tams;

import java.io.FileInputStream;
import java.util.Scanner;

import org.junit.Test;

import tams.course.CourseList;

/**
 * ShellTest
 */
public class ShellTest {

    @Test
    public void test() {
        try {
            FileInputStream fileInputStream = new FileInputStream(
                    "/home/zhijian/fourth/oop/tams-lab2/src/test/java/tams/input.txt");
            System.setIn(fileInputStream);
        } catch (Exception e) {
            assert false;
        }

        Shell shell = new CourseTest();
        CourseTest.courseList = new CourseList();
        CourseTest.out = System.out;

        Scanner scanner = new Scanner(System.in);

        while (scanner.hasNextLine()) {
            String[] args = scanner.nextLine().split("\\s+");
            shell.run(args);
        }
        scanner.close();
    }
}