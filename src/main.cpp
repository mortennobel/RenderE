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
#include "render_e/Material.h"
#include "render_e/MeshComponent.h"
#include "render_e/MeshFactory.h"
#include "render_e/FBXLoader.h"
#include "render_e/Mesh.h"
#include "render_e/math/Vector3.h"
#include "render_e/math/Quaternion.h"
#include "render_e/shaders/ShaderFileDataSource.h"
#include "render_e/shaders/DefaultShaders.h"
#include "render_e/SceneXMLParser.h"
#include "render_e/math/Mathf.h"


#ifndef RENDER_FPS
#define RENDER_FPS (1000/60)
#endif

using namespace render_e;
using namespace std;

RenderBase *renderBase = RenderBase::Instance();
MeshComponent *meshTeapot = new MeshComponent();
SceneObject *meshTeapotContainer = new SceneObject();
SceneObject *cameraContainer = new SceneObject();
    
bool mouseDown = false;
int mouseOffsetX, mouseOffsetY;
Vector3 mouseRotation;
Vector3 rotation(0,0,0);
int moveForward = 0;

// The main purpose of the main is to created a windows
// and hook up the opengl to that (using GLUT).
// Other purposes include:
// - Create a timer that keeps a steady framerate
// - Capture events and delegate them to the RenderEngine singleton

void display() {
    renderBase->Display();
}

void printMatrix(float *m){
    
    for (int i=0;i<16;i++){
        cout << m[i]<<"f, ";
    }
    cout << endl;
    
    for (int c = 0;c<4;c++){
        for (int r=0;r<4;r++){
            cout << m[c+r*4]<<" ";
        }
        cout << endl;
    }
}


void localUpdate(float time){
    static float totalTime =0;
    totalTime += time;
    if (moveForward!=0){
        float movementSpeed = 2.0;
        Vector3 forward(0,0,-1);
        forward = cameraContainer->GetTransform()->GetRotation()*forward;
        Vector3 newPos = cameraContainer->GetTransform()->GetPosition()+forward*(movementSpeed*time*moveForward);
        cameraContainer->GetTransform()->SetPosition(newPos);
    }
}

void timerFunc(int value) {
    static int lastUpdate = 0;
    int time = glutGet(GLUT_ELAPSED_TIME);
    float timeSec = (time-lastUpdate)/1000.0f;
    localUpdate(timeSec);
    lastUpdate = time;
    glutPostRedisplay();
    glutTimerFunc(RENDER_FPS, timerFunc, 0);
}

void reshape(int w, int h){
    renderBase->Reshape(w, h);
}


//forward declaration
void initWorld(const char *filename);
void initGL();
void initRenderBase();

void keyPress(unsigned char key, int x, int y){
    Transform *t = meshTeapotContainer->GetTransform();
    Vector3 cameraPosition = cameraContainer->GetTransform()->GetPosition();
    switch (key){
        case 'd':
            cameraPosition[0] = cameraPosition[0]+1;
            break;
        case 'a':
            cameraPosition[0] = cameraPosition[0]-1;
            break;
        case 's':
            cameraPosition[2] = cameraPosition[2]+1;
            break;
        case 'w':
            cameraPosition[2] = cameraPosition[2]-1;
            break;
        case 'z':
            static bool renderMode = false;
            renderMode = !renderMode;
            renderBase->SetRenderMode(renderMode?RENDER_MODE_LINE:RENDER_MODE_FILL);
            
    }
    cameraContainer->GetTransform()->SetPosition(cameraPosition);
}

void mouseMotionFunc(int x, int y){
    if (mouseDown){
        float rotationSpeed = 0.3;
        rotation[0] = Mathf::Clamp(mouseRotation[0]+(-y+mouseOffsetY)*rotationSpeed,-89.0f,89.0f);
        rotation[1] = mouseRotation[1]+(-x+mouseOffsetX)*rotationSpeed;

        Quaternion newRotation = Quaternion::MakeFromEuler(
                rotation[0]*Mathf::DEGREE_TO_RADIAN, 
                rotation[1]*Mathf::DEGREE_TO_RADIAN, 0);
        cameraContainer->GetTransform()->SetRotation(newRotation);
    }
}

void mouseFunc(int button, int state, int x, int y){
    if (button == GLUT_RIGHT_BUTTON){
        if (state==GLUT_DOWN){
            mouseOffsetX = x;
            mouseOffsetY = y;
            mouseRotation = rotation;
            mouseDown = true;
        } else if (state==GLUT_UP){
            mouseDown = false;
        }
    } else if (button == GLUT_LEFT_BUTTON){
        if (state==GLUT_DOWN){
            moveForward = 1;
        } else {
            moveForward = 0;
        }
    } else if (button == GLUT_MIDDLE_BUTTON){
        if (state==GLUT_DOWN){
            moveForward = -1;
        } else {
            moveForward = 0;
        }
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 500);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("RenderE");
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        // Problem: glewInit failed, something is seriously wrong. 
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return -1;
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    if (GLEW_EXT_framebuffer_object){
        cout<<"Framebuffer objects ok" << endl;
    } else {
        cout << "Error: Framebuffer objects not supported" << endl;
        return -1;
    }
    
    initGL();
    initRenderBase();
    
    const char *filename;
    if (argc<2){
        filename = "testdata/render_to_texture.xml";
        cout<<"Using scene not found - using default: "<<filename<<endl;  
    } else {
        filename = argv[1];
    
    }
    
    initWorld(filename);
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseFunc);
    glutMotionFunc(mouseMotionFunc);

    glutKeyboardFunc(keyPress);
    glutTimerFunc(RENDER_FPS, timerFunc, 0);
    glutMainLoop();
    return EXIT_SUCCESS;
}

void initGL(){
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
}

void swap(){
	glutSwapBuffers();
}

void initRenderBase(){
    renderBase->Init(swap);
}

void initWorld(const char *filename) {
    SceneXMLParser parser;
    parser.LoadScene(filename, renderBase);
    cameraContainer = (*(renderBase->GetCameras()))[0]; 
        
    // renderBase->PrintDebug();
}

void setMatrial (Shader *shader, SceneObject *so){
    Material *mat = new Material(shader);
    so->AddCompnent(mat);   
    
    vector<Transform *> *trans = so->GetTransform()->GetChildren();
    for (vector<Transform*>::iterator iter = trans->begin();iter != trans->end();iter++){
        so = (*iter)->GetSceneObject();
        setMatrial(shader, so);
    }
}

