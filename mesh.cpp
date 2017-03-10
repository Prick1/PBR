#include "mesh.h"

Mesh::Mesh(const std::string &pFile){
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(pFile, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
    if (scene){
	for (unsigned int k = 0; k < scene->mNumMeshes; k++){
        	aiMesh *mesh1 = scene->mMeshes[k];
        	for(unsigned int i = 0; i < mesh1->mNumFaces; i++){
            		aiFace face = mesh1->mFaces[i];
            		if(face.mNumIndices == 3){
                		glm::vec3 vertices[3];
                		vertices[0].x = mesh1->mVertices[face.mIndices[0]].x; 
                		vertices[0].y = mesh1->mVertices[face.mIndices[0]].y;
                		vertices[0].z = mesh1->mVertices[face.mIndices[0]].z;
                		vertices[1].x = mesh1->mVertices[face.mIndices[1]].x; 
                		vertices[1].y = mesh1->mVertices[face.mIndices[1]].y;
                		vertices[1].z = mesh1->mVertices[face.mIndices[1]].z;
                		vertices[2].x = mesh1->mVertices[face.mIndices[2]].x; 
                		vertices[2].y = mesh1->mVertices[face.mIndices[2]].y;
                		vertices[2].z = mesh1->mVertices[face.mIndices[2]].z;
                		triangles.push_back(Triangle(vertices[0],vertices[1], vertices[2]));
            		}
        	}
	}
        created = true;
    }
}
