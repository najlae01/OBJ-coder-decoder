#include "Renderer.h"
#include <iostream>

/*
    Constructor for the Renderer class. Initializes the Renderer object with the provided
    ObjLoader, vector of Meshes, and an initial mesh index. Sets the render mode to GL_FILL
*/
Renderer::Renderer(ObjLoader& objLoader, std::vector<Mesh>& meshes, int meshIndex)
    : objLoader(objLoader), meshes(meshes), currentMeshIndex(meshIndex), renderMode(GL_FILL) {
    }

/*
    Displays the scene in the viewport. Clears the color and depth buffers,
    updates the object to be centered, displays menu text, and renders the current mesh
*/
void Renderer::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    updateObjectToCenter(meshes[currentMeshIndex]);

    glColor3f(1.0, 1.0, 1.0);

    drawText(10, 90, "Cloud Mode ==> c");
    drawText(10, 70, "Wireframe Mode ==> w");
    drawText(10, 50, "Solid Mode ==> s");
    drawText(10, 30, "Display Next Object ==> n");
    drawText(10, 10, "Close the Viewport ==> o");

    //printf("Displaying the Mesh with Index %d", currentMeshIndex);
    objLoader.displayMesh(meshes[currentMeshIndex], renderMode);

    glutSwapBuffers();
}

/*
    Draws text on the screen at the specified coordinates. Uses GLUT functions for rendering
*/
void Renderer::drawText(float x, float y, const std::string& text) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT));

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glRasterPos2f(x, y);

    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
}

/*
    Handles keyboard input. Switches render modes, displays the next mesh,
    or closes the viewport based on the pressed key
*/
void Renderer::keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'c':
            std::cout<< "cloud" << std::endl;
            renderMode = GL_POINT;
            break;
        case 'w':
            std::cout<< "wireframe" << std::endl;
            renderMode = GL_LINE;
            break;
        case 's':
            std::cout<< "solid" << std::endl;
            renderMode = GL_FILL;
            break;
        case 'n':
            std::cout<< "next mesh" << std::endl;
            currentMeshIndex = (currentMeshIndex + 1) % meshes.size();
            break;
        case 'o':
            std::cout << "Closing the viewport" << std::endl;
            glutDestroyWindow(glutGetWindow());
            exit(0);
            break;
    }

    glutPostRedisplay();
}

/*
    Sets the current mesh index to the specified value
*/
void Renderer::setMeshIndex(int chosenObject){
    currentMeshIndex = chosenObject;
}

/*
    Updates the object to be centered in the viewport. Uses the bounding box of the mesh
    to calculate the center and applies translation using the model-view matrix
*/
void Renderer::updateObjectToCenter(const Mesh& mesh) {
    // Ensuring that the mesh has at least one vertex
    if (mesh.data.empty()) {
        return;
    }

    // Initializing min and max values to the extremes
    glm::vec3 minValues(std::numeric_limits<float>::max());
    glm::vec3 maxValues(std::numeric_limits<float>::lowest());

    // Iterating through all vertices to find the min and max values along each axis
    for (const std::string& line : mesh.data) {
        if (line.compare(0, 2, "v ") == 0) {
            std::istringstream iss(line.substr(2));
            glm::vec3 vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;

            // Updating min and max values
            minValues = glm::min(minValues, vertex);
            maxValues = glm::max(maxValues, vertex);
        }
    }

    // Calculating the center of the bounding box
    glm::vec3 boundingBoxCenter = (minValues + maxValues) * 0.5f;

    // Using the model-view matrix for translation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-boundingBoxCenter.x, -boundingBoxCenter.y, -boundingBoxCenter.z);
}
