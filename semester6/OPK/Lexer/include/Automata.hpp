#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

#include "Words.hpp"

namespace Lexer {

class Automata
{
public: // types
    enum class State
    {
        Character,
        Operator,
        OneLineComment,
        NewToken,
        EndOfToken,
        Literal,
        EndLiteral,
        PunctualMark,
        Invalid,
    };
    enum class Trigger
    {
        Character,
        Operator,
        PunctualMark,
        WhiteSpace,
        EndOfLine,
        LiteralMark,
    };

public: // member functions
    Automata();
    State goToNewState(const char character);

private: // member functions
    Trigger convertToTrigger(const std::string& character);

private: // member variables
    std::map<State, std::vector<std::pair<Trigger, State>>> m_rules;
    State m_current_state;
    bool m_prev_was_slash;
};

} // namespace Lexer