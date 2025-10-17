#include "../include/lexer/lexer-iterator.h"

using namespace lexer;

LexerIterator::LexerIterator(contaner& c) :
    LexerTemplateIterator(c.begin(), c.end(), c.begin()->tokens.begin()) {}

LexerIterator::token_it_t LexerIterator::getBegin() {
    return _current_line->tokens.begin();
}

LexerConstIterator::LexerConstIterator(const contaner& c) :
    LexerTemplateIterator(c.cbegin(), c.cend(), c.cbegin()->tokens.cbegin()) {}

LexerConstIterator::token_it_t LexerConstIterator::getBegin() {
    return _current_line->tokens.cbegin();
}

LexerReverseIterator::LexerReverseIterator(contaner& c) :
    LexerTemplateIterator(c.rbegin(), c.rend(), c.rbegin()->tokens.rbegin()) {}

LexerReverseIterator::token_it_t LexerReverseIterator::getBegin() {
    return _current_line->tokens.rbegin();
}

LexerConstReverseIterator::LexerConstReverseIterator(const contaner& c) :
    LexerTemplateIterator(c.crbegin(), c.crend(), c.crbegin()->tokens.crbegin()) {}

LexerConstReverseIterator::token_it_t LexerConstReverseIterator::getBegin() {
    return _current_line->tokens.crbegin();
}
