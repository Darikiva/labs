#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "Automata.hpp"
#include "Token.hpp"
#include "Words.hpp"

namespace Lexer {

class Lexer
{
public: // member functions
    using State = Automata::State;
    Lexer();
    std::vector<Token> lex(const std::string& input);

private: // member functions
    Token::Type convertToTokenType(const std::string& target);

private: // member variables
    std::unique_ptr<Automata> automata;
};

} // namespace Lexer