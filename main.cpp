#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <cmath>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
using namespace std;


// Window dimensions
int windowWidth = 800;
int windowHeight = 600;

// Camera position and movement variables
float cameraPosX = -1.5f;
float cameraPosY = 1.5f;
float cameraPosZ = 0.0f;
float cameraYaw = -90.0f;
float cameraPitch = 0.0f;
float cameraSpeed = 0.2f;
float cameraStep = 5.0f;
GLboolean thirdPerson = true;
GLboolean firstPerson = false;
GLboolean firstLeftButton = true;

// score values 
float scoreHight = 0.5f;
string scoreTotal = "25";
string  scoreCurrent = "0";
float scorePosX[25];
float scorePosZ[25];
GLboolean scoreFound[25];
GLboolean finished = false;
float HP = 100;

// ball position and movement variables
float ballPosX = 30.0f;
float ballPosY = 0.0f;
float ballPosZ = 30.0f;
float ballspeed = 0.1f;
float ballJumpRadios = 2.5;
float ballJumpStep = 2.5;
float ballJumpAngle = 0.0;
float ballJumpRotation = 0.0f;
GLboolean isBallNotJumping = true;

// Cow position and movement variables
float cowPosX = 0.0f;
float cowPosY = 0.0f;
float cowPosZ = 0.0f;
float cowRotation = 0.0f;
float cowSpeed = 0.2f;
float cowRotationSpeed = 0.2f;
float cowTailXAngel = 0.0f;
float cowTailZAngel = 0.0f;
float cowTailBuffer = 3.0;
float cowHeadZAngel = 0.0f;
float cowHeadYAngel = 0.0f;
float cowHeadBuffer = 3.0;
float cowJumpRadios = 2.5;
float cowJumpStep = 9.8;
float cowJumpAngle = 0.0;
float cowJumpRotation = 0.0f;
float cowYaw = 90.0f;
float cowPitch = 0.0f;
float cowLegRange = 30.0f;
float cowLegAngle = 0.0f;
float cowLegRotationZ = 0.0f;
float cowLegRotationX = 0.0f;
float cowLegStep = 2.0f;
float cowDirection[] = { 1.0f, 0.0f, 0.0f };
GLboolean isNotJumping = true;

// Light position
float lightPosition[] = { 1.0f, 2.0f, 1.0f, 1.0f };
float lightRotationSpeed = 0.1f;
float lightStep = 0.5f;
float light0AmbientRed = 0.2;
float light0AmbientGreen = 0.2;
float light0AmbientBlue = 0.0;
float light1AmbientRed = 0.2;
float light1AmbientGreen = 0.2;
float light1AmbientBlue = 0.0;
float lightAmbientStep = 0.1;
float light1XPos = 0.0f;
float light1YPos = 0.5f;
float light1ZPos = 0.0f;
float light1Range = 0.0;
float light1XAngle = 0.0;
float light1YAngle = 0.0;
float light1ZAngle = 0.0;
float light1Angle = 0.0;
GLfloat lightAngle = 0.0f; 

// Box values
float boxAngle = 0.1f;
float boxStep = 0.5f;

// Ring values
float ringAngle = 0.0f;
float ringStep = 1.0f;

// Meadow color
float meadowColor[] = { 0.4f, 0.8f, 0.2f };

GLuint trunkTextureID;
GLuint leavesTextureID;
GLuint grassTextureID;
GLuint lamppostTextureID;
GLuint cowTextureID;
GLuint boxTextureID;
GLuint sunTextureID;
GLuint wallTextureID;
GLuint skyTextureID;
GLuint ballTextureID;
float grassOffset = 0.0f;
float grassDelta = 0.0f;

