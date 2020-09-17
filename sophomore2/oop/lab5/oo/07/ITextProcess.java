public interface ITextProcess {
    String process(String s);
}

class SnakeCaseProcessor implements ITextProcess {
    @Override
    public String process(String s) {
        return s.replaceAll(" ", "_");
    }
}

class Splitter implements ITextProcess {
    @Override
    public String process(String s) {
        return s.replaceAll(" ", "");
    }
}

class UpperCaseProcessor implements ITextProcess {
    @Override
    public String process(String s) {
        return s.toUpperCase();
    }
}