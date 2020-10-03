mod scanner;
mod parser;

use clap::App;

use scanner::Scanner;
// use parser::parser::Parser;

fn main() {
    let matches = App::new("cc0")
        .arg_from_usage("-h '显示关于编译器使用的帮助'")
        .arg_from_usage("-s [input] '将输入的 c0 源代码翻译为文本汇编文件'")
        .arg_from_usage("-c [input] '将输入的 c0 源代码翻译为二进制目标文件'")
        .arg_from_usage("-o [file] '输出到指定的文件 file'")
        .get_matches();

    let program = "int a = 1;\n int b = 2; \n a + b * a; ";
    let (tokens, errors): (Vec<_>, Vec<_>) = Scanner::new(program.chars())
        .into_iter()
        .partition(Result::is_ok);

    if errors.len() != 0 {
        for error in errors {
            println!("{:?}", error);
        }
        return;
    }

    for token in &tokens {
        println!("{:?}", token);
    }

    tokens.into_iter();
}
