use std::fmt;

// NOTE: Требует наличия поля args: Vec<Any> (или [Any; n]) в реализующих структурах
// Функция, возвращающая тип T 
pub trait Fn<T> {
    fn execute(&self) -> T;
}


// Сложение переданных аргументов (int, float, string)
pub struct FnAdd<T> {
    pub args: Vec<T>,
}

impl Fn<i64> for FnAdd<i64> {
    fn execute(&self) -> i64 {
        let mut res: i64 = 0;
        for item in &self.args {
            res += item;
        }

        res
    }
}

impl Fn<f64> for FnAdd<f64> {
    fn execute(&self) -> f64 {
        let mut res: f64 = 0.0;
        for item in &self.args {
            res += item
        }

        res
    }
}

impl Fn<String> for FnAdd<&str> {
    fn execute(&self) -> String {
        let mut res: String = String::new();
        for item in &self.args {
            res += item;
        }

        res
    }
}


// Вычесть из первого аргумента второй
pub struct FnSubtract<T> {
    pub args: [T; 2],
}

impl Fn<i64> for FnSubtract<i64> {
    fn execute(&self) -> i64 {
        self.args[0] - self.args[1]
    }
}

impl Fn<f64> for FnSubtract<f64> {
    fn execute(&self) -> f64 {
        self.args[0] - self.args[1]
    }
}


// Перемножить аргументы
pub struct FnMultiply<T> {
    pub args: Vec<T>,
}

impl Fn<i64> for FnMultiply<i64> {
    fn execute(&self) -> i64 {
        let mut res: i64 = 1;
        for item in &self.args {
            res *= item;
        }

        res
    }
}

impl Fn<f64> for FnMultiply<f64> {
    fn execute(&self) -> f64 {
        let mut res: f64 = 1.0;
        for item in &self.args {
            res *= item;
        }

        res
    }
}


// Разделить первый аргумент на второй
pub struct FnDivide<T> {
    pub args: [T; 2],
}

impl Fn<i64> for FnDivide<i64> {
    fn execute(&self) -> i64 {
        self.args[0] / self.args[1]
    }
}

impl Fn<f64> for FnDivide<f64> {
    fn execute(&self) -> f64 {
        self.args[0] / self.args[1]
    }
}


// Напечатать аргументы через пробел
pub struct FnPrint {
    pub args: Vec<Box<dyn fmt::Display>>,
}

impl Fn<()> for FnPrint {
    fn execute(&self) -> () {
        for item in &self.args {
            print!("{}", item);
        }
    }
}
