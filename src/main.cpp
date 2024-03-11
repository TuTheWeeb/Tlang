#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <typeinfo>
#include <boost/variant.hpp>

enum class TokenType {
    IF,
    EQUAL,
    BINARY_OPR,
    INT,
    FLOAT,
    ID
};

typedef struct {
    TokenType tokenval = TokenType::ID;
    boost::variant<int, float, std::string> Attribute;
} TokenRecord;

template<class Type>
void eat(Type &tensor) {
    std::string tname = typeid(Type).name();

    if ((tname.compare(typeid(std::string).name()) != 0) or (tname.compare(typeid(std::vector<TokenRecord>).name()) != 0)) {
        tensor = Type{tensor.begin() + 1, tensor.end()};
    }
}

std::vector<TokenRecord> tokenize(const char file_name[]) {
    static std::vector<TokenRecord> tokens;
    std::string str;

    // Reads the file and writes to the string
    {
        std::stringstream str_stream;
        str_stream << std::ifstream(file_name).rdbuf();
        str = str_stream.str() + " /eof";
    }
    
    std::string val = "";

    while (true) {
        if (str.size() == 0) break;
        char c = str.at(0);
        
        // Check if c is a space char and if it's then push back a token
        if (val.compare("if") == 0) {
            TokenRecord tk = {.tokenval=TokenType::IF, .Attribute=val};
            tokens.push_back(tk);
            val.clear();
        } else if (val.compare("=") == 0) {
            TokenRecord tk = {.tokenval=TokenType::EQUAL, .Attribute=val};
            tokens.push_back(tk);
            val.clear();
        } else if (std::isalpha(val.at(0)) != 0) {
            TokenRecord tk = {.tokenval=TokenType::ID, .Attribute=val};
            tokens.push_back(tk);
            val.clear();
        } else {
            int point = val.find(".");
            
            if (point == -1) {
                TokenRecord tk = {.tokenval=TokenType::INT, .Attribute=std::stoi(val)};
                tokens.push_back(tk);
                val.clear();
            } else {
                TokenRecord tk = {.tokenval=TokenType::FLOAT, .Attribute=std::stof(val)};
                tokens.push_back(tk);
                val.clear();
            }
        }

        // If it's a space character then push c to the val string
        val.push_back(c);

        eat<std::string>(str);
    }

    return tokens;
}



int main(int argc, char *argv[]) {

    std::vector<TokenRecord> tokens;

    if (argc > 1) tokens = tokenize(argv[1]);
    else {
        std::cout << "You din't select a file!" << std::endl;
        std::cout << "PROJECT_NAME <file name>" << std::endl;
    }
    std::cout << "{ ";
    for (auto tk : tokens) {
        switch (tk.tokenval) {
            case TokenType::ID:
                std::cout << "[ID: " << tk.Attribute << "], ";
                break;
            case TokenType::EQUAL:
                std::cout << "[EQUAL: " << tk.Attribute << "], ";
                break;
            case TokenType::INT:
                std::cout << "[INT: " << tk.Attribute << "], ";
                break;
            case TokenType::FLOAT:
                std::cout << "[FLOAT: " << tk.Attribute << "], ";
                break;
            default:
                std::cout << "[NONE: " << tk.Attribute << "], ";
                break;
        }
    }
    std::cout << " }" << std::endl;

    
    return 0;
}