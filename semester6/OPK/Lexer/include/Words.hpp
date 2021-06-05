#pragma once

#include <set>
#include <string>

namespace Lexer {
namespace Word {

static std::set<std::string> operators{"+", "-", "*", "/", "%", "<", ">", "=", "&"};

static std::set<std::string> double_operators{
    "+=",
    "-=",
    "%=",
    "/=",
    "*=",
    "<<",
    ">>",
    "--",
    "++",
    "<=",
    ">=",
    "++",
    "//",
    "/*",
    "*/"};

static std::set<std::string> key_words{
    "auto",   "break",  "case",     "char",   "const",    "continue", "default",  "do",
    "double", "else",   "enum",     "extern", "float",    "for",      "foto",     "if",
    "int",    "long",   "register", "return", "short",    "signed",   "sizeof",   "static",
    "struct", "switch", "typedef",  "union",  "unsigned", "void",     "volatile", "while"};

static std::set<std::string> preprocessor_directives{
    "#define",
    "#include",
    "#undef",
    "#ifdef",
    "#ifndef",
    "#if",
    "#else",
    "#elif",
    "#endif",
    "#error",
    "#pragma once"};

static std::set<std::string> punctual_marks{",", ";", "}", "{", "(", ")"};

static std::set<std::string> non_token{"\n", "\t", " "};

} // namespace Word
} // namespace Lexer
