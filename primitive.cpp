#include "primitive.h"

Primitive::Primitive(Material* material):material_(material)
{}

Primitive::~Primitive( void )
{ 
    //if(material_ != NULL)	
	//delete material_;
}

