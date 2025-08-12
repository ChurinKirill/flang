#[derive(PartialEq, Debug)]
pub enum Token {
    Identifier {value: String},
    LBr,
    RBr,
    Comma,
    Colon,
    Data {value: ConstValue},
    Keyword {value: Keyword},
    DataType {value: DataType},
    // Встроенные функции
    Print,
    Plus,
    Minus,
    Multiply,
    Divide,
    Equal,
}

#[derive(PartialEq, Debug)]
pub enum ConstValue {
    Int {value: i64},
    Float {value: f64},
    Str {value: String},
    Bool {value: bool},
    Void,
}

#[derive(PartialEq, Debug)]
pub enum Keyword {
    Fn,
    Returning,
    Return,
    Body,
    Args,
}

#[derive(PartialEq, Debug)]
pub enum DataType {
    Int,
    Float,
    Str,
    Bool,
    Void,
}


pub struct Variable<T> {
    pub name: String,
    pub value: T,
}