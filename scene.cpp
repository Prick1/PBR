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
void Scene::load_mesh(const Mesh& mesh1,const glm::vec3 position){
    if(mesh1.created){
    for(unsigned int i = 0; i < mesh1.triangles.size(); i++ )
        primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle{ position + mesh1.triangles[i].point1_,
                                                                          position + mesh1.triangles[i].point2_,
                                                                          position + mesh1.triangles[i].point3_}));
    }
    else{
        primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f, 0.0f, -2.0f }, 0.4f }));
    }
}




void Scene::load( void ) 
{
    Mesh mesh1("lowpolytree.obj");
    load_mesh(mesh1, glm::vec3 {0.0f, 0.0f, -2.0f});
    /*primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  -1.0f, 0.0f, -1.0f }, 0.4f } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f, 0.0f, -2.0f }, 0.4f } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f,-1.0f, -3.0f }, 0.4f } ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f, 1.0f, -4.0f }, 0.4f } ) );
    //primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f,-0.5f, -3.0f }, 0.2f } ) );
    primitives_.push_back(Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{1.0f, 1.0f, -5.0f},
glm::vec3{0.7f, 1.0f, -3.0f}, glm::vec3{0.85f, 0.85f, -1.0f}} ) ); 
    primitives_.push_back(Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{0.9f, 0.9f, -5.1f},
glm::vec3{0.6f, 0.9f, -3.1f}, glm::vec3{0.75f, 0.75f, -1.1f}} ) ); 
    primitives_.push_back(Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{0.8f, 0.8f, -5.2f},
glm::vec3{0.5f, 0.8f, -3.2f}, glm::vec3{0.65f, 0.65f, -1.2f}} ) );
    primitives_.push_back(Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{0.7f, 0.7f, -5.3f},
glm::vec3{0.4f, 0.7f, -3.3f}, glm::vec3{0.55f, 0.55f, -1.3f}} ) );
    primitives_.push_back(Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{0.6f, 0.6f, -5.4f},
glm::vec3{0.3f, 0.6f, -3.4f}, glm::vec3{0.45f, 0.45f, -1.4f}} ) );
    primitives_.push_back(Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{0.5f, 0.5f, -5.5f},
glm::vec3{0.2f, 0.5f, -3.5f}, glm::vec3{0.35f, 0.35f, -1.5f}} ) );
    primitives_.push_back(Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{0.4f, 0.4f, -5.6f},
glm::vec3{0.1f, 0.4f, -3.6f}, glm::vec3{0.25f, 0.25f, -1.6f}} ) );		
    primitives_.push_back(Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{0.3f, 0.3f, -5.7f},
glm::vec3{0.0f, 0.3f, -3.7f}, glm::vec3{0.15f, 0.15f, -1.7f}} ) );
    primitives_.push_back(Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{0.2f, 0.2f, -5.8f},
glm::vec3{-0.1f, 0.2f, -3.8f}, glm::vec3{0.05f, 0.05f, -1.8f}} ) );
    primitives_.push_back(Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{0.1f, 0.1f, -5.9f},
glm::vec3{-0.2f, 0.1f, -3.9f}, glm::vec3{-0.05f, -0.05f, -1.9f}} ) );
    primitives_.push_back(Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{0.0f, 0.0f, -6.0f},
glm::vec3{-0.3f, 0.0f, -4.0f}, glm::vec3{-0.15f, -0.15f, -2.0f}} ) );
    primitives_.push_back(Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{-0.1f, -0.1f, -6.1f},
glm::vec3{-0.4f, -0.1f, -4.1f}, glm::vec3{-0.25f, -0.25f, -2.1f}} ) );
    primitives_.push_back(Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{-0.2f, -0.2f, -6.2f},
glm::vec3{-0.5f, -0.2f, -4.2f}, glm::vec3{-0.35f, -0.35f, -2.2f}} ) );
    primitives_.push_back(Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{-0.3f, -0.3f, -6.3f},
glm::vec3{-0.6f, -0.3f, -4.3f}, glm::vec3{-0.45f, -0.45f, -2.3f}} ) );
    primitives_.push_back(Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{-0.4f, -0.4f, -6.4f},
glm::vec3{-0.7f, -0.4f, -4.4f}, glm::vec3{-0.55f, -0.55f, -2.4f}} ) );
    primitives_.push_back(Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{-0.5f, -0.5f, -6.5f},
glm::vec3{-0.8f, -0.5f, -4.5f}, glm::vec3{-0.65f, -0.65f, -2.5f}} ) );
    primitives_.push_back(Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{-0.6f, -0.6f, -6.6f},
glm::vec3{-0.9f, -0.6f, -4.6f}, glm::vec3{-0.75f, -0.75f, -2.6f}} ) );
    primitives_.push_back(Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{-0.7f, -0.7f, -6.7f},
glm::vec3{-1.0f, -0.7f, -4.7f}, glm::vec3{-0.85f, -0.85f, -2.7f}} ) );
    primitives_.push_back(Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{-0.8f, -0.8f, -6.8f},
glm::vec3{-1.1f, -0.8f, -4.8f}, glm::vec3{-0.95f, -0.95f, -2.8f}} ) );
    primitives_.push_back(Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{-0.9f, -0.9f, -6.9f},
glm::vec3{-1.2f, -0.9f, -4.9f}, glm::vec3{-1.05f, -1.05f, -2.9f}} ) );
    primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  -0.8f, 0.7f, -2.0f }, 0.3f } ) );
    primitives_.push_back(Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{ 1.0f, -1.0f, -2.0f},
glm::vec3{ 0.4f, -1.0f, -3.0f}, glm::vec3{ 1.0f, -0.4f, -3.0f}} ) );
    primitives_.push_back(Primitive::PrimitiveUniquePtr( new Triangle{ glm::vec3{ 0.4f, -0.4f, -4.0f},
glm::vec3{ 0.4f, -1.0f, -3.0f}, glm::vec3{ 1.0f, -0.4f, -3.0f}} ) );*/
    
						       
}

