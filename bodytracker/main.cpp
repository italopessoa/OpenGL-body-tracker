#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <iostream>
#include <objeto3d.h>
using namespace std;

enum RotationEnum {ROT_X, ROT_Y, ROT_Z, ROT_STOP};
enum GroundTypeEnum {EMPTY, SQUARES, POLYGON};

double _mRotacao[16];

RotationEnum _rotacao = ROT_STOP;

static Objeto3d* _torus = new Objeto3d();

/**
 * @brief _teta angulo de rotação
 */
static double _teta;

void log(std::string mensagem)
{
    cout << mensagem << endl;
}

/**
 * @brief DisplayInit
 */
void DisplayInit()
{
    // Limpa a janela e o depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 800, 600);

    const float ar = 600>0 ? (float) 800 / (float) 600 : 1.0;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.,ar,0.1,1000.);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //posicao inicial da camera
    gluLookAt(0,90,180, 0,0,0, 0,1,0);
}

/**
 * @brief DisplayEnd
 */
void DisplayEnd()
{
    glutSwapBuffers();
}

/**
 * @brief DrawLineGround
 * @param x
 * @param y
 * @param z
 * @param size
 * @param space
 */
void DrawLineGround(GLfloat x, GLfloat z,int size, GLfloat space)
{
    glPushMatrix();
        glBegin(GL_LINE_STRIP);
            glVertex3f(x,0,z);
            glVertex3f(x+size,0,z);
            glVertex3f(x+size,0,z-size);
            glVertex3f(x,0,z-size);
            glVertex3f(x,0,z);
        glEnd();

        GLfloat total = size/space;

        int i;

        for (i = 1; i< total; i++)
        {
            glBegin(GL_LINES);
                glVertex3f(x+(space*i),0,z);
                glVertex3f(x+(space*i),0,z-size);
            glEnd();

            glBegin(GL_LINES);
                glVertex3f(x,0,z-(space*i));
                glVertex3f(x+size,0,z-(space*i));
            glEnd();
        }
    glPopMatrix();
}

/**
 * @brief DrawPolygonGround
 * @param x
 * @param z
 * @param size
 * @param space
 */
void DrawPolygonGround(GLfloat x, GLfloat z,int size, GLfloat space)
{
    glPushMatrix();

    GLfloat total = size/space;

    int i,j, r,g,b;
    r = 0;
    g = 0;
    b = 0;
    GLfloat xAux;

    for (j = 0; j< total; j++)
    {
        xAux = x;

        for (i = 0; i< total; i++)
        {
            if((i+j)%2 == 0)
            {
                g = 1;
                b = r = 0;
            }
            else
            {
                b = 1;
                g = r = 0;
            }
            glBegin(GL_POLYGON);
                glColor3d(r,g,b);
                glVertex3f(xAux,0,z);
                glVertex3f(xAux+space,0,z);
                glVertex3f(xAux+space,0,z-space);
                glVertex3f(xAux,0,z-space);
            glEnd();

            xAux+=space;
        }
        z-=space;
    }
    glPopMatrix();
}


/**
 * @brief DrawGround
 * @param groundType
 * @param initialPoint
 * @param groundSize
 * @param space
 */
void DrawGround(GroundTypeEnum groundType, GLint* initialPoint, int groundSize, GLfloat space)
{
    switch (groundType) {
    case EMPTY:
        glPushMatrix();
            glBegin(GL_LINE_STRIP);
                glVertex3f(initialPoint[0],0,initialPoint[1]);
                glVertex3f(initialPoint[0]+groundSize,0,initialPoint[1]);
                glVertex3f(initialPoint[0]+groundSize,0,initialPoint[1]-groundSize);
                glVertex3f(initialPoint[0],0,initialPoint[1]-groundSize);
                glVertex3f(initialPoint[0],0,initialPoint[1]);
            glEnd();
        glPopMatrix();
        break;
    case SQUARES:
        DrawLineGround(initialPoint[0],initialPoint[1],groundSize,space);
        break;
    case POLYGON:
        DrawPolygonGround(initialPoint[0],initialPoint[1],groundSize,space);
        break;
    }
}

/**
 * @brief Função callback chamada para fazer o desenho.
 *
 */
