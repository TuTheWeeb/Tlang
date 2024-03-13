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
    TokenType tokenval;
    boost::variant<int, float, std::string> Attribute;
} TokenRecord;

template<class Type>
bool eat(Type &tensor) {
    std::string tname = typeid(Type).name();

    if (((tname.compare(typeid(std::string).name()) != 0) or (tname.compare(typeid(std::vector<TokenRecord>).name()) != 0))) {
        tensor = Type{tensor.begin() + 1, tensor.end()};
    }
    
    if (tensor.size() == 0) return true;

    return false;
}

std::vector<TokenRecord> tokenize(const char file_name[]) {
    static std::vector<TokenRecord> tokens;
    std::string str;

    // Reads the file and writes to the string
    {
        std::stringstream str_stream;
        str_stream << std::ifstream(file_name).rdbuf();
        str = str_stream.str();
    }
    
    std::string val = "";

    while (true) {
        if (str.size() == 0) break;
        char c = str.at(0);
        bool cond = true;

        if (std::isspace(c) != 0) eat(str);
        
        if (std::isalpha(c) != 0) {
            val.push_back(c);
            
            // Eat Character and go out
            if (eat(str)) goto token_add;
            char k = str.at(0);

            while ((std::isdigit(k) != 0) or (std::isalpha(k) != 0) or (k == '_')) {
                val.push_back(k);

                // Eat character and go out
                if (eat(str)) goto token_add;
                else k = str.at(0);
            }
        }

        if (std::isdigit(c) != 0) {
            val.push_back(c);

            bool point = false;

            // Eat Character and go out
            if (eat(str)) goto token_add;
            char k = str.at(0);

            while ((std::isdigit(k) != 0) or (k == '.')) {
                if (point == true) continue;
                val.push_back(k);
                
                // Eat character and go out
                if (eat(str)) goto token_add;
                else k = str.at(0);
            }
        }
 

        if (c == '=') {
            val.push_back(c);
            if(eat(str)) goto token_add;
        }

        token_add:
        if (val.size() > 0) {
            if (val.compare("if") == 0) {
                tokens.push_back({.tokenval=TokenType::IF, .Attribute=val});
            } 

            else if (val.compare("=") == 0) {
                tokens.push_back({.tokenval=TokenType::EQUAL, .Attribute=val});
            }

            else if (std::isalpha(val.at(0)) != 0) {
                tokens.push_back({.tokenval=TokenType::ID, .Attribute=val});
            }
             
            else if (std::isdigit(val.at(0)) != 0) {

                int point = val.find('.');
                if (point == -1) tokens.push_back({.tokenval=TokenType::INT, .Attribute=stoi(val)});
                else tokens.push_back({.tokenval=TokenType::FLOAT, .Attribute=stof(val)});
            }
        }
        val.clear();
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