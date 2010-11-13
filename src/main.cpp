#include <iostream>
#include <GL/glew.h>
#ifdef _WIN32
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif
#include "render_e/RenderBase.h"
#include "render_e/Camera.h"
#include "render_e/SceneObject.h"
#include "render_e/Mesh.h"
#include "render_e/math/Vector3.h"


#ifndef RENDER_FPS
#define RENDER_FPS (1000/60)
#endif

using namespace render_e;

RenderBase *renderBase = RenderBase::instance();

// The main purpose of the main is to created a windows
// and hook up the opengl to that (using GLUT).
// Other purposes include:
// - Create a timer that keeps a steady framerate
// - Capture events and delegate them to the RenderEngine singleton

void display() {
    renderBase->Display();
}

void timerFunc(int value) {
    static int lastUpdate = 0;
    int time = glutGet(GLUT_ELAPSED_TIME);
    lastUpdate = time;
    glutPostRedisplay();
    glutTimerFunc(RENDER_FPS, timerFunc, 0);
}


//forward declaration
void initWorld();
void testPNG();

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 500);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Hello World");
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        // Problem: glewInit failed, something is seriously wrong. 
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return -1;
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    initWorld();

    glutDisplayFunc(display);

    glutTimerFunc(RENDER_FPS, timerFunc, 0);
    glutMainLoop();
    return EXIT_SUCCESS;
}

void initWorld() {
    Camera *camera = new Camera();
    SceneObject *cameraContainer = new SceneObject();
    camera->SetProjection(25, 1, 0.1,1000);
    cameraContainer->AddCompnent(camera);
    renderBase->AddSceneObject(cameraContainer);
    Vector3 v(0.0,0.0,10.0);
    cameraContainer->GetTransform().SetPosition(v);
    
    Mesh *mesh = new Mesh();
    SceneObject *sceneObject = new SceneObject();
    renderBase->AddSceneObject(sceneObject);
    sceneObject->AddCompnent(mesh);
    
}

/*
#include "render_e/textures/PNGTextureDataSource.h"

void testPNG() {
    using namespace render_e;
    PNGTextureDataSource t;
    TextureFormat textureFormat;
    int width, height;
    unsigned char *data;
    char filename[] = "/Users/morten/Desktop/Screen shot 2010-11-06 at 6.24.22 PM.png";
    TextureLoadStatus res = t.LoadTexture(filename, width, height, textureFormat, &data);

    std::cout << "Load texture returned " << res << std::endl;
    if (res == OK) {
        std::cout << "Width: " << width << " height " << height << " Texture format " << textureFormat << std::endl;
        std::cout << "First pixel " << (int) data[0] << " " << (int) data[1] << " " << (int) data[2] << std::endl;
        std::cout << "First pixel " << (int) data[1620 - 1] << " " << (int) data[1620 - 2] << " " << (int) data[1620 - 3] << std::endl;
    }
}
 * */