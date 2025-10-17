#pragma once

#include "token.h"

#include <stdexcept>

namespace lexer {
    using lexer_contaner_t = std::vector<TokenLine>;

    /**
     * @brief A template parent class for all types of iterators.
     *
     * @tparam LineIterator - an iterator that is used to track the current line.
     * @tparam TokenIterator - an iterator that is used to track the current token.
     * @tparam Iterator - child class.
     */
    template <class LineIterator, class TokenIterator, class Iterator>
    class LexerTemplateIterator {
    protected:
        using contaner = lexer_contaner_t;
        using line_it_t = LineIterator;
        using token_it_t = TokenIterator;

        line_it_t _current_line;
        token_it_t _current_token;

        line_it_t _start_line;
        line_it_t _end_line;

        /**
         * @brief Causes an exception related to going beyond the container that stores
         * the tokens.
         *
         * @throw std::out_of_range
         */
        static void exceptionOutOfRange() {
            throw std::out_of_range("no more tokens");
        }

        /**
         * @brief Returns an iterator to the first element of the current row.
         *
         * @return token_it_t
         */
        virtual token_it_t getBegin() = 0;

    public:
        /**
         * @brief A constructor that initializes all the fields of an iterator.
         *
         * @param start_line - an iterator that points to the first row of the container.
         * @param end_line - an iterator that points to a field after the last row of a
         * container.
         * @param start_token - an iterator that points to the first token of the first
         * row of the container.
         */
        LexerTemplateIterator(const line_it_t& start_line, const line_it_t& end_line,
                              const token_it_t& start_token) :
            _start_line(start_line),
            _end_line(end_line),
            _current_line(start_line),
            _current_token(start_token) {}

        /**
         * @brief Copy constructor.
         *
         * @param other - another iterator.
         */
        LexerTemplateIterator(const LexerTemplateIterator& other) :
            _start_line(other._start_line),
            _end_line(other._end_line),
            _current_line(other._current_line),
            _current_token(other._current_token) {}

        /**
         * @brief Move constructor.
         *
         * @param other - another iterator.
         */
        LexerTemplateIterator(LexerTemplateIterator&& other) noexcept :
            _start_line(std::move(other._start_line)),
            _end_line(std::move(other._end_line)),
            _current_line(std::move(other._current_line)),
            _current_token(std::move(other._current_token)) {}

        /**
         * @brief Copy operator.
         *
         * @param other - another iterator.
         */
        LexerTemplateIterator& operator=(const LexerTemplateIterator& other) {
            _current_line = other._current_line;
            _current_token = other._current_token;
            _start_line = other._start_line;
            _end_line = other._end_line;
            return *this;
        }

        /**
         * @brief Move operator.
         *
         * @param other - another iterator.
         */
        LexerTemplateIterator& operator=(LexerTemplateIterator&& other) {
            _current_line = std::move(other._current_line);
            _current_token = std::move(other._current_token);
            _start_line = std::move(other._start_line);
            _end_line = std::move(other._end_line);
            return *this;
        }

        /**
         * @brief Moves on to the next token.
         *
         * @param it - movable iterator.
         *
         * @throw std::out_of_range
         *
         * @return Iterator&
         */
        friend Iterator& operator++(Iterator& it) {
            if (it._current_token !=
                it.getBegin() + (it._current_line->tokens.size() - 1)) {
                ++it._current_token;
            } else if (it._current_line != it._end_line) {
                ++it._current_line;
                if (it._current_line != it._end_line) {
                    it._current_token = it.getBegin();
                }
            } else {
                exceptionOutOfRange();
            }
            return it;
        }

        /**
         * @brief Moves on to the next token.
         *
         * @param it - movable iterator.
         *
         * @throw std::out_of_range
         *
         * @return Iterator&
         */
        friend Iterator operator++(Iterator& it, int) {
            auto temp = it;
            ++it;
            return temp;
        }

        /**
         * @brief Goes to the previous token.
         *
         * @param it - movable iterator.
         *
         * @throw std::out_of_range
         *
         * @return Iterator&
         */
        friend Iterator& operator--(Iterator& it) {
            if (it._current_token != it.getBegin()) {
                --it._current_token;
            } else if (it._current_line != it._end_line) {
                --it._current_line;
                if (it._current_line != it._end_line) {
                    it._current_token =
                        it.getBegin() + (it._current_line->tokens.size() - 1);
                }
            } else {
                exceptionOutOfRange();
            }
            return it;
        }

        /**
         * @brief Goes to the previous token.
         *
         * @param it - movable iterator.
         *
         * @throw std::out_of_range
         *
         * @return Iterator&
         */
        friend Iterator operator--(Iterator& it, int) {
            auto temp = it;
            --it;
            return temp;
        }

