
public class Test {
    public static void process(ITextProcess p, String s) {
        s = p.process(s);
        System.out.println(s);
    }

    public static void main(String[] args) {
        process(new SnakeCaseProcessor(), "i am a student");
        process(new Splitter(), "Alpha Go");
        process(new UpperCaseProcessor(), "upper case");
    }
}