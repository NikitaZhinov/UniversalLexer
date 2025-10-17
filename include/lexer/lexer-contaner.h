#include "lexer-iterator.h"

namespace lexer {
    /**
     * @brief It serves as a token storage.
     */
    class LexerContaner {
        lexer_contaner_t _contaner;
        size_t _size;

        void _countSize();

    public:
        /**
         * @brief Default constructor.
         */
        LexerContaner();

        /**
         * @brief Copy constructor.
         *
         * @param other - another container.
         */
        LexerContaner(const LexerContaner& other);

        /**
         * @brief Move constructor.
         *
         * @param other - another container.
         */
        LexerContaner(LexerContaner&& other) noexcept;

        /**
         * @brief Copies the token storage.
         *
         * @param contaner - another the token storage.
         */
        LexerContaner(const lexer_contaner_t& contaner);

        /**
         * @brief Moves the token storage.
         *
         * @param contaner - another the token storage.
         */
        LexerContaner(lexer_contaner_t&& contaner);

        /**
         * @brief Copy operator.
         *
         * @param other - another container.
         *
         * @return LexerContaner&
         */
        LexerContaner& operator=(const LexerContaner& other);

        /**
         * @brief Move operator.
         *
         * @param other - another container.
         *
         * @return LexerContaner&
         */
        LexerContaner& operator=(LexerContaner&& other) noexcept;

        /**
         * @brief Copies the token storage.
         *
         * @param contaner - another the token storage.
         *
         * @return LexerContaner&
         */
        LexerContaner& operator=(const lexer_contaner_t& contaner);

        /**
         * @brief Moves the token storage.
         *
         * @param contaner - another the token storage.
         *
         * @return LexerContaner&
         */
        LexerContaner& operator=(lexer_contaner_t&& contaner) noexcept;

        /**
         * @brief Returns an iterator on the first element.
         *
         * @return LexerIterator
         */
        LexerIterator begin();

        /**
         * @brief Returns a constant iterator on the first element.
         *
         * @return LexerConstIterator
         */
        LexerConstIterator begin() const;

        /**
         * @brief Returns a constant iterator on the first element.
         *
         * @return LexerConstIterator
         */
        LexerConstIterator cbegin() const;

        /**
         * @brief Returns an iterator to the field after the last element.
         *
         * @return LexerIterator
         */
        LexerIterator end();

        /**
         * @brief Returns a constant iterator to the field after the last element.
         *
         * @return LexerConstIterator
         */
        LexerConstIterator end() const;

        /**
         * @brief Returns a constant iterator to the field after the last element.
         *
         * @return LexerConstIterator
         */
        LexerConstIterator cend() const;

        /**
         * @brief Returns a reverse iterator on the last element.
         *
         * @return LexerReverseIterator
         */
        LexerReverseIterator rbegin();

        /**
         * @brief Returns a constant reverse iterator on the last element.
         *
         * @return LexerConstReverseIterator
         */
        LexerConstReverseIterator rbegin() const;

        /**
         * @brief Returns a constant reverse iterator on the last element.
         *
         * @return LexerConstReverseIterator
         */
        LexerConstReverseIterator crbegin() const;

        /**
         * @brief Returns a reverse iterator to the field before the first element.
         *
         * @return LexerReverseIterator
         */
        LexerReverseIterator rend();

        /**
         * @brief Returns a constant iterator to the field before the first element.
         *
         * @return LexerConstReverseIterator
         */
        LexerConstReverseIterator rend() const;

        /**
         * @brief Returns a constant iterator to the field before the first element.
         *
         * @return LexerConstReverseIterator
         */
        LexerConstReverseIterator crend() const;

        /**
         * @brief Returns a row of tokens.
         *
         * @param i - row index.
         *
         * @return TokenLine&
         */
        TokenLine& getLine(size_t i);

        /**
         * @brief Returns a row of tokens.
         *
         * @param i - row index.
         *
         * @return const TokenLine&
         */
        const TokenLine& getLine(size_t i) const;

        /**
         * @brief Returns a row of tokens.
         *
         * @param i - row index.
         *
         * @return TokenLine&
         */
        TokenLine& operator[](size_t i);

        /**
         * @brief Returns a row of tokens.
         *
         * @param i - row index.
         *
         * @return const TokenLine&
         */
        const TokenLine& operator[](size_t i) const;

        /**
         * @brief Returns the stored number of tokens.
         *
         * @return size_t
         */
        size_t getSize() const;

        /**
         * @brief Returns the stored number of tokens.
         *
         * @return size_t
         */
        size_t getTokensNumber() const;

        /**
         * @brief Returns the number of stored rows with tokens.
         *
         * @return size_t
         */
        size_t getLinesNumber() const;
    };
}  // namespace lexer
