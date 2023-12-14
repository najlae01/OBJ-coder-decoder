/*
    The Mesh struct represents a 3D mesh or object loaded from an OBJ file.
    It consists of a name, a vector of string data representing the lines of the OBJ file,
    information about the first face value encountered, and a flag indicating whether the
    first face value has been set.
    This struct is typically used in conjunction with the ObjLoader class to represent
    individual meshes in a Obj file
*/

#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>

struct Mesh {
    std::string name; // represents the name of the mesh
    std::vector<std::string> data; // contains the raw data lines from the OBJ file
    int firstFaceValue; // represents the value of the first face index encountered
    bool hasFirstFaceValue; // flag indicating whether the first face index has been set

    Mesh() : firstFaceValue(1), hasFirstFaceValue(false) {}
};


#endif // MESH_H_INCLUDED
