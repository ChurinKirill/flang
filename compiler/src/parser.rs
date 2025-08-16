use crate::elements::*;

pub struct Parser {
    tokens: Vec<Token>,
    pos: usize,
}

impl Parser {

    pub fn new(tokens: Vec<Token>) -> Self {
        Parser { tokens: tokens, pos: 0 }
    }

    pub fn parse(&mut self) {
        while let Some(t) = self.tokens.get(self.pos) {
            if *t == Token::LBr {
                let content = self.get_func_content();
                self.parse_func(content);
            }
        }
    }

    fn parse_func(&mut self, func_tokens: Vec<Token>) {}

    fn get_func_content(&mut self) -> Vec<Token> {
        let start = self.pos;
        let mut cnt = 1;
        loop {
            let t = &self.tokens[self.pos];
            if *t == Token::LBr { cnt += 1; }
            else if *t == Token::RBr { cnt -= 1; }
            if cnt == 0 { break; }
            self.pos += 1;
        }

        self.tokens[start..self.pos].to_vec()
        
    }
}