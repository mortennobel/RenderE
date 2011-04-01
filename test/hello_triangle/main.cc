/* 
 * File:   main.cc
 * Author: morten
 *
 * Created on April 1, 2011, 11:52 AM
 */

#include <cstdlib>
#include <iostream>

#ifdef _WIN32
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include <glm/glm.hpp>
#include <render_e/Camera.h>

using namespace std;

render_e::SceneObject so;
render_e::Camera cam;

int w;
int h;

void display(void) {
    cam.Setup(w, h);
    //glViewport(0, 0, w, h);
    //glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    {
        glColor3f(1, 0, 0);
        glVertex2f(0, 0);

        glColor3f(0, 1, 0);
        glVertex2f(.5, 0);

        glColor3f(0, 0, 1);
        glVertex2f(.5, .5);
    }
    glEnd();
    cam.TearDown();
    glutSwapBuffers();
}

void reshape(int w1, int h1) {
    w = w1;
    h = h1;
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    so.AddCompnent(&cam);
    so.GetTransform()->SetPosition(glm::vec3(0,0,1));
//    so.GetTransform()->SetRotation(glm::vec3(0,10,0));
    cam.SetProjection(40, 1, 0.1f, 100.0f);

    glm::mat4 invMat = so.GetTransform()->GetLocalTransformInverse();
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            cout<<invMat[x][y]<<" ";
        }
        cout<<endl;
    }

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Part 1");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
