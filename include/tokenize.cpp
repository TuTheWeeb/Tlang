#include "tokenize.hpp"

template <class Type>
bool is_binary_op(Type ch) {
    std::array<std::string, 4> vars = {"+", "-", "*", "/"};
    std::string cha;
    cha = ch;

    for (auto v : vars) {
        if (v.compare(cha) == 0) return true;
    }

    return false;
}

template<class Type>
bool eat(Type &tensor) {
    std::string tname = typeid(Type).name();

    if (((tname.compare(typeid(std::string).name()) != 0) or (tname.compare(typeid(std::vector<TokenRecord>).name()) != 0)) and (tensor.size() > 0)) {
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

        if (std::isspace(c) != 0) eat(str);
        
        // Check for names
        else if (std::isalpha(c) != 0) {
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

        // Check for numbers
        else if (std::isdigit(c) != 0) {
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

        else if (c == '(') {
            val.push_back(c);
            eat(str);
            goto token_add;
        }

        else if (c == ')') {
            val.push_back(c);
            eat(str);
            goto token_add;
        }

        else if (c == '{') {
            val.push_back(c);
            eat(str);
            goto token_add;
        }

        else if (c == '}') {
            val.push_back(c);
            eat(str);
            goto token_add;
        }

        else if (c == '=') {
            val.push_back(c);
            eat(str);
            goto token_add;
        }

        else if (is_binary_op(c)) {
            val.push_back(c);

            // Eat Character and go out
            eat(str);
            goto token_add;
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
            
            else if (is_binary_op(val)) {
                tokens.push_back({.tokenval=TokenType::BINARY_OPR, .Attribute=val});
            }

            else if (val.compare("(") == 0) tokens.push_back({.tokenval=TokenType::OPEN_PAREN, .Attribute=val});

            else if (val.compare(")") == 0) tokens.push_back({.tokenval=TokenType::CLOSE_PAREN, .Attribute=val});
            
            else if (val.compare("{") == 0) tokens.push_back({.tokenval=TokenType::OPEN_KEY, .Attribute=val});

            else if (val.compare("}") == 0) tokens.push_back({.tokenval=TokenType::CLOSE_KEY, .Attribute=val});
        }
        val.clear();
    }

    return tokens;
}
