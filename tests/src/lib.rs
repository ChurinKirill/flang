// Тесты
#[cfg(test)]
mod tests {
    use compiler::lexer::*;
    use compiler::functions::*;
    use compiler::elements::*;

    #[test]
    fn add_int() {
        let func: FnAdd<i64> = FnAdd {
            args: vec![1, 2, 3],
        };

        assert_eq!(func.execute(), 6);
    }

    #[test]
    fn add_float() {
        let func: FnAdd<f64> = FnAdd {
            args: vec![1.5, 2.3, 3.8],
        };

        assert_eq!(func.execute(), 7.6);
    }

    #[test]
    fn add_string() {
        let func: FnAdd<&str> = FnAdd {
            args: vec!["Hello,", " world!"],
        };

        assert_eq!(func.execute(), String::from("Hello, world!"));
    }


    #[test]
    fn print() {
        let func: FnPrint = FnPrint {
            args: vec![Box::new(12), Box::new(" Hello!")],
        };

        func.execute();
    }

    #[test]
    fn long_tokenize() {
         let mut lexer: Lexer = Lexer::new("(fn main returning int,\n\t(body,\n\t(=, a: int, 5),\nreturn 0\n)\n)".to_string());

        let tokens: Vec<Token>  = lexer.tokenize();

        println!("{:?}", tokens);

        let expected: Vec<Token> = vec![
            Token::LBr,
            Token::Keyword { value: Keyword::Fn },
            Token::Identifier { value: "main".to_string() },
            Token::Keyword { value: Keyword::Returning },
            Token::DataType { value: DataType::Int },
            Token::Comma,
            Token::LBr,
            Token::Keyword { value: Keyword::Body },
            Token::Comma,
            Token::LBr,
            Token::Equal,
            Token::Comma,
            Token::Identifier { value: "a".to_string() },
            Token::Colon,
            Token::DataType { value: DataType::Int },
            Token::Comma,
            Token::Data { value: ConstValue::Int { value: 5 } },
            Token::RBr,
            Token::Comma,
            Token::Keyword { value: Keyword::Return },
            Token::Data { value: ConstValue::Int { value: 0 } },
            Token::RBr,
            Token::RBr,
        ];

        assert_eq!(tokens.len(), expected.len());

        assert_eq!(tokens, expected);
        
    }
}