// function to load the textures
void loadTextures()
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);

    // Load trunk texture
    unsigned char* trunkData = stbi_load("trunk_texture.jpg", &width, &height, &channels, 0);
    if (!trunkData)
    {
        printf("Failed to load trunk texture\n");
        return;
    }
    glGenTextures(1, &trunkTextureID);
    glBindTexture(GL_TEXTURE_2D, trunkTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, trunkData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(trunkData);

    // Load leaves texture
    unsigned char* leavesData = stbi_load("leaves_texture.jpg", &width, &height, &channels, 0);
    if (!leavesData)
    {
        printf("Failed to load leaves texture\n");
        return;
    }
    glGenTextures(1, &leavesTextureID);
    glBindTexture(GL_TEXTURE_2D, leavesTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, leavesData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(leavesData);

    // Load grass texture
    unsigned char* grassData = stbi_load("grass_texture.jpg", &width, &height, &channels, 0);
    if (!grassData)
    {
        printf("Failed to load grass texture\n");
        return;
    }
    glGenTextures(1, &grassTextureID);
    glBindTexture(GL_TEXTURE_2D, grassTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, grassData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(grassData);

    // Load lamppot texture
    unsigned char* lamppsotData = stbi_load("lamppsot_texture.jpg", &width, &height, &channels, 0);
    if (!lamppsotData)
    {
        printf("Failed to load grass texture\n");
        return;
    }
    glGenTextures(1, &lamppostTextureID);
    glBindTexture(GL_TEXTURE_2D, lamppostTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, lamppsotData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(lamppsotData);

    // Load cow texture
    unsigned char* cowData = stbi_load("cow_texture.jpg", &width, &height, &channels, 0);
    if (!cowData)
    {
        printf("Failed to load cow_texture texture\n");
        return;
    }
    glGenTextures(1, &cowTextureID);
    glBindTexture(GL_TEXTURE_2D, cowTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, cowData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(cowData);

    // Load box texture
    unsigned char* boxData = stbi_load("box_texture.jpg", &width, &height, &channels, 0);
    if (!boxData)
    {
        printf("Failed to load box texture\n");
        return;
    }
    glGenTextures(1, &boxTextureID);
    glBindTexture(GL_TEXTURE_2D, boxTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, boxData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(boxData);

    // Load sun texture
    unsigned char* sunData = stbi_load("sun_texture.jpg", &width, &height, &channels, 0);
    if (!sunData)
    {
        printf("Failed to load sun texture\n");
        return;
    }
    glGenTextures(1, &sunTextureID);
    glBindTexture(GL_TEXTURE_2D, sunTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, sunData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(sunData);

    // Load wall texture
    unsigned char* wallData = stbi_load("wall_texture.jpg", &width, &height, &channels, 0);
    if (!wallData)
    {
        printf("Failed to load wall texture\n");
        return;
    }
    glGenTextures(1, &wallTextureID);
    glBindTexture(GL_TEXTURE_2D, wallTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, wallData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(wallData);

    // Load sky texture
    unsigned char* skyData = stbi_load("sky_texture.jpg", &width, &height, &channels, 0);
    if (!skyData)
    {
        printf("Failed to load sky texture\n");
        return;
    }
    glGenTextures(1, &skyTextureID);
    glBindTexture(GL_TEXTURE_2D, skyTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, skyData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(skyData);

    // Load ball texture
    unsigned char* ballData = stbi_load("ball_texture.jpg", &width, &height, &channels, 0);
    if (!ballData)
    {
        printf("Failed to load ball texture\n");
        return;
    }
    glGenTextures(1, &ballTextureID);
    glBindTexture(GL_TEXTURE_2D, ballTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, ballData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(ballData);
}

// function to controll the cow's jump
void jump(int value) {
    if (value != 1) { // cow jumping
        if (isNotJumping == false) {

            cowJumpAngle += cowJumpStep;
            cowTailXAngel += cowJumpStep * 8;
            if (value == 7) {
                cowJumpRotation += cowJumpStep * 4;
            }
            if (value == 9) {
                cowJumpRotation -= cowJumpStep * 4;
            }
            cowPosY = cowJumpRadios * sin(cowJumpAngle * 3.14159f / 180.0f);
            if (cowJumpAngle > 180.0f) {
                cowJumpAngle = 0.0f;
                isNotJumping = true;
                cowPosY = 0;
                cowJumpRotation = 0;
                return;
            }
        }
    }
    else { // ball jumping
        if (isBallNotJumping == false) {
            ballJumpAngle += ballJumpStep;
            ballJumpRotation += ballJumpStep * 2;
            ballPosY = ballJumpRadios * sin(ballJumpAngle * 3.14159f / 180.0f);
            if (ballJumpAngle > 180.0f) {
                ballJumpAngle = 0.0f;
                isBallNotJumping = true;
                ballPosY = 0;
                ballJumpRotation = 0;
                return;
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, jump, value);
}

// function to update the box rotation and grass movment
void update(int value)
{
    // Update box's angle
    boxAngle += boxStep;
    if (boxStep > 360.0f)
        boxStep -= 360.0f;
    // Update grass offset for animation
    grassDelta += 0.05;
    grassOffset = sin(grassDelta * 3.14159f / 180.0f);
    if (grassDelta > 360.0f)
        grassDelta -= 360.0f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// function to update light0 (sun) angle
void updateLight()
{
    // Update the light angle
    lightAngle += lightStep;

    // Keep the angle within 360 degrees
    if (lightAngle >= 90.0f)
        lightAngle -= 180.0f;

    // Calculate the light direction
    GLfloat lightDirection[] = { 0.0f, 1.0f, 0.0f, 0.0f };
    glPushMatrix();
    glRotatef(lightAngle, 0.0f, 0.0f, 1.0f);
    glLightfv(GL_LIGHT0, GL_POSITION, lightDirection);
    glPopMatrix();
}

// function to draw a sphere with texture
void sphereTexture(float radius, int slices, int stacks, GLuint textureID) {
    // Enable texturing
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Calculate the angle increment based on the number of slices and stacks
    float sliceAngle = 2.0f * 3.14159f / slices;
    float stackAngle = 3.14159f / stacks;

    // Iterate through the stacks and slices
    for (int stack = 0; stack < stacks; stack++) {
        float phi1 = stack * stackAngle;
        float phi2 = (stack + 1) * stackAngle;

        glBegin(GL_TRIANGLE_STRIP);
        for (int slice = 0; slice <= slices; slice++) {
            float theta = slice * sliceAngle;

            // Calculate the vertex positions and texture coordinates
            float x1 = radius * sin(phi1) * cos(theta);
            float y1 = radius * sin(phi1) * sin(theta);
            float z1 = radius * cos(phi1);

            float x2 = radius * sin(phi2) * cos(theta);
            float y2 = radius * sin(phi2) * sin(theta);
            float z2 = radius * cos(phi2);

            // Calculate the texture coordinates
            float s = (float)slice / slices;
            float t1 = (float)stack / stacks;
            float t2 = (float)(stack + 1) / stacks;

            // Set the texture coordinates and vertices
            glTexCoord2f(s, t1);
            glVertex3f(x1, y1, z1);

            glTexCoord2f(s, t2);
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }

    // Disable texturing after drawing the sphere
    glDisable(GL_TEXTURE_2D);
}

// function to enable light1 (lamppost)
void enableLighting1()
{

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);

    // Set light properties
    GLfloat lightPosition[] = { -1.0f + light1XPos, 7.5f + light1YPos, -3.0f + light1ZPos, 1.0f };
    GLfloat lightAmbient[] = { light1AmbientRed, light1AmbientGreen, light1AmbientBlue, 1.0f };
    GLfloat lightDiffuse[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 0.0f, 1.0f };

    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);

    glPushMatrix();
    glRotatef(light1XAngle, 1, 0, 0);
    glRotatef(light1YAngle, 0, 1, 0);
    glRotatef(light1ZAngle, 0, 0, 1);
    // Set spotlight properties
    GLfloat spotDirection[] = { 0.0f, -1.0f, 0.0f };
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 75.0f + light1Angle);

    // Set light range
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.5f + light1Range);
    glPopMatrix();
}

// Function to handle key press events
void handleKeyPress(unsigned char key, int x, int y) {
    // Move the camera based on key input
    float cameraDirX = -std::sin(cameraYaw * 3.14159f / 180.0f) * std::cos(cameraPitch * 3.14159f / 180.0f);
    float cameraDirY = -std::sin(cameraPitch * 3.14159f / 180.0f);
    float cameraDirZ = -std::cos(cameraYaw * 3.14159f / 180.0f) * std::cos(cameraPitch * 3.14159f / 180.0f);

    float cowDirX = -std::sin(cowYaw * 3.14159f / 180.0f) * std::cos(cowPitch * 3.14159f / 180.0f);
 //   float cameraDirY = -std::sin(cameraPitch * 3.14159f / 180.0f);
    float cowDirZ = -std::cos(cowYaw * 3.14159f / 180.0f) * std::cos(cowPitch * 3.14159f / 180.0f);

    if (key == 'w' || key == 'W') { // forword
        cowPosX -= cowSpeed * cowDirZ;
        cowPosZ += cowSpeed * cowDirX;
        cowLegAngle += cowLegStep;
        cowLegRotationZ = cowLegRange * sin(cowLegAngle++);
        cowLegRotationX = 0;
    }
    if (key == 's' || key == 'S') { // backword
        cowPosX += cowSpeed * cowDirZ;
        cowPosZ -= cowSpeed * cowDirX;
        cowLegAngle -= cowLegStep;
        cowLegRotationZ = cowLegRange * sin(cowLegAngle++);
        cowLegRotationX = 0;
    }
    if (key == 'd' || key == 'D') { // right
        cowPosX -= cowSpeed * cowDirX;
        cowPosZ -= cowSpeed * cowDirZ;
        cowLegAngle -= cowLegStep;
        cowLegRotationX = (cowLegRange/2) * sin(cowLegAngle++);
        cowLegRotationZ = 0;

    }
    if (key == 'a' || key == 'A') { // left
        cowPosX += cowSpeed * cowDirX;
        cowPosZ += cowSpeed * cowDirZ;
        cowLegAngle += cowLegStep;
        cowLegRotationX = (cowLegRange / 2) * sin(cowLegAngle++);
        cowLegRotationZ = 0;
    }
    if (cowLegAngle > 360) {
        cowLegAngle -= 360;
    }
    if (cowLegAngle < -360) {
        cowLegAngle += 360;
    }
    // tail movment
    if (key == 'z' || key == 'Z') {
        cowTailXAngel += cowTailBuffer;
    }
    if (key == 'x' || key == 'X') {
        cowTailXAngel -= cowTailBuffer;
    }
    if (key == 'c' || key == 'C') {
        cowTailZAngel += cowTailBuffer;
    }
    if (key == 'v' || key == 'V') {
        cowTailZAngel -= cowTailBuffer;
    }
    // head movment
    if (key == 'f' || key == 'F') {
        cowHeadZAngel += cowHeadBuffer;
    }
    if (key == 'g' || key == 'G') {
        cowHeadZAngel -= cowHeadBuffer;
    }
    if (key == 'h' || key == 'H') {
        cowHeadYAngel += cowHeadBuffer;
    }
    if (key == 'j' || key == 'J') {
        cowHeadYAngel -= cowHeadBuffer;
    }
    if (key == '8') { // camera forword
        cameraPosX += cameraSpeed * cameraDirX;
        cameraPosY += cameraSpeed * cameraDirY;
        cameraPosZ += cameraSpeed * cameraDirZ;
    }
    if (key == '1') { // first person mode
        firstPerson = true;
        thirdPerson = false;
        scoreHight = 0;
    }
    if (key == '2') { // spector mode
        firstPerson = false;
        thirdPerson = false;
    }
    if (key == '3') { // third person mode
        firstPerson = false;
        thirdPerson = true;
        scoreHight = 1;
    }
    if (key == '4') { // camera left
        cameraPosX += cameraSpeed * cameraDirZ;
        cameraPosZ -= cameraSpeed * cameraDirX;
        cameraPosY += cameraSpeed * cameraDirY;
    }
    if (key == '6') { // camra right
        cameraPosX -= cameraSpeed * cameraDirZ;
        cameraPosZ += cameraSpeed * cameraDirX;
        cameraPosY += cameraSpeed * cameraDirY;
    }
    if (key == '5') { // camera backword
        cameraPosX -= cameraSpeed * cameraDirX;
        cameraPosY -= cameraSpeed * cameraDirY;
        cameraPosZ -= cameraSpeed * cameraDirZ;
    }
    if (key == 'q' || key == 'Q') { // cow rotate left
        cowYaw += 1;
    }
    if (key == 'e' || key == 'E') { // cow rotate right
        cowYaw -= 1;
    }
    if (key == '+') { // camera zoom in
        cameraPosX += cameraStep * cameraDirX;
        cameraPosY += cameraStep * cameraDirY;
        cameraPosZ += cameraStep * cameraDirZ;
    }
    if (key == '-') { // camera zoom out
        cameraPosX -= cameraStep * cameraDirX;
        cameraPosY -= cameraStep * cameraDirY;
        cameraPosZ -= cameraStep * cameraDirZ;
    }
    if ((key == ' ') && (isNotJumping == true)) { // jump
        isNotJumping = false;
        jump(5);
    }
    
}

// function to handle mouse click (to drag the diraction)
void mouseClick(int button, int state, int x, int y) {
    static int lastX = x;
    static int lastY = y;

    // Move the camera based on key input
    float cameraDirX = -std::sin(cameraYaw * 3.14159f / 180.0f) * std::cos(cameraPitch * 3.14159f / 180.0f);
    float cameraDirY = -std::sin(cameraPitch * 3.14159f / 180.0f);
    float cameraDirZ = -std::cos(cameraYaw * 3.14159f / 180.0f) * std::cos(cameraPitch * 3.14159f / 180.0f);

    // Move the cow based on key input
    float cowDirX = -std::sin(cowYaw * 3.14159f / 180.0f) * std::cos(cowPitch * 3.14159f / 180.0f);
    float cowDirY = -std::sin(cowPitch * 3.14159f / 180.0f);
    float cowDirZ = -std::cos(cowYaw * 3.14159f / 180.0f) * std::cos(cowPitch * 3.14159f / 180.0f);
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN) {
            if (firstLeftButton == true) {
                lastX = x;
                lastY = y;
                firstLeftButton = false;
            }
        }
        else {
            int deltaX = x - lastX;
            int deltaY = y - lastY;

            // Flip camera motion with the mouse in the x-axis
            cameraYaw += (deltaX * cameraSpeed) * 2;
            // Clamp the camera yaw to the range [0, 360)
            if (cameraYaw >= 360.0f)
                cameraYaw -= 360.0f;
            else if (cameraYaw < 0.0f)
                cameraYaw += 360.0f;

            // Flip cow motion with the mouse in the x-axis
            cowYaw += (deltaX * cowSpeed) * 2;
            // Clamp the camera yaw to the range [0, 360)
            if (cowYaw >= 360.0f)
                cowYaw -= 360.0f;
            else if (cowYaw < 0.0f)
                cowYaw += 360.0f;

            // Add y-axis movement to the camera
            cameraPitch -= (deltaY * cameraSpeed) * 2;
            // Clamp the camera pitch to the range [-90, 90]
            if (cameraPitch > 90.0f)
                cameraPitch = 90.0f;
            else if (cameraPitch < -90.0f)
                cameraPitch = -90.0f;

            // Add y-axis movement to the cow
            cowPitch -= (deltaY * cowSpeed) * 2;
            // Clamp the camera pitch to the range [-90, 90]
            if (cowPitch > 90.0f)
                cowPitch = 90.0f;
            else if (cowPitch < -90.0f)
                cowPitch = -90.0f;
            firstLeftButton = true;
        }        
    }
}


// Function to handle mouse movement events
void handleMouseMove(int x, int y) {
    static int lastX = x;
    static int lastY = y;

    int deltaX = x - lastX;
    int deltaY = y - lastY;

    lastX = x;
    lastY = y;

    // Flip camera motion with the mouse in the x-axis
    cameraYaw -= deltaX * cameraSpeed;
    // Clamp the camera yaw to the range [0, 360)
    if (cameraYaw >= 360.0f)
        cameraYaw -= 360.0f;
    else if (cameraYaw < 0.0f)
        cameraYaw += 360.0f;

    // Flip cow motion with the mouse in the x-axis
    cowYaw -= deltaX * cowSpeed;
    // Clamp the camera yaw to the range [0, 360)
    if (cowYaw >= 360.0f)
        cowYaw -= 360.0f;
    else if (cowYaw < 0.0f)
        cowYaw += 360.0f;

    // Add y-axis movement to the camera
    cameraPitch += deltaY * cameraSpeed;
    // Clamp the camera pitch to the range [-90, 90]
    if (cameraPitch > 90.0f)
        cameraPitch = 90.0f;
    else if (cameraPitch < -90.0f)
        cameraPitch = -90.0f;

    // Add y-axis movement to the camera
    cowPitch += deltaY * cowSpeed;
    // Clamp the camera pitch to the range [-90, 90]
    if (cowPitch > 90.0f)
        cowPitch = 90.0f;
    else if (cowPitch < -90.0f)
        cowPitch = -90.0f;
}

// Function to handle window reshape events
void handleReshape(int width, int height) {
    // Update the window dimensions
    windowWidth = width;
    windowHeight = height;

    // Set the viewport to match the new window size
    glViewport(0, 0, width, height);

    // Set the perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / height, 0.1f, 150.0f);
}

// Function to draw a cow
void drawCow() {

    // Draw body
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(1.5f, 0.7f, 1.0f);
    sphereTexture(0.5f, 50, 50, cowTextureID);
    glPopMatrix();

    // Draw udders
    glColor3i(255, 105, 180);
    glPushMatrix();
    glTranslatef(-0.25, -0.2, 0);
    glutSolidSphere(0.25f, 20, 20);
    glPopMatrix();


    glPushMatrix();
    glRotatef(cowHeadZAngel, 0.0f, 0.0f, 1.0f);
    glRotatef(cowHeadYAngel, 0.0f, 1.0f, 0.0f);

    // Draw head
    glPushMatrix();
    glTranslatef(0.7f, 0.4f, 0.0f);
    sphereTexture(0.3f, 50, 50, cowTextureID);
    glPopMatrix();

    // Draw ears
    glPushMatrix();
    glTranslatef(0.80f, 0.6f, 0.3f);
    glRotatef(45.0f, 0.0f, 2.0f, 1.0f);
    glScalef(0.10f, 0.3f, 0.5f);
    sphereTexture(0.3f, 50, 50, cowTextureID);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.80f, 0.6f, -0.3f);
    glRotatef(-45.0f, 0.0f, 2.0f, 1.0f);
    glScalef(0.10f, 0.3f, 0.5f);
    sphereTexture(0.3f, 50, 50, cowTextureID);
    glPopMatrix();

    // Draw nose
    glColor3f(0.8f, 0.6f, 0.4f);
    glPushMatrix();
    glTranslatef(1.05f, 0.4f, 0.0f);
    glScalef(0.1f, 0.2f, 0.2f);
    glutSolidSphere(0.5f, 20, 20);
    glPopMatrix();

    // Draw eyes
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.9f, 0.5f, 0.15f);
    glScalef(0.05f, 0.05f, 0.05f);
    glutSolidSphere(1.0f, 20, 20);
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(0.945f, 0.52f, 0.15f);
    glScalef(0.05f, 0.05f, 0.05f);
    glutSolidSphere(0.3f, 20, 20);
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.9f, 0.5f, -0.15f);
    glScalef(0.05f, 0.05f, 0.05f);
    glutSolidSphere(1.0f, 20, 20);
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(0.945f, 0.52f, -0.15f);
    glScalef(0.05f, 0.05f, 0.05f);
    glutSolidSphere(0.3f, 20, 20);
    glPopMatrix();

    glPopMatrix(); // the head rotation

    // Draw legs
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(-0.3f, -0.3f, 0.25f);
    glRotatef(cowLegRotationZ, 0, 0, 1);
    glRotatef(cowLegRotationX, 1, 0, 0);
    glScalef(0.3f, 0.75f, 0.3f);
    sphereTexture(0.3f, 20, 20, cowTextureID);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3f, -0.3f, 0.25f);
    glRotatef(-cowLegRotationZ, 0, 0, 1);
    glRotatef(cowLegRotationX, 1, 0, 0);
    glScalef(0.3f, 0.75f, 0.3f);
    sphereTexture(0.3f, 20, 20, cowTextureID);
    glPopMatrix(); 

    glPushMatrix();
    glTranslatef(-0.3f, -0.3f, -0.25f);
    glRotatef(-cowLegRotationZ, 0, 0, 1);
    glRotatef(-cowLegRotationX, 1, 0, 0);
    glScalef(0.3f, 0.75f, 0.3f);
    sphereTexture(0.3f, 20, 20, cowTextureID);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3f, -0.3f, -0.25f);
    glRotatef(cowLegRotationZ, 0, 0, 1);
    glRotatef(-cowLegRotationX, 1, 0, 0);
    glScalef(0.3f, 0.75f, 0.3f);
    sphereTexture(0.3f, 20, 20, cowTextureID);
    glPopMatrix();

    //draw tail
    glPushMatrix();
    glTranslatef(-0.75f, -0.15f, 0.0f);
    glTranslatef(+0.375f, +0.13f, 0.0f);
    glRotatef(cowTailXAngel, 1.0f, 0.0f, 0.0f);
    glTranslatef(-0.375f, -0.13f, 0.0f);
    glRotatef(cowTailZAngel, 0.0f, 0.0f, 1.0f);
    glRotatef(75.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.75f, 0.15f, 0.15f);
    sphereTexture(0.3f, 20, 20, cowTextureID);
    glPopMatrix();

}

// Function to draw a branch
void drawBranch(float height, float radius, GLuint textureID)
{
    const int numStacks = 10;
    const int numSlices = 20;

    // Draw a sphere for the branch
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    for (int i = 0; i < numStacks; i++)
    {
        float stack1 = static_cast<float>(i) / numStacks;
        float stack2 = static_cast<float>(i + 1) / numStacks;

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= numSlices; j++)
        {
            float slice = static_cast<float>(j) / numSlices;
            float theta = slice * 2.0f * 3.14159f;

            // Calculate vertex positions
            float x1 = radius * cos(theta) * sin(stack1);
            float y1 = height * cos(stack1);
            float z1 = radius * sin(theta) * sin(stack1);

            float x2 = radius * cos(theta) * sin(stack2);
            float y2 = height * cos(stack2);
            float z2 = radius * sin(theta) * sin(stack2);

            // Calculate texture coordinates
            float u = slice;
            float v1 = stack1;
            float v2 = stack2;

            glTexCoord2f(u, v1);
            glVertex3f(x1, y1, z1);

            glTexCoord2f(u, v2);
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);
}

// function to draw tree
void drawTree(float trunkHeight, float trunkRadius, float branchHeight, float branchRadius)
{
    // Draw trunk
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, trunkTextureID);
    glPushMatrix();
    glTranslatef(0, -2.25, 0);
    glScalef(10, 4, 10);
    drawBranch(trunkHeight, trunkRadius, trunkTextureID);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // Draw branches
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, leavesTextureID);
    glPushMatrix();

    glTranslatef(0.0f, trunkHeight, 0.0f);
    for (int i = 0; i < 3; i++)
    {
        glTranslatef(0, -0.5, 0);
        glRotatef(120.0f, 0.0f, 1.0f, 0.0f);
        glScalef(4.0f, 2.0f, 4.0f);
        drawBranch(branchHeight, branchRadius, leavesTextureID);
    }

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

// a function to draw grass
void drawGrass()
{
    const float groundSize = 100.0f;
    const float tileSize = 0.5f;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, grassTextureID);

    // Apply grass texture to a grid of quads
    for (float x = -groundSize; x < groundSize; x += tileSize)
    {
        for (float z = -groundSize; z < groundSize; z += tileSize)
        {
            glBegin(GL_QUADS);
            glTexCoord2f(0.0f + grassOffset, 0.0f + grassOffset);
            glVertex3f(x, -0.5f, z);

            glTexCoord2f(1.0f + grassOffset, 0.0f + grassOffset);
            glVertex3f(x + tileSize, -0.5f, z);

            glTexCoord2f(1.0f + grassOffset, 1.0f + grassOffset);
            glVertex3f(x + tileSize, -0.5f, z + tileSize);

            glTexCoord2f(0.0f + grassOffset, 1.0f + grassOffset);
            glVertex3f(x, -0.5f, z + tileSize);
            glEnd();
        }
    }

    glDisable(GL_TEXTURE_2D);
}

