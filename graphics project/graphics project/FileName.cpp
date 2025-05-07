#include <windows.h>
#include <GL/glut.h>
#include <iostream>

// Add stb_image.h for texture loading
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const int MAZE_WIDTH = 20;
const int MAZE_HEIGHT = 20;

int level = 0;
bool gameEnded = false;

int playerX = 0, playerZ = 0;
int goalX = 0, goalZ = 0;

// Texture variables
unsigned int wallTexture;
unsigned int floorTexture;
unsigned int doorTexture;
int width, height, nrChannels;
unsigned char* data;

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

// === Texture Loading Functions ===
void check(unsigned char* data, unsigned int* texture_id) {
    if (data) {
        glGenTextures(1, texture_id);
        glBindTexture(GL_TEXTURE_2D, *texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void loadTextures() {
    // Load wall texture
    data = stbi_load("room.jpeg", &width, &height, &nrChannels, 0);
    check(data, &wallTexture);

    // Load floor texture
    data = stbi_load("floor.jpeg", &width, &height, &nrChannels, 0);
    check(data, &floorTexture);

    // Load door texture
    data = stbi_load("wall.bmp", &width, &height, &nrChannels, 0);
    check(data, &doorTexture);
}

// === Initialization ===
void loadLevel(int lvl) {
    if (lvl >= totalLevels) {
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

    // Enable texturing
    glEnable(GL_TEXTURE_2D);

    // Load all textures
    loadTextures();

    initLighting();
    loadLevel(0);
}

// === Drawing ===
void drawTexturedCube(float x, float y, float z, unsigned int textureID) {
    glPushMatrix();
    glTranslatef(x, y, z);

    // Enable texturing for this cube
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Define the vertices of a cube
    float vertices[][3] = {
        {-0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, -0.5f}, {0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, -0.5f},  // Front face
        {-0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, 0.5f}, {0.5f, 0.5f, 0.5f}, {-0.5f, 0.5f, 0.5f},     // Back face
    };

    // Texture coordinates
    float texCoords[][2] = {
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
    };

    // Draw the cube with textures
    glBegin(GL_QUADS);

    // Front face
    glTexCoord2f(texCoords[0][0], texCoords[0][1]); glVertex3fv(vertices[0]);
    glTexCoord2f(texCoords[1][0], texCoords[1][1]); glVertex3fv(vertices[1]);
    glTexCoord2f(texCoords[2][0], texCoords[2][1]); glVertex3fv(vertices[2]);
    glTexCoord2f(texCoords[3][0], texCoords[3][1]); glVertex3fv(vertices[3]);

    // Back face
    glTexCoord2f(texCoords[0][0], texCoords[0][1]); glVertex3fv(vertices[4]);
    glTexCoord2f(texCoords[1][0], texCoords[1][1]); glVertex3fv(vertices[5]);
    glTexCoord2f(texCoords[2][0], texCoords[2][1]); glVertex3fv(vertices[6]);
    glTexCoord2f(texCoords[3][0], texCoords[3][1]); glVertex3fv(vertices[7]);

    // Top face
    glTexCoord2f(texCoords[0][0], texCoords[0][1]); glVertex3fv(vertices[3]);
    glTexCoord2f(texCoords[1][0], texCoords[1][1]); glVertex3fv(vertices[2]);
    glTexCoord2f(texCoords[2][0], texCoords[2][1]); glVertex3fv(vertices[6]);
    glTexCoord2f(texCoords[3][0], texCoords[3][1]); glVertex3fv(vertices[7]);

    // Bottom face
    glTexCoord2f(texCoords[0][0], texCoords[0][1]); glVertex3fv(vertices[0]);
    glTexCoord2f(texCoords[1][0], texCoords[1][1]); glVertex3fv(vertices[1]);
    glTexCoord2f(texCoords[2][0], texCoords[2][1]); glVertex3fv(vertices[5]);
    glTexCoord2f(texCoords[3][0], texCoords[3][1]); glVertex3fv(vertices[4]);

    // Left face
    glTexCoord2f(texCoords[0][0], texCoords[0][1]); glVertex3fv(vertices[0]);
    glTexCoord2f(texCoords[1][0], texCoords[1][1]); glVertex3fv(vertices[4]);
    glTexCoord2f(texCoords[2][0], texCoords[2][1]); glVertex3fv(vertices[7]);
    glTexCoord2f(texCoords[3][0], texCoords[3][1]); glVertex3fv(vertices[3]);

    // Right face
    glTexCoord2f(texCoords[0][0], texCoords[0][1]); glVertex3fv(vertices[1]);
    glTexCoord2f(texCoords[1][0], texCoords[1][1]); glVertex3fv(vertices[5]);
    glTexCoord2f(texCoords[2][0], texCoords[2][1]); glVertex3fv(vertices[6]);
    glTexCoord2f(texCoords[3][0], texCoords[3][1]); glVertex3fv(vertices[2]);

    glEnd();

    // Disable texturing after drawing
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void drawTexturedFloor(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(1.0f, 0.1f, 1.0f);

    // Enable texturing for the floor
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, floorTexture);

    // Draw a textured quad for the floor tile
    glBegin(GL_QUADS);

    // Top face of the floor (slightly scaled cube)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    glEnd();

    // Disable texturing after drawing
    glDisable(GL_TEXTURE_2D);

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
    // Use texture for the door
    glColor3f(1.0f, 1.0f, 1.0f); // Set to white to show texture properly
    drawTexturedCube(x, y, z, doorTexture);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(MAZE_WIDTH / 2.0, 16.0, MAZE_HEIGHT + 3,
        MAZE_WIDTH / 2.0, 0.0, MAZE_HEIGHT / 2.0,
        0.0, 1.0, 0.0);

    // Floor with texture
    glColor3f(1.0f, 1.0f, 1.0f); // Set to white to show texture properly
    for (int z = 0; z < MAZE_HEIGHT; ++z) {
        for (int x = 0; x < MAZE_WIDTH; ++x) {
            drawTexturedFloor(x, -0.5f, z);
        }
    }

    // Walls with texture
    glColor3f(1.0f, 1.0f, 1.0f); // Set to white to show texture properly
    for (int z = 0; z < MAZE_HEIGHT; ++z) {
        for (int x = 0; x < MAZE_WIDTH; ++x) {
            if (mazes[level][z][x] == 1) {
                drawTexturedCube(x, 0.2f, z, wallTexture);
            }
        }
    }

    // Door with texture
    drawDoor(goalX, 0.5f, goalZ);

    // Player doesn't need a texture
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