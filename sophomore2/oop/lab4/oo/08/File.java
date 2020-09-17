import java.util.*;

// 使用继承
abstract class File {
    protected String name;
    protected Date createDate;
    protected int size;
    protected List<Byte> content;
    protected Folder folder;
    protected String path;

    protected File(String name) {
        this.name = name;
        this.createDate = new Date();
        this.size = 0;
        this.content = new ArrayList<>();
        this.folder = null;
        this.path = "C:/";
    }

    protected void write(ArrayList<Byte> content) {
        this.content.addAll(content);
        this.size += content.size();
    }

    public abstract void open();
}

class Folder extends File {
    protected List<File> files;
    protected FileSystem fileSystem;

    public Folder(String name) {
        super(name);
        this.files = new ArrayList<>();
    }

    public void add(File file) {
        files.add(file);
        file.folder = this;
        file.path = this.path += this.name + "/";
        this.size += file.size;
    }

    @Override
    public void open() {
        this.fileSystem.workPath = this.path;
    }
}

class Shortcut extends File {
    protected File linkedFile;

    public Shortcut(String name, File linkedFile) {
        super(name);
        this.linkedFile = linkedFile;
    }

    @Override
    public void open() {
        linkedFile.open();
    }
}

class ExecutableFile extends File {

    public ExecutableFile(String name) {
        super(name);
    }

    @Override
    public void open() {
        // do something;
    }
}

class NotExecutableFile extends File {
    public NotExecutableFile(String name) {
        super(name);
    }

    public void open() {
        System.out.println("could not execute nor-executable file");
    }
}

class FileSystem {
    public String workPath;
}