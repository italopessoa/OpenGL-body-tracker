#include "objeto3d.h"
#include <iostream>
#include <stdio.h>

Objeto3d::Objeto3d()
{
    //inicializar matrizes de rotação
    _rotacao = new Matriz(4,4);
    _rotacao->CarregarIdentidade();

    /*_rotacaoAuxiliar = new Matriz(4,4);
    _rotacaoAuxiliar->CarregarIdentidade();*/

    _rotX = new Matriz(4,4);
    _rotX->CarregarIdentidade();

    _rotY = new Matriz(4,4);
    _rotY->CarregarIdentidade();

    _rotZ = new Matriz(4,4);
    _rotZ->CarregarIdentidade();

    _mEscala = new Matriz(4,4);
    _mEscala->CarregarIdentidade();

    _fatorEscala = 1;
}

Objeto3d::~Objeto3d()
{

}


void Objeto3d::RotacionaX(double theta)
{
    /*_rotacaoAuxiliar->CarregarIdentidade();
    _rotacaoAuxiliar->AlterarValor(5,cos(theta));
    _rotacaoAuxiliar->AlterarValor(6,-sin(theta));
    _rotacaoAuxiliar->AlterarValor(9,sin(theta));
    _rotacaoAuxiliar->AlterarValor(10,cos(theta));
    _rotacao->MultiplicaTransformacao(_rotacaoAuxiliar);
    rx->CarregarIdentidade();
    */
    _theta = theta;
    //configurar matriz de rotacao no eixo X
    _rotX->AlterarValor(5,cos(theta));
    _rotX->AlterarValor(6,-sin(theta));
    _rotX->AlterarValor(9,sin(theta));
    _rotX->AlterarValor(10,cos(theta));
}

void Objeto3d::RotacionaY(double theta)
{
    /*_rotacaoAuxiliar->CarregarIdentidade();
    _rotacaoAuxiliar->AlterarValor(0,cos(theta));
    _rotacaoAuxiliar->AlterarValor(2,-sin(theta));
    _rotacaoAuxiliar->AlterarValor(8,sin(theta));
    _rotacaoAuxiliar->AlterarValor(10,cos(theta));

    _rotacao->MultiplicaTransformacao(_rotacaoAuxiliar);
    */
    _theta = theta;
    //montar matriz de rotacao em torno do eixo x
    _rotY->AlterarValor(0,cos(theta));
    _rotY->AlterarValor(2,-sin(theta));
    _rotY->AlterarValor(8,sin(theta));
    _rotY->AlterarValor(10,cos(theta));
}

void Objeto3d::RotacionaZ(double theta)
{
    /*
   _rotacaoAuxiliar->CarregarIdentidade();
    _rotacaoAuxiliar->AlterarValor(0,cos(theta));
    _rotacaoAuxiliar->AlterarValor(1,-sin(theta));
    _rotacaoAuxiliar->AlterarValor(4,sin(theta));
    _rotacaoAuxiliar->AlterarValor(5,cos(theta));

    _rotacao->MultiplicaTransformacao(_rotacaoAuxiliar);

    _rotacaoAuxiliar->MultiplicaTransformacao();
    */

    _theta = theta;
    //montar matriz de rotacao em torno do eixo z
    _rotZ->AlterarValor(0,cos(theta));
    _rotZ->AlterarValor(1,-sin(theta));
    _rotZ->AlterarValor(4,sin(theta));
    _rotZ->AlterarValor(5,cos(theta));
}

void Objeto3d::Translada(GLfloat* vetorTranslacao)
{
    _rotacao->AlterarValor(3,vetorTranslacao[0] + _rotacao->_m[3]); //tx' + tx
    _rotacao->AlterarValor(7,vetorTranslacao[1] + _rotacao->_m[7]); //ty' + ty
    _rotacao->AlterarValor(11,vetorTranslacao[2] + _rotacao->_m[11]);//tz' + tz
}

void Objeto3d::Desenha()
{
    glPushMatrix();
        glMultTransposeMatrixd(this->GetMatrizRotacao());
        //glMultTransposeMatrixd(_rotacao->MatrixToGLDArray());
        //glutSolidTorus(8/*innerRadius*/
                       //,20/*outerRadius*/
                       //,152/*sides*/
                       //,5/*rings*/);

        glutSolidSphere(30,150,110);

        glPushMatrix();
            glColor3d(0.4,0.4,0.4);
            glutSolidTorus(10,70,2,120);
        glPopMatrix();

        glPushMatrix();
            glColor3d(1,0,0);
            glTranslated(100,0,0);
            glutSolidSphere(9,50,10);
        glPopMatrix();

        glPushMatrix();
            glColor3d(1,0.5,0.2);
            glTranslated(40,0,0);
            glutSolidSphere(4,50,10);
        glPopMatrix();


    glPopMatrix();

    glColor3d(0,0,0);

    sprintf(_texto,"[%.2f][%.2f][%.2f][%.2f]",_rotacao->_m[0],_rotacao->_m[1],_rotacao->_m[2],_rotacao->_m[3]);
    WriteData(_texto, -70.0f,10.0f,0.0f);

    sprintf(_texto,"[%.2f][%.2f][%.2f][%.2f]",_rotacao->_m[4],_rotacao->_m[5],_rotacao->_m[6],_rotacao->_m[7]);
    WriteData(_texto,-71.0f,5.0f,0.0f);

    sprintf(_texto,"[%.2f][%.2f][%.2f][%.2f]",_rotacao->_m[8],_rotacao->_m[9],_rotacao->_m[10],_rotacao->_m[11]);
    WriteData(_texto ,-71.0f,0.0f,0.0f);

    sprintf(_texto,"[%.2f][%.2f][%.2f][%.2f]",_rotacao->_m[12],_rotacao->_m[13],_rotacao->_m[14],_rotacao->_m[15]);
    WriteData(_texto ,-71.0f,-5.0f,0.0f);


}

GLdouble* Objeto3d::GetMatrizRotacao()
{
    _rotacao->MultiplicaTransformacao(_rotX);
    _rotacao->MultiplicaTransformacao(_rotZ);
    _rotacao->MultiplicaTransformacao(_rotY);
    //_rotacao->AlterarValor(0,3,50);
    //_rotacao->AlterarValor(1,3,30);
    //_rotacao->AlterarValor(2,3,-60);

    //diminuir o tamanho

    //_rotacao->AlterarValor(3,3,2.5);

    _rotacao->MultiplicaTransformacao(_mEscala);
    return _rotacao->MatrixToGLDArray();
}

void Objeto3d::WriteData(char *texto, GLfloat x, GLfloat y, GLfloat z)
{
    // Posição no universo onde o texto será colocado
    glRasterPos3f(x,y,z);
    // Exibe caracter a caracter
    while(*texto)
         glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*texto++);
}

void Objeto3d::AumentarEscala()
{
    _fatorEscala += ESCALA;
    _rotacao->_m[0] = _rotacao->_m[5] = _rotacao->_m[10] = _fatorEscala;
}

void Objeto3d::DiminuirEscala()
{
    if((_fatorEscala - ESCALA) < 0)
    {
        _fatorEscala = 0;
    }
    else
    {
        _fatorEscala -= ESCALA;
    }
    _rotacao->_m[0] = _rotacao->_m[5] = _rotacao->_m[10] = _fatorEscala;
}

void Objeto3d::Reiniciar()
{
    _rotacao->CarregarIdentidade();
}
