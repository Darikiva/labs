#include <iostream>
#include <fstream>

#include "Controller.hpp"
#include "Lexer.hpp"

int main()
{
    Lexer::Controller controller;
    std::ifstream in("../test/input.txt");
    std::ofstream out("../test/output.txt");
    controller.work(in, out);
    in.close();
    out.close();
    // Lexer::Lexer lexer;
    // std::string data = "*";
    // lexer.lex(data);
}
