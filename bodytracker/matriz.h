#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>
#include <GL/glut.h>


using namespace std;

/**
 * @brief The Matriz class
 */
class Matriz
{
public:

    /**
     * @brief Matriz
     */
    Matriz();

    /**
     * @brief Matriz
     * @param linha
     * @param coluna
     */
    Matriz(int linha, int coluna);

    ~Matriz();

    /**
     * @brief Multiplicar
     * @param m
     * @return
     */
    Matriz* Multiplicar(Matriz* m);

    /**
     * @brief MultiplicaTransformacao
     * @param m
     */
    void MultiplicaTransformacao(Matriz* m);

    /**
     * @brief Somar
     * @param m
     * @return
     */
    Matriz* Somar(Matriz* m);

    /**
     * @brief Subtrair
     * @param m
     * @return
     */
    Matriz* Subtrair(Matriz* m);

    /**
     * @brief Transposta
     * @return
     */
    Matriz* Transposta();

    /**
     * @brief CarregarIdentidade
     */
    void CarregarIdentidade();

    /**
     * @brief RetornaValor
     * @param indice
     * @return
     */
    float RetornaValor(int indice);

    /**
     * @brief AlterarValor
     * @param i
     * @param valor
     */
    void AlterarValor(int i, double valor);

    /**
     * @brief AlterarValor
     * @param x
     * @param y
     * @param valor
     */
    void AlterarValor(int x, int y, double valor);

    /**
     * @brief BuscarValor
     * @param x
     * @param y
     * @return
     */
    float BuscarValor(int x, int y);

    /**
     * @brief GetLinha
     * @return
     */
    int GetLinha();

    /**
     * @brief GetColuna
     * @return
     */
    int GetColuna();

    /**
     * @brief _m
     */
    std::vector<GLdouble> _m;

    /**
     * @brief MatrixToGLDArray
     * @return
     */
    GLdouble* MatrixToGLDArray();

private:

    /**
     * @brief _linha
     */
    int _linha;

    /**
     * @brief _coluna
     */
    int _coluna;




};

#endif // MATRIZ_H
