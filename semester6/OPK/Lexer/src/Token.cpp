#include "Token.hpp"

namespace Lexer {

std::map<Token::Type, std::string> Token::c_type_to_str = 
{
    {Token::Type::Comment, "Comment"},
    {Token::Type::Identifier, "Identifier"},
    {Token::Type::Keyword, "Keyword"},
    {Token::Type::Literal, "Literal"},
    {Token::Type::NumericConstant, "NumericConstant"},
    {Token::Type::Operator, "Operator"},
    {Token::Type::PreprocessorDirective, "PreprocessorDirective"},
    {Token::Type::PunctualMark, "PunctualMark"},
    {Token::Type::SymbolicConstant, "SymbolicConstant"},
};

Token::Token(const std::string& data, const Type type)
    : m_data{data}
    , m_type{type}
{
}

std::string Token::getData() const
{
    return m_data;
}

Token::Type Token::getType() const
{
    return m_type;
}

std::string Token::getStringType() const
{
    return c_type_to_str[m_type];
}


} // namespace Lexer