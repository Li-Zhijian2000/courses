import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class Parser {

    public static void removeComments(String input, String output) throws IOException {
        FileReader fr = new FileReader(input);
        FileWriter fw = new FileWriter(output);
        BufferedReader in = new BufferedReader(fr);
        PrintWriter out = new PrintWriter(fw);
        
        String line;
        boolean flag = false;

        while ((line = in.readLine()) != null) {
            char[] buf = line.toCharArray();
            StringBuilder sb = new StringBuilder();
            
            for (int i = 0; i < buf.length; i++) {
                if (flag) {
                    while (i < buf.length - 1 && (buf[i] != '*' || buf[i + 1] != '/')) i++;

                    if (i == buf.length - 1) 
                        break;
                    flag = false;
                    i += 2;
                }

                if (i < buf.length - 1 && buf[i] == '/') {
                    i++;
                    if (buf[i] == '/') break;
                    else if (buf[i] == '*') {
                        flag = true;
                        continue;
                    }
                    else i--;
                }
                if (i < buf.length) sb.append(buf[i]);
            }
            sb.append('\n');
            System.out.print(sb.toString());
            out.write(sb.toString());
        }
        out.flush();
    }

    public static void main(String[] args) {
        try {
            removeComments("input.txt", "output.txt");
        } catch (IOException e) {
            System.out.println("can not open file");
        }
    }
}