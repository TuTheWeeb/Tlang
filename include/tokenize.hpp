#pragma once
#include <cmath>
#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <typeinfo>
#include <boost/variant.hpp>

// TokenType
enum class TokenType {
    ID,
    IF,
    EQUAL,
    OPEN_PAREN,
    CLOSE_PAREN,
    OPEN_KEY,
    CLOSE_KEY,
    BINARY_OPR,
    INT,
    FLOAT
};

// TokenRecord
typedef struct {
    TokenType tokenval;
    boost::variant<int, float, std::string> Attribute;
} TokenRecord;

// Check if the value is a binary operator
template <class Type>
bool is_binary_op(Type ch);

// eat a value in a tensor
template<class Type>
bool eat(Type &tensor);

// Get all tokens in a file
std::vector<TokenRecord> tokenize(const char file_name[]);
