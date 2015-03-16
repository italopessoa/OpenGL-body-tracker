#ifndef OBJETO3D_H
#define OBJETO3D_H

#include "matriz.h"
#include <math.h>
#define ESCALA 0.025

/**
 * @brief Classe que representa um objeto 3D
 *
 * Esta classe emgloba propriedades e operações disponíveis para um objeto 3D
 */
class Objeto3d
{
public:
    /**
     * @brief Construtor padrão
     */
    Objeto3d();

    ~Objeto3d();

    /**
     * @brief Rotacionar o objeto no eixo X
     *
     * Gerar a matrix de rotação no eixo X com o ângulo indicado
     * @param Angulo de rotação
     */
    void RotacionaX(double teta);

    /**
     * @brief Rotacionar o objeto no eixo Y
     *
     * Gerar a matrix de rotação no eixo Y com o ângulo indicado
     * @param Angulo de rotação
     */
    void RotacionaY(double teta);

    /**
     * @brief Rotacionar o objeto no eixo Z
     *
     * Gerar a matrix de rotação no eixo Z com o ângulo indicado
     * @param Angulo de rotação
     */
    void RotacionaZ(double teta);

    /**
     * @brief Desenhar objeto
     */
    void Desenha();

    /**
     * @brief Recuperar matriz de rotação atual
     * @return Vetor contendo os valores da matriz de rotação
     */
    GLdouble* GetMatrizRotacao();

    /**
     * @brief Escrever informações do objeto em um ponto da janela
     * @param Texto a ser escrito
     * @param x Posição X onde texto objeto será desenhado
     * @param y Posição Y onde texto objeto será desenhado
     * @param z Posição Z onde texto objeto será desenhado
     */
    void WriteData(char *texto, GLfloat x, GLfloat y, GLfloat z);

    /**
     * @brief Aumentar o fator de escala do objeto
     */
    void AumentarEscala();

    /**
     * @brief Diminuir o fator de escala do objeto
     */
    void DiminuirEscala();

private:

    /**
     * @brief Matriz de rotação atual
     *
     * Composição de todas as submatrizes\n
     * [R][R][R][T]\n
     * [R][R][R][T]\n
     * [R][R][R][T]\n
     * [0][0][0][1]
     */
    Matriz* _rotacao;


    //Matriz* _rotacaoAuxiliar;*

    /**
     * @brief Matriz utilizada para calcular a rotação no eixo X
     */
    Matriz* _rotX;

    /**
     * @brief Matriz utilizada para calcular a rotação no eixo Y
     */
    Matriz* _rotY;

    /**
     * @brief Matriz utilizada para calcular a rotação no eixo Z
     */
    Matriz* _rotZ;

    /**
     * @brief Texto utilizado para escrever mensagens na tela com informações do objeto
     */
    char _texto[60];

    /**
     * @brief Ângulo de rotação do objeto em relação a um eixo
     */
    double _teta;

    /**
     * @brief Fator de escala
     */
    GLdouble _fatorEscala;

    /**
     * @brief Matriz escala
     */
    Matriz* _mEscala;
};

#endif // OBJETO3D_H
