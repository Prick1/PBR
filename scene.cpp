#include "scene.h"

Scene::Scene( void )
{}

Scene::~Scene( void )
{
      if ( bvh_ )
    {
        delete bvh_;
        bvh_ = nullptr;
    }
}
/*
CheckIntersection::CheckIntersection(const Ray &ray, IntersectionRecord &intersection_record, const std::vector< Primitive::PrimitiveUniquePtr > &primitivesIn): ray(ray), primitives(primitivesIn){
    this->intersection_record = intersection_record;
    this->intersection_record.t_ = std::numeric_limits< double >::max();
}

void CheckIntersection::operator()(BoundingBox* node){
    if(node == nullptr)
        return;
    
    if(node->intersect(ray)){


        if(node->primitivesIndex == nullptr){
            this->operator()(node->left);
            this->operator()(node->right);
            return;
        }

        for(int primitiveId: *(node->primitivesIndex))
            
            if(primitives[primitiveId]->intersect(ray, tmp_intersection_record))
                
                if( (tmp_intersection_record.t_ < intersection_record.t_) && (tmp_intersection_record.t_ > 0.0) ){
                    intersection_record = tmp_intersection_record;
                    intersection_result = true;
                }
            
    }
}*/


bool Scene::intersect( const Ray &ray,
                       IntersectionRecord &intersection_record ) const
{
    /*CheckIntersection check_intersection{ray, intersection_record, primitives_};
    check_intersection(bvh->root);
    intersection_record = check_intersection.intersection_record;
    return check_intersection.intersection_result;
    return false;*/
    bool intersection_result = false;
    IntersectionRecord tmp_intersection_record;
    std::size_t num_primitives = primitives_.size();

    switch( acceleration_structure_ )
    {
        case AccelerationStructure::NONE:
            for ( std::size_t primitive_id = 0; primitive_id < num_primitives; primitive_id++ )
            {

                if ( primitives_[primitive_id]->intersect( ray, tmp_intersection_record ) )
                {


                    if ( ( tmp_intersection_record.t_ < intersection_record.t_ ) && ( tmp_intersection_record.t_ > 0.0 ) )
                    {
                        intersection_record = tmp_intersection_record;
                        intersection_result = true;
                    }
                }
            }
            break;

        case AccelerationStructure::BVH_SAH:
            intersection_result = bvh_->intersect( ray, intersection_record);
            break;
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
        primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.0f, 0.0f, -2.0f }, 0.4f , new LightSource(glm::vec3(20.0f))}));
    }
}

void Scene::buildAccelerationStructure( void )
{
    if ( acceleration_structure_ == Scene::AccelerationStructure::BVH_SAH )
    {
        buildBVH();
        std::clog << std::endl;
    }
}

void Scene::buildBVH( void )
{
    bvh_ = new BVH( primitives_ );
}


void Scene::load( void ) 
{
    

    Mesh mesh1("CornellBoxWithoutCrates.obj");
    load_mesh(mesh1, glm::vec3 {0.0f});
    Mesh mesh2("monkey.obj");
    load_mesh(mesh2, glm::vec3 (0.0f, 1.0f, -0.5f));
    
    //primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f, 0.31f, 0.1f }, 0.3f, new Dielectric(1.0f, 1.458f) }));
    //primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.3f, 0.31f, -0.3f}, 0.3f , new Specular() }));

    //bvh = new BVH(primitives_);
    //bvh->BVHBuild();						       
}

