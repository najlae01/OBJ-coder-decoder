/*
    The Renderer class is responsible for rendering 3D meshes in a viewport.
    It works in conjunction with an ObjLoader to load and display meshes. The class
    allows for user interaction to switch render modes, navigate through meshes, and
    view the scene in the viewport
*/

#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include "ObjLoader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <vector>
#include <limits>
#include <GL/glew.h>
#include <GL/glut.h>

class Renderer {
public:
    Renderer(ObjLoader& objLoader, std::vector<Mesh>& meshes, int meshIndex);

    void display();
    void keyboard(unsigned char key, int x, int y);
    void drawText(float x, float y, const std::string& text);
    void setMeshIndex(int chosenObject);
    void updateObjectToCenter(const Mesh& mesh);

private:
    ObjLoader& objLoader; // Reference to the ObjLoader for loading and managing meshes
    std::vector<Mesh>& meshes; // Reference to a vector of Meshes representing the 3D objects in the file
    int currentMeshIndex; // Index of the currently displayed or saved mesh in the meshes vector
    GLenum renderMode; // GLenum representing the current rendering mode (e.g., GL_FILL, GL_POINT)
};


#endif // RENDERER_H_INCLUDED
