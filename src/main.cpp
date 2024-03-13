#include "tokenize.hpp"

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
            case TokenType::BINARY_OPR:
                std::cout << "[BINARY_OPR: " << tk.Attribute << "], ";
                break;
            case TokenType::OPEN_PAREN:
                std::cout << "[OPEN_PAREN: " << tk.Attribute << "], ";
                break;
            case TokenType::CLOSE_PAREN:
                std::cout << "[CLOSE_PAREN: " << tk.Attribute << "], ";
                break;
            case TokenType::OPEN_KEY:
                std::cout << "[OPEN_KEY: " << tk.Attribute << "], ";
                break;
            case TokenType::CLOSE_KEY:
                std::cout << "[CLOSE_KEY: " << tk.Attribute << "], ";
                break;
            default:
                std::cout << "[NONE: " << tk.Attribute << "], ";
                break;
        }
    }
    std::cout << " }" << std::endl;

    
    return 0;
}