# Lexer

A universal lexer for splitting text into tokens.

## About

This lexer works on a special alphabet system, which means that if the current character is in the alphabet that makes up the word, it is added to the word, otherwise the word is considered complete and a new word is created.

All characters that are not specified as special alphabet characters are considered to be the same alphabet.

Individual symbols are also used in the lexer. These are symbols that are words in themselves. They can also be considered as special alphabets consisting of single symbols.

If you want to define multiple words as a single token, you can use combined tokens. All characters between a pair of combined tokens will be treated as a single word.

Separators are used to separate words whose characters are all the same alphabet. Separators are characters that are ignored by the lexer and cannot be part of a word. The exception is the use of combined tokens.

To identify tokens, a function is used that accepts the token itself. By default, this function calculates a 64-bit hash of the token using the FNV-1a algorithm.

## Usage

A class object is created that specifies special alphabets, individual characters, combined tokens, separators, and, as an optional parameter, a function for token identification.
To perform lexical analysis, call the `createTokens` method.

## Example

main.cpp
```cpp
#include <iostream>
#include <lexer/lexer.h>

int main() {
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

    for (auto token_iterator = lexer_contaner.begin(); token_iterator != lexer_contaner.end(); ++token_iterator) {
        std::wcout << L"----------------------------------------------------------\n";
        std::wcout << L"original row = " << token_iterator.getLine().original << '\n';
        std::wcout << L"token id = " << token_iterator->getId() << '\n';
        std::wcout << L"token text = " << token_iterator->getText() << '\n';
        std::wcout << L"----------------------------------------------------------\n";
    }

  return 0;
}
```

CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.30)

project(MyApp)

include(FetchContent)
FetchContent_Declare(
  UniversalLexer
  GIT_REPOSITORY "https://github.com/NikitaZhinov/UniversalLexer"
  GIT_TAG v2.0
)
FetchContent_MakeAvailable(UniversalLexer)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE UniversalLexer)
target_include_directories(${PROJECT_NAME} PRIVATE ${UniversalLexer_SOURCE_DIR}/include)
```

Output:
```
----------------------------------------------------------
original row = hello world

token id = 11831194018420276491
token text = hello
----------------------------------------------------------
----------------------------------------------------------
original row = hello world

token id = 5717881983045765875
token text = world
----------------------------------------------------------
----------------------------------------------------------
original row = hello world

token id = 12638164110811449565
token text =

----------------------------------------------------------
----------------------------------------------------------
original row = 10 * name

token id = 574369514284255396
token text = 10
----------------------------------------------------------
----------------------------------------------------------
original row = 10 * name

token id = 12638128926439346813
token text = *
----------------------------------------------------------
----------------------------------------------------------
original row = 10 * name

token id = 14176396743819860870
token text = name
----------------------------------------------------------
----------------------------------------------------------
original row = 10 * name

token id = 12638164110811449565
token text =

----------------------------------------------------------
----------------------------------------------------------
original row =

token id = 12638164110811449565
token text =

----------------------------------------------------------
----------------------------------------------------------
original row = return   false;

token id = 14251563519059995999
token text = return
----------------------------------------------------------
----------------------------------------------------------
original row = return   false;

token id = 13113042584710199672
token text = false
----------------------------------------------------------
----------------------------------------------------------
original row = return   false;

token id = 12638145419113769978
token text = ;
----------------------------------------------------------
----------------------------------------------------------
original row = return   false;

token id = 12638164110811449565
token text =

----------------------------------------------------------
----------------------------------------------------------
original row = if (age >= 18) then goodbay!

token id = 628023482707099174
token text = if
----------------------------------------------------------
----------------------------------------------------------
original row = if (age >= 18) then goodbay!

token id = 12638126727416090391
token text = (
----------------------------------------------------------
----------------------------------------------------------
original row = if (age >= 18) then goodbay!

token id = 16651413216827089244
token text = age
----------------------------------------------------------
----------------------------------------------------------
original row = if (age >= 18) then goodbay!

token id = 581112819098748884
token text = >=
----------------------------------------------------------
----------------------------------------------------------
original row = if (age >= 18) then goodbay!

token id = 574360718191229708
token text = 18
----------------------------------------------------------
----------------------------------------------------------
original row = if (age >= 18) then goodbay!

token id = 12638125627904462180
token text = )
----------------------------------------------------------
----------------------------------------------------------
original row = if (age >= 18) then goodbay!

token id = 2700409281739296150
token text = then
----------------------------------------------------------
----------------------------------------------------------
original row = if (age >= 18) then goodbay!

token id = 3876496727903589804
token text = goodbay
----------------------------------------------------------
----------------------------------------------------------
original row = if (age >= 18) then goodbay!

token id = 12638116831811436492
token text = !
----------------------------------------------------------
----------------------------------------------------------
original row = if (age >= 18) then goodbay!

token id = 12638164110811449565
token text =

----------------------------------------------------------
----------------------------------------------------------
original row = "some text"

token id = 12638120130346321125
token text = "
----------------------------------------------------------
----------------------------------------------------------
original row = "some text"

token id = 1565534772893300484
token text = some text
----------------------------------------------------------
----------------------------------------------------------
original row = "some text"

token id = 12638120130346321125
token text = "
----------------------------------------------------------
----------------------------------------------------------
original row = "some text"

token id = 12638164110811449565
token text =

----------------------------------------------------------
----------------------------------------------------------
original row = // some comment

token id = 564807061655596579
token text = //
----------------------------------------------------------
----------------------------------------------------------
original row = // some comment

token id = 13944730148112409578
token text =  some comment
----------------------------------------------------------
----------------------------------------------------------
original row = // some comment

token id = 12638164110811449565
token text =

----------------------------------------------------------
----------------------------------------------------------
original row = /* one more comment
next comment line*/
token id = 564810360190481212
token text = /*
----------------------------------------------------------
----------------------------------------------------------
original row = /* one more comment
next comment line*/
token id = 1894670217688674451
token text =  one more comment
next comment line
----------------------------------------------------------
----------------------------------------------------------
original row = /* one more comment
next comment line*/
token id = 569592136260624726
token text = */
----------------------------------------------------------
```
