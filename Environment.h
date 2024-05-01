#include <cstdlib>  // Para getenv e strtol
#include <iostream> // Para std::cerr

class Environment {
public:
    static int getInt(const char* varName, int defaultValue) {
        const char* value = std::getenv(varName);
        if (value) {
            char* endPtr;
            long intValue = std::strtol(value, &endPtr, 10); // Conversão de string para long
            if (*endPtr == '\0') { // Verifica se a conversão foi bem-sucedida
                return static_cast<int>(intValue);
            } else {
                std::cerr << "Valor inválido para a variável de ambiente " << varName << std::endl;
            }
        }
        return defaultValue; // Retorna o valor padrão se a variável não estiver definida
    }
};