// a function to draw sky
void drawSky()
{
    const float groundSize = 100.0f;
    const float tileSize = 20.0f;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, skyTextureID);

    // Apply grass texture to a grid of quads
    for (float x = -groundSize; x < groundSize; x += tileSize)
    {
        for (float z = -groundSize; z < groundSize; z += tileSize)
        {
            glBegin(GL_QUADS);
            glTexCoord2f(0.0f + grassOffset, 0.0f + grassOffset);
            glVertex3f(x, 0.0f, z);

            glTexCoord2f(1.0f + grassOffset, 0.0f + grassOffset);
            glVertex3f(x + tileSize, -0.0f, z);

            glTexCoord2f(1.0f + grassOffset, 1.0f + grassOffset);
            glVertex3f(x + tileSize, -0.0f, z + tileSize);

            glTexCoord2f(0.0f + grassOffset, 1.0f + grassOffset);
            glVertex3f(x, -0.0f, z + tileSize);
            glEnd();
        }
    }

    glDisable(GL_TEXTURE_2D);
}

// Function to draw a tree
void drawTree() {
    
    glPushMatrix();

    // Apply texture
    glEnable(GL_TEXTURE_2D);
   // glBindTexture(GL_TEXTURE_2D, textureID);

    // Set tree color to white
    glColor3f(0.502f, 0.4431f, 0.3255f);

    // Enable alpha blending for texture transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Draw the tree
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 0.0f, 0.0f);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 2.0f, 0.0f);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 2.0f, 0.0f);
    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

