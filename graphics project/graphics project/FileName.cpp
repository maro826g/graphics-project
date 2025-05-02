#include <windows.h>
#include <GL/glut.h>
#include <iostream>

const int MAZE_WIDTH = 20;
const int MAZE_HEIGHT = 20;

int level = 0;
bool gameEnded = false;

int playerX = 0, playerZ = 0;
int goalX = 0, goalZ = 0;

// ==== Level Definitions ====
int maze1[MAZE_HEIGHT][MAZE_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,3,0,0,0,1,0,1,0,0,0,0,0,1,0,1,1,1},
    {1,1,1,0,1,1,0,1,0,1,0,1,1,1,0,1,0,1,1,1},
    {1,1,1,0,0,1,0,0,0,0,0,1,0,1,0,0,0,1,1,1},
    {1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1},
    {1,1,1,1,0,0,0,1,2,0,0,1,0,0,0,1,0,1,1,1},
    {1,1,1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,1,1},
    {1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1},
    {1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,1,1},
    {1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1},
    {1,1,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,1,1},
    {1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1},
    {1,1,1,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,1,1},
    {1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1},
    {1,1,1,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

int maze2[MAZE_HEIGHT][MAZE_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,1,1,1},
    {1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1},
    {1,1,0,0,1,0,0,1,0,1,0,0,0,0,0,1,0,1,1,1},
    {1,1,1,0,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1},
    {1,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,1,1},
    {1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1},
    {1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1,1},
    {1,1,1,0,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1},
    {1,1,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1},
    {1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1},
    {1,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,1,1},
    {1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1},
    {1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,1,1},
    {1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1},
    {1,1,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

int maze3[MAZE_HEIGHT][MAZE_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,3,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,1,1,1,1,1,0,1,1,1,1,0,1,1},
    {1,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,1,1},
    {1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,0,1},
    {1,0,0,0,0,0,1,0,1,0,1,0,0,0,1,0,1,1,0,1},
    {1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,0,1,0,1},
    {1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,1,0,1,0,1},
    {1,0,1,0,1,0,1,0,1,1,1,1,1,0,0,1,0,0,0,1},
    {1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,1,1,1,0,1},
    {1,0,1,0,1,0,1,1,1,1,1,1,1,0,0,0,0,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,0,1},
    {1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,1},
    {1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,1},
    {1,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,1,1},
    {1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,0,1,1},
    {1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,2},
    {1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

// === Array of Mazes ===
int (*mazes[])[MAZE_WIDTH] = { maze1, maze2, maze3 };
const int totalLevels = sizeof(mazes) / sizeof(mazes[0]);

// === Initialization ===
void loadLevel(int lvl) {
    if (lvl >= totalLevels) {
        std::cout << " All levels complete!\n";
        exit(0);
    }

    level = lvl;
    gameEnded = false;

    for (int z = 0; z < MAZE_HEIGHT; ++z) {
        for (int x = 0; x < MAZE_WIDTH; ++x) {
            if (mazes[level][z][x] == 2) {
                goalX = x;
                goalZ = z;
            }
            if (mazes[level][z][x] == 3) {
                playerX = x;
                playerZ = z;
                mazes[level][z][x] = 0; // Clear start position
            }
        }
    }

    std::cout << " Level " << (level + 1) << " started!\n";
}

void initLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lightPos[] = { 5.0f, 10.0f, 5.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    GLfloat ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    initLighting();
    loadLevel(0);
}

// === Drawing ===
void drawCube(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawPlayer(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(0.0f, 0.8f, 1.0f);
    glutSolidSphere(0.3, 20, 20);
    glPopMatrix();
}

void drawDoor(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(0.0f, 1.0f, 0.0f);
    glutSolidCube(1.0);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(MAZE_WIDTH / 2.0, 16.0, MAZE_HEIGHT + 3,
        MAZE_WIDTH / 2.0, 0.0, MAZE_HEIGHT / 2.0,
        0.0, 1.0, 0.0);

    // Floor
    glColor3f(0.3f, 0.3f, 0.3f);
    for (int z = 0; z < MAZE_HEIGHT; ++z) {
        for (int x = 0; x < MAZE_WIDTH; ++x) {
            glPushMatrix();
            glTranslatef(x, -0.5f, z);
            glScalef(1.0f, 0.1f, 1.0f);
            glutSolidCube(1.0);
            glPopMatrix();
        }
    }

    // Walls
    glColor3f(0.6f, 0.1f, 0.1f);
    for (int z = 0; z < MAZE_HEIGHT; ++z) {
        for (int x = 0; x < MAZE_WIDTH; ++x) {
            if (mazes[level][z][x] == 1) {
                drawCube(x, 0.2f, z);
            }
        }
    }

    drawDoor(goalX, 0.5f, goalZ);
    drawPlayer(playerX, 0.3f, playerZ);

    glutSwapBuffers();
}

// === Movement & Input ===
bool canMove(int x, int z) {
    if (x < 0 || x >= MAZE_WIDTH || z < 0 || z >= MAZE_HEIGHT)
        return false;
    return mazes[level][z][x] != 1;
}

void checkWin() {
    if (playerX == goalX && playerZ == goalZ && !gameEnded) {
        gameEnded = true;
        std::cout << " You completed Level " << (level + 1) << "!\n";
        glutTimerFunc(1000, [](int) {
            loadLevel(level + 1);
            glutPostRedisplay();
            }, 0);
    }
}

void specialKeys(int key, int, int) {
    if (gameEnded) return;

    int newX = playerX;
    int newZ = playerZ;

    switch (key) {
    case GLUT_KEY_UP:    newZ -= 1; break;
    case GLUT_KEY_DOWN:  newZ += 1; break;
    case GLUT_KEY_LEFT:  newX -= 1; break;
    case GLUT_KEY_RIGHT: newX += 1; break;
    }

    if (canMove(newX, newZ)) {
        playerX = newX;
        playerZ = newZ;
        checkWin();
    }

    glutPostRedisplay();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / (float)h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, aspect, 1, 100);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(2000, 780);
    glutCreateWindow("speedy sphere");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}