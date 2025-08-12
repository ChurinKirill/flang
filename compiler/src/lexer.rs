use crate::elements::{ConstValue, DataType, Keyword, Token};


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
            // Кавычка - читаем строку
            '\"' => {
                self.pos += 1;
                let res: Option<Token> = Some(Token::Data { value: ConstValue::Str { value: self.read_string() } });
                self.pos += 1;
                return res;
            }
            // всякие символы и встроенные функции
            '(' => { self.pos += 1; Some(Token::LBr) }
            ')' => { self.pos += 1; Some(Token::RBr) }
            ',' => { self.pos += 1; Some(Token::Comma) }
            ':' => { self.pos += 1; Some(Token::Colon) }
            '+' => { self.pos += 1; Some(Token::Plus) }
            '-' => { self.pos += 1; Some(Token::Minus) }
            '*' => { self.pos += 1; Some(Token::Multiply) }
            '/' => { self.pos += 1; Some(Token::Divide) }
            '=' => { self.pos += 1; Some(Token::Equal) }
            // Цифра - читаем число
            _ if current_char.is_digit(10) => {
                return self.read_digit();
            }
            // Буква - читаем слово
            _ => {
                let word: String = self.read_word();

                self.check_word(&word[..])
            }
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

    fn read_digit(&mut self) -> Option<Token> {
        let start = self.pos;
        let mut is_float = false;
        while let Some(c) = self.input.chars().nth(self.pos) {
            if !c.is_digit(10) && c != '.' { break; }
            if c == '.' { is_float = true; }
            self.pos += 1;
        }

        let num_str = &self.input[start..self.pos];

        if is_float {
            Some(Token::Data { value: ConstValue::Float { value: num_str.parse().ok()? } })
        }
        else {
            Some(Token::Data { value: ConstValue::Int { value: num_str.parse().ok()? } })
        }

    }

    fn read_word(&mut self) -> String {
        let start = self.pos;
        while let Some(c) = self.input.chars().nth(self.pos) {
            if !c.is_ascii_alphabetic() { break; }
            self.pos += 1;
        }

        let word: &String = &self.input[start..self.pos].to_string();

        word.to_string()
    }

    // Если не ключевое слово/встроенная функция - то идентификатор
    fn check_word(&mut self, word: &str) -> Option<Token> {
        let mut token: Option<Token>;
        
        token = self.check_keywords(word);
        if token != None {
            return token;
        }

        token = self.check_funcs(word);
        if token != None {
            return token;
        }

        token = self.check_datatypes(word);
        if token != None {
            return token;
        }

        Some(Token::Identifier { value: word.to_string() })
    }

    fn check_keywords(&mut self, word: &str) -> Option<Token> {
        match word {
            "fn" => { Some(Token::Keyword { value: Keyword::Fn }) }
            "returning" => { Some(Token::Keyword { value: Keyword::Returning }) }
            "return" => { Some(Token::Keyword { value: Keyword::Return }) }
            "body" => { Some(Token::Keyword { value: Keyword::Body }) }
            "args" => { Some(Token::Keyword { value: Keyword::Args }) }
            _ => { None }
        }
    }

    fn check_funcs(&mut self, word: &str) -> Option<Token> {
        match word {
            "+" => { Some(Token::Plus) }
            "-" => { Some(Token::Minus) }
            "*" => { Some(Token::Multiply) }
            "/" => { Some(Token::Divide) }
            "=" => { Some(Token::Equal) }
            "print" => { Some(Token::Print) }
            _ => { None }
        }
    }

    fn check_datatypes(&mut self, word: &str) -> Option<Token> {
        match word {
            "int" => { Some(Token::DataType { value: DataType::Int }) }
            "float" => { Some(Token::DataType { value: DataType::Float }) }
            "str" => { Some(Token::DataType { value: DataType::Str }) }
            "bool" => { Some(Token::DataType { value: DataType::Bool }) }
            "void" => { Some(Token::DataType { value: DataType::Void }) }
            _ => { None }
        }
    }

    fn skip_unreadable(&mut self) {
        while let Some(c) = self.input.chars().nth(self.pos) {
            if !(c == ' ' || c == '\n' || c == '\t') { break; }
            self.pos += 1;
        }
    }

}