// Function to draw a sun
void drawSun()
{
    // Enable texturing
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, lamppostTextureID);

    // Set material properties
    GLfloat matAmbient2[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    GLfloat matDiffuse2[] = { 1.0f, 1.0f, 1.0f, 0.3f };
    GLfloat matSpecular2[] = { 1.0f, 1.0f, 1.0f, 0.3f };
    GLfloat matShininess2[] = { 50.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular2);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess2);

    glPushMatrix();
    glRotatef(-lightAngle, 0, 0, 1);
    glTranslatef(0, 50, 0);
    sphereTexture(3, 50, 50, sunTextureID);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

// Function to draw a Ball
void drawBall() {
    // Enable texturing
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ballTextureID);

    // Set material properties
    GLfloat matAmbient2[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    GLfloat matDiffuse2[] = { 1.0f, 1.0f, 1.0f, 0.3f };
    GLfloat matSpecular2[] = { 1.0f, 1.0f, 1.0f, 0.3f };
    GLfloat matShininess2[] = { 50.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular2);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess2);

    glPushMatrix();
    sphereTexture(1.3, 50, 50, ballTextureID);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    float distance = sqrt(((cowPosX - ballPosX) * (cowPosX - ballPosX)) + ((cowPosZ - ballPosZ) * (cowPosZ - ballPosZ)));
    if (distance > 5) {
        if (cowPosX < ballPosX) {
            ballPosX -= abs((cowPosX - ballPosX) / distance) * ballspeed;
        }
        else {
            ballPosX += abs((cowPosX - ballPosX) / distance) * ballspeed;
        }
        if (cowPosZ < ballPosZ) {
            ballPosZ -= abs((cowPosZ - ballPosZ) / distance) * ballspeed;
        }
        else {
            ballPosZ += abs((cowPosZ - ballPosZ) / distance) * ballspeed;
        }
    }
    if (isBallNotJumping == true) {
        isBallNotJumping = false;
        jump(1);
    }

}

