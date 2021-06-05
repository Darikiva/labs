#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

namespace Lexer {

class Token
{
public:
    enum class Type
    {
        NumericConstant,
        Literal,
        SymbolicConstant,
        PreprocessorDirective,
        Comment,
        Keyword,
        Identifier,
        Operator,
        PunctualMark,
        None,
    };
    static std::map<Type, std::string> c_type_to_str;
    Token(const std::string& data, const Type type);
    std::string getData() const;
    Type getType() const;
    std::string getStringType() const;

private:
    std::string m_data;
    Type m_type;
};
}