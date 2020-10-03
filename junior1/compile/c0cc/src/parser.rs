use std::iter::Peekable;
use crate::scanner::PeekHelper;


use super::scanner::TokenType;
pub struct Parser<T> 
where T: Iterator<Item = TokenType>
{
    tokens: Peekable<T>
}

impl<T> Parser<T>
where T: Iterator<Item = TokenType>
{
    fn test(&mut self) {
        self.tokens.expect(item)
    }
}