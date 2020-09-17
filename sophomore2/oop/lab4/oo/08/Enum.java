import java.util.*;

enum File {
    Folder {
        protected List<File> files;
        protected FileSystem fileSystem;

        public void init(String name) {
            this.name = name;
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
    },
    Shortcut {
        protected File linkedFile;

        public void init(String name, File linkedFile) {
            this.name = name;
            this.linkedFile = linkedFile;
        }

        @Override
        public void open() {
            linkedFile.open();
        }
    },
    ExecutableFile {
        public void init(String name) {
            this.name = name;
        }

        @Override
        public void open() {
            // do something;
        }
    },
    NotExecutableFile {
        public void init(String name) {
            this.name = name;
        }

        public void open() {
            System.out.println("could not execute nor-executable file");
        }
    };

    protected String name;
    protected Date createDate;
    protected int size;
    protected List<Byte> content;
    protected File folder;
    protected String path;

    public abstract void open();

    public void write(ArrayList<Byte> content) {
        this.content.addAll(content);
        this.size += content.size();
    }
}

class FileSystem {
    public String workPath;
}

public class Enum {
    public static void main(String[] args) {
        File folder = File.Folder;
        File exe = File.ExecutableFile;
        exe.init("login.exe");
        folder.init("fasdf", exe);
    }
}