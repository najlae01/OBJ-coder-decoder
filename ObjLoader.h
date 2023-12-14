/*
    The ObjLoader class is responsible for loading, saving, and displaying 3D mesh data
    from OBJ files. It works with a vector of Mesh objects to represent individual
    meshes or objects in a file or a scene
*/

#ifndef OBJLOADER_H_INCLUDED
#define OBJLOADER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm.hpp>
#include "mesh.h"


class ObjLoader {
public:
    std::vector<Mesh> loadObj();
    void saveMeshes(std::vector<Mesh>& meshes);
    void saveSpecificMesh(std::vector<Mesh>& meshes, int chosenObject);
    void displayMesh(const Mesh& mesh, GLenum renderMode);

private:
    std::string getNextToken(std::istringstream& iss);
};


#endif // OBJLOADER_H_INCLUDED
