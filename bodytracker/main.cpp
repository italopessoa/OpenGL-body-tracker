#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <iostream>
#include <objeto3d.h>
#include <utils.h>
#include <camera.h>

using namespace std;
#define MAX_ARVORE 10

int _groundType = Utils::EMPTY;

int _width = 1000;
int _height = 600;
double _mRotacao[16];
GLfloat _vetorTranslacao[3];
int _rotacao = Utils::ROT_STOP;

Camera _camera;

static Objeto3d* _torus = new Objeto3d();

/**
 * @brief _theta angulo de rotação
 */
static double _theta;

GLdouble _thetaY=_height/180.0;
GLdouble _thetaX=_width/180.0;
int _lastYMouse,_lastXMouse;

float camAngleX=0;
float camAngleY=-10;
float distancia=10;

/**
 * @brief DisplayInit
 */
void DisplayInit()
{
    // Limpa a janela e o depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, _width, _height);

    const float ar = _height>0 ? (float) _width / (float) _height : 1.0;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.,ar,0.1,1000.);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


//http://gamedev.stackexchange.com/questions/20758/how-can-i-orbit-a-camera-about-its-target-point
    //http://stackoverflow.com/questions/287655/opengl-rotating-a-camera-around-a-point
    // Calculate the camera position using the distance and angles
    float camX = distancia * -sinf(camAngleX*(M_PI/180)) * cosf((camAngleY)*(M_PI/180));
    float camY = distancia * -sinf((camAngleY)*(M_PI/180));
    float camZ = -distancia * cosf((camAngleX)*(M_PI/180)) * cosf((camAngleY)*(M_PI/180));
    //cout << "camY: " << camY<< endl;
//cout << "camX: " << camX << "camY: " << camY << "camZ: " << camZ << endl;
    // Set the camera position and lookat point
    gluLookAt(camX,camY,camZ,   // Camera position
              0.0, 0.0, 0.0,    // Look at point
              0.0, 1.0, 0.0);


    //posicao inicial da camera
    //gluLookAt(0,90,180, 0,0,0, 0,1,0);
    /*gluLookAt(_camera.eye[0], _camera.eye[1],_camera.eye[2],
            _camera.center[0], _camera.center[1],_camera.center[2],
            _camera.up[0], _camera.up[1],_camera.up[2]);*/
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

void DrawCubeGround(GLfloat x,GLfloat y, GLfloat z,int size, GLfloat space)
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
void DrawGround(int groundType, GLint* initialPoint, int groundSize, GLfloat space)
{
    switch (groundType) {
    case Utils::EMPTY:
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
    case Utils::SQUARES:
        DrawLineGround(initialPoint[0],initialPoint[1],groundSize,space);
        break;
    case Utils::POLYGON:
        DrawPolygonGround(initialPoint[0],initialPoint[1],groundSize,space);
        break;
    case Utils::CUBE:
        glPushMatrix();
            glBegin(GL_LINE_STRIP);
                glVertex3f(initialPoint[0],0,initialPoint[1]);
                glVertex3f(initialPoint[0]+groundSize,0,initialPoint[1]);
                glVertex3f(initialPoint[0]+groundSize,0,initialPoint[1]-groundSize);
                glVertex3f(initialPoint[0],0,initialPoint[1]-groundSize);
                glVertex3f(initialPoint[0],0,initialPoint[1]);
            glEnd();

            glBegin(GL_LINE_STRIP);
                glVertex3f(initialPoint[0],0,initialPoint[1]);
                glVertex3f(initialPoint[0],50,initialPoint[1]);
                glVertex3f(initialPoint[0]+groundSize,50,initialPoint[1]);
                glVertex3f(initialPoint[0]+groundSize,0,initialPoint[1]);
            glEnd();

            glBegin(GL_LINE_STRIP);
                glVertex3f(initialPoint[0],0,initialPoint[1]-groundSize);
                glVertex3f(initialPoint[0],50,initialPoint[1]-groundSize);
                glVertex3f(initialPoint[0]+groundSize,50,initialPoint[1]-groundSize);
                glVertex3f(initialPoint[0]+groundSize,0,initialPoint[1]-groundSize);
            glEnd();

            glBegin(GL_LINES);
                glVertex3f(initialPoint[0],50,initialPoint[1]-groundSize);
                glVertex3f(initialPoint[0],50,initialPoint[1]);
            glEnd();

            glBegin(GL_LINES);
                glVertex3f(initialPoint[0]+groundSize,50,initialPoint[1]-groundSize);
                glVertex3f(initialPoint[0]+groundSize,50,initialPoint[1]);
            glEnd();
        glPopMatrix();
        break;
    }
}

