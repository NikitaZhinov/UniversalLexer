#include "../include/lexer/lexer.h"

#include <gtest/gtest.h>

static const std::vector<lexer::CombiningTokens> COMBINING_TOKENS = {
    lexer::CombiningTokens { lexer::Token(L"\""), lexer::Token(L"\"") },
    lexer::CombiningTokens { lexer::Token(L"//"), lexer::Token(L"\n") },
    lexer::CombiningTokens { lexer::Token(L"/*"), lexer::Token(L"*/") }
};

static lexer::Lexer LEXER({ L"+-/*=<>!" }, L"&?;$#@^:\"'|.,(){}[]\n", COMBINING_TOKENS,
                          L" \t");

TEST(LexerTest, Test_Creating_0) {
    const std::wstring test_code = L"hello world\n";
    auto tokens = LEXER.createTokens(test_code);

    ASSERT_EQ(tokens.getSize(), 3);
    ASSERT_EQ(tokens.getTokensNumber(), 3);
    ASSERT_EQ(tokens.getLinesNumber(), 1);

    ASSERT_EQ(tokens.getLine(0).line_number, 1);
    ASSERT_EQ(tokens.getLine(0).original, L"hello world\n");
    ASSERT_EQ(tokens.getLine(0).tokens.size(), 3);
    ASSERT_EQ(tokens.getLine(0).tokens.at(0).getId(), lexer::defineTokenId(L"hello"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(0).getText(), L"hello");
    ASSERT_EQ(tokens.getLine(0).tokens.at(1).getId(), lexer::defineTokenId(L"world"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(1).getText(), L"world");
    ASSERT_EQ(tokens.getLine(0).tokens.at(2).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(2).getText(), L"\n");
}

TEST(LexerTest, Test_Creating_1) {
    const std::wstring test_code = L"10 * name\n";
    auto tokens = LEXER.createTokens(test_code);

    ASSERT_EQ(tokens.getSize(), 4);
    ASSERT_EQ(tokens.getTokensNumber(), 4);
    ASSERT_EQ(tokens.getLinesNumber(), 1);

    ASSERT_EQ(tokens.getLine(0).line_number, 1);
    ASSERT_EQ(tokens.getLine(0).original, L"10 * name\n");
    ASSERT_EQ(tokens.getLine(0).tokens.size(), 4);
    ASSERT_EQ(tokens.getLine(0).tokens.at(0).getId(), lexer::defineTokenId(L"10"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(0).getText(), L"10");
    ASSERT_EQ(tokens.getLine(0).tokens.at(1).getId(), lexer::defineTokenId(L"*"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(1).getText(), L"*");
    ASSERT_EQ(tokens.getLine(0).tokens.at(2).getId(), lexer::defineTokenId(L"name"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(2).getText(), L"name");
    ASSERT_EQ(tokens.getLine(0).tokens.at(3).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(3).getText(), L"\n");
}

TEST(LexerTest, Test_Creating_2) {
    const std::wstring test_code = L"\n";
    auto tokens = LEXER.createTokens(test_code);

    ASSERT_EQ(tokens.getSize(), 1);
    ASSERT_EQ(tokens.getTokensNumber(), 1);
    ASSERT_EQ(tokens.getLinesNumber(), 1);

    ASSERT_EQ(tokens.getLine(0).line_number, 1);
    ASSERT_EQ(tokens.getLine(0).original, L"\n");
    ASSERT_EQ(tokens.getLine(0).tokens.size(), 1);
    ASSERT_EQ(tokens.getLine(0).tokens.at(0).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(0).getText(), L"\n");
}

TEST(LexerTest, Test_Creating_3) {
    const std::wstring test_code = L"return\tfalse;\n";
    auto tokens = LEXER.createTokens(test_code);

    ASSERT_EQ(tokens.getSize(), 4);
    ASSERT_EQ(tokens.getTokensNumber(), 4);
    ASSERT_EQ(tokens.getLinesNumber(), 1);

    ASSERT_EQ(tokens.getLine(0).line_number, 1);
    ASSERT_EQ(tokens.getLine(0).original, L"return\tfalse;\n");
    ASSERT_EQ(tokens.getLine(0).tokens.size(), 4);
    ASSERT_EQ(tokens.getLine(0).tokens.at(0).getId(), lexer::defineTokenId(L"return"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(0).getText(), L"return");
    ASSERT_EQ(tokens.getLine(0).tokens.at(1).getId(), lexer::defineTokenId(L"false"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(1).getText(), L"false");
    ASSERT_EQ(tokens.getLine(0).tokens.at(2).getId(), lexer::defineTokenId(L";"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(2).getText(), L";");
    ASSERT_EQ(tokens.getLine(0).tokens.at(3).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(3).getText(), L"\n");
}

TEST(LexerTest, Test_Creating_4) {
    const std::wstring test_code = L"if (age >= 18) then goodbay!\n";
    auto tokens = LEXER.createTokens(test_code);

    ASSERT_EQ(tokens.getSize(), 10);
    ASSERT_EQ(tokens.getTokensNumber(), 10);
    ASSERT_EQ(tokens.getLinesNumber(), 1);

    ASSERT_EQ(tokens.getLine(0).line_number, 1);
    ASSERT_EQ(tokens.getLine(0).original, L"if (age >= 18) then goodbay!\n");
    ASSERT_EQ(tokens.getLine(0).tokens.size(), 10);
    ASSERT_EQ(tokens.getLine(0).tokens.at(0).getId(), lexer::defineTokenId(L"if"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(0).getText(), L"if");
    ASSERT_EQ(tokens.getLine(0).tokens.at(1).getId(), lexer::defineTokenId(L"("));
    ASSERT_EQ(tokens.getLine(0).tokens.at(1).getText(), L"(");
    ASSERT_EQ(tokens.getLine(0).tokens.at(2).getId(), lexer::defineTokenId(L"age"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(2).getText(), L"age");
    ASSERT_EQ(tokens.getLine(0).tokens.at(3).getId(), lexer::defineTokenId(L">="));
    ASSERT_EQ(tokens.getLine(0).tokens.at(3).getText(), L">=");
    ASSERT_EQ(tokens.getLine(0).tokens.at(4).getId(), lexer::defineTokenId(L"18"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(4).getText(), L"18");
    ASSERT_EQ(tokens.getLine(0).tokens.at(5).getId(), lexer::defineTokenId(L")"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(5).getText(), L")");
    ASSERT_EQ(tokens.getLine(0).tokens.at(6).getId(), lexer::defineTokenId(L"then"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(6).getText(), L"then");
    ASSERT_EQ(tokens.getLine(0).tokens.at(7).getId(), lexer::defineTokenId(L"goodbay"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(7).getText(), L"goodbay");
    ASSERT_EQ(tokens.getLine(0).tokens.at(8).getId(), lexer::defineTokenId(L"!"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(8).getText(), L"!");
    ASSERT_EQ(tokens.getLine(0).tokens.at(9).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(9).getText(), L"\n");
}

TEST(LexerTest, Test_Creating_5) {
    const std::wstring test_code = L"\"some text\"\n";
    auto tokens = LEXER.createTokens(test_code);

    ASSERT_EQ(tokens.getSize(), 4);
    ASSERT_EQ(tokens.getTokensNumber(), 4);
    ASSERT_EQ(tokens.getLinesNumber(), 1);

    ASSERT_EQ(tokens.getLine(0).line_number, 1);
    ASSERT_EQ(tokens.getLine(0).original, L"\"some text\"\n");
    ASSERT_EQ(tokens.getLine(0).tokens.size(), 4);
    ASSERT_EQ(tokens.getLine(0).tokens.at(0).getId(), lexer::defineTokenId(L"\""));
    ASSERT_EQ(tokens.getLine(0).tokens.at(0).getText(), L"\"");
    ASSERT_EQ(tokens.getLine(0).tokens.at(1).getId(), lexer::defineTokenId(L"some text"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(1).getText(), L"some text");
    ASSERT_EQ(tokens.getLine(0).tokens.at(2).getId(), lexer::defineTokenId(L"\""));
    ASSERT_EQ(tokens.getLine(0).tokens.at(2).getText(), L"\"");
    ASSERT_EQ(tokens.getLine(0).tokens.at(3).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(3).getText(), L"\n");
}

TEST(LexerTest, Test_Creating_6) {
    const std::wstring test_code = L"// some comment\n";
    auto tokens = LEXER.createTokens(test_code);

    ASSERT_EQ(tokens.getSize(), 3);
    ASSERT_EQ(tokens.getTokensNumber(), 3);
    ASSERT_EQ(tokens.getLinesNumber(), 1);

    ASSERT_EQ(tokens.getLine(0).line_number, 1);
    ASSERT_EQ(tokens.getLine(0).original, L"// some comment\n");
    ASSERT_EQ(tokens.getLine(0).tokens.size(), 3);
    ASSERT_EQ(tokens.getLine(0).tokens.at(0).getId(), lexer::defineTokenId(L"//"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(0).getText(), L"//");
    ASSERT_EQ(tokens.getLine(0).tokens.at(1).getId(),
              lexer::defineTokenId(L" some comment"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(1).getText(), L" some comment");
    ASSERT_EQ(tokens.getLine(0).tokens.at(2).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(2).getText(), L"\n");
}

TEST(LexerTest, Test_Creating_7) {
    const std::wstring test_code = L"/* one more comment\n"
                                   "next comment line*/";
    auto tokens = LEXER.createTokens(test_code);

    ASSERT_EQ(tokens.getSize(), 3);
    ASSERT_EQ(tokens.getTokensNumber(), 3);
    ASSERT_EQ(tokens.getLinesNumber(), 1);

    ASSERT_EQ(tokens.getLine(0).line_number, 1);
    ASSERT_EQ(tokens.getLine(0).original, L"/* one more comment\nnext comment line*/");
    ASSERT_EQ(tokens.getLine(0).tokens.size(), 3);
    ASSERT_EQ(tokens.getLine(0).tokens.at(0).getId(), lexer::defineTokenId(L"/*"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(0).getText(), L"/*");
    ASSERT_EQ(tokens.getLine(0).tokens.at(1).getId(),
              lexer::defineTokenId(L" one more comment\nnext comment line"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(1).getText(),
              L" one more comment\nnext comment line");
    ASSERT_EQ(tokens.getLine(0).tokens.at(2).getId(), lexer::defineTokenId(L"*/"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(2).getText(), L"*/");
}

TEST(LexerTest, Test_Creating_8_ManyRows) {
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

    ASSERT_EQ(tokens.getSize(), 32);
    ASSERT_EQ(tokens.getTokensNumber(), 32);
    ASSERT_EQ(tokens.getLinesNumber(), 8);

    ASSERT_EQ(tokens.getLine(0).line_number, 1);
    ASSERT_EQ(tokens.getLine(0).original, L"hello world\n");
    ASSERT_EQ(tokens.getLine(0).tokens.size(), 3);
    ASSERT_EQ(tokens.getLine(0).tokens.at(0).getId(), lexer::defineTokenId(L"hello"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(0).getText(), L"hello");
    ASSERT_EQ(tokens.getLine(0).tokens.at(1).getId(), lexer::defineTokenId(L"world"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(1).getText(), L"world");
    ASSERT_EQ(tokens.getLine(0).tokens.at(2).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(2).getText(), L"\n");

    ASSERT_EQ(tokens.getLine(1).line_number, 2);
    ASSERT_EQ(tokens.getLine(1).original, L"10 * name\n");
    ASSERT_EQ(tokens.getLine(1).tokens.size(), 4);
    ASSERT_EQ(tokens.getLine(1).tokens.at(0).getId(), lexer::defineTokenId(L"10"));
    ASSERT_EQ(tokens.getLine(1).tokens.at(0).getText(), L"10");
    ASSERT_EQ(tokens.getLine(1).tokens.at(1).getId(), lexer::defineTokenId(L"*"));
    ASSERT_EQ(tokens.getLine(1).tokens.at(1).getText(), L"*");
    ASSERT_EQ(tokens.getLine(1).tokens.at(2).getId(), lexer::defineTokenId(L"name"));
    ASSERT_EQ(tokens.getLine(1).tokens.at(2).getText(), L"name");
    ASSERT_EQ(tokens.getLine(1).tokens.at(3).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.getLine(1).tokens.at(3).getText(), L"\n");

    ASSERT_EQ(tokens.getLine(2).line_number, 3);
    ASSERT_EQ(tokens.getLine(2).original, L"\n");
    ASSERT_EQ(tokens.getLine(2).tokens.size(), 1);
    ASSERT_EQ(tokens.getLine(2).tokens.at(0).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.getLine(2).tokens.at(0).getText(), L"\n");

    ASSERT_EQ(tokens.getLine(3).line_number, 4);
    ASSERT_EQ(tokens.getLine(3).original, L"return\tfalse;\n");
    ASSERT_EQ(tokens.getLine(3).tokens.size(), 4);
    ASSERT_EQ(tokens.getLine(3).tokens.at(0).getId(), lexer::defineTokenId(L"return"));
    ASSERT_EQ(tokens.getLine(3).tokens.at(0).getText(), L"return");
    ASSERT_EQ(tokens.getLine(3).tokens.at(1).getId(), lexer::defineTokenId(L"false"));
    ASSERT_EQ(tokens.getLine(3).tokens.at(1).getText(), L"false");
    ASSERT_EQ(tokens.getLine(3).tokens.at(2).getId(), lexer::defineTokenId(L";"));
    ASSERT_EQ(tokens.getLine(3).tokens.at(2).getText(), L";");
    ASSERT_EQ(tokens.getLine(3).tokens.at(3).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.getLine(3).tokens.at(3).getText(), L"\n");

    ASSERT_EQ(tokens.getLine(4).line_number, 5);
    ASSERT_EQ(tokens.getLine(4).original, L"if (age >= 18) then goodbay!\n");
    ASSERT_EQ(tokens.getLine(4).tokens.size(), 10);
    ASSERT_EQ(tokens.getLine(4).tokens.at(0).getId(), lexer::defineTokenId(L"if"));
    ASSERT_EQ(tokens.getLine(4).tokens.at(0).getText(), L"if");
    ASSERT_EQ(tokens.getLine(4).tokens.at(1).getId(), lexer::defineTokenId(L"("));
    ASSERT_EQ(tokens.getLine(4).tokens.at(1).getText(), L"(");
    ASSERT_EQ(tokens.getLine(4).tokens.at(2).getId(), lexer::defineTokenId(L"age"));
    ASSERT_EQ(tokens.getLine(4).tokens.at(2).getText(), L"age");
    ASSERT_EQ(tokens.getLine(4).tokens.at(3).getId(), lexer::defineTokenId(L">="));
    ASSERT_EQ(tokens.getLine(4).tokens.at(3).getText(), L">=");
    ASSERT_EQ(tokens.getLine(4).tokens.at(4).getId(), lexer::defineTokenId(L"18"));
    ASSERT_EQ(tokens.getLine(4).tokens.at(4).getText(), L"18");
    ASSERT_EQ(tokens.getLine(4).tokens.at(5).getId(), lexer::defineTokenId(L")"));
    ASSERT_EQ(tokens.getLine(4).tokens.at(5).getText(), L")");
    ASSERT_EQ(tokens.getLine(4).tokens.at(6).getId(), lexer::defineTokenId(L"then"));
    ASSERT_EQ(tokens.getLine(4).tokens.at(6).getText(), L"then");
    ASSERT_EQ(tokens.getLine(4).tokens.at(7).getId(), lexer::defineTokenId(L"goodbay"));
    ASSERT_EQ(tokens.getLine(4).tokens.at(7).getText(), L"goodbay");
    ASSERT_EQ(tokens.getLine(4).tokens.at(8).getId(), lexer::defineTokenId(L"!"));
    ASSERT_EQ(tokens.getLine(4).tokens.at(8).getText(), L"!");
    ASSERT_EQ(tokens.getLine(4).tokens.at(9).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.getLine(4).tokens.at(9).getText(), L"\n");

    ASSERT_EQ(tokens.getLine(5).line_number, 6);
    ASSERT_EQ(tokens.getLine(5).original, L"\"some text\"\n");
    ASSERT_EQ(tokens.getLine(5).tokens.size(), 4);
    ASSERT_EQ(tokens.getLine(5).tokens.at(0).getId(), lexer::defineTokenId(L"\""));
    ASSERT_EQ(tokens.getLine(5).tokens.at(0).getText(), L"\"");
    ASSERT_EQ(tokens.getLine(5).tokens.at(1).getId(), lexer::defineTokenId(L"some text"));
    ASSERT_EQ(tokens.getLine(5).tokens.at(1).getText(), L"some text");
    ASSERT_EQ(tokens.getLine(5).tokens.at(2).getId(), lexer::defineTokenId(L"\""));
    ASSERT_EQ(tokens.getLine(5).tokens.at(2).getText(), L"\"");
    ASSERT_EQ(tokens.getLine(5).tokens.at(3).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.getLine(5).tokens.at(3).getText(), L"\n");

    ASSERT_EQ(tokens.getLine(6).line_number, 7);
    ASSERT_EQ(tokens.getLine(6).original, L"// some comment\n");
    ASSERT_EQ(tokens.getLine(6).tokens.size(), 3);
    ASSERT_EQ(tokens.getLine(6).tokens.at(0).getId(), lexer::defineTokenId(L"//"));
    ASSERT_EQ(tokens.getLine(6).tokens.at(0).getText(), L"//");
    ASSERT_EQ(tokens.getLine(6).tokens.at(1).getId(),
              lexer::defineTokenId(L" some comment"));
    ASSERT_EQ(tokens.getLine(6).tokens.at(1).getText(), L" some comment");
    ASSERT_EQ(tokens.getLine(6).tokens.at(2).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.getLine(6).tokens.at(2).getText(), L"\n");

    ASSERT_EQ(tokens.getLine(7).line_number, 8);
    ASSERT_EQ(tokens.getLine(7).original, L"/* one more comment\nnext comment line*/");
    ASSERT_EQ(tokens.getLine(7).tokens.size(), 3);
    ASSERT_EQ(tokens.getLine(7).tokens.at(0).getId(), lexer::defineTokenId(L"/*"));
    ASSERT_EQ(tokens.getLine(7).tokens.at(0).getText(), L"/*");
    ASSERT_EQ(tokens.getLine(7).tokens.at(1).getId(),
              lexer::defineTokenId(L" one more comment\nnext comment line"));
    ASSERT_EQ(tokens.getLine(7).tokens.at(1).getText(),
              L" one more comment\nnext comment line");
    ASSERT_EQ(tokens.getLine(7).tokens.at(2).getId(), lexer::defineTokenId(L"*/"));
    ASSERT_EQ(tokens.getLine(7).tokens.at(2).getText(), L"*/");
}

TEST(LexerTest, Test_Creating_9_ManyRowsFromFile) {
    std::wofstream fout("test.txt");
    fout << L"hello world\n"
            "10 * name\n"
            "\n"
            "return\tfalse;\n"
            "if (age >= 18) then goodbay!\n"
            "\"some text\"\n"
            "// some comment\n"
            "/* one more comment\n"
            "next comment line*/";
    fout.close();

    std::wifstream fin("test.txt");
    lexer::Lexer lexer({ L"+-/*=<>!" }, L"&?;$#@^:\"'|.,(){}[]\n", COMBINING_TOKENS,
                       L" \t");
    auto tokens = lexer.createTokens(fin);
    fin.close();

    ASSERT_EQ(tokens.getSize(), 32);
    ASSERT_EQ(tokens.getTokensNumber(), 32);
    ASSERT_EQ(tokens.getLinesNumber(), 8);

    ASSERT_EQ(tokens.getLine(0).line_number, 1);
    ASSERT_EQ(tokens.getLine(0).original, L"hello world\n");
    ASSERT_EQ(tokens.getLine(0).tokens.size(), 3);
    ASSERT_EQ(tokens.getLine(0).tokens.at(0).getId(), lexer::defineTokenId(L"hello"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(0).getText(), L"hello");
    ASSERT_EQ(tokens.getLine(0).tokens.at(1).getId(), lexer::defineTokenId(L"world"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(1).getText(), L"world");
    ASSERT_EQ(tokens.getLine(0).tokens.at(2).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.getLine(0).tokens.at(2).getText(), L"\n");

    ASSERT_EQ(tokens.getLine(1).line_number, 2);
    ASSERT_EQ(tokens.getLine(1).original, L"10 * name\n");
    ASSERT_EQ(tokens.getLine(1).tokens.size(), 4);
    ASSERT_EQ(tokens.getLine(1).tokens.at(0).getId(), lexer::defineTokenId(L"10"));
    ASSERT_EQ(tokens.getLine(1).tokens.at(0).getText(), L"10");
    ASSERT_EQ(tokens.getLine(1).tokens.at(1).getId(), lexer::defineTokenId(L"*"));
    ASSERT_EQ(tokens.getLine(1).tokens.at(1).getText(), L"*");
    ASSERT_EQ(tokens.getLine(1).tokens.at(2).getId(), lexer::defineTokenId(L"name"));
    ASSERT_EQ(tokens.getLine(1).tokens.at(2).getText(), L"name");
    ASSERT_EQ(tokens.getLine(1).tokens.at(3).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.getLine(1).tokens.at(3).getText(), L"\n");

    ASSERT_EQ(tokens.getLine(2).line_number, 3);
    ASSERT_EQ(tokens.getLine(2).original, L"\n");
    ASSERT_EQ(tokens.getLine(2).tokens.size(), 1);
    ASSERT_EQ(tokens.getLine(2).tokens.at(0).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.getLine(2).tokens.at(0).getText(), L"\n");

    ASSERT_EQ(tokens.getLine(3).line_number, 4);
    ASSERT_EQ(tokens.getLine(3).original, L"return\tfalse;\n");
    ASSERT_EQ(tokens.getLine(3).tokens.size(), 4);
    ASSERT_EQ(tokens.getLine(3).tokens.at(0).getId(), lexer::defineTokenId(L"return"));
    ASSERT_EQ(tokens.getLine(3).tokens.at(0).getText(), L"return");
    ASSERT_EQ(tokens.getLine(3).tokens.at(1).getId(), lexer::defineTokenId(L"false"));
    ASSERT_EQ(tokens.getLine(3).tokens.at(1).getText(), L"false");
    ASSERT_EQ(tokens.getLine(3).tokens.at(2).getId(), lexer::defineTokenId(L";"));
    ASSERT_EQ(tokens.getLine(3).tokens.at(2).getText(), L";");
    ASSERT_EQ(tokens.getLine(3).tokens.at(3).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.getLine(3).tokens.at(3).getText(), L"\n");

    ASSERT_EQ(tokens.getLine(4).line_number, 5);
    ASSERT_EQ(tokens.getLine(4).original, L"if (age >= 18) then goodbay!\n");
    ASSERT_EQ(tokens.getLine(4).tokens.size(), 10);
    ASSERT_EQ(tokens.getLine(4).tokens.at(0).getId(), lexer::defineTokenId(L"if"));
    ASSERT_EQ(tokens.getLine(4).tokens.at(0).getText(), L"if");
    ASSERT_EQ(tokens.getLine(4).tokens.at(1).getId(), lexer::defineTokenId(L"("));
    ASSERT_EQ(tokens.getLine(4).tokens.at(1).getText(), L"(");
    ASSERT_EQ(tokens.getLine(4).tokens.at(2).getId(), lexer::defineTokenId(L"age"));
    ASSERT_EQ(tokens.getLine(4).tokens.at(2).getText(), L"age");
    ASSERT_EQ(tokens.getLine(4).tokens.at(3).getId(), lexer::defineTokenId(L">="));
    ASSERT_EQ(tokens.getLine(4).tokens.at(3).getText(), L">=");
    ASSERT_EQ(tokens.getLine(4).tokens.at(4).getId(), lexer::defineTokenId(L"18"));
    ASSERT_EQ(tokens.getLine(4).tokens.at(4).getText(), L"18");
    ASSERT_EQ(tokens.getLine(4).tokens.at(5).getId(), lexer::defineTokenId(L")"));
    ASSERT_EQ(tokens.getLine(4).tokens.at(5).getText(), L")");
    ASSERT_EQ(tokens.getLine(4).tokens.at(6).getId(), lexer::defineTokenId(L"then"));
    ASSERT_EQ(tokens.getLine(4).tokens.at(6).getText(), L"then");
    ASSERT_EQ(tokens.getLine(4).tokens.at(7).getId(), lexer::defineTokenId(L"goodbay"));
    ASSERT_EQ(tokens.getLine(4).tokens.at(7).getText(), L"goodbay");
    ASSERT_EQ(tokens.getLine(4).tokens.at(8).getId(), lexer::defineTokenId(L"!"));
    ASSERT_EQ(tokens.getLine(4).tokens.at(8).getText(), L"!");
    ASSERT_EQ(tokens.getLine(4).tokens.at(9).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.getLine(4).tokens.at(9).getText(), L"\n");

    ASSERT_EQ(tokens.getLine(5).line_number, 6);
    ASSERT_EQ(tokens.getLine(5).original, L"\"some text\"\n");
    ASSERT_EQ(tokens.getLine(5).tokens.size(), 4);
    ASSERT_EQ(tokens.getLine(5).tokens.at(0).getId(), lexer::defineTokenId(L"\""));
    ASSERT_EQ(tokens.getLine(5).tokens.at(0).getText(), L"\"");
    ASSERT_EQ(tokens.getLine(5).tokens.at(1).getId(), lexer::defineTokenId(L"some text"));
    ASSERT_EQ(tokens.getLine(5).tokens.at(1).getText(), L"some text");
    ASSERT_EQ(tokens.getLine(5).tokens.at(2).getId(), lexer::defineTokenId(L"\""));
    ASSERT_EQ(tokens.getLine(5).tokens.at(2).getText(), L"\"");
    ASSERT_EQ(tokens.getLine(5).tokens.at(3).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.getLine(5).tokens.at(3).getText(), L"\n");

    ASSERT_EQ(tokens.getLine(6).line_number, 7);
    ASSERT_EQ(tokens.getLine(6).original, L"// some comment\n");
    ASSERT_EQ(tokens.getLine(6).tokens.size(), 3);
    ASSERT_EQ(tokens.getLine(6).tokens.at(0).getId(), lexer::defineTokenId(L"//"));
    ASSERT_EQ(tokens.getLine(6).tokens.at(0).getText(), L"//");
    ASSERT_EQ(tokens.getLine(6).tokens.at(1).getId(),
              lexer::defineTokenId(L" some comment"));
    ASSERT_EQ(tokens.getLine(6).tokens.at(1).getText(), L" some comment");
    ASSERT_EQ(tokens.getLine(6).tokens.at(2).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.getLine(6).tokens.at(2).getText(), L"\n");

    ASSERT_EQ(tokens.getLine(7).line_number, 8);
    ASSERT_EQ(tokens.getLine(7).original, L"/* one more comment\nnext comment line*/");
    ASSERT_EQ(tokens.getLine(7).tokens.size(), 3);
    ASSERT_EQ(tokens.getLine(7).tokens.at(0).getId(), lexer::defineTokenId(L"/*"));
    ASSERT_EQ(tokens.getLine(7).tokens.at(0).getText(), L"/*");
    ASSERT_EQ(tokens.getLine(7).tokens.at(1).getId(),
              lexer::defineTokenId(L" one more comment\nnext comment line"));
    ASSERT_EQ(tokens.getLine(7).tokens.at(1).getText(),
              L" one more comment\nnext comment line");
    ASSERT_EQ(tokens.getLine(7).tokens.at(2).getId(), lexer::defineTokenId(L"*/"));
    ASSERT_EQ(tokens.getLine(7).tokens.at(2).getText(), L"*/");
}
