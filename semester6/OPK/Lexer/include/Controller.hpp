#pragma once

#include <iostream>
#include <memory>

#include "Lexer.hpp"
#include "Token.hpp"

namespace Lexer {
class Controller
{
public: // member functions
    Controller();
    void work(std::istream& in, std::ostream& out);

private: // member variables
    std::unique_ptr<Lexer> m_lexer;
};
} // namespace Lexer