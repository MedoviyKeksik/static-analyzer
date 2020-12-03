//
// Created by Slonik on 24.11.2020.
//

#ifndef STATIC_ANALYZER_AST_H
#define STATIC_ANALYZER_AST_H
#include <vector>
#include <string>

class Node {
public:
    enum class Kind {If, function, };
    Kind kind;
};

class NodeComposite: Node {
public:
    std::vector<Node> nodes;
};

class NodeNamespace: Node {
    std::string identificator;
    NodeComposite body;
};


class NodeVariable: Node {
    std::string data_type;
    std::string identificator;
};

class NodeFunction: Node {
    class NodeVariable {
        std::string data_type;
        std::string identificator;
        std::string default_value;
    };
    std::string ReturnType;
    std::string Identificator;
    std::vector<NodeVariable> params;
    NodeComposite body;
};

class NodeExpression: Node {

};

class NodeIf: Node {
    NodeExpression statement;
    NodeComposite body_if;
    NodeComposite body_else;
};

class AST {
//    vector<NodeDefine> defines;
//    struct_definitions;
//    globalvars;
//    functions;
};


#endif //STATIC_ANALYZER_AST_H
