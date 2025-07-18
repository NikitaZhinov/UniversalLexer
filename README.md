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

  lexer::Lexer lexer({ L"+-/*=<>!" }, L"&?;$#@^:\"'|.,(){}[]\n", combining_tokens, L" \t");
  auto tokens = lexer.createTokens(code);

  for (auto line : tokens) {
    std::cout << "original: '" << line.original << "' -> tokens: ";
    for (auto token : line.tokens) {
      std::cout << "'" << token.getText() << "', ";
    }
    std::cout << std::endl;
  }

  return 0;
}
```

CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.20)

project(MyApp)

include(FetchContent)
FetchContent_Declare(
  UniversalLexer
  GIT_REPOSITORY "https://github.com/NikitaZhinov/UniversalLexer"
  GIT_TAG v1.1
)
FetchContent_MakeAvailable(UniversalLexer)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE UniversalLexer)
target_include_directories(${PROJECT_NAME} PRIVATE ${UniversalLexer_SOURCE_DIR}/include)
```

Output:
```
original: 'hello world
' -> tokens: 'hello', 'world'. '
', 
orginal: '10 * name
' -> tokens: '10', '*', 'name', '
', 
original: '
' -> tokens: '
', 
original: 'return  false;
' -> tokens: 'return', 'false', ';', '
',
original: 'if (age >= 18) then goodbay!
' -> tokens: 'if', '(', 'age', '>=', '18', ')', 'then', 'goodbay', '!', '
', 
original: '"some text"
' -> tokens: '"', 'some text', '"', '
',
original: '// some comment
' -> tokens: '//', ' some comment', '
', 
original: '/* one more comment
next comment line*/' -> tokens: '/*', ' one more comment
next comment line', '*/', 
```
