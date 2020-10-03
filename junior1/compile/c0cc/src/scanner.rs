use std::iter::Peekable;
use std::str::Chars;

// type CompileResult<T> = Result<T, String>;
type ScanResult = Result<TokenType, String>;

#[derive(Debug, Eq, PartialEq, Hash, Clone)]
pub enum Literal {
    Integer(u128),
}

#[derive(Debug, Eq, PartialEq, Hash, Clone)]
pub enum TokenType {
    Const,
    Int,

    Semicolon,
    Minus,
    Plus,
    Multiply,
    Divide,
    Assign,

    LParenthesis,
    RParenthesis,
    LCurlyBrace,
    RCurlyBrace,

    Identifier(String),
    Literal(Literal),

    EOF,
}

pub trait PeekHelper<T, U>
where
    T: Iterator<Item = U>,
{
    fn test(&mut self, item: &U) -> bool;
    fn expect(&mut self, item: &U) -> Result<U, String>;
}

impl<T, U> PeekHelper<T, U> for Peekable<T>
where
    T: Iterator<Item = U>, U: std::cmp::Eq + std::fmt::Debug
{
    fn test(&mut self, item: &U) -> bool {
        if self.peek().unwrap() == item {
            self.next();
            true
        } else {
            false
        }
    }

    fn expect(&mut self, item: &U) -> Result<U, String> {
        let n = *self.peek().unwrap().clone();

        if self.test(item) {
            Ok(n)
        } else {
            Err(format!("expect {:?}, but got {:?}", item, n))
        }
    }
}


pub struct Scanner<'a> {
    chars: Peekable<Chars<'a>>,
}

impl<'a> Iterator for Scanner<'a> {
    type Item = ScanResult;
    fn next(&mut self) -> Option<ScanResult> {
        match self.get_next_token() {
            Ok(TokenType::EOF) => None,
            e @ _ => Some(e),
        }
    }
}

impl<'a> Scanner<'a> {
    pub fn new(chars: Chars) -> Scanner {
        Scanner {
            chars: chars.peekable(),
        }
    }

    fn get_next_token(&mut self) -> ScanResult {
        loop {
            match self.chars.peek() {
                Some(c) if c.is_whitespace() => self.chars.next(),
                _ => break,
            };
        }

        if let Some(c) = self.chars.peek() {
            match c {
                '_' | 'a'..='z' | 'A'..='Z' => self.scan_idetifier(),
                '0'..='9' => self.scan_integer(),
                ';' | '+' | '-' | '*' | '/' | '{' | '}' | '(' | ')' | '=' => self.scan_oprator(),
                _ => Err(format!("invalid character {}", self.chars.next().unwrap())),
            }
        } else {
            Ok(TokenType::EOF)
        }
    }

    fn scan_integer(&mut self) -> ScanResult {
        let mut integer = String::new();
        while self.chars.peek().map_or(false, |c| c.is_numeric()) {
            integer.push(self.chars.next().unwrap());
        }

        let integer = integer.parse::<u128>().unwrap();
        Ok(TokenType::Literal(Literal::Integer(integer)))
    }

    fn scan_idetifier(&mut self) -> ScanResult {
        let mut identifier = String::new();
        while self
            .chars
            .peek()
            .map_or(false, |c| c.is_ascii_alphanumeric() || c == &'_')
        {
            identifier.push(self.chars.next().unwrap());
        }

        let token = match &identifier[..] {
            "const" => TokenType::Const,
            "int" => TokenType::Int,
            _ => TokenType::Identifier(identifier),
        };
        Ok(token)
    }

    fn scan_oprator(&mut self) -> ScanResult {
        let operator = match self.chars.next().unwrap() {
            ';' => TokenType::Semicolon,
            '+' => TokenType::Plus,
            '-' => TokenType::Minus,
            '*' => TokenType::Multiply,
            '/' => TokenType::Divide,
            '{' => TokenType::LCurlyBrace,
            '}' => TokenType::RCurlyBrace,
            '(' => TokenType::LParenthesis,
            ')' => TokenType::RParenthesis,
            '=' => TokenType::Assign,
            _ => panic!(),
        };
        Ok(operator)
    }
}
