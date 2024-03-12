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
bool eat(Type &tensor) {
    std::string tname = typeid(Type).name();

    if (tensor.size() == 0) return false;

    if (((tname.compare(typeid(std::string).name()) != 0) or (tname.compare(typeid(std::vector<TokenRecord>).name()) != 0)) and tensor.size() > 0) {
        tensor = Type{tensor.begin() + 1, tensor.end()};
    }

    return true;
}

std::vector<TokenRecord> tokenize(const char file_name[]) {
    static std::vector<TokenRecord> tokens;
    std::string str;

    // Reads the file and writes to the string
    {
        std::stringstream str_stream;
        str_stream << std::ifstream(file_name).rdbuf();
        str = str_stream.str() + "";
    }
    
    std::vector<std::string> parts;

    while (str != "") {
        std::string val = "";
        if (str.size() == 0) break;
        if (std::isspace(str.at(0)) != 0) eat<std::string>(str);
        char c = str.at(0);
        bool point = false;

        if (std::isalpha(c) != 0) {
            eat<std::string>(str);   
        }
        c = str.at(0);
        if (c == '=') eat<std::string>(str);
        c = str.at(0);
        
        std::cout << c << std::endl;

        // Get a number
        while (std::isdigit(c) != 0) {
            val.push_back(c);
            std::cout << "val: " << val << " " << str.size() << std::endl;           //std::cout << c;
            eat<std::string>(str);
            //if (str.at(0) == ';') break;

            if ((str.at(0) == '.') and (point == false)) {
                val.push_back(str.at(0));
                eat<std::string>(str);
                point = true;
            }
            
            c = str.at(0);

        }
        if (val.compare("") != 0) parts.push_back(val);
        val.clear();
        // Get a ID
        /*
        while (std::isalpha(c) != 0) {
            val.push_back(c);
            eat<std::string>(str);
            //if (str.at(0) == ';') break;

            while ((std::isdigit(str.at(0) != 0) or (str.at(0) == '_'))) {
                if (str.at(0) == ' ') break;
                val.push_back(str.at(0));
                eat<std::string>(str);
            }

            c = str.at(0);
        }
        if (val.compare("") != 0) parts.push_back(val);
        val.clear();*/

        /*if (c == '=') {
            parts.push_back("=");
            eat<std::string>(str);
            c = str.at(0);
        }*/
        
        /*for (auto s : parts) {
            std::cout << "s: " << s << std::endl;
        }*/
    }   
    std::cout << "ERROR" << std::endl;
    
    /*
    while (parts.size() > 0) {
        std::string val = parts.at(0);
        std::cout << "Val: " << val << std::endl;

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
        } else if (std::isdigit(val.at(0) != 0)) {
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

        eat<std::vector<std::string>>(parts);
    }*/

    return tokens;
}



int main(int argc, char *argv[]) {

    std::vector<TokenRecord> tokens;

    if (argc > 1) tokens = tokenize(argv[1]);
    else {
        std::cout << "You din't select a file!" << std::endl;
        std::cout << "PROJECT_NAME <file name>" << std::endl;
    }
    /*std::cout << "{ ";
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
    std::cout << " }" << std::endl;*/

    
    return 0;
}