#include "scene.h"

Scene::Scene( void )
{}

Scene::~Scene( void )
{}

bool Scene::intersect( const Ray &ray,
                       IntersectionRecord &intersection_record ) const
{
    bool intersection_result = false;
    IntersectionRecord tmp_intersection_record;
    std::size_t num_primitives = primitives_.size();

    // Loops over the list of primitives, testing the intersection of each primitive against the given ray 
    for ( std::size_t primitive_id = 0; primitive_id < num_primitives; primitive_id++ )
        if ( primitives_[primitive_id]->intersect( ray, tmp_intersection_record ) )
            if ( ( tmp_intersection_record.t_ < intersection_record.t_ ) && ( tmp_intersection_record.t_ > 0.0 ) )
            {
                intersection_record = tmp_intersection_record;
                intersection_result = true; // the ray intersects a primitive!
            }

    return intersection_result;
}
void Scene::load_mesh(Mesh& mesh1,const glm::vec3 position){
    
    if(mesh1.created){
        mesh1.Translate(position);
        for(unsigned int i = 0; i < mesh1.triangles.size(); i++ ){
	        primitives_.push_back(Primitive::PrimitiveUniquePtr(mesh1.triangles[i]));
	    }
    }

    else{
        primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f, 0.0f, -2.0f }, 0.4f , new Diffuse(glm::vec3(20.0f), glm::vec3(1.0f))}));
    }
}




void Scene::load( void ) 
{
    

    Mesh mesh1("CornellBox.obj");
    load_mesh(mesh1, glm::vec3 {0.0f});
    
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f, 1.0f, 0.0f }, 0.4f, new Specular() }));
/*
    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle( glm::vec3(-1.0f,-1.0f, 0.0f),  //DOWN
                                                                      glm::vec3(1.0f, -1.0f, 0.0f),
                                                                      glm::vec3(1.0f, -1.0f, -5.0f)
								, new Diffuse(glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f)))));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle( glm::vec3(-1.0f,-1.0f, 0.0f), 
                                                                      glm::vec3(-1.0f, -1.0f, -5.0f),
                                                                      glm::vec3(1.0f, -1.0f, -5.0f)
								, new Diffuse(glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f)))));

    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle( glm::vec3(-1.0f, 1.0f, 0.0f), //TOP
                                                                      glm::vec3(-1.0f, 1.0f, -5.0f),
                                                                      glm::vec3(1.0f, 1.0f, -5.0f)
								, new Diffuse(glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f)))));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle( glm::vec3(-1.0f, 1.0f, 0.0f), 
                                                                      glm::vec3(1.0f, 1.0f, 0.0f),
                                                                      glm::vec3(1.0f, 1.0f, -5.0f)
								, new Diffuse(glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f)))));

    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle( glm::vec3(-1.0f, -1.0f, 0.0f), //LEFT
                                                                      glm::vec3(-1.0f, 1.0f, 0.0f),
                                                                      glm::vec3(-1.0f, 1.0f, -5.0f)
								, new Diffuse(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)))));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle( glm::vec3(-1.0f, 1.0f, -5.0f), 
                                                                      glm::vec3(-1.0f, -1.0f, -5.0f),
                                                                      glm::vec3(-1.0f, -1.0f, 0.0f)
								, new Diffuse(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)))));

    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle( glm::vec3( 1.0f, -1.0f, 0.0f), //RIGHT
                                                                      glm::vec3( 1.0f, 1.0f, 0.0f),
                                                                      glm::vec3( 1.0f, 1.0f, -5.0f)
								, new Diffuse(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)))));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle( glm::vec3( 1.0f, 1.0f, -5.0f), 
                                                                      glm::vec3( 1.0f, -1.0f, -5.0f),
                                                                      glm::vec3( 1.0f, -1.0f, 0.0f)
								, new Diffuse(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)))));

    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle( glm::vec3( -1.0f, -1.0f, -5.0f), //BACK
                                                                      glm::vec3( -1.0f, 1.0f,-5.0f),
                                                                      glm::vec3( 1.0f, 1.0f, -5.0f)
								, new Diffuse(glm::vec3(0.0f), glm::vec3(0.5f, 0.5f, 0.5f)))));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle( glm::vec3( 1.0f, 1.0f, -5.0f), 
                                                                      glm::vec3( 1.0f, -1.0f, -5.0f),
                                                                      glm::vec3( -1.0f, -1.0f, -5.0f)
								, new Diffuse(glm::vec3(0.0f), glm::vec3(0.5f, 0.5f, 0.5f)))));

    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle( glm::vec3( 1.5f, -1.0f, 0.0f), //RIGHT 2(test)
                                                                      glm::vec3( 1.5f, 1.0f, 0.0f),
                                                                      glm::vec3( 1.5f, 1.0f, -5.0f)
								, new Diffuse(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)))));
    primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle( glm::vec3( 1.5f, 1.0f, -5.0f), 
                                                                      glm::vec3( 1.5f, -1.0f, -5.0f),
                                                                      glm::vec3( 1.5f, -1.0f, 0.0f)
								, new Diffuse(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)))));*/

    
    


						       
}