// Function to draw a lamppost
void drawLamppost()
{
    // Set material properties for the metal
    GLfloat matAmbient[] = { 0.25f, 0.25f, 0.25f, 1.0f };
    GLfloat matDiffuse[] = { 0.4f, 0.4f, 0.4f, 1.0f };
    GLfloat matSpecular[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat matShininess[] = { 50.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

    // Enable texturing
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, lamppostTextureID);

    // Draw main cylinder
    const float height = 6.0f;
    const float radius = 0.3f;
    const int numSegments = 50;
    GLUquadricObj* mainCylinder = gluNewQuadric();
    gluQuadricTexture(mainCylinder, GL_TRUE);
    gluCylinder(mainCylinder, radius, radius, height, numSegments, 1);
    gluDeleteQuadric(mainCylinder);

    // Disable texturing
    glDisable(GL_TEXTURE_2D);
    
    // Set material properties
    GLfloat matAmbient2[] = { light1AmbientRed, light1AmbientGreen, light1AmbientBlue, 0.0f };
    GLfloat matDiffuse2[] = { 1.0f, 1.0f, 0.0f, 0.3f };
    GLfloat matSpecular2[] = { 1.0f, 1.0f, 1.0f, 0.3f };
    GLfloat matShininess2[] = { 50.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular2);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess2);
    
    // Draw light source
    const float lightHeight = height + 0.5f;
    glEnable(GL_BLEND);
    glColor4f(light1AmbientRed, light1AmbientGreen, light1AmbientBlue, 0.3f);
    glPushMatrix();
    glTranslatef(0.0f, 0, lightHeight);
    glutSolidSphere(1.0f, 10, 10);
    glPopMatrix();
    glDisable(GL_BLEND);
    
}

// Function to draw wall
void drawWall() {
    // Enable texturing
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, wallTextureID);

    // Draw the box
    glBegin(GL_QUADS);

    // Front face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-50, -0.5, 0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(50, -0.5, 0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(50, 50, 0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-50, 50, 0);

    glEnd();

    // Disable texturing
    glDisable(GL_TEXTURE_2D);
}

// Function to draw box
void drawBox(GLfloat size, GLuint textureID)
{
    // Enable texturing
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set the material properties
    GLfloat matAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat matDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat matSpecular[] = { 10.0f, 10.0f, 10.0f, 1.0f };
    GLfloat matShininess = 10000.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, matShininess);

    // Draw the box
    glBegin(GL_QUADS);

    // Front face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-size, -size, size);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(size, -size, size);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(size, size, size);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-size, size, size);

    // Back face
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-size, -size, -size);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-size, size, -size);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(size, size, -size);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(size, -size, -size);

    // Left face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-size, -size, -size);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-size, -size, size);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-size, size, size);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-size, size, -size);

    // Right face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(size, -size, -size);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(size, size, -size);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(size, size, size);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(size, -size, size);

    // Top face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-size, size, -size);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-size, size, size);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(size, size, size);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(size, size, -size);

    // Bottom face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-size, -size, -size);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(size, -size, -size);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(size, -size, size);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-size, -size, size);

    glEnd();

    // Disable texturing
    glDisable(GL_TEXTURE_2D);
}

