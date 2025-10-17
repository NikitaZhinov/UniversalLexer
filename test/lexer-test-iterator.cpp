#include "../include/lexer/lexer.h"

#include <gtest/gtest.h>

static const std::vector<lexer::CombiningTokens> COMBINING_TOKENS = {
    lexer::CombiningTokens { lexer::Token(L"\""), lexer::Token(L"\"") },
    lexer::CombiningTokens { lexer::Token(L"//"), lexer::Token(L"\n") },
    lexer::CombiningTokens { lexer::Token(L"/*"), lexer::Token(L"*/") }
};

static lexer::Lexer LEXER({ L"+-/*=<>!" }, L"&?;$#@^:\"'|.,(){}[]\n", COMBINING_TOKENS,
                          L" \t");

TEST(TestLexer, Test_Iterator_0) {
    const std::wstring test_code = L"hello world\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"hello"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L"world"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_Iterator_1) {
    const std::wstring test_code = L"10 * name\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"10"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L"*"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"name"));
                break;
            case 3:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_Iterator_2) {
    const std::wstring test_code = L"\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_Iterator_3) {
    const std::wstring test_code = L"return\tfalse;\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"return"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L"false"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L";"));
                break;
            case 3:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_Iterator_4) {
    const std::wstring test_code = L"if (age >= 18) then goodbay!\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"if"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L"("));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"age"));
                break;
            case 3:
                ASSERT_EQ(*it, lexer::Token(L">="));
                break;
            case 4:
                ASSERT_EQ(*it, lexer::Token(L"18"));
                break;
            case 5:
                ASSERT_EQ(*it, lexer::Token(L")"));
                break;
            case 6:
                ASSERT_EQ(*it, lexer::Token(L"then"));
                break;
            case 7:
                ASSERT_EQ(*it, lexer::Token(L"goodbay"));
                break;
            case 8:
                ASSERT_EQ(*it, lexer::Token(L"!"));
                break;
            case 9:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_Iterator_5) {
    const std::wstring test_code = L"\"some text\"\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"\""));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L"some text"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"\""));
                break;
            case 3:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_Iterator_6) {
    const std::wstring test_code = L"// some comment\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"//"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L" some comment"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_Iterator_7) {
    const std::wstring test_code = L"/* one more comment\n"
                                   "next comment line*/";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"/*"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L" one more comment\nnext comment line"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"*/"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_Iterator_All) {
    const std::wstring test_code = L"hello world\n"
                                   "10 * name\n"
                                   "\n"
                                   "return\tfalse;\n"
                                   "if (age >= 18) then goodbay!\n"
                                   "\"some text\"\n"
                                   "// some comment\n"
                                   "/* one more comment\n"
                                   "next comment line*/";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"hello"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L"world"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 3:
                ASSERT_EQ(*it, lexer::Token(L"10"));
                break;
            case 4:
                ASSERT_EQ(*it, lexer::Token(L"*"));
                break;
            case 5:
                ASSERT_EQ(*it, lexer::Token(L"name"));
                break;
            case 6:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 7:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 8:
                ASSERT_EQ(*it, lexer::Token(L"return"));
                break;
            case 9:
                ASSERT_EQ(*it, lexer::Token(L"false"));
                break;
            case 10:
                ASSERT_EQ(*it, lexer::Token(L";"));
                break;
            case 11:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 12:
                ASSERT_EQ(*it, lexer::Token(L"if"));
                break;
            case 13:
                ASSERT_EQ(*it, lexer::Token(L"("));
                break;
            case 14:
                ASSERT_EQ(*it, lexer::Token(L"age"));
                break;
            case 15:
                ASSERT_EQ(*it, lexer::Token(L">="));
                break;
            case 16:
                ASSERT_EQ(*it, lexer::Token(L"18"));
                break;
            case 17:
                ASSERT_EQ(*it, lexer::Token(L")"));
                break;
            case 18:
                ASSERT_EQ(*it, lexer::Token(L"then"));
                break;
            case 19:
                ASSERT_EQ(*it, lexer::Token(L"goodbay"));
                break;
            case 20:
                ASSERT_EQ(*it, lexer::Token(L"!"));
                break;
            case 21:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 22:
                ASSERT_EQ(*it, lexer::Token(L"\""));
                break;
            case 23:
                ASSERT_EQ(*it, lexer::Token(L"some text"));
                break;
            case 24:
                ASSERT_EQ(*it, lexer::Token(L"\""));
                break;
            case 25:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 26:
                ASSERT_EQ(*it, lexer::Token(L"//"));
                break;
            case 27:
                ASSERT_EQ(*it, lexer::Token(L" some comment"));
                break;
            case 28:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 29:
                ASSERT_EQ(*it, lexer::Token(L"/*"));
                break;
            case 30:
                ASSERT_EQ(*it, lexer::Token(L" one more comment\nnext comment line"));
                break;
            case 31:
                ASSERT_EQ(*it, lexer::Token(L"*/"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ConstIterator_0) {
    const std::wstring test_code = L"hello world\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"hello"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L"world"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ConstIterator_1) {
    const std::wstring test_code = L"10 * name\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.cbegin(); it != tokens.cend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"10"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L"*"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"name"));
                break;
            case 3:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ConstIterator_2) {
    const std::wstring test_code = L"\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.cbegin(); it != tokens.cend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ConstIterator_3) {
    const std::wstring test_code = L"return\tfalse;\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.cbegin(); it != tokens.cend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"return"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L"false"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L";"));
                break;
            case 3:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ConstIterator_4) {
    const std::wstring test_code = L"if (age >= 18) then goodbay!\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.cbegin(); it != tokens.cend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"if"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L"("));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"age"));
                break;
            case 3:
                ASSERT_EQ(*it, lexer::Token(L">="));
                break;
            case 4:
                ASSERT_EQ(*it, lexer::Token(L"18"));
                break;
            case 5:
                ASSERT_EQ(*it, lexer::Token(L")"));
                break;
            case 6:
                ASSERT_EQ(*it, lexer::Token(L"then"));
                break;
            case 7:
                ASSERT_EQ(*it, lexer::Token(L"goodbay"));
                break;
            case 8:
                ASSERT_EQ(*it, lexer::Token(L"!"));
                break;
            case 9:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ConstIterator_5) {
    const std::wstring test_code = L"\"some text\"\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.cbegin(); it != tokens.cend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"\""));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L"some text"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"\""));
                break;
            case 3:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ConstIterator_6) {
    const std::wstring test_code = L"// some comment\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.cbegin(); it != tokens.cend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"//"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L" some comment"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ConstIterator_7) {
    const std::wstring test_code = L"/* one more comment\n"
                                   "next comment line*/";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.cbegin(); it != tokens.cend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"/*"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L" one more comment\nnext comment line"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"*/"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ConstIterator_All) {
    const std::wstring test_code = L"hello world\n"
                                   "10 * name\n"
                                   "\n"
                                   "return\tfalse;\n"
                                   "if (age >= 18) then goodbay!\n"
                                   "\"some text\"\n"
                                   "// some comment\n"
                                   "/* one more comment\n"
                                   "next comment line*/";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.cbegin(); it != tokens.cend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"hello"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L"world"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 3:
                ASSERT_EQ(*it, lexer::Token(L"10"));
                break;
            case 4:
                ASSERT_EQ(*it, lexer::Token(L"*"));
                break;
            case 5:
                ASSERT_EQ(*it, lexer::Token(L"name"));
                break;
            case 6:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 7:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 8:
                ASSERT_EQ(*it, lexer::Token(L"return"));
                break;
            case 9:
                ASSERT_EQ(*it, lexer::Token(L"false"));
                break;
            case 10:
                ASSERT_EQ(*it, lexer::Token(L";"));
                break;
            case 11:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 12:
                ASSERT_EQ(*it, lexer::Token(L"if"));
                break;
            case 13:
                ASSERT_EQ(*it, lexer::Token(L"("));
                break;
            case 14:
                ASSERT_EQ(*it, lexer::Token(L"age"));
                break;
            case 15:
                ASSERT_EQ(*it, lexer::Token(L">="));
                break;
            case 16:
                ASSERT_EQ(*it, lexer::Token(L"18"));
                break;
            case 17:
                ASSERT_EQ(*it, lexer::Token(L")"));
                break;
            case 18:
                ASSERT_EQ(*it, lexer::Token(L"then"));
                break;
            case 19:
                ASSERT_EQ(*it, lexer::Token(L"goodbay"));
                break;
            case 20:
                ASSERT_EQ(*it, lexer::Token(L"!"));
                break;
            case 21:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 22:
                ASSERT_EQ(*it, lexer::Token(L"\""));
                break;
            case 23:
                ASSERT_EQ(*it, lexer::Token(L"some text"));
                break;
            case 24:
                ASSERT_EQ(*it, lexer::Token(L"\""));
                break;
            case 25:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 26:
                ASSERT_EQ(*it, lexer::Token(L"//"));
                break;
            case 27:
                ASSERT_EQ(*it, lexer::Token(L" some comment"));
                break;
            case 28:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 29:
                ASSERT_EQ(*it, lexer::Token(L"/*"));
                break;
            case 30:
                ASSERT_EQ(*it, lexer::Token(L" one more comment\nnext comment line"));
                break;
            case 31:
                ASSERT_EQ(*it, lexer::Token(L"*/"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ReverseIterator_0) {
    const std::wstring test_code = L"hello world\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.rbegin(); it != tokens.rend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L"world"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"hello"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ReverseIterator_1) {
    const std::wstring test_code = L"10 * name\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.rbegin(); it != tokens.rend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L"name"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"*"));
                break;
            case 3:
                ASSERT_EQ(*it, lexer::Token(L"10"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ReverseIterator_2) {
    const std::wstring test_code = L"\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.rbegin(); it != tokens.rend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ReverseIterator_3) {
    const std::wstring test_code = L"return\tfalse;\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.rbegin(); it != tokens.rend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L";"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"false"));
                break;
            case 3:
                ASSERT_EQ(*it, lexer::Token(L"return"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ReverseIterator_4) {
    const std::wstring test_code = L"if (age >= 18) then goodbay!\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.rbegin(); it != tokens.rend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L"!"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"goodbay"));
                break;
            case 3:
                ASSERT_EQ(*it, lexer::Token(L"then"));
                break;
            case 4:
                ASSERT_EQ(*it, lexer::Token(L")"));
                break;
            case 5:
                ASSERT_EQ(*it, lexer::Token(L"18"));
                break;
            case 6:
                ASSERT_EQ(*it, lexer::Token(L">="));
                break;
            case 7:
                ASSERT_EQ(*it, lexer::Token(L"age"));
                break;
            case 8:
                ASSERT_EQ(*it, lexer::Token(L"("));
                break;
            case 9:
                ASSERT_EQ(*it, lexer::Token(L"if"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ReverseIterator_5) {
    const std::wstring test_code = L"\"some text\"\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.rbegin(); it != tokens.rend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L"\""));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"some text"));
                break;
            case 3:
                ASSERT_EQ(*it, lexer::Token(L"\""));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ReverseIterator_6) {
    const std::wstring test_code = L"// some comment\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.rbegin(); it != tokens.rend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L" some comment"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"//"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ReverseIterator_7) {
    const std::wstring test_code = L"/* one more comment\n"
                                   "next comment line*/";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.rbegin(); it != tokens.rend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"*/"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L" one more comment\nnext comment line"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"/*"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ReverseIterator_All) {
    const std::wstring test_code = L"hello world\n"
                                   "10 * name\n"
                                   "\n"
                                   "return\tfalse;\n"
                                   "if (age >= 18) then goodbay!\n"
                                   "\"some text\"\n"
                                   "// some comment\n"
                                   "/* one more comment\n"
                                   "next comment line*/";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.rbegin(); it != tokens.rend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"*/"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L" one more comment\nnext comment line"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"/*"));
                break;
            case 3:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 4:
                ASSERT_EQ(*it, lexer::Token(L" some comment"));
                break;
            case 5:
                ASSERT_EQ(*it, lexer::Token(L"//"));
                break;
            case 6:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 7:
                ASSERT_EQ(*it, lexer::Token(L"\""));
                break;
            case 8:
                ASSERT_EQ(*it, lexer::Token(L"some text"));
                break;
            case 9:
                ASSERT_EQ(*it, lexer::Token(L"\""));
                break;
            case 10:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 11:
                ASSERT_EQ(*it, lexer::Token(L"!"));
                break;
            case 12:
                ASSERT_EQ(*it, lexer::Token(L"goodbay"));
                break;
            case 13:
                ASSERT_EQ(*it, lexer::Token(L"then"));
                break;
            case 14:
                ASSERT_EQ(*it, lexer::Token(L")"));
                break;
            case 15:
                ASSERT_EQ(*it, lexer::Token(L"18"));
                break;
            case 16:
                ASSERT_EQ(*it, lexer::Token(L">="));
                break;
            case 17:
                ASSERT_EQ(*it, lexer::Token(L"age"));
                break;
            case 18:
                ASSERT_EQ(*it, lexer::Token(L"("));
                break;
            case 19:
                ASSERT_EQ(*it, lexer::Token(L"if"));
                break;
            case 20:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 21:
                ASSERT_EQ(*it, lexer::Token(L";"));
                break;
            case 22:
                ASSERT_EQ(*it, lexer::Token(L"false"));
                break;
            case 23:
                ASSERT_EQ(*it, lexer::Token(L"return"));
                break;
            case 24:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 25:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 26:
                ASSERT_EQ(*it, lexer::Token(L"name"));
                break;
            case 27:
                ASSERT_EQ(*it, lexer::Token(L"*"));
                break;
            case 28:
                ASSERT_EQ(*it, lexer::Token(L"10"));
                break;
            case 29:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 30:
                ASSERT_EQ(*it, lexer::Token(L"world"));
                break;
            case 31:
                ASSERT_EQ(*it, lexer::Token(L"hello"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ConstReverseIterator_0) {
    const std::wstring test_code = L"hello world\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.crbegin(); it != tokens.crend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L"world"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"hello"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ConstReverseIterator_1) {
    const std::wstring test_code = L"10 * name\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.crbegin(); it != tokens.crend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L"name"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"*"));
                break;
            case 3:
                ASSERT_EQ(*it, lexer::Token(L"10"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ConstReverseIterator_2) {
    const std::wstring test_code = L"\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.crbegin(); it != tokens.crend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ConstReverseIterator_3) {
    const std::wstring test_code = L"return\tfalse;\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.crbegin(); it != tokens.crend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L";"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"false"));
                break;
            case 3:
                ASSERT_EQ(*it, lexer::Token(L"return"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ConstReverseIterator_4) {
    const std::wstring test_code = L"if (age >= 18) then goodbay!\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.crbegin(); it != tokens.crend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L"!"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"goodbay"));
                break;
            case 3:
                ASSERT_EQ(*it, lexer::Token(L"then"));
                break;
            case 4:
                ASSERT_EQ(*it, lexer::Token(L")"));
                break;
            case 5:
                ASSERT_EQ(*it, lexer::Token(L"18"));
                break;
            case 6:
                ASSERT_EQ(*it, lexer::Token(L">="));
                break;
            case 7:
                ASSERT_EQ(*it, lexer::Token(L"age"));
                break;
            case 8:
                ASSERT_EQ(*it, lexer::Token(L"("));
                break;
            case 9:
                ASSERT_EQ(*it, lexer::Token(L"if"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ConstReverseIterator_5) {
    const std::wstring test_code = L"\"some text\"\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.crbegin(); it != tokens.crend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L"\""));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"some text"));
                break;
            case 3:
                ASSERT_EQ(*it, lexer::Token(L"\""));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ConstReverseIterator_6) {
    const std::wstring test_code = L"// some comment\n";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.crbegin(); it != tokens.crend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L" some comment"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"//"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ConstReverseIterator_7) {
    const std::wstring test_code = L"/* one more comment\n"
                                   "next comment line*/";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.crbegin(); it != tokens.crend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"*/"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L" one more comment\nnext comment line"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"/*"));
                break;
            default:
                break;
        }

        ++i;
    }
}

TEST(TestLexer, Test_ConstReverseIterator_All) {
    const std::wstring test_code = L"hello world\n"
                                   "10 * name\n"
                                   "\n"
                                   "return\tfalse;\n"
                                   "if (age >= 18) then goodbay!\n"
                                   "\"some text\"\n"
                                   "// some comment\n"
                                   "/* one more comment\n"
                                   "next comment line*/";
    auto tokens = LEXER.createTokens(test_code);

    size_t i = 0;
    for (auto it = tokens.crbegin(); it != tokens.crend(); ++it) {
        switch (i) {
            case 0:
                ASSERT_EQ(*it, lexer::Token(L"*/"));
                break;
            case 1:
                ASSERT_EQ(*it, lexer::Token(L" one more comment\nnext comment line"));
                break;
            case 2:
                ASSERT_EQ(*it, lexer::Token(L"/*"));
                break;
            case 3:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 4:
                ASSERT_EQ(*it, lexer::Token(L" some comment"));
                break;
            case 5:
                ASSERT_EQ(*it, lexer::Token(L"//"));
                break;
            case 6:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 7:
                ASSERT_EQ(*it, lexer::Token(L"\""));
                break;
            case 8:
                ASSERT_EQ(*it, lexer::Token(L"some text"));
                break;
            case 9:
                ASSERT_EQ(*it, lexer::Token(L"\""));
                break;
            case 10:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 11:
                ASSERT_EQ(*it, lexer::Token(L"!"));
                break;
            case 12:
                ASSERT_EQ(*it, lexer::Token(L"goodbay"));
                break;
            case 13:
                ASSERT_EQ(*it, lexer::Token(L"then"));
                break;
            case 14:
                ASSERT_EQ(*it, lexer::Token(L")"));
                break;
            case 15:
                ASSERT_EQ(*it, lexer::Token(L"18"));
                break;
            case 16:
                ASSERT_EQ(*it, lexer::Token(L">="));
                break;
            case 17:
                ASSERT_EQ(*it, lexer::Token(L"age"));
                break;
            case 18:
                ASSERT_EQ(*it, lexer::Token(L"("));
                break;
            case 19:
                ASSERT_EQ(*it, lexer::Token(L"if"));
                break;
            case 20:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 21:
                ASSERT_EQ(*it, lexer::Token(L";"));
                break;
            case 22:
                ASSERT_EQ(*it, lexer::Token(L"false"));
                break;
            case 23:
                ASSERT_EQ(*it, lexer::Token(L"return"));
                break;
            case 24:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 25:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 26:
                ASSERT_EQ(*it, lexer::Token(L"name"));
                break;
            case 27:
                ASSERT_EQ(*it, lexer::Token(L"*"));
                break;
            case 28:
                ASSERT_EQ(*it, lexer::Token(L"10"));
                break;
            case 29:
                ASSERT_EQ(*it, lexer::Token(L"\n"));
                break;
            case 30:
                ASSERT_EQ(*it, lexer::Token(L"world"));
                break;
            case 31:
                ASSERT_EQ(*it, lexer::Token(L"hello"));
                break;
            default:
                break;
        }

        ++i;
    }
}
