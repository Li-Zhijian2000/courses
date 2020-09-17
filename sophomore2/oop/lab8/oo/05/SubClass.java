
//SubClass.java
import java.io.FileInputStream;
import java.io.IOException;

public class SubClass extends SuperClass {
    public void start() throws Exception {
        throw new Exception("Unable to open file");
    }

    public void open(String fileName) throws IOException {
        FileInputStream fis = new FileInputStream(fileName);
    }
}
