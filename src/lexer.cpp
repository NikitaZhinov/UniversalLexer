#include "../include/lexer/lexer.h"

#include <locale>
#include <codecvt>
#include <filesystem>

std::vector<lexer::CombiningTokens>::iterator
lexer::Lexer::_isCombiningToken(const Token& token) {
    for (auto it = _combining_tokens.begin(); it != _combining_tokens.end(); ++it) {
        if (it->start == token) {
            return it;
        }
    }
    return _combining_tokens.end();
}

void lexer::Lexer::_pushToken(_CurrentStats& current_stats) {
    if (!current_stats.token_name.empty()) {
        current_stats.token_line.tokens.push_back(
            Token(_defineTokenId, std::move(current_stats.token_name)));
        current_stats.token_name.clear();
        auto last_token = _isCombiningToken(current_stats.token_line.tokens.back());
        if (last_token != _combining_tokens.end()) {
            if (_separators.find(current_stats.c) != std::wstring::npos) {
                current_stats.token_name.push_back(current_stats.c);
            }
            _pushText(current_stats, last_token);
        }
    }
}

bool lexer::Lexer::_isCloseToken(
    _CurrentStats& current_stats,
    std::vector<lexer::CombiningTokens>::iterator& close_token) const {
    auto rit_token = current_stats.token_name.rbegin();
    auto close_token_text = close_token->end.getText();
    auto rit_close_token = close_token_text.rbegin();
    while (rit_token != current_stats.token_name.rend() &&
           rit_close_token != close_token_text.rend()) {
        if (*rit_token != *rit_close_token) {
            return false;
        }
        ++rit_token;
        ++rit_close_token;
    }
    return true;
}

void lexer::Lexer::_pushText(_CurrentStats& current_stats,
                             std::vector<lexer::CombiningTokens>::iterator& close_token) {
    while (current_stats.char_it != current_stats.end_it) {
        current_stats.c = *current_stats.char_it;
        ++current_stats.char_it;
        current_stats.token_name.push_back(current_stats.c);
        current_stats.token_line.original.push_back(current_stats.c);
        if (_isCloseToken(current_stats, close_token)) {
            for (std::size_t i = 0; i < close_token->end.getText().size(); ++i) {
                current_stats.token_name.pop_back();
            }
            if (!current_stats.token_name.empty()) {
                current_stats.token_line.tokens.push_back(
                    Token(_defineTokenId, std::move(current_stats.token_name)));
            }
            current_stats.token_name = close_token->end.getText();
            current_stats.token_line.tokens.push_back(
                Token(_defineTokenId, std::move(current_stats.token_name)));
            current_stats.token_name.clear();
            break;
        }
    }
}

void lexer::Lexer::_addIndividualChars(_CurrentStats& current_stats) {
    if (!current_stats.token_name.empty()) {
        _pushToken(current_stats);
    }
    current_stats.token_name.push_back(current_stats.c);
    _pushToken(current_stats);
}

void lexer::Lexer::_nextLine(_CurrentStats& current_stats) {
    _pushToken(current_stats);
    current_stats.token_line.line_number = current_stats.line_number++;
    if (!current_stats.token_line.tokens.empty()) {
        current_stats.token_lines.push_back(std::move(current_stats.token_line));
    }
}

bool lexer::Lexer::_isCharFromSpecialAlhpabet(wchar_t c) const {
    for (const std::wstring& alphabet : _special_alphabets) {
        if (alphabet.find(c) != std::wstring::npos) {
            return true;
        }
    }
    return false;
}

bool lexer::Lexer::_isDifferentAlphabets(wchar_t a, wchar_t b) const {
    if (a == b) {
        return false;
    }
    auto it_a = _special_alphabets.end(), it_b = _special_alphabets.end();
    for (auto it = _special_alphabets.begin(); it != _special_alphabets.end(); ++it) {
        if (it->find(a) != std::wstring::npos) {
            it_a = it;
        }
        if (it->find(b) != std::wstring::npos) {
            it_b = it;
        }
        if (it_a != _special_alphabets.end() && it_b != _special_alphabets.end()) {
            break;
        }
    }
    if (it_a == it_b) {
        return false;
    }
    return true;
}

void lexer::Lexer::_addSpecialAlphabet(_CurrentStats& current_stats) {
    if (!current_stats.token_name.empty() &&
        _isDifferentAlphabets(current_stats.token_name.back(), current_stats.c)) {
        _pushToken(current_stats);
    }
    current_stats.token_name.push_back(current_stats.c);
}

lexer::Lexer::Lexer(const std::vector<std::wstring>& special_alphabets,
                    const std::wstring& individual_chars,
                    const std::vector<CombiningTokens>& combining_tokens,
                    const std::wstring& separators,
                    Token::define_id_func_t defineTokenIdFunc) :
    _special_alphabets(special_alphabets),
    _individual_chars(individual_chars),
    _combining_tokens(combining_tokens),
    _separators(separators),
    _defineTokenId(defineTokenIdFunc) {}

lexer::Lexer::Lexer(const Lexer& other) :
    _special_alphabets(other._special_alphabets),
    _individual_chars(other._individual_chars),
    _combining_tokens(other._combining_tokens),
    _defineTokenId(other._defineTokenId),
    _separators(other._separators) {}

