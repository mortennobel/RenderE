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


#ifndef RENDER_FPS
#define RENDER_FPS (1000/60)
#endif

using namespace render_e;
using namespace std;

RenderBase *renderBase = RenderBase::Instance();
MeshComponent *meshTeapot = new MeshComponent();
SceneObject *cameraContainer = new SceneObject();
    
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
//    static Quaternion rotation = Quaternion::MakeFromEuler(10,0,0);
//    Quaternion q = meshTeapot->GetOwner()->GetTransform().GetRotation()*rotation/* *time*/;
//    meshTeapot->GetOwner()->GetTransform().SetRotation(q);
    static float totalTime =0;
    totalTime += time;
    Quaternion q = Quaternion::MakeFromEuler(0.0f,totalTime,0.0f);
    meshTeapot->GetOwner()->GetTransform().SetRotation(q);
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
void initWorld();
void testPNG();
void initGL();
void initRenderBase();
void transformTest();
void TestLoadShader();
void fbxTest();

void keyPress(unsigned char key, int x, int y){
    Transform *t = &(meshTeapot->GetOwner()->GetTransform());
    Vector3 position = t->GetPosition();
    Vector3 cameraPosition = cameraContainer->GetTransform().GetPosition();
    switch (key){
        case 'a':
            position[0] =position[0]+1;
            break;
        case 'd':
            position[0] =position[0]-1;
            break;
        case 'w':
            position[2] =position[2]+1;
            break;
        case 's':
            position[2] = position[2]-1;
            break;
        case 'A':
            cameraPosition[0] =cameraPosition[0]+1;
            break;
        case 'D':
            cameraPosition[0] =cameraPosition[0]-1;
            break;
        case 'W':
            cameraPosition[2] =cameraPosition[2]+1;
            break;
        case 'S':
            cameraPosition[2] = cameraPosition[2]-1;
            break;
            
    }
    cout<<position[0]<<" "<<position[1]<<" "<<position[2]<<endl;
    t->SetPosition(position);
    printMatrix(t->GetLocalTransform().GetReference());
    cameraContainer->GetTransform().SetPosition(cameraPosition);
}

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
    initGL();
    initRenderBase();
    
    // debug start
    transformTest();
    TestLoadShader();
    fbxTest();
    // endif
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyPress);
    glutTimerFunc(RENDER_FPS, timerFunc, 0);
    glutMainLoop();
    return EXIT_SUCCESS;
}

void TestLoadShader(){
    cout<<"TestLoadShader"<<endl;
    ShaderFileDataSource sfs;
    char name[] = "shadertest";
    ShaderLoadStatus status = SHADER_FILE_NOT_FOUND;
    Shader *s = sfs.LoadLinkShader(name, status);
    assert(status == SHADER_FILE_NOT_FOUND);

    char nameLinkBuggy[] = "linkbug";
    Shader *linkBug = sfs.LoadLinkShader(nameLinkBuggy, status);
    assert (linkBug == NULL);
    cout<<status<<endl;
    assert (status == SHADER_LINK_ERROR);

    char nameBuggy[] = "buggy";
    Shader *bug = sfs.LoadLinkShader(nameBuggy, status);
    assert (bug == NULL);
    assert (status == SHADER_COMPILE_ERROR_VERTEX_SHADER);
    
    char name2[] = "diffuse";
    Shader *b = sfs.LoadLinkShader(name2, status);
    assert (b!= NULL);
    assert (status == SHADER_OK);
    
    DefaultShaders *df = DefaultShaders::Instance();
    Shader *diffuseColor = df->GetDiffuseColor();
    assert(diffuseColor!=NULL);
}

void initGL(){
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
}

void initRenderBase(){
    renderBase->Init(glutSwapBuffers);
}

void transformTest(){
    Transform transform;
    Vector3 v(1,2,3);
    transform.SetPosition(v);
    float *localTransform = transform.GetLocalTransform().GetReference();
    float *localInverse = transform.GetLocalTransformInverse().GetReference();
    cout<<"localTranfor"<<endl;
    printMatrix(localTransform);
    cout<<"localInverse"<<endl;
    printMatrix(localInverse);
    
    Transform transform2;
    Matrix44 m;
    transform2.GetRotation().GetMatrix(&m);
    cout<<"Rotation"<<endl;
    printMatrix(m.GetReference());
}

void initWorld() {
    Camera *camera = new Camera();
    camera->SetProjection(40, 1, 0.1,1000);
    cameraContainer->AddCompnent(camera);
    renderBase->AddSceneObject(cameraContainer);
    Vector3 v(0.0,0.0,15.0);
    cameraContainer->GetTransform().SetPosition(v);
    
    SceneObject *teapotSceneObject = new SceneObject();
    Vector3 v2(0.0,0.0,0.0);
    teapotSceneObject->GetTransform().SetPosition(v2);
    renderBase->AddSceneObject(teapotSceneObject);
    meshTeapot->SetMesh(MeshFactory::CreateCube());
    teapotSceneObject->AddCompnent(meshTeapot);
    
    ShaderFileDataSource sfs;
    char name2[] = "diffuse";
    ShaderLoadStatus status = SHADER_FILE_NOT_FOUND;
    Shader *b = sfs.LoadLinkShader(name2, status);
    
    Material *mat = new Material(b);
    teapotSceneObject->AddCompnent(mat);
    
}

void fbxTest(){
    FBXLoader loader;
    
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