// Function to draw coin
void drawCoin() {
    // Coin radius
    float coinRadius = 0.5f;

    // Coin center position
    float coinCenterX = 0.0f;
    float coinCenterY = 0.0f;
    float coinCenterZ = 0.0f;

    // Number of segments to approximate the coin's circular shape
    int numSegments = 100;

    // Shiny material properties
    GLfloat materialCoinAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat materialCoinDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat materialCoinSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat materialCoinShininess = 100.0f;

    // Set material properties
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialCoinAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialCoinDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialCoinSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, materialCoinShininess);
    // Draw the coin
    glBegin(GL_TRIANGLE_FAN);

    // Coin center
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex3f(coinCenterX, coinCenterY, coinCenterZ);

    // Coin edge
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i <= numSegments; ++i) {
        float angle = 2.0f * 3.14159f * static_cast<float>(i) / static_cast<float>(numSegments);
        float x = coinRadius * cos(angle);
        float y = coinRadius * sin(angle);
        glVertex3f(x, y, coinCenterZ);
    }

    glEnd();
}

// Function to draw coin
void drawScore(void)
{
    float cowDirX = cowPosX - std::sin(cowYaw * 3.14159f / 180.0f) * std::cos(cowPitch * 3.14159f / 180.0f);
    float cowDirY = cowPosY - std::sin(cowPitch * 3.14159f / 180.0f);
    float cowDirZ = cowPosZ - std::cos(cowYaw * 3.14159f / 180.0f) * std::cos(cowPitch * 3.14159f / 180.0f);
    float sqrtNorm = sqrt((cowDirX * cowDirX)  + (cowDirZ * cowDirZ));


    glRasterPos3d(cowPosX + (cowDirX / sqrtNorm) * 2, cowPosY + scoreHight, cowPosZ + (cowDirZ / sqrtNorm) * 2);
    glColor3f(0.0f, 0.0f, 0.0f);
    string str = "";
    if (scoreCurrent == scoreTotal) {
        glColor3f(0.0f, 0.0f, 1.0f);
        str = "Congratulations! You won!";
    }
    else if (HP > 0) {
        str = "Score = " + scoreCurrent + " / " + scoreTotal + "    HP = " + to_string(HP);
    }
    else {
        glColor3f(1.0f, 0.0f, 0.0f);
        str = "GAME OVER";
    }
    for (int i = 0; i < str.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
    }
}

// Function to render the 3D scene
void renderScene() {
    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    //glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    // Set the camera transformation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float cameraDirX = cameraPosX - std::sin(cameraYaw * 3.14159f / 180.0f) * std::cos(cameraPitch * 3.14159f / 180.0f);
    float cameraDirY = cameraPosY - std::sin(cameraPitch * 3.14159f / 180.0f);
    float cameraDirZ = cameraPosZ - std::cos(cameraYaw * 3.14159f / 180.0f) * std::cos(cameraPitch * 3.14159f / 180.0f);
    float delta = sqrt((cameraDirX * cameraDirX) + (cameraDirY * cameraDirY) + (cameraDirZ * cameraDirZ));

    float cowDirX = cowPosX - std::sin(cowYaw * 3.14159f / 180.0f) * std::cos(cowPitch * 3.14159f / 180.0f);
    float cowDirY = cowPosY - std::sin(cowPitch * 3.14159f / 180.0f);
    float cowDirZ = cowPosZ - std::cos(cowYaw * 3.14159f / 180.0f) * std::cos(cowPitch * 3.14159f / 180.0f);
    float sqrtNorm = sqrt((cowDirX * cowDirX) + (cowDirY * cowDirY) + (cowDirZ * cowDirZ));

    int coX = 1;
    int coZ = 1;
    if (cowDirX < 0)
        coX *= -1;
    if (cowDirZ < 0)
        coZ *= -1;

    if (thirdPerson) {
        glRotatef(90, 0, 1, 0);
        glRotatef(cowPitch, 0, 0, 1);
        glTranslatef( 4, -2,0);
        gluLookAt(cowPosX , cowPosY, cowPosZ,
            cowDirX, cowPosY, cowDirZ,
            0.0f, 1.0f, 0.0f);
    }
    else if (firstPerson) {// first person
        glRotatef(90, 0, 1, 0);
        glRotatef(cowPitch, 0, 0, 1);
        glTranslatef(-1.5, 0,0);
        gluLookAt(cowPosX, cowPosY, cowPosZ,
            cowDirX, cowPosY, cowDirZ,
            0.0f, 1.0f, 0.0f);
    }
    else { // specture
        gluLookAt(cameraPosX, cameraPosY, cameraPosZ,
            cameraPosX - std::sin(cameraYaw * 3.14159f / 180.0f) * std::cos(cameraPitch * 3.14159f / 180.0f),
            cameraPosY - std::sin(cameraPitch * 3.14159f / 180.0f),
            cameraPosZ - std::cos(cameraYaw * 3.14159f / 180.0f) * std::cos(cameraPitch * 3.14159f / 180.0f),
            0.0f, 1.0f, 0.0f);
    }
    

    // Set the light properties
    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Set light properties
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // Update the light position
    updateLight();

    float meadowAmbient[] = { 0.4f, 0.8f, 0.2f, 1.0f };
    float meadowDiffuse[] = { 0.4f, 0.8f, 0.2f, 1.0f };
    float meadowSpecular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, meadowAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, meadowDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, meadowSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.0f);

    // Draw sun
    drawSun();

    // Draw the meadow
    drawGrass();

    // Draw the sky
    glPushMatrix();
    glTranslatef(0, 50, 0);
    drawSky();
    glPopMatrix();

    // Draw the ball
    glPushMatrix();
    glTranslatef(ballPosX, ballPosY + 0.5, ballPosZ);
    glRotatef(ballJumpRotation, 0, 1, 0);
    glRotatef(90, 1, 0, 0);
    drawBall();
    if (((cowPosX - ballPosX) * (cowPosX - ballPosX) + (cowPosZ - ballPosZ) * (cowPosZ - ballPosZ)) < 2) {
        HP -= 0.3321;
    }
    glPopMatrix();

    // Draw the Walls
    glPushMatrix();
    glTranslatef(0, -0.5, 50);
    drawWall();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(50, -0.5,0);
    glRotatef(90, 0, 1, 0);
    drawWall();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -0.5, -50);
    glRotatef(180, 0, 1, 0);
    drawWall();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-50, -0.5, 0);
    glRotatef(270, 0, 1, 0);
    drawWall();
    glPopMatrix();

    // Draw some boxes
    for (int i = 0; i < 10; ++i) {

        glPushMatrix();
        glTranslatef(5.0f * std::cos(i), 3.0f, 5.0f * std::sin(i));
        glRotatef(boxAngle, 1, 0, 0);
        glRotatef(boxAngle, 0, 1, 0);
        drawBox(0.7, boxTextureID);
        glPopMatrix();

    }
    
    // Draw some trees
    for (int j = 1; j < 6; j++) {
        for (int i = 0; i < 5; ++i) {
            glPushMatrix();
            glTranslatef(10.0f * std::cos(i + (100 * j)) * j, -0.5f, 10.0f * std::sin(i + (100 * j)) * j);
            glScalef(1 * j, 2 * j, 1 * j);
            glColor3f(0.502f, 0.4431f, 0.3255f);
            drawTree(1.0f, 0.1f, 0.8f, 0.05f);
            glPopMatrix();
        }
    }
    // Draw some coins
    for (int j = 1; j < 6; j++) {
        for (int i = 0; i < 5; ++i) {
            if (scoreFound[i + (j - 1) * 5] == false) {
                glPushMatrix();
                glTranslatef(-10.0f * std::cos(i + (100 * j)) * j, 0.5f, -10.0f * std::sin(i + (100 * j)) * j);
                glRotatef(boxAngle * 5, 0, 1, 0);
                drawCoin();
                scorePosX[i + (j - 1) * 5] = -10.0f * std::cos(i + (100 * j)) * j;
                scorePosZ[i + (j - 1) * 5] = -10.0f * std::sin(i + (100 * j)) * j; 
                // update score and visabiliti of coin
                if ((cowPosX - scorePosX[i + (j - 1) * 5]) * (cowPosX - scorePosX[i + (j - 1) * 5]) + (cowPosZ - scorePosZ[i + (j - 1) * 5]) * (cowPosZ - scorePosZ[i + (j - 1) * 5]) < 1) {
                    scoreFound[i + (j - 1) * 5] = true;
                    scoreCurrent = to_string(stoi(scoreCurrent) + 1);
                }
                glPopMatrix();
            }
        }
    }

    // Enable lighting
    enableLighting1();
    glPushMatrix();
    // Rotate and translate the lamppost to stand upright
    glTranslatef(-1.0f + light1XPos, -1.0f + light1YPos, -3.0f + light1ZPos);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    drawLamppost();
    glPopMatrix();

    // Set material properties for the cow
   // float cowAmbient[] = { 0.8f, 0.6f, 0.4f, 1.0f };
    float cowAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float cowDiffuse[] = { 0.8f, 0.6f, 0.4f, 1.0f };
    float cowSpecular[] = { 0.5f, 0.35f, 0.05f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, cowAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cowDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cowSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);


    // Draw the cow
    glPushMatrix();
    glTranslatef(cowPosX, cowPosY, cowPosZ);
    glRotatef(cowJumpRotation, 0, 1, 0);
    glRotatef(cowYaw, 0.0f, 1.0f, 0.0f);
    drawCow();
    glPopMatrix();

    // draw the score
    drawScore();

    glDisable(GL_TEXTURE_2D);

    // Swap Buffer the OpenGL commands
    glutSwapBuffers();
}

