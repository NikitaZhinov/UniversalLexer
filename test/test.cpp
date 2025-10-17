#include <gtest/gtest.h>

#include <iostream>
#include "../include/lexer/lexer.h"

TEST(Test_Test, Test_Test_Test) {
    std::vector<lexer::CombiningTokens> combining_tokens = {
        lexer::CombiningTokens { lexer::Token(L"\""), lexer::Token(L"\"") },
        lexer::CombiningTokens { lexer::Token(L"//"), lexer::Token(L"\n") },
        lexer::CombiningTokens { lexer::Token(L"/*"), lexer::Token(L"*/") }
    };

    std::wstring code = L"hello world\n"
                        "10 * name\n"
                        "\n"
                        "return\tfalse;\n"
                        "if (age >= 18) then goodbay!\n"
                        "\"some text\"\n"
                        "// some comment\n"
                        "/* one more comment\n"
                        "next comment line*/";

    lexer::Lexer lexer_contaner_generator({ L"+-/*=<>!" }, L"&?;$#@^:\"'|.,(){}[]\n",
                                          combining_tokens, L" \t");
    auto lexer_contaner = lexer_contaner_generator.createTokens(code);

    for (auto token_iterator = lexer_contaner.begin();
         token_iterator != lexer_contaner.end(); ++token_iterator) {
        std::wcout << L"----------------------------------------------------------\n";
        std::wcout << L"original row = " << token_iterator.getLine().original << '\n';
        std::wcout << L"token id = " << token_iterator->getId() << '\n';
        std::wcout << L"token text = " << token_iterator->getText() << '\n';
        std::wcout << L"----------------------------------------------------------\n";
    }
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
