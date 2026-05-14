#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

using namespace std;

int main() {

    Interpreter interpreter;

    while (true) {

        string input;

        cout << ">> ";

        getline(cin, input);

        if (
            input == "exit"
        ) {

            break;
        }

        Lexer lexer(input);

        vector<Token> tokens =
            lexer.tokenize();

        Parser parser(tokens);

        AST* tree =
            parser.parse();

        int result =
            interpreter.visit(tree);

        cout
            << result
            << endl;
    }

    return 0;
}