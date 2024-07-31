#include <GL/glut.h>
#include <iostream>

#define SIZE 20

int ww = 1000, wh = 700;
double xmin = 0, ymin = 0;
int size = 10;

extern "C" void start_chemical_reaction(); // Declare the function from chemical_reaction.cpp

void print_text(float x, float y, const char* arr) {
    glRasterPos2f(x, y);
    int i = 0;
    while (arr[i] != '\0') {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, arr[i]);
        i++;
    }
}

void display_welcome() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 1, 0.5); // spring green
    print_text(350, 600, "CMR INSTITUTE OF TECHNOLOGY");
    glColor3f(0.56, 0.56, 0.74); // light STEEL Blue
    print_text(300, 550, "DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
    glColor3f(0.8, 0.498, 0.196); // gold
    print_text(270, 500, "18CSL67 - COMPUTER GRAPHICS WITH MINI PROJECT LABORATORY");

    glColor3f(0.196, 0.6, 0.8); // sky blue
    print_text(30, 450, "______________________________________________________________________________________________________________________________________________________________________________");

    glColor3f(0.196, 0.6, 0.8); // sky blue
    print_text(350, 400, "CHEMICAL REACTION - SIMULATION");

    glColor3f(0.85, 0.85, 0.1);
    print_text(100, 350, "Created By");
    glColor3f(0.45, 0.85, 0.57);
    print_text(80, 300, "SHREYAS JIDDIBAGIL (1CR21CS175)");
    print_text(80, 250, "SOMNATH PATIL (1CR21CS181)");

    glColor3f(0.85, 0.85, 0.1);
    print_text(700, 350, "Guided By");
    glColor3f(0.45, 0.85, 0.57);
    print_text(600, 300, "DR. PREETHI SHEBA HEPSIBA, ASSOSCIATE PROFESSOR");
    print_text(600, 250, "MRS. SREEDEVI N, ASSISTANT PROFESSOR");

    glColor3f(1, 0.1, 0.1); // RED
    print_text(400, 100, "PRESS <<ENTER>>  TO BEGIN");

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 13) { // ASCII value of Enter key is 13
        start_chemical_reaction();
    }
}

void welcome_init() {
    glClearColor(0, 0, 0, 1.0); // Background color black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, ww, 0.0, wh);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(ww, wh);
    glutCreateWindow("Welcome Screen");
    welcome_init();
    glutDisplayFunc(display_welcome);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

