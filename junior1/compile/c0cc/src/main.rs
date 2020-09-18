// mod scanner;
use clap::{App};

fn main() {
    let matches = App::new("cc0")
        .arg_from_usage("-h '显示关于编译器使用的帮助'")
        .arg_from_usage("-s [input] '将输入的 c0 源代码翻译为文本汇编文件'")
        .arg_from_usage("-c [input] '将输入的 c0 源代码翻译为二进制目标文件'")
        .arg_from_usage("-o [file] '输出到指定的文件 file'")
        .get_matches();

}