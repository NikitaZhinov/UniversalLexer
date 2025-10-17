#include "../include/lexer/token.h"

using namespace lexer;

void Token::_updateId() {
    _id = _defineId(_text.c_str());
}

Token::Token() : _id(0), _defineId(defineTokenId<uint64_t>) {}

Token::Token(const std::wstring& text) : _text(text), _defineId(defineTokenId<uint64_t>) {
    _updateId();
}

Token::Token(define_id_func_t defineId) : _id(0), _defineId(defineId) {}

Token::Token(define_id_func_t defineId, const std::wstring& text) :
    _id(0),
    _defineId(defineId),
    _text(text) {
    _updateId();
}

Token::Token(const Token& other) :
    _id(other._id),
    _text(other._text),
    _defineId(other._defineId) {}

Token::Token(Token&& other) noexcept :
    _id(std::move(other._id)),
    _text(std::move(other._text)),
    _defineId(std::move(other._defineId)) {}

void Token::setText(const std::wstring& new_text) {
    _text = new_text;
    _updateId();
}

void Token::setText(std::wstring&& new_text) noexcept {
    _text = std::move(new_text);
    _updateId();
}

uint64_t Token::getId() const {
    return _id;
}

std::wstring Token::getText() const {
    return _text;
}

Token& Token::operator=(const Token& right) {
    _text = right._text;
    _defineId = right._defineId;
    _updateId();
    return *this;
}

Token& Token::operator=(Token&& right) noexcept {
    _text = std::move(right._text);
    _defineId = std::move(right._defineId);
    _updateId();
    return *this;
}

bool lexer::operator==(const Token& left, const Token& right) {
    return left._id == right._id;
}

bool lexer::operator!=(const Token& left, const Token& right) {
    return left._id != right._id;
}

bool lexer::operator==(const TokenLine& left, const TokenLine& right) {
    return left.line_number == right.line_number && left.tokens == right.tokens;
}

bool lexer::operator!=(const TokenLine& left, const TokenLine& right) {
    return !(left == right);
}

bool lexer::operator==(const CombiningTokens& left, const CombiningTokens& right) {
    return left.start == right.start && left.end == right.end;
}

bool lexer::operator!=(const CombiningTokens& left, const CombiningTokens& right) {
    return !(left == right);
}

TokenLine::TokenLine() : line_number(0) {}

TokenLine::TokenLine(size_t line_number, const std::wstring& original,
                     const token_contaner_t& tokens) :
    line_number(line_number),
    original(original),
    tokens(tokens) {}

TokenLine::TokenLine(const TokenLine& other) :
    line_number(other.line_number),
    original(other.original),
    tokens(other.tokens) {}

TokenLine::TokenLine(TokenLine&& other) noexcept :
    line_number(std::move(other.line_number)),
    original(std::move(other.original)),
    tokens(std::move(other.tokens)) {}

TokenLine& TokenLine::operator=(const TokenLine& right) {
    line_number = right.line_number;
    original = right.original;
    tokens = right.tokens;
    return *this;
}

TokenLine& TokenLine::operator=(TokenLine&& right) noexcept {
    line_number = std::move(right.line_number);
    original = std::move(right.original);
    tokens = std::move(right.tokens);
    return *this;
}

CombiningTokens::CombiningTokens(const Token& start, const Token& end) :
    start(start),
    end(end) {}

CombiningTokens::CombiningTokens(const CombiningTokens& other) :
    start(other.start),
    end(other.end) {}

CombiningTokens::CombiningTokens(CombiningTokens&& other) noexcept :
    start(std::move(other.end)),
    end(std::move(other.end)) {}

CombiningTokens& CombiningTokens::operator=(const CombiningTokens& right) {
    start = right.start;
    end = right.end;
    return *this;
}

CombiningTokens& CombiningTokens::operator=(CombiningTokens&& right) noexcept {
    start = std::move(right.start);
    end = std::move(right.end);
    return *this;
}
