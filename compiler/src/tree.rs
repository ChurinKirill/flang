use crate::elements::DataType;

trait Node {}

struct FnunctionDefinitionNode {
    name: String,
    args: Vec<DataType>,
    body: BodyNode,
    return_type: DataType,
}

impl Node for FnunctionDefinitionNode {}

struct ExpressionNode {
    content: dyn Node,
}

struct BodyNode {
    content: Vec<Box<dyn Node>>,
}

impl Node for BodyNode {}

struct FunctionInvocationNode {
    name: String,
    args: Vec<Box<ExpressionNode>>,
    return_type: DataType
}

impl Node for FunctionInvocationNode {}


struct VariableDeclarationNode {
    name: String,
    data_type: DataType,
    value: ExpressionNode,
}

impl Node for VariableDeclarationNode {}

struct IfStatementNode {
    statement: BodyNode,
    else_clause: Option<BodyNode>,
    condition: ExpressionNode,
}

impl Node for IfStatementNode {}

struct WhileStatementNode {
    body: BodyNode,
    condition: ExpressionNode,
}

struct ReturnNode {
    return_value: ExpressionNode,
}

impl Node for ReturnNode {}

struct ConstNode<T> {
    value: T,
}

impl Node for ConstNode<i64> {}
impl Node for ConstNode<f64> {}
impl Node for ConstNode<bool> {}
impl Node for ConstNode<String> {}

