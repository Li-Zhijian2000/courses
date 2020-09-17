import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

/**
 * Copy
 */
public class Copy {

    public static void copyFile(String sourceFile, String targetFile) throws IOException {
        FileInputStream in = new FileInputStream(sourceFile);
        FileOutputStream out = new FileOutputStream(targetFile);

        byte[] bytes = in.readAllBytes();
        out.write(bytes);
        out.flush();
    }

    public static void main(String[] args) {
        try {
            copyFile("input", "output");
        } catch (IOException e) {
            System.out.println("can not open file");
        }
    }
}