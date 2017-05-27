#include "mesh.h"

Mesh::Mesh(const std::string &pFile,Material* material){
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(pFile, aiProcess_CalcTangentSpace       |
                                             aiProcess_Triangulate            |
                                             aiProcess_JoinIdenticalVertices  |
                                             aiProcess_SortByPType);
    if (scene){
		for (unsigned int c = 0; c < scene->mNumMaterials; c++){
			aiColor3D diffuseColor = {0.0,0.0,0.0};
			aiColor3D emissiveColor = {0.0,0.0,0.0};

		
			if(scene->mMaterials && material == NULL){
				scene->mMaterials[c]->Get(AI_MATKEY_COLOR_EMISSIVE, emissiveColor);
				scene->mMaterials[c]->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor);
				glm::vec3 emittance(emissiveColor.r, emissiveColor.g, emissiveColor.b);
				glm::vec3 diffusereflectance(diffuseColor.r, diffuseColor.g, diffuseColor.b);

				if(glm::length(emittance) > 0.001f){
					materials.push_back(new LightSource(emittance));
				}

				else if(glm::length(diffusereflectance) > 0.001f){
					materials.push_back(new Diffuse(diffusereflectance));
				}
			}
			else
				materials.push_back(new Diffuse(glm::vec3 (0.7f, 0.5f, 0.3f)));
			
			
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
					if(material == NULL)
						triangles.push_back(new Triangle(vertices[0], vertices[1], vertices[2]
											, materials[mesh1->mMaterialIndex]));
					else
                	    triangles.push_back(new Triangle(vertices[0],vertices[1], vertices[2], material));
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

void Mesh::Scale(glm::vec3 factor){
	for(unsigned int i = 0; i < triangles.size(); i++){
		triangles[i]->point1_ *= factor;
		triangles[i]->point2_ *= factor;
		triangles[i]->point3_ *= factor;
	}
}