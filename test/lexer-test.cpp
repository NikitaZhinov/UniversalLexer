#include "../include/lexer/lexer.h"

#include <gtest/gtest.h>

TEST(LexerTest, Test_0) {
    std::vector<lexer::CombiningTokens> combining_tokens = {
        lexer::CombiningTokens { lexer::Token(L"\""), lexer::Token(L"\"") },
        lexer::CombiningTokens { lexer::Token(L"//"), lexer::Token(L"\n") },
        lexer::CombiningTokens { lexer::Token(L"/*"), lexer::Token(L"*/") }
    };

    std::wofstream file_out("test.txt");
    file_out << L"hello world\n"
                "10 * name\n"
                "\n"
                "return\tfalse;\n"
                "if (age >= 18) then goodbay!\n"
                "\"some text\"\n"
                "// some comment\n"
                "/* one more comment\n"
                "next comment line*/";
    file_out.close();

    std::wifstream file("test.txt");

    lexer::Lexer lexer({ L"+-/*=<>!" }, L"&?;$#@^:\"'|.,(){}[]\n", combining_tokens,
                       L" \t");
    auto tokens = lexer.createTokens(file);

    file.close();

    ASSERT_EQ(tokens.size(), 8);

    ASSERT_EQ(tokens.at(0).line_number, 1);
    ASSERT_EQ(tokens.at(0).original, L"hello world\n");
    ASSERT_EQ(tokens.at(0).tokens.size(), 3);
    ASSERT_EQ(tokens.at(0).tokens.at(0).getId(), lexer::defineTokenId(L"hello"));
    ASSERT_EQ(tokens.at(0).tokens.at(0).getText(), L"hello");
    ASSERT_EQ(tokens.at(0).tokens.at(1).getId(), lexer::defineTokenId(L"world"));
    ASSERT_EQ(tokens.at(0).tokens.at(1).getText(), L"world");
    ASSERT_EQ(tokens.at(0).tokens.at(2).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.at(0).tokens.at(2).getText(), L"\n");

    ASSERT_EQ(tokens.at(1).line_number, 2);
    ASSERT_EQ(tokens.at(1).original, L"10 * name\n");
    ASSERT_EQ(tokens.at(1).tokens.size(), 4);
    ASSERT_EQ(tokens.at(1).tokens.at(0).getId(), lexer::defineTokenId(L"10"));
    ASSERT_EQ(tokens.at(1).tokens.at(0).getText(), L"10");
    ASSERT_EQ(tokens.at(1).tokens.at(1).getId(), lexer::defineTokenId(L"*"));
    ASSERT_EQ(tokens.at(1).tokens.at(1).getText(), L"*");
    ASSERT_EQ(tokens.at(1).tokens.at(2).getId(), lexer::defineTokenId(L"name"));
    ASSERT_EQ(tokens.at(1).tokens.at(2).getText(), L"name");
    ASSERT_EQ(tokens.at(1).tokens.at(3).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.at(1).tokens.at(3).getText(), L"\n");

    ASSERT_EQ(tokens.at(2).line_number, 3);
    ASSERT_EQ(tokens.at(2).original, L"\n");
    ASSERT_EQ(tokens.at(2).tokens.size(), 1);
    ASSERT_EQ(tokens.at(2).tokens.at(0).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.at(2).tokens.at(0).getText(), L"\n");

    ASSERT_EQ(tokens.at(3).line_number, 4);
    ASSERT_EQ(tokens.at(3).original, L"return\tfalse;\n");
    ASSERT_EQ(tokens.at(3).tokens.size(), 4);
    ASSERT_EQ(tokens.at(3).tokens.at(0).getId(), lexer::defineTokenId(L"return"));
    ASSERT_EQ(tokens.at(3).tokens.at(0).getText(), L"return");
    ASSERT_EQ(tokens.at(3).tokens.at(1).getId(), lexer::defineTokenId(L"false"));
    ASSERT_EQ(tokens.at(3).tokens.at(1).getText(), L"false");
    ASSERT_EQ(tokens.at(3).tokens.at(2).getId(), lexer::defineTokenId(L";"));
    ASSERT_EQ(tokens.at(3).tokens.at(2).getText(), L";");
    ASSERT_EQ(tokens.at(3).tokens.at(3).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.at(3).tokens.at(3).getText(), L"\n");

    ASSERT_EQ(tokens.at(4).line_number, 5);
    ASSERT_EQ(tokens.at(4).original, L"if (age >= 18) then goodbay!\n");
    ASSERT_EQ(tokens.at(4).tokens.size(), 10);
    ASSERT_EQ(tokens.at(4).tokens.at(0).getId(), lexer::defineTokenId(L"if"));
    ASSERT_EQ(tokens.at(4).tokens.at(0).getText(), L"if");
    ASSERT_EQ(tokens.at(4).tokens.at(1).getId(), lexer::defineTokenId(L"("));
    ASSERT_EQ(tokens.at(4).tokens.at(1).getText(), L"(");
    ASSERT_EQ(tokens.at(4).tokens.at(2).getId(), lexer::defineTokenId(L"age"));
    ASSERT_EQ(tokens.at(4).tokens.at(2).getText(), L"age");
    ASSERT_EQ(tokens.at(4).tokens.at(3).getId(), lexer::defineTokenId(L">="));
    ASSERT_EQ(tokens.at(4).tokens.at(3).getText(), L">=");
    ASSERT_EQ(tokens.at(4).tokens.at(4).getId(), lexer::defineTokenId(L"18"));
    ASSERT_EQ(tokens.at(4).tokens.at(4).getText(), L"18");
    ASSERT_EQ(tokens.at(4).tokens.at(5).getId(), lexer::defineTokenId(L")"));
    ASSERT_EQ(tokens.at(4).tokens.at(5).getText(), L")");
    ASSERT_EQ(tokens.at(4).tokens.at(6).getId(), lexer::defineTokenId(L"then"));
    ASSERT_EQ(tokens.at(4).tokens.at(6).getText(), L"then");
    ASSERT_EQ(tokens.at(4).tokens.at(7).getId(), lexer::defineTokenId(L"goodbay"));
    ASSERT_EQ(tokens.at(4).tokens.at(7).getText(), L"goodbay");
    ASSERT_EQ(tokens.at(4).tokens.at(8).getId(), lexer::defineTokenId(L"!"));
    ASSERT_EQ(tokens.at(4).tokens.at(8).getText(), L"!");
    ASSERT_EQ(tokens.at(4).tokens.at(9).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.at(4).tokens.at(9).getText(), L"\n");

    ASSERT_EQ(tokens.at(5).line_number, 6);
    ASSERT_EQ(tokens.at(5).original, L"\"some text\"\n");
    ASSERT_EQ(tokens.at(5).tokens.size(), 4);
    ASSERT_EQ(tokens.at(5).tokens.at(0).getId(), lexer::defineTokenId(L"\""));
    ASSERT_EQ(tokens.at(5).tokens.at(0).getText(), L"\"");
    ASSERT_EQ(tokens.at(5).tokens.at(1).getId(), lexer::defineTokenId(L"some text"));
    ASSERT_EQ(tokens.at(5).tokens.at(1).getText(), L"some text");
    ASSERT_EQ(tokens.at(5).tokens.at(2).getId(), lexer::defineTokenId(L"\""));
    ASSERT_EQ(tokens.at(5).tokens.at(2).getText(), L"\"");
    ASSERT_EQ(tokens.at(5).tokens.at(3).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.at(5).tokens.at(3).getText(), L"\n");

    ASSERT_EQ(tokens.at(6).line_number, 7);
    ASSERT_EQ(tokens.at(6).original, L"// some comment\n");
    ASSERT_EQ(tokens.at(6).tokens.size(), 3);
    ASSERT_EQ(tokens.at(6).tokens.at(0).getId(), lexer::defineTokenId(L"//"));
    ASSERT_EQ(tokens.at(6).tokens.at(0).getText(), L"//");
    ASSERT_EQ(tokens.at(6).tokens.at(1).getId(), lexer::defineTokenId(L" some comment"));
    ASSERT_EQ(tokens.at(6).tokens.at(1).getText(), L" some comment");
    ASSERT_EQ(tokens.at(6).tokens.at(2).getId(), lexer::defineTokenId(L"\n"));
    ASSERT_EQ(tokens.at(6).tokens.at(2).getText(), L"\n");

    ASSERT_EQ(tokens.at(7).line_number, 8);
    ASSERT_EQ(tokens.at(7).original, L"/* one more comment\nnext comment line*/");
    ASSERT_EQ(tokens.at(7).tokens.size(), 3);
    ASSERT_EQ(tokens.at(7).tokens.at(0).getId(), lexer::defineTokenId(L"/*"));
    ASSERT_EQ(tokens.at(7).tokens.at(0).getText(), L"/*");
    ASSERT_EQ(tokens.at(7).tokens.at(1).getId(),
              lexer::defineTokenId(L" one more comment\nnext comment line"));
    ASSERT_EQ(tokens.at(7).tokens.at(1).getText(),
              L" one more comment\nnext comment line");
    ASSERT_EQ(tokens.at(7).tokens.at(2).getId(), lexer::defineTokenId(L"*/"));
    ASSERT_EQ(tokens.at(7).tokens.at(2).getText(), L"*/");
}
