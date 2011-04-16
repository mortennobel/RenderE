
/// The purpose of this test is simply to test that the update function is called
/// on every Component each frame and that the FrameTime is updated each frame.

#include <iostream>
#include <GL/glew.h>
#ifdef _WIN32
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "render_e/RenderBase.h"
#include "render_e/Camera.h"
#include "render_e/SceneObject.h"
#include "render_e/Component.h"
#include "render_e/FrameTime.h"
#include "render_e/Material.h"
#include "render_e/MeshComponent.h"
#include "render_e/MeshFactory.h"
#include "render_e/FBXLoader.h"
#include "render_e/Mesh.h"
#include "render_e/shaders/ShaderFileDataSource.h"
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
SceneObject *selectedSceneObject = new SceneObject();
int selectedObjectIndex;

bool mouseDown = false;
int mouseOffsetX, mouseOffsetY;
glm::vec3 mouseRotation(0);
glm::vec3 rotation(0,0,0);
int moveForward = 0;
float timeSec;


// The main purpose of the main is to created a windows
// and hook up the opengl to that (using GLUT).
// Other purposes include:
// - Create a timer that keeps a steady framerate
// - Capture events and delegate them to the RenderEngine singleton
void display() {
    renderBase->Update(timeSec);
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
        glm::vec3 forward(0,0,-1);
        forward = cameraContainer->GetTransform()->GetRotation()*forward;
        glm::vec3 newPos = cameraContainer->GetTransform()->GetPosition()+forward*(movementSpeed*time*moveForward);
        cameraContainer->GetTransform()->SetPosition(newPos);
    }
}

void timerFunc(int value) {
    static int lastUpdate = 0;
    int time = glutGet(GLUT_ELAPSED_TIME);
    timeSec = (time-lastUpdate)/1000.0f;
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
    glm::vec3 translate = glm::vec3(0);
    switch (key){
        case 'd':
            translate[0] = +1;
            break;
        case 'a':
            translate[0] = -1;
            break;
        case 's':
            translate[2] = +1;
            break;
        case 'w':
            translate[2] = -1;
            break;
        case 'r':
            renderBase->ReloadAllShaders();
            std::cout<<"Reload all shaders"<<std::endl;
            break;
        case 'z':
            static bool renderMode = false;
            renderMode = !renderMode;
            renderBase->SetRenderMode(renderMode?RENDER_MODE_LINE:RENDER_MODE_FILL);
            break;
        case 9: // tab
            selectedObjectIndex ++;
            if (selectedObjectIndex>5){
                selectedObjectIndex=1;
            }
            static char cubeName[] = "Cube1";
            cubeName[4] = selectedObjectIndex+'0';
            selectedSceneObject = renderBase->Find(cubeName);
            if (selectedSceneObject==NULL){
                std::cout << "Didn't find anything"<<std::endl;
            } else {
                std::cout << "Found "<<selectedSceneObject->GetName()<<std::endl;
                Transform *parent = selectedSceneObject->GetTransform()->GetParent();
                if (parent == NULL){
                    std::cout << "Has no parent"<<std::endl;
                } else {
                    std::cout << "Has parent "<<parent->GetOwner()->GetName()<<std::endl;
                }
            }
            break;
            
    }
    selectedSceneObject->GetTransform()->SetPosition(translate+selectedSceneObject->GetTransform()->GetPosition());
}

void mouseMotionFunc(int x, int y){
    if (mouseDown){
        float rotationSpeed = 0.3;
        rotation[0] = Mathf::Clamp(mouseRotation[0]+(-y+mouseOffsetY)*rotationSpeed,-89.0f,89.0f);
        rotation[1] = mouseRotation[1]+(-x+mouseOffsetX)*rotationSpeed;

        glm::quat newRotation;
        Mathf::SetFromEuler(
                rotation[0]*Mathf::DEGREE_TO_RADIAN, 
                rotation[1]*Mathf::DEGREE_TO_RADIAN, 0,newRotation);
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
        filename = "testdata/parent_child.xml";
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
}

void setMatrial (Shader *shader, SceneObject *so){
    Material *mat = new Material(shader);
    so->AddCompnent(mat);   
    
    const vector<Transform *> *trans = so->GetTransform()->GetChildren();
    for (vector<Transform*>::const_iterator iter = trans->begin();iter != trans->end();iter++){
        so = (*iter)->GetOwner();
        setMatrial(shader, so);
    }
}

