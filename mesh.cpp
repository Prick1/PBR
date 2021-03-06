#include "mesh.h"

Mesh::Mesh(const std::string &pFile){
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(pFile, aiProcess_CalcTangentSpace       |
                                             aiProcess_Triangulate            |
                                             aiProcess_JoinIdenticalVertices  |
                                             aiProcess_SortByPType);
    if (scene){
		for (unsigned int c = 0; c < scene->mNumMaterials; c++){
			aiColor3D diffuseColor = {0.5,0.5,0.5};
			aiColor3D emissiveColor = {2,2,2};

		
			if(scene->mMaterials){
				scene->mMaterials[c]->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor);
            	scene->mMaterials[c]->Get(AI_MATKEY_COLOR_EMISSIVE, emissiveColor);
			}
			glm::vec3 emittance(emissiveColor.r, emissiveColor.g, emissiveColor.b);
			glm::vec3 diffusereflectance(diffuseColor.r, diffuseColor.g, diffuseColor.b);
			materials.push_back(new Diffuse(emittance, diffusereflectance));
		}

		for (unsigned int k = 0; k < scene->mNumMeshes; k++){
        	aiMesh *mesh1 = scene->mMeshes[k];

			
			//std::cout << "(" << diffusereflectance.x << "," << diffusereflectance.y << "," << diffusereflectance.z  << ")" << std::endl;

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

					triangles.push_back(new Triangle(vertices[0], vertices[1], vertices[2]
										, materials[mesh1->mMaterialIndex]));
                	//triangles.push_back(Triangle(vertices[0],vertices[1], vertices[2], m));
            	}

        	}

	}

    created = true;

    }
}

void Mesh::Translate(glm::vec3 position){
	for(unsigned int i = 0; i < triangles.size(); i++){
		triangles[i]->point1_ += position;
		triangles[i]->point2_ += position;
		triangles[i]->point3_ += position;
	}
}