        /**
         * @brief Moves a certain number of tokens forward.
         *
         * @param start - the initial iterator.
         * @param n - the number of movements.
         *
         * @throw std::out_of_range
         *
         * @return Iterator&
         */
        friend Iterator operator+(const Iterator& start, size_t n) {
            Iterator it = start;
            while (n--) {
                ++it;
            }
            return it;
        }

        /**
         * @brief Moves a certain number of tokens back.
         *
         * @param start - the initial iterator.
         * @param n - the number of movements.
         *
         * @throw std::out_of_range
         *
         * @return Iterator&
         */
        friend Iterator operator-(const Iterator& start, size_t n) {
            Iterator it = start;
            while (n--) {
                --it;
            }
            return it;
        }

        /**
         * @brief Compares two iterators.
         * Returns "true" if both iterators point to the same token.
         * Else returns "false".
         *
         * @param l - first iterator.
         * @param r - second iterator.
         *
         * @return bool
         */
        friend bool operator==(const LexerTemplateIterator& l,
                               const LexerTemplateIterator& r) {
            return l._current_line == r._current_line &&
                   l._current_token == r._current_token;
        }

        /**
         * @brief Compares two iterators.
         * Returns "true" if the iterators point to different tokens.
         * Else returns "false".
         *
         * @param l - first iterator.
         * @param r - second iterator.
         *
         * @return bool
         */
        friend bool operator!=(const LexerTemplateIterator& l,
                               const LexerTemplateIterator& r) {
            return !(l == r);
        }

        /**
         * @brief Returns the current token.
         *
         * @return const Token&
         */
        inline const Token& operator*() const {
            return *_current_token;
        }

        /**
         * @brief Returns a pointer to the current token.
         *
         * @return const Token*
         */
        inline const Token* operator->() const {
            return &(*_current_token);
        }

        /**
         * @brief Returns the current row.
         *
         * @return TokenLine
         */
        TokenLine getLine() const {
            return *_current_line;
        }

        /**
         * @brief Returns the current token.
         *
         * @return Token
         */
        Token getToken() const {
            return *_current_token;
        }
    };

    /**
     * @brief An iterator that points to a specific token in the contaner.
     */
    class LexerIterator
        : public LexerTemplateIterator<lexer_contaner_t::iterator,
                                       TokenLine::token_contaner_t::iterator,
                                       LexerIterator> {
    public:
        /**
         * @brief A constructor that initializes fields within the constructor. Sets the
         * pointers to the first element in the container.
         *
         * @param c - contaner.
         */
        LexerIterator(contaner& c);

        /**
         * @brief Returns an iterator to the first element of the current row.
         *
         * @return token_it_t
         */
        token_it_t getBegin() override;
    };

    /**
     * @brief A constant iterator that points to a specific token in the contaner.
     */
    class LexerConstIterator
        : public LexerTemplateIterator<lexer_contaner_t::const_iterator,
                                       TokenLine::token_contaner_t::const_iterator,
                                       LexerConstIterator> {
    public:
        /**
         * @brief A constructor that initializes fields within the constructor. Sets the
         * pointers to the first element in the container.
         *
         * @param c - contaner.
         */
        LexerConstIterator(const contaner& c);

        /**
         * @brief Returns an iterator to the first element of the current row.
         *
         * @return token_it_t
         */
        token_it_t getBegin() override;
    };

    /**
     * @brief A reverse iterator that points to a specific token in the contaner.
     */
    class LexerReverseIterator
        : public LexerTemplateIterator<lexer_contaner_t::reverse_iterator,
                                       TokenLine::token_contaner_t::reverse_iterator,
                                       LexerReverseIterator> {
    public:
        /**
         * @brief A constructor that initializes fields within the constructor. Sets the
         * pointers to the last element in the container.
         *
         * @param c - contaner.
         */
        LexerReverseIterator(contaner& c);

        /**
         * @brief Returns an iterator to the first element of the current row.
         *
         * @return token_it_t
         */
        token_it_t getBegin() override;
    };

    /**
     * @brief A constant reverse iterator that points to a specific token in the contaner.
     */
    class LexerConstReverseIterator
        : public LexerTemplateIterator<
              lexer_contaner_t::const_reverse_iterator,
              TokenLine::token_contaner_t::const_reverse_iterator,
              LexerConstReverseIterator> {
    public:
        /**
         * @brief A constructor that initializes fields within the constructor. Sets the
         * pointers to the last element in the container.
         *
         * @param c - contaner.
         */
        LexerConstReverseIterator(const contaner& c);

        /**
         * @brief Returns an iterator to the first element of the current row.
         *
         * @return token_it_t
         */
        token_it_t getBegin() override;
    };
}  // namespace lexer
