#include <GLFW/glfw3.h>
#include <iostream>
#include "field.h"
#include "player.h"
#include "texture.h"
#include "text.h"
#include "box.h"
#include "points.h"
#include "moving.h"
#include "returnFromJson.h"

#define ECRANW 1200
#define ECRANH 900
#define SCENE 200

Player player;
Field field(SCENE, SCENE);
Box box;
Points points;

inline bool isPressed(GLFWwindow* w, int key, bool& prev) {
    bool curr = glfwGetKey(w, key) == GLFW_PRESS;
    bool result = curr && !prev;
    prev = curr;
    return result;
}
bool isDown(GLFWwindow* window, int key) {
    return glfwGetKey(window, key) == GLFW_PRESS;
}
void processInput(GLFWwindow* window,float dt){
    static bool prevW = false;
    static bool prevS = false;
    static bool prevA = false;
    static bool prevD = false;

    float speed = 40.0f;

    if (isDown(window,GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(window, true);
    if (isPressed(window, GLFW_KEY_W,prevW)) {
        tryMovePlayer(player.collider,box.coordinates,field.verticlesLabirynt, field.verticlesBord,
        box.boxDown,Direction::Up,speed);
    }

    if (isPressed(window, GLFW_KEY_S,prevS)) {
        tryMovePlayer(player.collider,box.coordinates,field.verticlesLabirynt, field.verticlesBord,
        box.boxDown,Direction::Down,speed);
    }

    if (isPressed(window, GLFW_KEY_A,prevA)) {
        tryMovePlayer(player.collider,box.coordinates,field.verticlesLabirynt, field.verticlesBord,
        box.boxDown, Direction::Left,speed);
    }

    if (isPressed(window, GLFW_KEY_D, prevD)) {
        tryMovePlayer(player.collider, box.coordinates, field.verticlesLabirynt, field.verticlesBord,
        box.boxDown, Direction::Right, speed);
    }
}

int main(){
    if (!glfwInit()){
        std::cout << "Failed to initialize GLFW\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(ECRANW, ECRANH, "Sokoban", NULL, NULL);
    if (!window){
        std::cout << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    BuildFont();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-SCENE, SCENE, -SCENE, SCENE, -SCENE, SCENE);
    glMatrixMode(GL_MODELVIEW);

    field.loadWallsToField("maze.json",field.verticlesLabirynt);

    box.setCoordinates();
    points.coordinates = returnValueFromJson("maze.json", "circles");

    LoadAllTextures();

    double lastTime = glfwGetTime();
    double deltaTime = 0.0;

    while (!glfwWindowShouldClose(window)){
        double currentTime = glfwGetTime();

        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        processInput(window,deltaTime);

        glClear(GL_COLOR_BUFFER_BIT);

        field.drawPerimetr();
        field.drawLab();
        field.drawGrid(-SCENE, SCENE, -SCENE, SCENE);

        player.draw();
        box.drawBox();
        points.draw();

        box.getFinish(points);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

