#include "Controller.hpp"
#include <iomanip>

namespace Lexer {


Controller::Controller()
    : m_lexer{std::make_unique<Lexer>()}
{
}

void Controller::work(std::istream& in, std::ostream& out)
{
    std::string input_data;
    std::string buffer;
    while(in)
    {
        input_data += in.get();
    }
    auto tokens = m_lexer->lex(input_data);
    const char separator = ' ';
    const int width_token_type = 25;
    const int width_token_data = 100;
    for (const auto& token: tokens)
    {
        out << std::left << std::setw(width_token_type) << std::setfill(separator) << token.getStringType();
        out << std::left << std::setw(width_token_data) << std::setfill(separator) << token.getData();
        out << '\n';
    }
}

} // namespace Lexer
