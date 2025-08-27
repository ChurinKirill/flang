use crate::elements::*;
use crate::tree::*;

struct FnunctionDescription {
    pub name: Token,
    pub args: Vec<Vec<Token>>,
}

pub struct Parser {
    tokens: Vec<Token>,
    pos: usize,
}

impl Parser {

    pub fn new(tokens: Vec<Token>) -> Self {
        Parser { tokens: tokens, pos: 0 }
    }

    pub fn parse(&mut self) -> Vec<Box<dyn Node>> {
        let result: Vec<Box<dyn Node>> = Vec::new();
        while let Some(t) = self.tokens.get(self.pos) {

        }
        result
    }

    fn parse_func(&mut self, func_tokens: Vec<Token>) -> FnunctionDescription {
        let name: Token = func_tokens.get(0).unwrap().clone();
        let mut args: Vec<Vec<Token>> = Vec::new();
        let mut i = 2;
        let mut arg: Vec<Token> = Vec::new();
        while let Some(t) = func_tokens.get(i) {
            arg.push(t.clone());
            if *t == Token::Comma {
                args.push(arg);
                arg.clear();
            }
            i += 1;
        }
        FnunctionDescription {
            name: name,
            args: args
        }
    }

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