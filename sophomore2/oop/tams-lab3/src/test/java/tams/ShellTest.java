package tams;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.util.Scanner;

import org.junit.Test;

import tams.course.CourseList;

/**
 * Unit test for simple App.
 */
public class ShellTest {
    /**
     * Rigorous Test :-)
     */
    @Test
    public void test() {
        try {
            FileInputStream fileInputStream = new FileInputStream(
                    "/home/zhijian/fourth/oop/tams-lab3/input.txt");

            PrintStream printStream = new PrintStream(new FileOutputStream(
                    "/home/zhijian/fourth/oop/tams-lab3/output.txt"));
            System.setIn(fileInputStream);
            System.setOut(printStream);
        } catch (Exception e) {
            assert false;
        }

        Scanner scanner = new Scanner(System.in);

        Shell shell = new tams.Test();
        tams.Test.scanner = scanner;
        tams.Test.courseList = new CourseList();
        tams.Test.out = System.out;

        while (scanner.hasNextLine()) {
            String[] args = scanner.nextLine().split("\\s+");
            shell.run(args);
        }
        scanner.close();
    }
}
