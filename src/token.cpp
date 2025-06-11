#include "../include/lexer/token.h"

void lexer::Token::_updateId() {
    _id = _defineId(_text.c_str());
}

lexer::Token::Token() : _id(0), _defineId(defineTokenId<uint64_t>) {}

lexer::Token::Token(const std::wstring& text) :
    _text(text),
    _defineId(defineTokenId<uint64_t>) {
    _updateId();
}

lexer::Token::Token(define_id_func_t defineId) : _id(0), _defineId(defineId) {}

lexer::Token::Token(define_id_func_t defineId, const std::wstring& text) :
    _id(0),
    _defineId(defineId),
    _text(text) {
    _updateId();
}

lexer::Token::Token(const Token& other) :
    _id(other._id),
    _text(other._text),
    _defineId(other._defineId) {}

lexer::Token::Token(Token&& other) noexcept :
    _id(std::move(other._id)),
    _text(std::move(other._text)),
    _defineId(std::move(other._defineId)) {}

void lexer::Token::setText(const std::wstring& new_text) {
    _text = new_text;
    _updateId();
}

void lexer::Token::setText(std::wstring&& new_text) noexcept {
    _text = std::move(new_text);
    _updateId();
}

std::uint64_t lexer::Token::getId() const {
    return _id;
}

std::wstring lexer::Token::getText() const {
    return _text;
}

lexer::Token& lexer::Token::operator=(const Token& right) {
    _text = right._text;
    _defineId = right._defineId;
    _updateId();
    return *this;
}

lexer::Token& lexer::Token::operator=(Token&& right) noexcept {
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

lexer::TokenLine::TokenLine() : line_number(0) {}

lexer::TokenLine::TokenLine(std::size_t line_number, const std::wstring& original,
                            const std::vector<Token>& tokens) :
    line_number(line_number),
    original(original),
    tokens(tokens) {}

lexer::TokenLine::TokenLine(const TokenLine& other) :
    line_number(other.line_number),
    original(other.original),
    tokens(other.tokens) {}

lexer::TokenLine::TokenLine(TokenLine&& other) noexcept :
    line_number(std::move(other.line_number)),
    original(std::move(other.original)),
    tokens(std::move(other.tokens)) {}

lexer::TokenLine& lexer::TokenLine::operator=(const TokenLine& right) {
    line_number = right.line_number;
    original = right.original;
    tokens = right.tokens;
    return *this;
}

lexer::TokenLine& lexer::TokenLine::operator=(TokenLine&& right) noexcept {
    line_number = std::move(right.line_number);
    original = std::move(right.original);
    tokens = std::move(right.tokens);
    return *this;
}

lexer::CombiningTokens::CombiningTokens(const Token& start, const Token& end) :
    start(start),
    end(end) {}

lexer::CombiningTokens::CombiningTokens(const CombiningTokens& other) :
    start(other.start),
    end(other.end) {}

lexer::CombiningTokens::CombiningTokens(CombiningTokens&& other) noexcept :
    start(std::move(other.end)),
    end(std::move(other.end)) {}

lexer::CombiningTokens& lexer::CombiningTokens::operator=(const CombiningTokens& right) {
    start = right.start;
    end = right.end;
    return *this;
}

lexer::CombiningTokens&
lexer::CombiningTokens::operator=(CombiningTokens&& right) noexcept {
    start = std::move(right.start);
    end = std::move(right.end);
    return *this;
}
