#pragma once

#include <string>
#include <functional>

namespace lexer {
    /**
     * @brief Calculates the hash of the token.
     * Use FNV-1a.
     *
     * @param token - the text of the token.
     *
     * @return std::uint64_t
     */
    template <class INT = uint64_t> constexpr INT defineTokenId(const wchar_t* token) {
        INT hash = 0xcbf29ce484222325;
        if constexpr (sizeof(INT) == 4) {
            hash = 0x811c9dc5;
        }
        for (std::size_t i = 0; token[i] != L'\0'; ++i) {
            hash ^= static_cast<INT>(token[i]);
            if constexpr (sizeof(INT) == 4) {
                hash *= 0x01000193;
            } else {
                hash *= 0x100000001b3;
            }
        }
        return hash;
    }

    class Token {
    public:
        using define_id_func_t = std::function<std::uint64_t(const wchar_t*)>;

    private:
        std::uint64_t _id;

        std::wstring _text;

        define_id_func_t _defineId;

        void _updateId();

    public:
        /**
         * @brief Sets id = 0 and text = ""
         */
        Token();

        /**
         * @brief Sets id = 0 and text.
         *
         * @param text - a token text.
         */
        Token(const std::wstring& text);

        /**
         * @brief Sets id = 0, text = "" and defineId.
         *
         * @param defineId - a function for identifying tokens.
         */
        Token(define_id_func_t defineId);

        /**
         * @brief Sets id = 0, text and defineId.
         *
         * @param defineId - a function for identifying tokens.
         * @param text - a token text.
         */
        Token(define_id_func_t defineId, const std::wstring& text);

        /**
         * @brief Copy constructor.
         *
         * @param other - another token.
         */
        Token(const Token& other);

        /**
         * @brief Move constructor.
         *
         * @param other - another token.
         */
        Token(Token&& other) noexcept;

        /**
         * @brief Sets a token text.
         *
         * @param new_text - a new token text.
         */
        void setText(const std::wstring& new_text);

        /**
         * @brief Sets a token text.
         *
         * @param new_text - a new token text.
         */
        void setText(std::wstring&& new_text) noexcept;

        /**
         * @brief Return token id.
         *
         * @return std::uint64_t
         */
        std::uint64_t getId() const;

        /**
         * @brief Return token text.
         *
         * @return std::wstring
         */
        std::wstring getText() const;

        /**
         * @brief Copy constructor.
         *
         * @param right - another token.
         */
        Token& operator=(const Token& right);

        /**
         * @brief Move constructor.
         *
         * @param right - another token.
         */
        Token& operator=(Token&& right) noexcept;

        /**
         * @brief Compares the text of the tokens.
         *
         * @param left - left token.
         * @param right - right token.
         *
         * @return bool
         */
        friend bool operator==(const Token& left, const Token& right);

        /**
         * @brief Compares the text of the tokens.
         *
         * @param left - left token.
         * @param right - right token.
         *
         * @return bool
         */
        friend bool operator!=(const Token& left, const Token& right);
    };

    /**
     * @brief Defines a string of tokens.
     * In addition to the tokens themselves, the row number and the original row are
     * stored.
     */
    struct TokenLine {
        /**
         * @brief The row number.
         */
        std::size_t line_number;

        /**
         * @brief The original row.
         */
        std::wstring original;

        /**
         * @brief List of tokens.
         */
        std::vector<Token> tokens;

        /**
         * @brief Sets line_number = 0.
         */
        TokenLine();

        /**
         * @brief Sets line_number, original and tokens.
         *
         * @param line_number - a line number.
         * @param original - a original row.
         * @param tokens - a list of tokens.
         */
        TokenLine(std::size_t line_number, const std::wstring& original,
                  const std::vector<Token>& tokens);

        /**
         * @brief Copy constructor.
         *
         * @param other - another TokenLine.
         */
        TokenLine(const TokenLine& other);

        /**
         * @brief Move constructor.
         *
         * @param other - another TokenLine.
         */
        TokenLine(TokenLine&& other) noexcept;

        /**
         * @brief Copy operator.
         *
         * @param right - another TokenLine.
         */
        TokenLine& operator=(const TokenLine& right);

        /**
         * @brief Move operator.
         *
         * @param right - another TokenLine.
         */
        TokenLine& operator=(TokenLine&& right) noexcept;

        /**
         * @brief Compares the TokenLines.
         *
         * @param left - left TokenLine.
         * @param right - right TokenLine.
         *
         * @return bool
         */
        friend bool operator==(const TokenLine& left, const TokenLine& right);

        /**
         * @brief Compares the TokenLines.
         *
         * @param left - left TokenLine.
         * @param right - right TokenLine.
         *
         * @return bool
         */
        friend bool operator!=(const TokenLine& left, const TokenLine& right);
    };

    /**
     * @brief Defines the combining tokens.
     */
    struct CombiningTokens {
        /**
         * @brief The initial token.
         */
        Token start;

        /**
         * @brief The final token.
         */
        Token end;

        /**
         * Init start and end tokens.
         *
         * @param start - the initial token.
         * @param end - the final token.
         */
        CombiningTokens(const Token& start, const Token& end);

        /**
         * @brief Copy constructor.
         *
         * @param other - another CombiningTokens.
         */
        CombiningTokens(const CombiningTokens& other);

        /**
         * @brief Move constructor.
         *
         * @param other - another CombiningTokens.
         */
        CombiningTokens(CombiningTokens&& other) noexcept;

        /**
         * @brief Copy operator.
         *
         * @param right - another CombiningTokens.
         */
        CombiningTokens& operator=(const CombiningTokens& right);

        /**
         * @brief Move operator.
         *
         * @param right - another CombiningTokens.
         */
        CombiningTokens& operator=(CombiningTokens&& right) noexcept;

        /**
         * @brief Compares the CombiningTokens.
         *
         * @param left - left CombiningTokens.
         * @param right - right CombiningTokens.
         *
         * @return bool
         */
        friend bool operator==(const CombiningTokens& left, const CombiningTokens& right);

        /**
         * @brief Compares the CombiningTokens.
         *
         * @param left - left CombiningTokens.
         * @param right - right CombiningTokens.
         *
         * @return bool
         */
        friend bool operator!=(const CombiningTokens& left, const CombiningTokens& right);
    };
}  // namespace lexer
