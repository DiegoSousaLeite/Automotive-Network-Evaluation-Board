#include <QString>
#include <QDir>

class UtilsConversion {
public:
    // Converte uma string hexadecimal para um valor do tipo short.
    // O método utiliza o método `toInt` da classe QString para realizar a conversão.
    // A string é interpretada como um número hexadecimal (base 16).
    // Retorna o valor convertido para short.
    static short hexToShort(const QString &hexStr) {
        bool ok;
        return static_cast<short>(hexStr.toInt(&ok, 16));
    }

    // Converte um número inteiro em um vetor de inteiros representando seu valor binário.
    // O método cria um vetor de tamanho 4, inicializado com zeros, para armazenar os bits binários.
    // A conversão é feita dividindo o número por 2 e armazenando os restos (0 ou 1) no vetor.
    // Retorna um vetor contendo a representação binária do número.
    static QVector<int> parseBinary(int num) {
        QVector<int> binary(4, 0);
        int index = 0;
        while (num > 0 && index < binary.size()) {
            binary[index++] = num % 2;
            num /= 2;
        }
        return binary;
    }

    // Verifica se um caminho de diretório é válido.
    // O método utiliza a classe QDir para verificar a existência do diretório especificado pelo caminho.
    // Retorna true se o diretório existir, caso contrário, retorna false.
    static bool isPathValid(const QString &path) {
        QDir dir(path);
        return dir.exists();
    }
};
