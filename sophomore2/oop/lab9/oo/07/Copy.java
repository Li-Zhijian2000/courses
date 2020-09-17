import java.io.File;
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

    public static void copyDirectiory(String sourceDir, String targetDir) throws IOException {
        File source = new File(sourceDir), target = new File(targetDir);
        for (File subFile : source.listFiles()) {
            File targetFile = new File(target, subFile.getName());

            if (subFile.isFile()) {
                targetFile.createNewFile();
                copyFile(subFile.getPath(), targetFile.getPath());
            } else {
                targetFile.mkdir();
                copyDirectiory(subFile.getPath(), targetFile.getPath());
            }
        }
    }
    public static void main(String[] args) {
        try {
            copyDirectiory("input", "output");
        } catch (IOException e) {
            System.out.println("can not open file");
        }
    }
}