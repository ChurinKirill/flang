use crate::elements::{ConstValue, Token};


pub struct Lexer {
    input: String,
    pos: usize,
}

impl Lexer {
    pub fn new(input: String) -> Self {
        Lexer { input: input, pos: 0 }
    }
    
    pub fn tokenize(&mut self) -> Vec<Token> {
        let mut tokens: Vec<Token> = Vec::new();

        while let Some(token) = self.next_token() {
            tokens.push(token);
        }

        tokens
    }

    fn next_token(&mut self) -> Option<Token> {
        self.skip_unreadable();
        if self.pos >= self.input.len() {
            return None;
        }
        let current_char = self.input.chars().nth(self.pos)?;
        match current_char {
            '\"' => {
                self.pos += 1;
                let res: Option<Token> = Some(Token::Data { value: ConstValue::Str { value: self.read_string() } });
                self.pos += 1;
                return res;
            }
            '(' => { self.pos += 1; Some(Token::LBr) }
            ')' => { self.pos += 1; Some(Token::RBr) }
            _ => Some(Token::LBr)
        }
    }

    fn read_string(&mut self) -> String {
        let start = self.pos;
        while let Some(c) = self.input.chars().nth(self.pos) {
            if c == '\"' {
                break;
            }
            self.pos += 1
        }

        let res: &String = &self.input[start..self.pos].to_string();
        
        res.to_string()

    }

    fn skip_unreadable(&mut self) {
        while let Some(c) = self.input.chars().nth(self.pos) {
            if !(c == ' ' || c == '\n' || c == '\t') { break; }
            self.pos += 1;
        }
    }

}

