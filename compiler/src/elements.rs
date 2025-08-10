#[derive(PartialEq, Debug)]
pub enum Token {
    Identifier {value: String},
    LBr,
    RBr,
    Comma,
    Colon,
    Data {value: ConstValue},
    Keyword {value: Keyword},
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
    Body
}


pub struct Variable<T> {
    pub name: String,
    pub value: T,
}