lexer::Lexer::Lexer(Lexer&& other) noexcept :
    _special_alphabets(std::move(other._special_alphabets)),
    _individual_chars(std::move(other._individual_chars)),
    _combining_tokens(std::move(other._combining_tokens)),
    _defineTokenId(std::move(other._defineTokenId)),
    _separators(std::move(other._separators)) {}

lexer::Lexer& lexer::Lexer::operator=(const Lexer& right) {
    _defineTokenId = right._defineTokenId;
    _special_alphabets = right._special_alphabets;
    _individual_chars = right._individual_chars;
    _combining_tokens = right._combining_tokens;
    _separators = right._separators;
    return *this;
}

lexer::Lexer& lexer::Lexer::operator=(Lexer&& right) noexcept {
    _defineTokenId = std::move(right._defineTokenId);
    _special_alphabets = std::move(right._special_alphabets);
    _individual_chars = std::move(right._individual_chars);
    _combining_tokens = std::move(right._combining_tokens);
    _separators = std::move(right._separators);
    return *this;
}

void lexer::Lexer::setSpecialAlphabets(
    const std::vector<std::wstring>& new_special_alphabets) {
    _special_alphabets = new_special_alphabets;
}

void lexer::Lexer::addSpecialAlphabet(const std::wstring& new_special_alphabet) {
    _special_alphabets.push_back(new_special_alphabet);
}

void lexer::Lexer::setSpecialAlphabets(
    std::vector<std::wstring>&& new_special_alphabets) noexcept {
    _special_alphabets = std::move(new_special_alphabets);
}

void lexer::Lexer::addSpecialAlphabet(std::wstring&& new_special_alphabet) noexcept {
    _special_alphabets.push_back(std::move(new_special_alphabet));
}

void lexer::Lexer::setIndividualChars(const std::wstring& new_individual_chars) {
    _individual_chars = new_individual_chars;
}

void lexer::Lexer::addIndividualChar(const wchar_t& new_individual_char) {
    _individual_chars.push_back(new_individual_char);
}

void lexer::Lexer::setIndividualChars(std::wstring&& new_individual_chars) noexcept {
    _individual_chars = std::move(new_individual_chars);
}

void lexer::Lexer::addIndividualChar(wchar_t&& new_individual_char) noexcept {
    _individual_chars.push_back(std::move(new_individual_char));
}

void lexer::Lexer::setCombiningTokens(
    const std::vector<CombiningTokens>& new_combining_tokens) {
    _combining_tokens = new_combining_tokens;
}

void lexer::Lexer::addCombiningToken(const CombiningTokens& new_combining_token) {
    _combining_tokens.push_back(new_combining_token);
}

void lexer::Lexer::setCombiningTokens(
    std::vector<CombiningTokens>&& new_combining_tokens) noexcept {
    _combining_tokens = std::move(new_combining_tokens);
}

void lexer::Lexer::addCombiningToken(CombiningTokens&& new_combining_token) noexcept {
    _combining_tokens.push_back(std::move(new_combining_token));
}

std::vector<std::wstring> lexer::Lexer::getSpecialAlphabets() const {
    return _special_alphabets;
}

std::wstring lexer::Lexer::getIndividualChars() const {
    return _individual_chars;
}

std::vector<lexer::CombiningTokens> lexer::Lexer::getCombiningTokens() const {
    return std::vector<CombiningTokens>();
}

std::vector<lexer::TokenLine> lexer::Lexer::createTokens(const char* file_name) {
    std::wifstream file(file_name);
    return createTokens(file);
}

std::vector<lexer::TokenLine> lexer::Lexer::createTokens(std::wifstream& file) {
#ifdef __linux__
    file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
#endif

    std::vector<lexer::TokenLine> tokens;

    if (file.is_open()) {
        file.seekg(0, std::ios_base::end);

        std::wstring str;
        str.reserve(file.tellg());

        file.seekg(0, std::ios_base::beg);

        while (!file.eof()) {
            str.push_back(file.get());
        }

        tokens = createTokens(str);
    } else {
        throw std::runtime_error("file is not exist");
    }

    return tokens;
}

std::vector<lexer::TokenLine> lexer::Lexer::createTokens(const std::wstring& str) {
    _CurrentStats current_stats { 1, {}, L"", {}, 0, str.begin(), str.end() };

    while (current_stats.char_it != current_stats.end_it) {
        current_stats.c = *current_stats.char_it;
        ++current_stats.char_it;
        current_stats.token_line.original.push_back(current_stats.c);

        if (_individual_chars.find(current_stats.c) != std::wstring::npos) {
            _addIndividualChars(current_stats);
        } else if (_isCharFromSpecialAlhpabet(current_stats.c)) {
            _addSpecialAlphabet(current_stats);
        } else if (_separators.find(current_stats.c) != std::wstring::npos) {
            _pushToken(current_stats);
        } else {
            current_stats.token_name.push_back(current_stats.c);
        }

        if (current_stats.c == L'\n') {
            _nextLine(current_stats);
        }
    }
    if (!current_stats.token_name.empty()) {
        current_stats.token_name.pop_back();
    }
    if (!current_stats.token_line.original.empty()) {
        current_stats.token_line.original.pop_back();
    }
    _nextLine(current_stats);

    return current_stats.token_lines;
}