/* Called back when there is no other event to be handled */
void idle() {
    glutPostRedisplay();   // Post a re-paint request to activate displayWirePolyhedra()
}

void top_menu(int i) {
    if (i == 1) {
        exit(1);
    }
    else if (i == 10) {
        printf("\nWelcome to the cow game!");
        printf("\n\nThis game represent a cow in a meadow");
        printf("\nViewing methods:");
        printf("\nYou can watch the cow in 3 diffrent ways by the following keys:");
        printf("\n\t- '1':\t first person, watch from the front of the cow");
        printf("\n\t- '2':\t spector mode, to move freely with the camera in the meadow");
        printf("\n\t- '3':\t thirnd person, watch from behind and above the cow");
        printf("\n\nMouse methods:");
        printf("\nTo move the camera/cow diraction you can move your mouse in the required diraction");
        printf("\n\To move the camera/cow in opposite diraction You can drag the view using the - 'left button'");
        printf("\nTo open the menu click on the - 'right button'");
        printf("\nIn the Menu you can chose to quit, adjust ambient light, adjust cow values and help.");
        printf("\nthere you can manage world properties");
        printf("\n\nMovment methods:");
        printf("\nTo move the cow use the following keys:");
        printf("\n\t- 'w':\t forward, move the cow in the forward diraction");
        printf("\n\t- 's':\t backward, move the cow in the backward diraction");
        printf("\n\t- 'a':\t left, move the cow in the left diraction");
        printf("\n\t- 'd':\t right, move the cow in the right diraction");
        printf("\n\t- 'q':\t rotate left, move the cow rotation in the left diraction");
        printf("\n\t- 'e':\t rotate right, move the cow rotation in the right diraction");
        printf("\n\t- 'space key' = ' ':\t jump, make the cow jump upward");
        printf("\n\nTo move the camera use the following keys:");
        printf("\n\t- '8':\t forward, move the camera in the forward diraction");
        printf("\n\t- '5':\t backward, move the camera in the backward diraction");
        printf("\n\t- '4':\t left, move the camera in the left diraction");
        printf("\n\t- '6':\t right, move the camera in the right diraction");
        printf("\n\t- '+':\t zoom-in, move the camera in the forward diraction with big step");
        printf("\n\t- '-':\t zoom-out, move the camera in the backward diraction with big step");
        printf("\n\nHead and tail movment methods:");
        printf("\n\t- 'z':\t tail left, move the tail in the left diraction");
        printf("\n\t- 'x':\t tail right, move the tail in the right diraction");
        printf("\n\t- 'c':\t tail up, move the tail in the upward diraction");
        printf("\n\t- 'v':\t tail down, move the tail in the down diraction");
        printf("\n\t- 'f':\t head upward, move the head in the upward diraction");
        printf("\n\t- 'g':\t head downward, move the head in the downward diraction");
        printf("\n\t- 'h':\t head left, move the tail head the left diraction");
        printf("\n\t- 'j':\t head right, move the tail head the right diraction");

        
    }
}

