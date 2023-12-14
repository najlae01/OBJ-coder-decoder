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
#include "ObjLoader.cpp"
#include "Renderer.cpp"

ObjLoader objLoader;
std::vector<Mesh> meshes;
int chosenObject = -1;
Renderer renderer(objLoader, meshes, chosenObject);

/*  Displays the rendered scene using the
    renderer object*/
void display() {
    renderer.display();
}

/*  Handles keyboard input, forwarding the key and
    its coordinates to the renderer for processing */
void keyboard(unsigned char key, int x, int y) {
    renderer.keyboard(key, x, y);
}

/*  Displays the names of sub-objects in the loaded meshes */
void displayNames(){
    std::cout << "Les noms des sous-objets :" << std::endl;
    for (const auto& mesh : meshes) {
        std::cout << mesh.name << std::endl;
    }
}

/*  Saves a specific mesh, chosen by index, to a
    file using the objLoader object */
void saveObjectInFile(int chosenObject) {
    objLoader.saveSpecificMesh(meshes, chosenObject);
}

/*  Displays a specific object in the viewport based on the chosen object index */
void displayObjectInViewport(int chosenObject) {
    int chosenObjectIndex = chosenObject - 1;
    renderer.setMeshIndex(chosenObjectIndex);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1000, 780);
    glutCreateWindow("Viewport");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
}

/*  Displays a menu with options for interacting with loaded objects */
void menu() {
    std::cout << "1. Afficher les noms des sous-objets." << std::endl;
    std::cout << "2. Sauvegarder un objet dans un fichier."<< std::endl;
    std::cout << "3. Afficher un objet dans le viewport."<< std::endl;
    std::cout << "4. Quitter."<< std::endl;
    while(true){
        std::cout << "Votre choix : ";
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1:
                displayNames();
                break;
            case 2:
                std::cout << "Enter le numero d'ordre d'objet à sauvegarder: ";
                std::cin >> chosenObject;
                saveObjectInFile(chosenObject);
                break;
            case 3:
                std::cout << "Enter le numero d'ordre d'objet à afficher dans le viewport: ";
                std::cin >> chosenObject;
                displayObjectInViewport(chosenObject);
                break;
            case 4:
                exit(0);
                break;
        }
    }
}

int main(int argc, char** argv) {
    objLoader = ObjLoader();
    meshes = objLoader.loadObj();

    glutInit(&argc, argv);
    menu();

    return 0;
}