void Draw(void)
{
    DisplayInit();

    glColor3d(0.4,0.3,1);

    GLint point[2] = {-50,50};
    DrawGround(POLYGON,point,100,3.125);
    glColor3d(0.4,0.3,1);
    //glPushMatrix();

    switch (_rotacao) {
    case ROT_X:
        /*              _mRotacao[0] = 1;  _mRotacao[1] = 0;          _mRotacao[2] = 0;           _mRotacao[3] = 0;
                _mRotacao[4] = 0;  _mRotacao[5] = cos(_teta); _mRotacao[6] = -sin(_teta); _mRotacao[7] = 0;
                _mRotacao[8] = 0;  _mRotacao[9] = sin(_teta); _mRotacao[10] = cos(_teta); _mRotacao[11] = 0;
                _mRotacao[12] = 0; _mRotacao[13] = 0;         _mRotacao[14] = 0;          _mRotacao[15] = 1;
*/
        //_torus->RotacionaX(_teta);
        break;
    case ROT_Y:
        /*_mRotacao[0] = cos(_teta); _mRotacao[1] = 0;  _mRotacao[2] = sin(_teta);  _mRotacao[3] = 0;
                _mRotacao[4] = 0;          _mRotacao[5] = 1;  _mRotacao[6] = 0;           _mRotacao[7] = 0;
                _mRotacao[8] = -sin(_teta);_mRotacao[9] = 0;  _mRotacao[10] = cos(_teta); _mRotacao[11] = 0;
                _mRotacao[12] = 0;         _mRotacao[13] = 0; _mRotacao[14] = 0;          _mRotacao[15] = 1;
                break;*/
        //_torus->RotacionaY(_teta);
        break;
    case ROT_Z:
        /*_mRotacao[0] = cos(_teta); _mRotacao[1] = -sin(_teta); _mRotacao[2] =     _mRotacao[3] = 0;
                _mRotacao[4] = sin(_teta); _mRotacao[5] = cos(_teta);  _mRotacao[6] =     _mRotacao[7] = 0;
                _mRotacao[8] = 0;          _mRotacao[9] = 0;           _mRotacao[10] = 1; _mRotacao[11] = 0;
                _mRotacao[12] = 0;         _mRotacao[13] = 0;          _mRotacao[14] = 0; _mRotacao[15] = 1;
                */
        //_torus->RotacionaZ(_teta);
        break;
    default:
        break;
    }

    _torus->RotacionaX(_teta);
    _torus->RotacionaY(_teta);
    _torus->RotacionaZ(_teta);
    //glPushMatrix();
        //glMultTransposeMatrixd(_torus->GetMatrizRotacao());
    _torus->Desenha();
        //glPushMatrix();
        //glPopMatrix();
    //glPopMatrix();


    DisplayEnd();
}

/**
 * @brief idle
 */
void idle(void)
{
    glutPostRedisplay();
}

/**
 * @brief KeyBoard
 * @param key
 */
void KeyBoard(unsigned char key, int, int)
{
    switch (key)
    {
        case 27 :
            exit(0);
        case 'x':
            log("eixo de rotação = x");
            _rotacao = ROT_X;
        break;
        case 'y':
            log("eixo de rotação = y");
            _rotacao = ROT_Y;
        break;
        case 'z':
            log("eixo de rotação = z");
            _rotacao = ROT_Z;
        break;
        case '+':
            _teta += 0.01;
            cout << "teta = " << _teta << endl;
        break;
        case '-':
            _teta -= 0.01;
            cout << "teta = " << _teta << endl;
        break;
        case 'm':

            cout << "[" << _torus->GetMatrizRotacao()[0] << "]" <<
                    "[" << _torus->GetMatrizRotacao()[1] << "]" <<
                    "[" << _torus->GetMatrizRotacao()[2] << "]" <<
                    "[" << _torus->GetMatrizRotacao()[3] << "]" << endl;

            cout << "[" << _torus->GetMatrizRotacao()[4] << "]" <<
                    "[" << _torus->GetMatrizRotacao()[5] << "]" <<
                    "[" << _torus->GetMatrizRotacao()[6] << "]" <<
                    "[" << _torus->GetMatrizRotacao()[7] << "]" << endl;

            cout << "[" << _torus->GetMatrizRotacao()[8] << "]" <<
                    "[" << _torus->GetMatrizRotacao()[9] << "]" <<
                    "[" << _torus->GetMatrizRotacao()[10] << "]" <<
                    "[" << _torus->GetMatrizRotacao()[11] << "]" << endl;

            cout << "[" << _torus->GetMatrizRotacao()[12] << "]" <<
                    "[" << _torus->GetMatrizRotacao()[13] << "]" <<
                    "[" << _torus->GetMatrizRotacao()[14] << "]" <<
                    "[" << _torus->GetMatrizRotacao()[15] << "]" << endl;
        break;
        case 'S':
            _torus->AumentarEscala();
        break;
        case 's':
            _torus->DiminuirEscala();
        break;
    }

    glutPostRedisplay();
}

/**
 * @brief GlutLightSetup
 */
void GlutLightSetup()
{
    glEnable(GL_LIGHT0);

    const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

    const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
    const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
    const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat high_shininess[] = { 100.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

/**
 * @brief Configuração inicial do glut.
 * @param argc Numero de argumentos.
 * @param argv Vetor de caracteres contendo as opções de configuração.
 */
void GlutSetup(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Visualizacao 3D");
    glutDisplayFunc(Draw);
    glutKeyboardFunc(KeyBoard);
    glutIdleFunc(idle);
    //cor utilizada para pintar toda a tela
    glClearColor(1,1,1,1);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE); //mantem a qualidade da iluminacao mesmo quando glScalef eh usada
    GlutLightSetup();
}

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    GlutSetup(argc, argv);

    glutMainLoop();
    /*Objeto3d* a  = new Objeto3d();

    a->RotacionaX(90);*/
}