GLdouble fatorP=1.4;
int tArvore = 0;

void ArvorePitagoras(GLdouble cubo,GLdouble r, GLdouble tx, GLdouble ty,int size )
{
    if(tArvore > 0)
    {
        int sizeD=size;
        int sizeE=size;
        glPushMatrix();
            glutSolidCube(cubo);
            if(sizeD <=tArvore)
            {
                glPushMatrix();
                    glRotated(r,0,0,1);
                    glTranslated(tx,ty,0);
                    if(sizeD >5){
                        glColor3d(0,0.7,0.99);
                    }else
                    {
                        glColor3d(1,0,0);
                    }

                    glutSolidCube(cubo/1.4);
                    ArvorePitagoras(cubo/fatorP,45,tx/fatorP,ty/fatorP,++sizeD);
                glPopMatrix();
            }
            if(sizeE <= tArvore)
            {
                glPushMatrix();
                    glRotated(-r,0,0,1);
                    glTranslated(-tx,ty,0);
                    if(sizeE >5){
                        glColor3d(0.8,1,0.1);
                    }else
                    {
                        glColor3d(0,1,0);
                    }
                    glutSolidCube(cubo/1.4);
                    ArvorePitagoras(cubo/fatorP,45,tx/fatorP,ty/fatorP,++sizeE);
                glPopMatrix();
            }
        glPopMatrix();
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
    DrawGround(_groundType,point,100,3.125);
    glColor3d(0.4,0.3,1);
    //glPushMatrix();

    switch (_rotacao) {
    case Utils::ROT_X:
        /*              _mRotacao[0] = 1;  _mRotacao[1] = 0;          _mRotacao[2] = 0;           _mRotacao[3] = 0;
                _mRotacao[4] = 0;  _mRotacao[5] = cos(_theta); _mRotacao[6] = -sin(_theta); _mRotacao[7] = 0;
                _mRotacao[8] = 0;  _mRotacao[9] = sin(_theta); _mRotacao[10] = cos(_theta); _mRotacao[11] = 0;
                _mRotacao[12] = 0; _mRotacao[13] = 0;         _mRotacao[14] = 0;          _mRotacao[15] = 1;
*/
        //_torus->RotacionaX(_theta);
        break;
    case Utils::ROT_Y:
        /*_mRotacao[0] = cos(_theta); _mRotacao[1] = 0;  _mRotacao[2] = sin(_theta);  _mRotacao[3] = 0;
                _mRotacao[4] = 0;          _mRotacao[5] = 1;  _mRotacao[6] = 0;           _mRotacao[7] = 0;
                _mRotacao[8] = -sin(_theta);_mRotacao[9] = 0;  _mRotacao[10] = cos(_theta); _mRotacao[11] = 0;
                _mRotacao[12] = 0;         _mRotacao[13] = 0; _mRotacao[14] = 0;          _mRotacao[15] = 1;
                break;*/
        //_torus->RotacionaY(_theta);
        break;
    case Utils::ROT_Z:
        /*_mRotacao[0] = cos(_theta); _mRotacao[1] = -sin(_theta); _mRotacao[2] =     _mRotacao[3] = 0;
                _mRotacao[4] = sin(_theta); _mRotacao[5] = cos(_theta);  _mRotacao[6] =     _mRotacao[7] = 0;
                _mRotacao[8] = 0;          _mRotacao[9] = 0;           _mRotacao[10] = 1; _mRotacao[11] = 0;
                _mRotacao[12] = 0;         _mRotacao[13] = 0;          _mRotacao[14] = 0; _mRotacao[15] = 1;
                */
        //_torus->RotacionaZ(_theta);
        break;
    default:
        break;
    }

    glPushMatrix();
        ArvorePitagoras(1*10,45,0.35*10,1.058*10,0);
    glPopMatrix();

    glPushMatrix();
        glRotated(90,0,1,0);
        ArvorePitagoras(1*10,45,0.35*10,1.058*10,0);
    glPopMatrix();

    _torus->RotacionaX(_theta);
    _torus->RotacionaY(_theta);
    _torus->RotacionaZ(_theta);
    _torus->Translada(_vetorTranslacao);
    //glPushMatrix();
    //glMultTransposeMatrixd(_torus->GetMatrizRotacao());
    //_torus->Desenha();


    //_torus->AumentarEscala();
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
        _rotacao = Utils::ROT_X;
        break;
    case 'y':
        _rotacao = Utils::ROT_Y;
        break;
    case 'z':
        _rotacao = Utils::ROT_Z;
        break;
    case '+':
        _theta += 0.01;
        cout << "theta = " << _theta << endl;
        break;
    case '-':
        _theta -= 0.01;
        cout << "theta = " << _theta << endl;
        break;
    case 'S':
        _torus->AumentarEscala();
        break;
    case 's':
        _torus->DiminuirEscala();
        break;
    case 'F':
        glutFullScreen();
        break;
    case 'f':
        glutReshapeWindow(_width,_height);
        break;
    /*TRANSLACAO z*/
    case '8':
        _vetorTranslacao[2] -= 1;
        break;
    case '2':
        _vetorTranslacao[2] += 1;
        break;
    /*TRANSLACAO x*/
    case '4':
        _vetorTranslacao[0] -= 1;
        break;
    case '6':
        _vetorTranslacao[0] += 1;
        break;
    /*TRANSLACAO Y*/
    case '7':
        _vetorTranslacao[1] += 0.3;
        break;
    case '1':
        _vetorTranslacao[1] -= 0.3;
        break;
    /*PARAR TRANSLACAO*/
    case '5':
        _vetorTranslacao[0] =_vetorTranslacao[1]=_vetorTranslacao[2]=0;
        break;
    case 'r':
        if(glutGetModifiers() == GLUT_ACTIVE_ALT)
        {
            _torus->Reiniciar();
        }
        break;
    case 'd':
        distancia+=5;
        break;
    case 'D':
        distancia-=5;
        break;
    case 'l':
        camAngleX+=1;
        break;
    case 'L':
        camAngleX-=1;
        break;
    case 'i':
        camAngleY+=1;
        //cout << camAngleY << endl;
        break;
    case 'I':
        camAngleY-=1;
        //cout << camAngleY << endl;
        break;
    case 'T':
        tArvore++;
        if(tArvore > MAX_ARVORE) tArvore = MAX_ARVORE;
        break;
    case 't':
        tArvore--;
        if(tArvore < 0) tArvore = 0;
        //cout << camAngleY << endl;
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

    const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 0.0f };
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
 * @brief Reshape
 * @param width
 * @param height
 */
void Reshape(int width, int height)
{
    _width = width;
    _height = height;
    glutPostRedisplay();
}

/**
 * @brief MenuGround
 * @param option
 */
void MenuGround(int option)
{
    switch(option) {
    case 0:
        _groundType = Utils::EMPTY;
        break;
    case 1:
        _groundType = Utils::SQUARES;
        break;
    case 2:
        _groundType = Utils::POLYGON;
        break;
    case 3:
        _groundType = Utils::CUBE;
        break;
    }
    glutPostRedisplay();
}

/**
 * @brief MenuPrincipal
 * @param option
 */
void MenuPrincipal(int option)
{

}

/**
 * @brief CreateMenu
 */
void CreateMenu()
{
    int subMenuGround;/*mainMenu,*/

    subMenuGround = glutCreateMenu(MenuGround);
    glutAddMenuEntry("Empty",0);
    glutAddMenuEntry("Square",1);
    glutAddMenuEntry("Polygon",2);
    glutAddMenuEntry("Cube",3);

    //mainMenu = glutCreateMenu(MenuPrincipal);
    glutCreateMenu(MenuPrincipal);
    glutAddSubMenu("Chao",subMenuGround);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/**
 * @brief MouseManager
 * @param button
 * @param state
 * @param x
 * @param y
 */
void MouseManager(int button, int state, int x, int y)
{
    if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            CreateMenu();
        }
    }

    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            _lastYMouse = y;
            _lastXMouse = x;
            //cout << "X: " << x << "Y: " << y << endl;
        }else
        {
            //cout << "out" << endl;
        }
    }

    glutPostRedisplay();
}

/**
 * @brief MouseMotion
 * @param x
 * @param y
 */

void MouseMotion(int x, int y)
{
    int novoY = _lastYMouse - y;
    int novoX = _lastXMouse - x;
    GLdouble a = novoY*_thetaY;
    camAngleY += (a/10);

    GLdouble b = novoX*_thetaX;
    camAngleX += (b/10);


    //cout << "Y: " << a << endl;
    _lastYMouse = y;
    _lastXMouse = x;
}

/**
 * @brief Configuração inicial do glut.
 * @param argc Numero de argumentos.
 * @param argv Vetor de caracteres contendo as opções de configuração.
 */
void GlutSetup(int argc, char *argv[])
{
    _camera.eye[0]=0;
    _camera.eye[1]=90;
    _camera.eye[2]=180;

    _camera.up[1]=1;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(_width,_height);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Visualizacao 3D");
    glutDisplayFunc(Draw);
    glutKeyboardFunc(KeyBoard);
    glutReshapeFunc(Reshape);
    glutIdleFunc(idle);
    glutMouseFunc(MouseManager);
    glutMotionFunc(MouseMotion);
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
}

