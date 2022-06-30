#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <GL/glut.h>
bool perspectiva = true, mouse = false, camera = true;
// Inicializa��o
void SetupRC(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);               // cor de fundo
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // limpa a janela e o depth buffer
    glEnable(GL_DEPTH_TEST);                            // habilita Z-buffer
    glShadeModel(GL_FLAT);                              // habilita o uso de sombreado plano
}
GLfloat fAspect;
GLdouble qa = -180.00, ws = 180.00, ed = -180.00, rf = 180.00, tg = 1, yh = 180;
GLdouble uj = 0.0f, ik = 0.0f, ol = -100;
GLdouble zx = 0.0f, cv = 0.0f, bn = 0.0f;
GLdouble _14 = 0.0f, _25 = 1.0f, _36 = 0.0f;
GLdouble angle = 0.0f;
GLdouble xc = 0.0f, yc = 0.0f, zc = 0.0f;

GLdouble eyeX = 100.0f, eyeY = 0.0f, eyeZ = 0.0f;
GLdouble centerX = 0.0f, centerY = 0.0f, centerZ = 0.0f;
GLdouble upX = 0.0f, upY = 1.0f, upZ = 0.0f;

void basicReal(float x, float y, float z)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glutWireCube(3);
    glPopMatrix();
}

void coloredCube(float x, float y, float z)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(0.5f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f(10.0f, 10.0f, 10.0f);
    glVertex3f(10.0f, 10.0f, -10.0f);
    glVertex3f(10.0f, -10.0f, -10.0f);
    glVertex3f(10.0f, -10.0f, 10.0f);
    glEnd();
    glColor3f(0.0f, 1.0f, 0.5f);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0f, 10.0f, 10.0f);
    glVertex3f(-10.0f, 10.0f, -10.0f);
    glVertex3f(-10.0f, -10.0f, -10.0f);
    glVertex3f(-10.0f, -10.0f, 10.0f);
    glEnd();
    glColor3f(0.0f, 0.5f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex3f(10.0f, 10.0f, 10.0f);
    glVertex3f(-10.0f, 10.0f, 10.0f);
    glVertex3f(-10.0f, -10.0f, 10.0f);
    glVertex3f(10.0f, -10.0f, 10.0f);
    glEnd();
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f(10.0f, 10.0f, -10.0f);
    glVertex3f(-10.0f, 10.0f, -10.0f);
    glVertex3f(-10.0f, -10.0f, -10.0f);
    glVertex3f(10.0f, -10.0f, -10.0f);
    glEnd();
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex3f(10.0f, 10.0f, 10.0f);
    glVertex3f(10.0f, 10.0f, -10.0f);
    glVertex3f(-10.0f, 10.0f, -10.0f);
    glVertex3f(-10.0f, 10.0f, 10.0f);
    glEnd();
    glColor3f(0.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex3f(10.0f, -10.0f, 10.0f);
    glVertex3f(10.0f, -10.0f, -10.0f);
    glVertex3f(-10.0f, -10.0f, -10.0f);
    glVertex3f(-10.0f, -10.0f, 10.0f);
    glEnd();

    glPopMatrix();
}

// Minha fun��o de desenho
void RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (perspectiva)
    {
        gluPerspective(qa + 290, fAspect, tg, yh);
    }
    else
    {
        glOrtho(qa, ws, ed, rf, tg, yh);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (camera)
    {
        gluLookAt(uj, ik, ol, zx, cv, bn, _14, _25, _36);
    }
    else
    {
        gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
    }
    glPushMatrix();
    glRotatef(angle, 0, 1, 0);
    glColor3f(1, 1, 1);
    // glutWireTeapot(50);
    glColor3f(1, 1, 0);
    glutWireCube(80);
    coloredCube(xc, yc, zc);
    glPopMatrix();
    glColor3f(1, 0, 0);
    basicReal(uj, ik, ol);
    glColor3f(0, 1, 0);
    basicReal(zx, cv, bn);

    glFlush();
}

void HandleMouse(int button, int state, int x, int y)
{

    if (mouse)
    {
        if (button == 3)
        {
            zc += 1;
        }
        if (button == 4)
        {
            zc -= 1;
        }
    }
    if (button == GLUT_MIDDLE_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            mouse = !mouse;
        }
    }
    glutPostRedisplay();
}
void MotionMouse(int x, int y)
{
    if (mouse)
    {

        xc = (1 - x / (glutGet(GLUT_WINDOW_WIDTH) / 2.0f)) * glutGet(GLUT_WINDOW_WIDTH) / 4.0f;
        yc = (1 - y / (glutGet(GLUT_WINDOW_HEIGHT) / 2.0f)) * glutGet(GLUT_WINDOW_HEIGHT) / 4.0f;
    }
    glutPostRedisplay();
}

