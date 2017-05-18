#include "scene.h"

Scene::Scene( void )
{}

Scene::~Scene( void )
{}

bool Scene::intersect( const Ray &ray,
                       IntersectionRecord &intersection_record ) const
{
   return boundingVolumeHierarchy->intersect(ray, intersection_record);
}
void Scene::load_mesh(Mesh& mesh1,const glm::vec3 position){
    
    if(mesh1.created){
        mesh1.Translate(position);
        for(unsigned int i = 0; i < mesh1.triangles.size(); i++ ){
	        primitives_.push_back(Primitive::PrimitiveUniquePtr(mesh1.triangles[i]));
	    }
    }

    else{
        primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f, 0.0f, -2.0f }, 0.4f , new LightSource(glm::vec3(20.0f))}));
    }
}




void Scene::load( void ) 
{
    

    Mesh mesh1("CornellBoxWithoutCrates.obj");
    load_mesh(mesh1, glm::vec3 {0.0f});
    Mesh mesh2("lowpolytree.obj");
    load_mesh(mesh2, glm::vec3 (0.0f, 1.0f, 0.0f));
    
    //primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f, 0.31f, 0.1f }, 0.3f, new Dielectric(1.0f, 1.458f) }));
    //primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.3f, 0.31f, -0.3f}, 0.3f , new Specular() }));


    boundingVolumeHierarchy = BVH::BVHBuild(primitives_);
						       
}

