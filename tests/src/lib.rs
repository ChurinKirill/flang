use compiler::functions::*;
use compiler::lexer::*;
use compiler::elements::*;

// Тесты
#[cfg(test)]
mod tests {
    use compiler::lexer;

    use super::*;

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
    fn tokenize() {
        let mut lexer: Lexer = Lexer::new("(\"Hello, World!\")".to_string());

        let tokens: Vec<Token>  = lexer.tokenize();

        let expected: Vec<Token> = vec![
            Token::LBr,
            Token::Data { value: ConstValue::Str { value: "Hello, World!".to_string() } },
            Token::RBr,
        ];

        assert_eq!(tokens.len(), expected.len());

        assert_eq!(tokens, expected);
        
    }
}
