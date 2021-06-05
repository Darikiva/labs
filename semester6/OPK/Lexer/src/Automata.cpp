#include "Automata.hpp"

#include <iostream>
#include <map>

namespace Lexer {

Automata::Automata()
    : m_current_state{State::EndOfToken}
{
    m_rules[State::Character] = {
        {Trigger::Character, State::Character},
        {Trigger::WhiteSpace, State::EndOfToken},
        {Trigger::PunctualMark, State::PunctualMark},
        {Trigger::Operator, State::Operator},
        {Trigger::EndOfLine, State::EndOfToken},
        {Trigger::LiteralMark, State::Literal},
    };

    m_rules[State::OneLineComment] = {
        {Trigger::Character, State::OneLineComment},
        {Trigger::WhiteSpace, State::OneLineComment},
        {Trigger::PunctualMark, State::OneLineComment},
        {Trigger::Operator, State::OneLineComment},
        {Trigger::EndOfLine, State::EndOfToken},
        {Trigger::LiteralMark, State::OneLineComment},
    };

    m_rules[State::NewToken] = {
        {Trigger::Character, State::Character},
        {Trigger::WhiteSpace, State::EndOfToken},
        {Trigger::PunctualMark, State::PunctualMark},
        {Trigger::Operator, State::Operator},
        {Trigger::EndOfLine, State::EndOfToken},
        {Trigger::LiteralMark, State::Literal},
    };

    m_rules[State::Operator] = {
        {Trigger::Character, State::NewToken},
        {Trigger::EndOfLine, State::EndOfToken},
        {Trigger::Operator, State::Operator},
        {Trigger::PunctualMark, State::PunctualMark},
        {Trigger::LiteralMark, State::Literal},
        {Trigger::WhiteSpace, State::EndOfToken},
    };

    m_rules[State::EndOfToken] = {
        {Trigger::Character, State::NewToken},
        {Trigger::Operator, State::Operator},
        {Trigger::EndOfLine, State::EndOfToken},
        {Trigger::PunctualMark, State::PunctualMark},
        {Trigger::WhiteSpace, State::EndOfToken},
        {Trigger::LiteralMark, State::Literal},
    };

    m_rules[State::Literal] = {
        {Trigger::Character, State::Literal},
        {Trigger::Operator, State::Literal},
        {Trigger::EndOfLine, State::Literal},
        {Trigger::PunctualMark, State::Literal},
        {Trigger::WhiteSpace, State::Literal},
        {Trigger::LiteralMark, State::EndOfToken},
    };

    m_rules[State::PunctualMark] = {
        {Trigger::Character, State::NewToken},
        {Trigger::Operator, State::Operator},
        {Trigger::EndOfLine, State::EndOfToken},
        {Trigger::PunctualMark, State::PunctualMark},
        {Trigger::WhiteSpace, State::EndOfToken},
        {Trigger::LiteralMark, State::Literal},
    };
}

Automata::State Automata::goToNewState(const char character)
{
    if (character == '/')
    {
        if (m_prev_was_slash)
        {
            m_current_state = State::OneLineComment;
            return m_current_state;
        }
        else
        {
            m_prev_was_slash = true;
        }
    }
    std::string input_character{character};
    const Trigger current_trigger{convertToTrigger(input_character)};
    for (const auto& [trigger, state] : m_rules[m_current_state])
    {
        if (trigger == current_trigger)
        {
            m_current_state = state;
            return state;
        }
    }
    return State::Invalid;
}

Automata::Trigger Automata::convertToTrigger(const std::string& character)
{
    Trigger answer = Trigger::Character;
    if (Word::operators.find(character) != Word::operators.end())
    {
        answer = Trigger::Operator;
    }
    else if (Word::punctual_marks.find(character) != Word::punctual_marks.end())
    {
        answer = Trigger::PunctualMark;
    }
    else if (character == "\n" || character == "\t" || character == std::string{(char)-1})
    {
        answer = Trigger::EndOfLine;
    }
    else if (character == " ")
    {
        answer = Trigger::WhiteSpace;
    }
    else if (character == "\"" || character == "\'")
    {
        answer = Trigger::LiteralMark;
    }
    return answer;
}
} // namespace Lexer
