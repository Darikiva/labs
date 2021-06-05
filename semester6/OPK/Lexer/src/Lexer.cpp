#include "Lexer.hpp"

#include <iostream>

namespace Lexer {

Lexer::Lexer()
    : automata{std::make_unique<Automata>()}
{
}

std::vector<Token> Lexer::lex(const std::string& input)
{
    std::vector<Token> output;
    std::string buffer;
    bool is_literal = false;
    bool cur_comment = false;
    for (const auto& character : input)
    {
        const auto current_state = automata->goToNewState(character);
        bool buffer_should_be_cleaned = false;
        bool buffer_should_add_current_character = false;
        switch (current_state)
        {
            case State::Character: {
                buffer_should_add_current_character = true;
            }
            break;
            case State::Operator: {
                if (!buffer.empty() && Word::operators.find(buffer) == Word::operators.end())
                {
                    output.push_back(Token(buffer, convertToTokenType(buffer)));
                    buffer_should_be_cleaned = true;
                    buffer_should_add_current_character = true;
                }
                else if (buffer.size() == 1)
                {
                    const std::string tmp_buffer{buffer + character};
                    if (Word::double_operators.find(tmp_buffer) != Word::double_operators.end())
                    {
                        output.push_back(Token(tmp_buffer, Token::Type::Operator));
                        buffer_should_be_cleaned = true;
                    }
                    else
                    {
                        output.push_back(Token(buffer, Token::Type::Operator));
                        buffer_should_add_current_character = true;
                    }
                }
                else
                {
                    buffer_should_add_current_character = true;
                }
            }
            break;
            case State::EndOfToken: {
                if (!buffer.empty())
                {
                    if (cur_comment)
                    {
                        output.push_back(Token(std::string(buffer, 2), Token::Type::Comment));
                    }
                    else if (buffer[0] == '\"')
                    {
                        output.push_back(Token(
                            std::string(buffer, 1, buffer.length() - 1), Token::Type::Literal));
                    }
                    else
                    {
                        output.push_back(Token(buffer, convertToTokenType(buffer)));
                    }
                    buffer_should_be_cleaned = true;
                    is_literal = false;
                    cur_comment = false;
                }
            }
            break;
            case State::NewToken: {
                if (!buffer.empty())
                {
                    output.push_back(Token(buffer, convertToTokenType(buffer)));
                    buffer_should_be_cleaned = true;
                }
                buffer_should_add_current_character = true;
            }
            break;
            default:
            case State::Invalid: {
                std::cout << "Invalid State; buffer = " << buffer << std::endl;
            }
            break;
            case State::Literal: {
                if (!buffer.empty() && !is_literal)
                {
                    output.push_back(Token(buffer, convertToTokenType(buffer)));
                    buffer_should_be_cleaned = true;
                }
                buffer_should_add_current_character = true;
                is_literal = true;
            }
            break;
            case State::OneLineComment: {
                buffer_should_add_current_character = true;
                cur_comment = true;
            }
            break;
            case State::PunctualMark: {
                if (!buffer.empty())
                {
                    output.push_back(Token(buffer, convertToTokenType(buffer)));
                    buffer_should_be_cleaned = true;
                }
                buffer_should_add_current_character = true;
            }
            break;
        }
        if (buffer_should_be_cleaned)
        {
            buffer.clear();
        }
        if (buffer_should_add_current_character)
        {
            buffer += character;
        }
    }
    if (!buffer.empty())
    {
        output.push_back(Token(buffer, convertToTokenType(buffer)));
    }
    return output;
}

Token::Type Lexer::convertToTokenType(const std::string& target)
{
    auto is_number = [](const std::string& str) {
        bool e_passed = false;
        bool dot_passed = false;
        bool minus_passed = false;
        for (const auto& character : str)
        {
            if (character == 'e' && !e_passed)
            {
                e_passed = true;
            }
            else if (e_passed && character == '-' && !minus_passed)
            {
                minus_passed = true;
            }
            else if (character == '.' && !dot_passed && !e_passed)
            {
                dot_passed = true;
            }
            else if (!std::isdigit(character))
            {
                return false;
            }
        }
        return true;
    };
    Token::Type answer = Token::Type::Identifier;
    if (Word::key_words.find(target) != Word::key_words.end())
    {
        answer = Token::Type::Keyword;
    }
    else if (Word::preprocessor_directives.find(target) != Word::preprocessor_directives.end())
    {
        answer = Token::Type::PreprocessorDirective;
    }
    else if (
        Word::operators.find(target) != Word::operators.end() ||
        Word::double_operators.find(target) != Word::double_operators.end())
    {
        answer = Token::Type::Operator;
    }
    else if (Word::punctual_marks.find(target) != Word::punctual_marks.end())
    {
        answer = Token::Type::PunctualMark;
    }
    else if (is_number(target))
    {
        answer = Token::Type::NumericConstant;
    }
    return answer;
}

} // namespace Lexer