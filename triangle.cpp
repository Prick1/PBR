#include "triangle.h"

Triangle::Triangle(void){}

Triangle::Triangle( const glm::vec3 &point1, const glm::vec3 &point2, const glm::vec3 &point3,
	glm::vec3 colorIn):
	Primitive(colorIn), 
	point1_(point1), 
	point2_(point2), 
	point3_(point3)
{}

bool Triangle::intersect( const Ray &ray,
                        IntersectionRecord &intersection_record ) const{
	
	float a, b, c, d, e, f, g, h, i, j, k, l;
	a = point1_.x - point2_.x;
	b = point1_.y - point2_.y;
	c = point1_.z - point2_.z;
	d = point1_.x - point3_.x;
	e = point1_.y - point3_.y;
	f = point1_.z - point3_.z;
	g = ray.direction_.x;
	h = ray.direction_.y;
	i = ray.direction_.z;
	j = point1_.x - ray.origin_.x;
	k = point1_.y - ray.origin_.y;
	l = point1_.z - ray.origin_.z;
	float M = a*(e*i-h*f)+b*(g*f-d*i)+c*(d*h-e*g);
	float t = -(f*(a*k-j*b)+e*(j*c-a*l)+d*(b*l-k*c))/M;
	if(t < 0.0f)
		return false;
	float gama = (i*(a*k-j*b)+h*(j*c-a*l)+g*(b*l-k*c))/M;
	if(gama < 0.0f || gama > 1.0f)
		return false;
	float beta = (j*(e*i-h*f)+k*(g*f-d*i)+l*(d*h-e*g))/M;
	if(beta < 0.0f || beta > 1.0f-gama)
		return false;
	intersection_record.t_ = t;
	intersection_record.position_ = ray.origin_ + intersection_record.t_ * ray.direction_;
	glm::vec3 center_ = glm::vec3((point1_.x+point2_.x+point3_.x)/3.0f, (point1_.y+point2_.y+point3_.y)/3.0f, (point1_.z+point2_.z+point3_.z)/3.0f);
	intersection_record.normal_ = glm::normalize(intersection_record.position_ - center_);
	intersection_record.intersectionColor = color;
	return true;	
}
