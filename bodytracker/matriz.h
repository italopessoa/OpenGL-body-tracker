#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>
#include <GL/glut.h>


using namespace std;

/**
 * @brief Classe que representa uma matriz e suas operações
 */
class Matriz
{
public:

    /**
     * @brief Construtor padrão
     */
    Matriz();

    /**
     * @brief Contrutor utilizado para inicializar uma matriz com suas dimensões
     * @param linha Número de linhas
     * @param coluna Número de colunas
     */
    Matriz(int linha, int coluna);

    ~Matriz();

    /**
     * @brief Método utilizado para multiplica duas matrizes
     * @param m Matriz que será multiplicada pela matriz atual
     * @return Uma nova matriz contendo o resultado da multiplicaçao
     */
    Matriz* Multiplicar(Matriz* m);

    /**
     * @brief Semelhante ao método Multiplicar
     *
     * Neste método o resultado da multiplicação é salvo na matriz atual.
     * @see Multiplicar();
     * @param m Matriz que será multiplicada pela matriz atual
     */
    void MultiplicaTransformacao(Matriz* m);

    /**
     * @brief Somar duas matrizes
     * @param m Matriz que será multiplicada a matriz atual
     * @return Uma nova matriz contendo o resultado da soma
     */
    Matriz* Somar(Matriz* m);

    /**
     * @brief Calculo da transposta da matriz atual
     * @return Matriz transposta da matriz atual
     */
    Matriz* Transposta();

    /**
     * @brief Subtrair duas matrizes
     *
     * @param m Matriz que será subtraída a matriz atual
     * @return Uma nova matriz contendo o resultado da soma
     */
    Matriz* Subtrair(Matriz *m);

    /**
     * @brief Preencher a matriz atual com a matriz identidade.
     *
     * [1][0][0]\n
     * [0][1][0]\n
     * [0][0][1]\n
     * Podendo variar de acordo com as dimenções da matriz.
     */
    void CarregarIdentidade();

    /**
     * @brief Buscar valor no vetor que representa a matriz
     * @param indice Índice direto do vetor
     * @return Valor armazenado no índice indicado
     */
    float RetornaValor(int indice);

    /**
     * @brief Alterar valor no vetor que representa a matriz
     * @param i Índice direto do vetor
     * @param valor Valor a ser inserido no índice do vetor
     */
    void AlterarValor(int i, double valor);

    /**
     * @brief Alterar valor utilizando coordenadas da matriz
     * @param x Linha
     * @param y Coluna
     * @param valor Valor a ser inserido
     */
    void AlterarValor(int x, int y, double valor);

    /**
     * @brief Buscar valor utilizando coordenadas da matriz
     * @param x Linha
     * @param y Coluna
     * @return Valor armazenado nas coordenadas indicadas
     */
    float BuscarValor(int x, int y);

    /**
     * @brief Método para acessar a quantidade de linhas de uma matriz
     * @return Quantidade de linhas da matriz
     */
    int GetLinha();

    /**
     * @brief Método para acessar a quantidade de colunas de uma matriz
     * @return Quantidade de colunas da matriz
     */
    int GetColuna();

    /**
     * @brief Vetor que representa a matriz
     */
    std::vector<GLdouble> _m;

    /**
     * @brief Converter matriz atual um array
     *
     * Este método é utilizado quando for necessário um vetor GLdouble
     * @return
     */
    GLdouble* MatrixToGLDArray();

private:

    /**
     * @brief Linhas da matriz
     */
    int _linha;

    /**
     * @brief Colunas da matriz
     */
    int _coluna;
};

#endif // MATRIZ_H
