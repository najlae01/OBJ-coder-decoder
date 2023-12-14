#include "mesh.h"
#include "ObjLoader.h"

/*
    Loads OBJ file, parses the data, and returns a vector of Mesh objects
    Each Mesh represents a group in the OBJ file
*/
    std::vector<Mesh> ObjLoader::loadObj() {
        std::string filename;
        std::cout << "Entrer le nom du fichier: " << std::endl;
        std::cin >> filename;
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Erreur lors de l'ouverture du fichier: " << filename << std::endl;
            return {};
        }

        std::vector<Mesh> meshes;
        Mesh currentMesh;

        std::string line;

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string token;
            iss >> token;

            if (token == "g") {

                // Start of a new group (mesh)
                if (!currentMesh.name.empty()) {
                    meshes.push_back(currentMesh);
                }
                currentMesh.name = getNextToken(iss);
                currentMesh.data.clear();
                currentMesh.data.push_back("g " + currentMesh.name);
                currentMesh.hasFirstFaceValue = false; // Reseting flag for each mesh
            }

            // Storing the line data for the current group
            if (!currentMesh.name.empty()) {
                if (token == "v") {
                    // Vertex coordinates
                    GLfloat x, y, z;
                    iss >> x >> y >> z;
                    currentMesh.data.push_back("v " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z));
                } else if (token == "f") {
                    int indices[3];
                    int index;

                    // Storing the first face value
                    if (!currentMesh.hasFirstFaceValue) {
                        currentMesh.hasFirstFaceValue = true;
                        iss >> indices[0] >> indices[1] >> indices[2];
                        currentMesh.firstFaceValue = indices[0];
                        //std::cout << currentMesh.firstFaceValue << std::endl;
                        for (int i = 0; i < 3; ++i) {
                            indices[i] -= currentMesh.firstFaceValue;
                            indices[i] ++;
                        }
                    }
                    else {
                        iss >> indices[0] >> indices[1] >> indices[2];

                        // Subtracting the first face value from each index
                        for (int i = 0; i < 3; ++i) {
                            indices[i] -= currentMesh.firstFaceValue;
                            indices[i] ++;
                        }
                    }

                    // Writing the new face with updated vertex indices
                    currentMesh.data.push_back("f " +
                                               std::to_string(indices[0]) + " " +
                                               std::to_string(indices[1]) + " " +
                                               std::to_string(indices[2]));
                } else if (token == "s") {
                    int smoothingGroup;
                    iss >> smoothingGroup;
                    currentMesh.data.push_back("s " + std::to_string(smoothingGroup));
                }
            }
        }

        if (!currentMesh.name.empty()) {
            meshes.push_back(currentMesh);
        }

        return meshes;
    }

/*
    Saves all meshes in the provided vector to separate OBJ files
    The files are named based on the mesh names
*/
    void saveMeshes(const std::vector<Mesh>& meshes) {
        for (const auto& mesh : meshes) {
            if (!mesh.data.empty()) {
                std::ofstream outFile(mesh.name + ".obj");
                if (outFile.is_open()) {
                    for (const auto& line : mesh.data) {
                        outFile << line << "\n";
                    }
                    outFile.close();
                    std::cout << "Objet " << mesh.name << " Sauvegarde dans le fichier: " << mesh.name + ".obj" << std::endl;
                } else {
                    std::cerr << "Erreur lors de la creation du fichier: " << mesh.name + ".obj" << std::endl;
                }
            }
        }
    }

/*
    Saves a specific mesh (chosen by index) to an OBJ file
    The file is named based on the mesh name
*/
    void ObjLoader::saveSpecificMesh(std::vector<Mesh>& meshes, int chosenObject){
        int chosenObjectIndex = chosenObject - 1;
        for (long unsigned int i=0; i < meshes.size(); i++) {
            if(i == chosenObjectIndex){
                if (!meshes[i].data.empty()) {
                    std::ofstream outFile(meshes[i].name + ".obj");
                    if (outFile.is_open()) {
                        for (const auto& line : meshes[i].data) {
                            outFile << line << "\n";
                        }
                        outFile.close();
                        std::cout << "Objet " << meshes[i].name << " Sauvegarde dans le fichier: " << meshes[i].name + ".obj" << std::endl;
                    } else {
                        std::cerr << "Erreur lors de la creation du fichier: " << meshes[i].name + ".obj" << std::endl;
                    }
                }
            }

        }
    }

/*
    Displays the specified mesh using the provided render mode
    Assumes the mesh data contains vertex and face information
    Renders triangles for simplicity
*/
    void ObjLoader::displayMesh(const Mesh& mesh, GLenum renderMode) {

        std::vector<glm::vec3> vertices;

        // Set render mode
        glPolygonMode(GL_FRONT_AND_BACK, renderMode);

        glBegin(GL_TRIANGLES);

        for (const auto& line : mesh.data) {
            std::istringstream iss(line);
            std::string token;
            iss >> token;

            if (token == "v") {
                // Vertex coordinates
                GLfloat x, y, z;
                iss >> x >> y >> z;
                vertices.push_back(glm::vec3(x, y, z));
            } else if (token == "f") {
                // Face definition (assuming triangles for simplicity)
                int v1, v2, v3;
                iss >> v1 >> v2 >> v3;

                // Assuming vertex indices start from 1 in OBJ files
                // Adjust if indices start from 0
                v1--; v2--; v3--;

                // Assuming vertices are specified in counter-clockwise order
                glVertex3f(vertices[v1].x, vertices[v1].y, vertices[v1].z);
                glVertex3f(vertices[v2].x, vertices[v2].y, vertices[v2].z);
                glVertex3f(vertices[v3].x, vertices[v3].y, vertices[v3].z);
            }
        }

        glEnd();

        // Reset render mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

/*
    Retrieves the next token from the istringstream
    Used for parsing OBJ file data
*/
    std::string ObjLoader::getNextToken(std::istringstream& iss) {
        std::string token;
        iss >> token;
        return token;
    }
