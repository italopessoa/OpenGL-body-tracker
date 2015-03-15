#ifndef OBJETO3D_H
#define OBJETO3D_H

#include "matriz.h"
#include <math.h>
#define ESCALA 0.025

class Objeto3d
{
public:
    Objeto3d();
    ~Objeto3d();

    /**
     * @brief RotacionaX
     * @param teta
     */
    void RotacionaX(double teta);

    /**
     * @brief RotacionaY
     * @param teta
     */
    void RotacionaY(double teta);

    /**
     * @brief RotacionaZ
     * @param teta
     */
    void RotacionaZ(double teta);

    /**
     * @brief Desenha
     */
    void Desenha();

    /**
     * @brief GetMatrizRotacao
     * @return
     */
    GLdouble* GetMatrizRotacao();

    /**
     * @brief WriteData Desenha um texto na janela GLUT
     * @param texto
     */
    void WriteData(char *texto, GLfloat x, GLfloat y, GLfloat z);

    /**
     * @brief AumentarEscala
     */
    void AumentarEscala();

    /**
     * @brief DiminuirEscala
     */
    void DiminuirEscala();

private:

    /**
     * @brief _rotacao
     */
    Matriz* _rotacao;


    //Matriz* _rotacaoAuxiliar;*

    /**
     * @brief _rotX
     */
    Matriz* _rotX;

    /**
     * @brief _rotY
     */
    Matriz* _rotY;

    /**
     * @brief _rotZ
     */
    Matriz* _rotZ;

    /**
     * @brief texto
     */
    char _texto[60];

    /**
     * @brief _teta
     */
    double _teta;

    /**
     * @brief _escala
     */
    GLdouble _fatorEscala;

    /**
     * @brief _mEscala
     */
    Matriz* _mEscala;
};

#endif // OBJETO3D_H