void CallbackTeclado(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ',':
        camera = !camera;
        if (!camera)
            printf("fixed\n");
        break;

    case '*':
        angle = 0.0f;
        break;
    case '/':
        xc = 0.0f;
        yc = 0.0f;
        zc = 0.0f;
        break;
    case '+':
        angle += 1;
        break;
    case '-':
        angle -= 1;
        break;
    case 'p':
        perspectiva = !perspectiva;
        break;
    case 'q':
        qa += 1;
        break;
    case 'w':
        ws += 1;
        break;
    case 'e':
        ed += 1;
        break;
    case 'r':
        rf += 1;
        break;
    case 't':
        tg += 1;
        break;
    case 'y':
        yh += 1;
        break;
    case 'u':
        uj += 1;
        break;
    case 'i':
        ik += 1;
        break;
    case 'o':
        ol += 1;
        break;
    case 'z':
        zx += 1;
        break;
    case 'c':
        cv += 1;
        break;
    case 'b':
        bn += 1;
        break;
    case 'a':
        qa -= 1;
        break;
    case 's':
        ws -= 1;
        break;
    case 'd':
        ed -= 1;
        break;
    case 'f':
        rf -= 1;
        break;
    case 'g':
        tg -= 1;
        break;
    case 'h':
        yh -= 1;
        break;
    case 'j':
        uj -= 1;
        break;
    case 'k':
        ik -= 1;
        break;
    case 'l':
        ol -= 1;
        break;
    case 'x':
        zx -= 1;
        break;
    case 'v':
        cv -= 1;
        break;
    case 'n':
        bn -= 1;
        break;
    case '1':
        _14 += 0.1f;
        break;
    case '2':
        _25 += 0.1f;
        break;
    case '3':
        _36 += 0.1f;
        break;
    case '4':
        _14 -= 0.1f;
        break;
    case '5':
        _25 -= 0.1f;
        break;
    case '6':
        _36 -= 0.1f;
        break;
    case '0':
        qa = -180.00;
        ws = 180.00;
        ed = -180.00;
        rf = 180.00;
        tg = 1;
        yh = 180;
        uj = 0.0f;
        ik = 0.0f;
        ol = -100;
        zx = 0.0f;
        cv = 0.0f;
        bn = 0.0f;
        _14 = 0.0f;
        _25 = 1.0f;
        _36 = 0.0f;
        angle = 0.0f;

        break;

    default:
        printf("%c\n", key);
        return;
    }
    printf("* %c *\n", key);

    if (perspectiva)
    {
        printf("Perspectiva\n");
        printf("fovy(qa) : %f - fAspect: %f ", qa + 290, fAspect);
        printf("zNear(tg): %f - zFar(yh): %f\neyeX(uj): %f - eyeY(ik): %f ", tg, yh, uj, ik);
        printf("eyeZ(ol): %f\ncenterX(zx): %f - centerY(cv): %f - centerZ(bn): %f ", ol, zx, cv, bn);
        printf("\nupX(14): %f - upY(25): %f - upZ(36): %f\n", _14, _25, _36);
    }
    else
    {
        printf("Ortografica\n");
        printf("left(qa) : %f - right(ws): %f - bottom(ed): %f - top(rf) %f ", qa, ws, ed, rf);
        printf("near_val(tg): %f - far_val(yh): %f\neyeX(uj): %f - eyeY(ik): %f ", tg, yh, uj, ik);
        printf("eyeZ(ol): %f\ncenterX(zx): %f - centerY(cv): %f - centerZ(bn): %f ", ol, zx, cv, bn);
        printf("\nupX(14): %f - upY(25): %f - upZ(36): %f\n", _14, _25, _36);
    }
    printf("'0': reseta pontos  ',': troca camera  '+-': gira  '*':reseta giro\n");
    printf("'meio do mouse': ativa/desativa movimento   '*': reseta movimento\n");

    glutPostRedisplay();
}
void ChangeSize(GLsizei w, GLsizei h)
{
    // Para prevenir uma divis�o por zero
    if (h == 0)
        h = 1;

    // Especifica o tamanho da viewport
    glViewport(0, 0, w, h);

    // Calcula a corre��o de aspecto
    fAspect = (GLfloat)w / (GLfloat)h;

    glutPostRedisplay();
}
int main(int argc, char *argv[])
{
    // Procedimento de inicializacao da GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Controle da Camera");
    glutKeyboardFunc(CallbackTeclado);
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutMouseFunc(HandleMouse);
    glutPassiveMotionFunc(MotionMouse);
    SetupRC();
    glutMainLoop();
    return 0;
}
