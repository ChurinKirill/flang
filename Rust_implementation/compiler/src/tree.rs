use crate::elements::DataType;

pub trait Node {}

pub struct FnunctionDefinitionNode {
    name: String,
    args: Vec<DataType>,
    body: BodyNode,
    return_type: DataType,
}

impl Node for FnunctionDefinitionNode {}

pub struct ExpressionNode {
    content: dyn Node,
}

pub struct BodyNode {
    content: Vec<Box<dyn Node>>,
}

impl Node for BodyNode {}

pub struct FunctionInvocationNode {
    name: String,
    args: Vec<Box<ExpressionNode>>,
    return_type: DataType
}

impl Node for FunctionInvocationNode {}


pub struct VariableDeclarationNode {
    name: String,
    data_type: DataType,
    value: ExpressionNode,
}

impl Node for VariableDeclarationNode {}

pub struct IfStatementNode {
    statement: BodyNode,
    else_clause: Option<BodyNode>,
    condition: ExpressionNode,
}

impl Node for IfStatementNode {}

pub struct WhileStatementNode {
    body: BodyNode,
    condition: ExpressionNode,
}

pub struct ReturnNode {
    return_value: ExpressionNode,
}


pub struct ConstNode<T> {
    value: T,
}

impl Node for ConstNode<i64> {}
impl Node for ConstNode<f64> {}
impl Node for ConstNode<bool> {}
impl Node for ConstNode<String> {}

pub struct IdentifierNode {
    name: String
}

impl Node for IdentifierNode {}
impl IdentifierNode {
    pub fn new(name: &str) -> Self {
        IdentifierNode { name: name.to_string() }
    }
}
