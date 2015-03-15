#include "matriz.h"
#include <stdexcept>

using namespace std;

Matriz::Matriz(int linha, int coluna)
{
    _linha = linha;
    _coluna = coluna;
    _m.resize(_linha*_coluna);
}

Matriz* Matriz::Multiplicar(Matriz* m)
{
    //verificar se é possível realizar a multiplicacao
    if(_coluna != m->GetLinha())
    {
        throw std::invalid_argument( "Matriz::Multiplicar - a matriz informada é incompatível para multiplicação" );
    }

    Matriz *matrizResultante = new Matriz(_linha,m->GetColuna());

    int colunaAtual = 0;
    float somatorio;

    for (int i = 0; i < _linha; i++)
    {
        somatorio = 0;

        while(colunaAtual < m->GetColuna())
        {
            for (int j = 0; j< _coluna; j++)
            {
                somatorio += (BuscarValor(i,j) * m->BuscarValor(j,colunaAtual)); //(i,j) * (i,c)
            }

            matrizResultante->AlterarValor(i,colunaAtual,somatorio);
            somatorio = 0;
            colunaAtual++;
        }

        colunaAtual = 0;
    }

    return matrizResultante;
}

void Matriz::MultiplicaTransformacao(Matriz* m)
{
    //verificar se é possível realizar a multiplicacao
    //TODO: verificar se é quadrada, pois aqui será armazenado na mesma matriz
    if(_coluna != m->GetLinha())
    {
        throw std::invalid_argument( "Matriz::Multiplicar - a matriz informada é incompatível para multiplicação" );
    }

    Matriz *matrizResultante = new Matriz(_linha,m->GetColuna());

    int colunaAtual = 0;
    float somatorio;

    for (int i = 0; i < _linha; i++)
    {
        somatorio = 0;

        while(colunaAtual < m->GetColuna())
        {
            for (int j = 0; j< _coluna; j++)
            {
                somatorio += (BuscarValor(i,j) * m->BuscarValor(j,colunaAtual)); //(i,j) * (i,c)
            }

            matrizResultante->AlterarValor(i,colunaAtual,somatorio);
            somatorio = 0;
            colunaAtual++;
        }

        colunaAtual = 0;
    }
    _m = matrizResultante->_m;
}

Matriz* Matriz::Somar(Matriz *m)
{
    if(_linha != m->GetLinha())
    {
        throw std::invalid_argument( "Matriz::Somar - a matriz informada é incompatível para multiplicação (colunas)" );
    }

    if(_coluna != m->GetColuna())
    {
        throw std::invalid_argument( "Matriz::Somar - a matriz informada é incompatível para multiplicação (colunas)" );
    }

    Matriz* matrizResultante = new Matriz(_linha, _coluna);

    for(int i = 0; i< _linha; i++)
    {
        for(int j = 0; j< _coluna; j++)
        {
            matrizResultante->AlterarValor(i,j,BuscarValor(i,j) + m->BuscarValor(i,j));
        }
    }

    return matrizResultante;
}

Matriz* Matriz::Subtrair(Matriz *m)
{
    if(_linha != m->GetLinha())
    {
        throw std::invalid_argument( "Matriz::Subtrair - a matriz informada é incompatível para multiplicação (colunas)" );
    }

    if(_coluna != m->GetColuna())
    {
        throw std::invalid_argument( "Matriz::Subtrair - a matriz informada é incompatível para multiplicação (colunas)" );
    }

    Matriz* matrizResultante = new Matriz(_linha, _coluna);

    for(int i = 0; i< _linha; i++)
    {
        for(int j = 0; j< _coluna; j++)
        {
            matrizResultante->AlterarValor(i,j,BuscarValor(i,j) - m->BuscarValor(i,j));
        }
    }

    return matrizResultante;
}

Matriz* Matriz::Transposta()
{
    throw std::invalid_argument( "Matriz::Transposta - a matriz informada não é quadrada." );

    Matriz* resultante = new Matriz(_linha,_coluna);

    for (int i = 0; i < _linha; i++) {
        for (int j = 0; j < _coluna; j++) {
            float a = BuscarValor(i,j);
            float b = BuscarValor(j,i);

            resultante->AlterarValor(i,j,b);
            resultante->AlterarValor(j,i,a);
        }
    }

    return resultante;
}

void Matriz::CarregarIdentidade()
{
    if(_linha != _coluna)
    {
        throw std::invalid_argument( "Matriz::CarregarIdentidade - a matriz informada é não é quadrada" );
    }

    for (int i = 0; i < _linha; i++)
    {
        _m[((_linha*i)+i)] = 1;
    }
}

int Matriz::GetColuna()
{
    return _coluna;
}

int Matriz::GetLinha()
{
    return _linha;
}

float Matriz::BuscarValor(int x, int y)
{
    if(x <= _linha)
    {
        if(y <= _coluna)
        {
            float valor = _m[(x * _coluna) + y];
            return valor;
        }
        else
        {
            throw std::invalid_argument( "Matriz::BuscarValor - O valor y é maior que o suportado." );
        }
    }
    else
    {
        throw std::invalid_argument( "Matriz::BuscarValor - O valor x é maior que o suportado." );
    }
}

void Matriz::AlterarValor(int x, int y, double valor)
{
    if(x <= _linha)
    {
        if(y <= _coluna)
        {
            _m[(x * _coluna) + y] = valor;
        }
        else
        {
            throw std::invalid_argument( "Matriz::AlterarValor - O valor y é maior que o suportado." );
        }
    }
    else
    {
        throw std::invalid_argument( "Matriz::AlterarValor - O valor x é maior que o suportado." );
    }
}

void Matriz::AlterarValor(int i, double valor)
{
    //TODO: verificar se nao está vazio
    _m[i]=valor;
}

GLdouble* Matriz::MatrixToGLDArray()
{
    //TODO: melhorar desempenho
    GLdouble values[_linha*_coluna];
    for (int i = 0; i < (_linha*_coluna); i++)
    {
        values[i] = _m[i];
    }

    return values;
}

Matriz::~Matriz()
{

}
