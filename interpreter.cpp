#include "interpreter.h"

using namespace std;

int Interpreter::visitNumberNode(NumberNode* node) {

    return stoi(node->value);
}

int Interpreter::visitBinaryOpNode(BinaryOpNode* node) {

    int left = visit(node->left);

    int right = visit(node->right);

    if (node->op == "+") {
        return left + right;
    }

    else if (node->op == "-") {
        return left - right;
    }

    else if (node->op == "*") {
        return left * right;
    }

    else if (node->op == "/") {
        return left / right;
    }

    return 0;
}

int Interpreter::visitVariableNode(
    VariableNode* node
) {

    return variables[node->name];
}

int Interpreter::visitAssignNode(
    AssignNode* node
) {

    int value = visit(node->value);

    variables[node->name] = value;

    return value;
}


int Interpreter::visit(AST* node) {

    NumberNode* numberNode =
        dynamic_cast<NumberNode*>(node);

    if (numberNode != nullptr) {
        return visitNumberNode(numberNode);
    }

    VariableNode* varNode =
        dynamic_cast<VariableNode*>(node);

    if (varNode != nullptr) {
        return visitVariableNode(varNode);
    }

    AssignNode* assignNode =
        dynamic_cast<AssignNode*>(node);

    if (assignNode != nullptr) {
        return visitAssignNode(assignNode);
    }

    ProgramNode* progNode =
    dynamic_cast<ProgramNode*>(node);

    if (progNode != nullptr) {
        return visitProgramNode(progNode);
    }

    BinaryOpNode* binaryNode =
        dynamic_cast<BinaryOpNode*>(node);

    if (binaryNode != nullptr) {
        return visitBinaryOpNode(binaryNode);
    }

    IfNode* ifNode =
    dynamic_cast<IfNode*>(node);

    if (ifNode != nullptr) {
        return visitIfNode(ifNode);
    }

    CompareNode* compareNode =
    dynamic_cast<CompareNode*>(node);

    if (compareNode != nullptr) {
        return visitCompareNode(compareNode);
    }

    WhileNode* whileNode =
    dynamic_cast<WhileNode*>(node);

    if (whileNode != nullptr) {

        return visitWhileNode(
            whileNode
        );
    }

    FunctionDefNode* funcDef =
    dynamic_cast<
        FunctionDefNode*
    >(node);

if (funcDef != nullptr) {

    return visitFunctionDefNode(
        funcDef
    );
}

FunctionCallNode* funcCall =
    dynamic_cast<
        FunctionCallNode*
    >(node);

if (funcCall != nullptr) {

    return visitFunctionCallNode(
        funcCall
    );
}

    return 0;
}

int Interpreter::visitProgramNode(
    ProgramNode* node
) {

    int result = 0;

    for (AST* stmt : node->statements) {

        result = visit(stmt);
    }

    return result;
}

int Interpreter::visitIfNode(
    IfNode* node
) {

    int cond =
        visit(node->condition);

    int result = 0;

    if (cond) {

        for (AST* stmt : node->ifBody) {

            result = visit(stmt);
        }
    }

    else {

        for (AST* stmt : node->elseBody) {

            result = visit(stmt);
        }
    }

    return result;
}

int Interpreter::visitCompareNode(
    CompareNode* node
) {

    int left =
        visit(node->left);

    int right =
        visit(node->right);

    if (node->op == ">") {
        return left > right;
    }

    else if (node->op == "<") {
        return left < right;
    }

    else if (node->op == "==") {
        return left == right;
    }

    return 0;
}


int Interpreter::visitWhileNode(
    WhileNode* node
) {

    int result = 0;

    while (
        visit(node->condition)
    ) {

        for (AST* stmt : node->body) {

            result = visit(stmt);
        }
    }

    return result;
}

int Interpreter::visitFunctionDefNode(
    FunctionDefNode* node
) {

    functions[node->name] = node;

    return 0;
}


int Interpreter::visitFunctionCallNode(
    FunctionCallNode* node
) {

    FunctionDefNode* func =
        functions[node->name];

    map<string, int> oldVariables =
        variables;

    for (
        int i = 0;
        i < func->params.size();
        i++
    ) {

        int value =
            visit(node->args[i]);

        variables[
            func->params[i]
        ] = value;
    }

    int result = 0;

    for (AST* stmt : func->body) {

        result = visit(stmt);
    }

    variables = oldVariables;

    return result;
}


