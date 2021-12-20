#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <vector>
#include <sstream>

enum class TokenType {
    COLON,
    COLON_DASH,
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    MULTIPLY,
    ADD,
    RULES,
    SCHEMES,
    FACTS,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    END_OF_FILE,
    UNDEFINED
};

class Token
{
private:
    std::string description;
    int line;

public:
    TokenType type;
    Token(TokenType type, std::string description, int line);


    std::string GetDescription();
    std::string GetLine();
    std::string GetType(TokenType);
    std::string toString();

    std::vector<std::string> tokenList;
};

#endif // TOKEN_H

