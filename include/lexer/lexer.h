#pragma once

#include "token.h"

#include <string>
#include <vector>
#include <fstream>

namespace lexer {
    /**
     * @brief It is used to divide the contents of a file into tokens.
     */
    class Lexer {
        struct _CurrentStats {
            std::size_t line_number;
            std::vector<TokenLine> token_lines;
            std::wstring token_name;
            TokenLine token_line;
            wchar_t c;
            std::wistream& file;
        };

        std::vector<std::wstring> _special_alphabets;
        std::wstring _individual_chars;
        std::vector<CombiningTokens> _combining_tokens;
        std::wstring _separators;

        Token::define_id_func_t _defineTokenId;

        std::vector<CombiningTokens>::iterator _isCombiningToken(const Token& token);
        bool _isCharFromSpecialAlhpabet(wchar_t c) const;
        bool _isDifferentAlphabets(wchar_t a, wchar_t b) const;
        bool
        _isCloseToken(_CurrentStats& current_stats,
                      std::vector<lexer::CombiningTokens>::iterator& close_token) const;

        void _pushToken(_CurrentStats& current_stats);
        void _pushText(_CurrentStats& current_stats,
                       std::vector<lexer::CombiningTokens>::iterator& close_token);

        void _addIndividualChars(_CurrentStats& current_stats);
        void _addSpecialAlphabet(_CurrentStats& current_stats);

        void _nextLine(_CurrentStats& current_stats);

    public:
        /**
         * @brief Sets the necessary parameters for operation.
         *
         * @param special_alphabets - a list of alphabets.
         * @param individual_chars - a list of characters, each of which is regarded as a
         * separate alphabet.
         * @param combining_tokens - tokens between which all symbols are considered as a
         * single token.
         * @param separators - symbols used to separate words.
         * @param defineTokenIdFunc - a function for identifying tokens
         * (calculates the hash of the token by default).
         */
        Lexer(const std::vector<std::wstring>& special_alphabets,
              const std::wstring& individual_chars,
              const std::vector<CombiningTokens>& combining_tokens,
              const std::wstring& separators,
              Token::define_id_func_t defineTokenIdFunc = lexer::defineTokenId<uint64_t>);

        /**
         * @brief Copy constructor.
         *
         * @param other - another lexer.
         */
        Lexer(const Lexer& other);

        /**
         * @brief Move constructor.
         *
         * @param other - another lexer.
         */
        Lexer(Lexer&& other) noexcept;

        /**
         * @brief Copy operator.
         *
         * @param right - another lexer.
         */
        Lexer& operator=(const Lexer& right);

        /**
         * @brief Move operator.
         *
         * @param right - another lexer.
         */
        Lexer& operator=(Lexer&& right) noexcept;

        /**
         * @brief Sets new special alphabets.
         *
         * @param new_special_alphabets - a new special alphabets.
         */
        void setSpecialAlphabets(const std::vector<std::wstring>& new_special_alphabets);

        /**
         * @brief Adds new special alphabet.
         *
         * @param new_special_alphabet - a new special alphabet.
         */
        void addSpecialAlphabet(const std::wstring& new_special_alphabet);

        /**
         * @brief Sets new special alphabets.
         *
         * @param new_special_alphabets - a new special alphabets.
         */
        void
        setSpecialAlphabets(std::vector<std::wstring>&& new_special_alphabets) noexcept;

        /**
         * @brief Adds new special alphabet.
         *
         * @param new_special_alphabet - a new special alphabet.
         */
        void addSpecialAlphabet(std::wstring&& new_special_alphabet) noexcept;

        /**
         * @brief Sets new individual chars.
         *
         * @param new_individual_chars - a new individual chars.
         */
        void setIndividualChars(const std::wstring& new_individual_chars);

        /**
         * @brief Adds new individual char.
         *
         * @param new_individual_char - a new individual char.
         */
        void addIndividualChar(const wchar_t& new_individual_char);

        /**
         * @brief Sets new individual chars.
         *
         * @param new_individual_chars - a new individual chars.
         */
        void setIndividualChars(std::wstring&& new_individual_chars) noexcept;

        /**
         * @brief Adds new individual char.
         *
         * @param new_individual_char - a new individual char.
         */
        void addIndividualChar(wchar_t&& new_individual_char) noexcept;

        /**
         * @brief Sets combining tokens.
         *
         * @param new_combining_tokens - a new combining tokens.
         */
        void setCombiningTokens(const std::vector<CombiningTokens>& new_combining_tokens);

        /**
         * @brief Adds combining tokens.
         *
         * @param new_combining_token - a new combining token.
         */
        void addCombiningToken(const CombiningTokens& new_combining_token);

        /**
         * @brief Sets combining tokens.
         *
         * @param new_combining_tokens - a new combining tokens.
         */
        void
        setCombiningTokens(std::vector<CombiningTokens>&& new_combining_tokens) noexcept;

        /**
         * @brief Adds combining tokens.
         *
         * @param new_combining_token - a new combining token.
         */
        void addCombiningToken(CombiningTokens&& new_combining_token) noexcept;

        /**
         * @brief Returns a special alphabets.
         *
         * @return std::vector<std::wstring>
         */
        std::vector<std::wstring> getSpecialAlphabets() const;

        /**
         * @brief Returns a individual chars.
         *
         * @return std::wstring
         */
        std::wstring getIndividualChars() const;

        /**
         * @brief Return a combining tokens.
         */
        std::vector<CombiningTokens> getCombiningTokens() const;

        /**
         * @brief Opens the file and starts lexical analysis of the file contents.
         *
         * @param file_name - a file name.
         */
        std::vector<TokenLine> createTokens(const char* file_name);

        /**
         * @brief Starts lexical analysis of the file contents.
         *
         * @param file - a file.
         */
        std::vector<TokenLine> createTokens(std::wifstream& file);
    };
}  // namespace lexer
