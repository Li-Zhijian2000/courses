import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class Parser {

    public static void addLineNo(String inputpath,String outpath) throws IOException {
        FileReader fr = new FileReader(inputpath);
        FileWriter fw = new FileWriter(outpath);
        BufferedReader in = new BufferedReader(fr);
        PrintWriter out = new PrintWriter(fw);
        
        String line;
        int lineNo = 1;
        while ((line = in.readLine()) != null) {
            out.format("%d. %s\n", lineNo++, line);
        }
        out.flush();
    }

    public static void main(String[] args) {
        try {
            addLineNo("input.txt", "output.txt");
        } catch (IOException e) {
            System.out.println("can not open file");
        }
    }
}