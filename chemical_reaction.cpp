#include <GL/glut.h>
#include <string.h>
#include <iostream>

const int windowWidth = 800;
const int windowHeight = 600;
bool isReacting = false;
bool showMenu = false;
int animationStage = 0;
float beakerFillLevel1 = 0.0f;
float beakerFillLevel2 = 0.0f;
float beakerFillLevel3 = 0.0f;
float reactionSpeed = 0.01f;
int currentReaction = 0;

struct Reaction {
    const char* reactant1;
    const char* reactant2;
    const char* product;
    float color[3];
};

Reaction reactions[] = {
    {"2KMnO4​(aq)", "3H2​O2​(aq)", "2MnO2​(s)+2KOH(aq)+3O2​(g)", { 0.647059f , 0.164706f, 0.164706f}},
    {"CuSO4​(aq)", "2NaOH(aq)", "Cu(OH)2​(s)+Na2​SO4​(aq)", { 0.258824f, 0.258824f, 0.43594f}},
    {"Pb(NO3​)2​(aq)", "2KI(aq)", "PbI2​(s)+2KNO3​(aq)", {0.576471f,0.858824f,0.439216f}} 
};
const int numReactions = sizeof(reactions) / sizeof(Reaction);

void drawString(float x, float y, const char* string) {
    glRasterPos2f(x, y);
    int len = strlen(string);
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    }
}

void drawBeaker(float x, float y, float fillLevel, float color[3]) {
    // Draw the beaker
    glColor3f(0.0f, 0.0f, 0.0f); // Beaker outline color
    glBegin(GL_LINE_LOOP);
        glVertex2f(x - 0.2f, y - 0.5f);
        glVertex2f(x + 0.2f, y - 0.5f);
        glVertex2f(x + 0.2f, y + 0.5f);
        glVertex2f(x - 0.2f, y + 0.5f);
    glEnd();

    // Draw the beaker fill level
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.2f, y - 0.5f);
        glVertex2f(x + 0.2f, y - 0.5f);
        glVertex2f(x + 0.2f, y - 0.5f + fillLevel);
        glVertex2f(x - 0.2f, y - 0.5f + fillLevel);
    glEnd();
}

void displayMenu() {
    glColor3f(0.0f, 0.0f, 0.0f); // Text color
    drawString(-0.9f, 0.8f, "Select a Reaction:");
    for (int i = 0; i < numReactions; i++) {
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "%d: %s + %s -> %s", i + 1, reactions[i].reactant1, reactions[i].reactant2, reactions[i].product);
        drawString(-0.9f, 0.7f - i * 0.1f, buffer);
    }
    drawString(-0.9f, 0.3f - numReactions * 0.1f, "Press the number key to select a reaction.");
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (showMenu) {
        displayMenu();
    } else {
    	
        float colorReactant1[3] = {1.0f, 0.0f, 1.0f}; // Color for reactant 1
        float colorReactant2[3] = {0.0f, 1.0f, 1.0f}; // Color for reactant 2
	
	
        drawBeaker(-0.6f, 0.0f, beakerFillLevel1, colorReactant1);
        drawBeaker(0.0f, 0.0f, beakerFillLevel2, colorReactant2);
        drawBeaker(0.6f, 0.0f, beakerFillLevel3, reactions[currentReaction].color);
	
	// Display reactants and product
        glColor3f(0.0f, 0.0f, 0.0f); // Text color
        drawString(-0.7f, 0.6f, reactions[currentReaction].reactant1);
        drawString(-0.4f, 0.6f, "+"); // Draw the + symbol
        drawString(-0.1f, 0.6f, reactions[currentReaction].reactant2);
        drawString(0.2f, 0.6f, "------>"); // Draw the arrrow
        drawString(0.5f, 0.6f, reactions[currentReaction].product);
            
        if (isReacting) {
            
            
            // Draw arrow
            glColor3f(0.0f, 0.0f, 0.0f); // Arrow color
            glBegin(GL_LINES);
                glVertex2f(0.2f, 0.0f);
                glVertex2f(0.4f, 0.0f);
                glVertex2f(0.35f, 0.05f);
                glVertex2f(0.4f, 0.0f);
                glVertex2f(0.35f, -0.05f);
                glVertex2f(0.4f, 0.0f);
            glEnd();
            
            
        }
    }

    glutSwapBuffers();
}

void timer(int) {
   if (isReacting) {
        if (animationStage == 0) {
            beakerFillLevel1 += reactionSpeed;
            beakerFillLevel2 += reactionSpeed;
            if (beakerFillLevel1 >= 1.0f && beakerFillLevel2 >= 1.0f) {
                animationStage = 1;
                glutTimerFunc(1000, [](int) { animationStage = 2; }, 0);
            }
        } else if (animationStage == 2) {
            beakerFillLevel1 -= reactionSpeed;
            beakerFillLevel2 -= reactionSpeed;
            beakerFillLevel3 += reactionSpeed;
            if (beakerFillLevel1 <= 0.0f && beakerFillLevel2 <= 0.0f && beakerFillLevel3 >= 1.0f) {
                beakerFillLevel3 = 1.0f;
                isReacting = false;
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}

void chemical_keyboard(unsigned char key, int x, int y) {
    if (key == 27) { // ASCII value of Esc key is 27
        exit(0);
    } 
    else if (key == 'r' || key == 'R') {
        isReacting = !isReacting;
        if (isReacting) {
            animationStage = 0;
            beakerFillLevel1 = 0.0f;
            beakerFillLevel2 = 0.0f;
            beakerFillLevel3 = 0.0f;
        }
    } else if (key == 'n' || key == 'N') {
        currentReaction = (currentReaction + 1) % numReactions;
        isReacting = false;
        beakerFillLevel1 = 0.0f;
        beakerFillLevel2 = 0.0f;
        beakerFillLevel3 = 0.0f;
    } else if (key == 'm' || key == 'M') {
        showMenu = true;
        isReacting = false;
    } else if (key >= '1' && key <= '9') {
        int selectedReaction = key - '1';
        if (selectedReaction < numReactions) {
            currentReaction = selectedReaction;
            
            showMenu = false;
            isReacting = false;
            beakerFillLevel1 = 0.0f;
            beakerFillLevel2 = 0.0f;
            beakerFillLevel3 = 0.0f;
        }
    }
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Background color white
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

extern "C" void start_chemical_reaction() {
    int argc = 1;
    char* argv[1] = {strdup("Chemical Reaction")};
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Chemical Reaction Simulation");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(chemical_keyboard);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
   
}

