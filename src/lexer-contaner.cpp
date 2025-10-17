#include "../include/lexer/lexer-contaner.h"

using namespace lexer;

void LexerContaner::_countSize() {
    _size = 0;
    for (auto& tl : _contaner) {
        _size += tl.tokens.size();
    }
}

LexerContaner::LexerContaner() : _size(0) {}

LexerContaner::LexerContaner(const LexerContaner& other) :
    _contaner(other._contaner),
    _size(other._size) {}

LexerContaner::LexerContaner(LexerContaner&& other) noexcept :
    _contaner(std::move(other._contaner)),
    _size(other._size) {
    other._size = 0;
}

LexerContaner::LexerContaner(const lexer_contaner_t& contaner) :
    _contaner(contaner),
    _size(0) {
    _countSize();
}

LexerContaner::LexerContaner(lexer_contaner_t&& contaner) :
    _contaner(std::move(contaner)),
    _size(0) {
    _countSize();
}

LexerContaner& LexerContaner::operator=(const LexerContaner& other) {
    _contaner = other._contaner;
    _size = other._size;
    return *this;
}

LexerContaner& LexerContaner::operator=(LexerContaner&& other) noexcept {
    _contaner = std::move(other._contaner);
    _size = other._size;
    other._size = 0;
    return *this;
}

LexerContaner& lexer::LexerContaner::operator=(const lexer_contaner_t& contaner) {
    _contaner = contaner;
    _countSize();
    return *this;
}

LexerContaner& lexer::LexerContaner::operator=(lexer_contaner_t&& contaner) noexcept {
    _contaner = std::move(contaner);
    _countSize();
    return *this;
}

LexerIterator LexerContaner::begin() {
    return LexerIterator(_contaner);
}

LexerConstIterator LexerContaner::begin() const {
    return LexerConstIterator(_contaner);
}

LexerConstIterator LexerContaner::cbegin() const {
    return LexerConstIterator(_contaner);
}

LexerIterator LexerContaner::end() {
    return LexerIterator(_contaner) + _size;
}

LexerConstIterator LexerContaner::end() const {
    return LexerConstIterator(_contaner) + _size;
}

LexerConstIterator LexerContaner::cend() const {
    return LexerConstIterator(_contaner) + _size;
}

LexerReverseIterator LexerContaner::rbegin() {
    return LexerReverseIterator(_contaner);
}

LexerConstReverseIterator LexerContaner::rbegin() const {
    return LexerConstReverseIterator(_contaner);
}

LexerConstReverseIterator LexerContaner::crbegin() const {
    return LexerConstReverseIterator(_contaner);
}

LexerReverseIterator LexerContaner::rend() {
    return LexerReverseIterator(_contaner) + _size;
}

LexerConstReverseIterator LexerContaner::rend() const {
    return LexerConstReverseIterator(_contaner) + _size;
}

LexerConstReverseIterator LexerContaner::crend() const {
    return LexerConstReverseIterator(_contaner) + _size;
}

TokenLine& LexerContaner::getLine(size_t i) {
    return _contaner.at(i);
}

const TokenLine& LexerContaner::getLine(size_t i) const {
    return _contaner.at(i);
}

TokenLine& LexerContaner::operator[](size_t i) {
    return _contaner[i];
}

const TokenLine& LexerContaner::operator[](size_t i) const {
    return _contaner[i];
}

size_t LexerContaner::getSize() const {
    return _size;
}

size_t LexerContaner::getTokensNumber() const {
    return getSize();
}

size_t LexerContaner::getLinesNumber() const {
    return _contaner.size();
}