void light_menu(int i) {
    if (i == 2) { // Red +
        light1AmbientRed += lightAmbientStep;
    }
    else if (i == 3) { // Red -
        light1AmbientRed = lightAmbientStep;
    }
    else if (i == 4) { // Green +
        light1AmbientGreen += lightAmbientStep;
    }
    else if (i == 5) { // Green -
        light1AmbientGreen -= lightAmbientStep;
    }
    else if (i == 6) { // Blue +
        light1AmbientBlue += lightAmbientStep;
    }
    else if (i == 7) { // Blue -
        light1AmbientBlue = lightAmbientStep;
    }
    else if (i == 21) { // Red +
        light1AmbientRed += lightAmbientStep;
    }
    else if (i == 22) { // Red -
        light1AmbientRed = lightAmbientStep;
    }
    else if (i == 23) { // Green +
        light1AmbientGreen += lightAmbientStep;
    }
    else if (i == 24) { // Green -
        light1AmbientGreen -= lightAmbientStep;
    }
    else if (i == 25) { // Blue +
        light1AmbientBlue += lightAmbientStep;
    }
    else if (i == 26) { // Blue -
        light1AmbientBlue = lightAmbientStep;
    }
    else if (i == 8) { // Step +
        lightAmbientStep *= 2;
    }
    else if (i == 9) { // Step -
        lightAmbientStep /= 2;
    }
    else if (i == 27) { // X position +
        light1XPos += 2;
    }
    else if (i == 28) { // X position -
        light1XPos -= 2;
    }
    else if (i == 29) { // Y position +
        light1YPos += 2;
    }
    else if (i == 30) { // Y position -
        light1YPos -= 2;
    }
    else if (i == 31) { // Z position +
        light1ZPos += 2;
    }
    else if (i == 32) { // Z position -
        light1ZPos -= 2;
    }
    else if (i == 33) { // Range +
        light1Range *= 2;
    }
    else if (i == 34) { // Z Range -
        light1Range /= 2;
    }
    else if (i == 35) { // Range +
        light1Angle += 10;
    }
    else if (i == 36) { // Range -
        light1Angle -= 10;
    }
    else if (i == 37) { // X rotation +
        light1XAngle += 10;
    }
    else if (i == 38) { // X rotation -
        light1XAngle -= 10;
    }
    else if (i == 39) { // Y rotation +
        light1YAngle += 10;
    }
    else if (i == 40) { // Y rotation -
        light1YAngle -= 10;
    }
    else if (i == 41) { // Z rotation +
        light1ZAngle += 10;
    }
    else if (i == 42) { // Z rotation -
        light1ZAngle -= 10;
    }

    if (light1AmbientRed > 1) {
        light1AmbientRed = 1;
    }
    if (light1AmbientRed < 0) {
        light1AmbientRed = 0;
    }
    if (light1AmbientGreen > 1) {
        light1AmbientGreen = 1;
    }
    if (light1AmbientGreen < 0) {
        light1AmbientGreen = 0;
    }
    if (light1AmbientBlue > 1) {
        light1AmbientBlue = 1;
    }
    if (light1AmbientBlue < 0) {
        light1AmbientBlue = 0;
    }
    if (lightAmbientStep > 1) {
        lightAmbientStep = 1;
    }
    if (lightAmbientStep == 0) {
        lightAmbientStep = 0.1;
    }
}

void cow_menu(int i) {
    if (i == 11) { // Speed +
        cowSpeed *= 2;
    }
    else if (i == 12) { // Speed -
        cowSpeed /= 2;
    }
    else if (i == 13) { // gravity +
        cowJumpStep *= 2;
    }
    else if (i == 14) { // gravity -
        cowJumpStep /= 2;
    }
    else if (i == 15) { // jump hight +
        cowJumpRadios *= 2;
    }
    else if (i == 16) { // jump hight -
        cowJumpRadios /= 2;
    }
    else if (i == 17) { // mouse speed +
        cameraSpeed *= 2;
    }
    else if (i == 18) { // mouse speed -
        cameraSpeed /= 2;
    }
    else if (i == 19) { // day speed +

        lightStep *= 2;
    }
    else if (i == 20) { // day speed -
        lightStep /= 2;
    }
}

void createMenu() {
    int sub_menu = glutCreateMenu(light_menu);
    glutAddMenuEntry("increase Red value light 1", 2);
    glutAddMenuEntry("decreace Red value light 1", 3);
    glutAddMenuEntry("increase Green value light 1", 4);
    glutAddMenuEntry("decreace Green value light 1", 5);
    glutAddMenuEntry("increase Blue value light 1", 6);
    glutAddMenuEntry("decreace Blue value light 1", 7);
    glutAddMenuEntry("increase Red value light 0", 21);
    glutAddMenuEntry("decreace Red value light 0", 22);
    glutAddMenuEntry("increase Green value light 0", 23);
    glutAddMenuEntry("decreace Green value light 0", 24);
    glutAddMenuEntry("increase Blue value light 0", 25);
    glutAddMenuEntry("decreace Blue value light 0", 26);
    glutAddMenuEntry("increase step value light 1", 8);
    glutAddMenuEntry("decreace step value light 1", 9);
    glutAddMenuEntry("increase X value location light 1", 27);
    glutAddMenuEntry("decrease X value location light 1", 28);
    glutAddMenuEntry("increase Y value location light 1", 29);
    glutAddMenuEntry("decrease Y value location light 1", 30);
    glutAddMenuEntry("increase Z value location light 1", 31);
    glutAddMenuEntry("decrease Z value location light 1", 32);
    glutAddMenuEntry("increase range value of light 1", 33);
    glutAddMenuEntry("decrease range value of light 1", 34);
    glutAddMenuEntry("increase angle value of light 1", 35);
    glutAddMenuEntry("decrease angle value of light 1", 36);
    glutAddMenuEntry("increase X angle value of light 1", 37);
    glutAddMenuEntry("decrease X angle value of light 1", 38);
    glutAddMenuEntry("increase Y angle value of light 1", 39);
    glutAddMenuEntry("decrease Y angle value of light 1", 40);
    glutAddMenuEntry("increase Z angle value of light 1", 41);
    glutAddMenuEntry("decrease Z angle value of light 1", 42);
    int sub_menu2 = glutCreateMenu(cow_menu);
    glutAddMenuEntry("increase speed value", 11);
    glutAddMenuEntry("decreace speed value", 12);
    glutAddMenuEntry("increase gravity value", 13);
    glutAddMenuEntry("decreace gravity value", 14);
    glutAddMenuEntry("increase jump hight value", 15);
    glutAddMenuEntry("decreace jump hight value", 16);
    glutAddMenuEntry("increase mouse speed value", 17);
    glutAddMenuEntry("decreace mouse speed value", 18);
    glutAddMenuEntry("increase day speed value", 19);
    glutAddMenuEntry("decreace day speed value", 20);
    glutCreateMenu(top_menu);
    glutAddMenuEntry("quit", 1);
    glutAddSubMenu("adjust ambient light", sub_menu);
    glutAddSubMenu("adjust cow values", sub_menu2);
    glutAddMenuEntry("help", 10);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH |GLUT_RGBA | GLUT_ALPHA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Cow in Meadow");

    // Register callback functions
    glutReshapeFunc(handleReshape);
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(handleKeyPress);
    glutPassiveMotionFunc(handleMouseMove);
    glutMouseFunc(mouseClick);

    // Set OpenGL options
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutIdleFunc(idle);             // Register callback handler if no other event

    loadTextures(); // load textures 

    glutTimerFunc(16, update, 0);

    // menu 
    createMenu();
    top_menu(10); // call the help to print the keyboards

    // Main rendering loop
    glutMainLoop();

    return 0;
}