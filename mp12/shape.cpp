#include "shape.hpp"
#include <iostream>


//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable
Shape::Shape(string name) { name_ = name; }
string Shape::getName() { return name_; }

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Rectangle::Rectangle(double width, double length):Shape("Rectangle") { width_ = width; length_ = length; }
double Rectangle::getArea() const { return width_ * length_; }
double Rectangle::getVolume() const { return 0; }
Rectangle Rectangle::operator + (const Rectangle& rec){
  double newWidth = width_ + rec.getWidth();
  double newLength = length_ + rec.getLength();
  Rectangle c = Rectangle(newWidth,newLength);
  return c;
}
Rectangle Rectangle::operator -(const Rectangle& rec){
  double newWidth = width_ - rec.getWidth();
  double newLength = length_ - rec.getLength();
  if(newWidth < 0) { newWidth = 0; }
  if(newLength < 0) { newLength = 0; }
  Rectangle c = Rectangle(newWidth,newLength);
  return c;
}
double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}


//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Circle::Circle(double radius):Shape("Circle") { radius_ = radius; }
double Circle::getArea() const { return M_PI * pow(radius_,2); }
double Circle::getVolume() const { return 0; }
Circle Circle::operator + (const Circle& cir){
  double newRadius = radius_ + cir.getRadius();
  Circle c = Circle(newRadius);
  return c;
}
Circle Circle::operator - (const Circle& cir){
  double newRadius = radius_ - cir.getRadius();
  if(newRadius < 0) { newRadius = 0; }
  Circle c = Circle(newRadius);
  return c;
}
double Circle::getRadius()const{return radius_;}

//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Sphere::Sphere(double radius):Shape("Sphere") { radius_ = radius; }
double Sphere::getArea() const { return 4.0 * M_PI * pow(radius_,2); }
double Sphere::getVolume() const { return (4.0/3.0) * M_PI * pow(radius_,3); }
Sphere Sphere::operator + (const Sphere& cir){
  double newRadius = radius_ + cir.getRadius();
  Sphere c = Sphere(newRadius);
  return c;
}
Sphere Sphere::operator - (const Sphere& cir){
  double newRadius = radius_ - cir.getRadius();
  if(newRadius < 0) { newRadius = 0; }
  Sphere c = Sphere(newRadius);
  return c;
}
double Sphere::getRadius()const{return radius_;}

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
RectPrism::RectPrism(double width, double length, double height):Shape("RectPrism") { height_ = height; length_ = length; width_ = width; }
double RectPrism::getArea() const { return 2 * (length_ * height_ + width_ * height_ + length_ * width_); }
double RectPrism::getVolume() const { return width_ * length_ * height_; }
RectPrism RectPrism::operator +(const RectPrism& rectp){
  double newWidth = width_ + rectp.getWidth();
  double newHeight = height_ + rectp.getHeight();
  double newLength = length_ + rectp.getLength();
  RectPrism c = RectPrism(newWidth,newLength,newHeight);
  return c;
}
RectPrism RectPrism::operator -(const RectPrism& rectp){
  double newWidth = width_ - rectp.getWidth();
  double newHeight = height_ - rectp.getHeight();
  double newLength = length_ - rectp.getLength();
  if(newWidth < 0) { newWidth = 0; }
  if(newHeight < 0) { newHeight = 0; }
  if(newLength < 0) { newLength = 0; }
  RectPrism c = RectPrism(newWidth,newLength,newHeight);
  return c;
}
double RectPrism::getWidth()const{return width_;}
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
vector<Shape*> CreateShapes(char* file_name){
	//@@Insert your code here
	int n;
	double h,w,l,r;
	string name;
	vector<Shape*> vector;
	ifstream file;
	file.open(file_name,std::ifstream::in);
  file >> n;
  for(int i = 0; i < n; i++){
    file >> name;
    if(name=="Rectangle"){
      file >> w >> l;
      Rectangle* rect = new Rectangle(w,l);
      vector.push_back(rect);
    }
    if(name=="Circle"){
      file >> r;
      Circle* cir = new Circle(r);
      vector.push_back(cir);
    }
    if(name=="Sphere"){
      file >> r;
      Sphere* sph = new Sphere(r);
      vector.push_back(sph);
    }
    if(name=="RectPrism"){
      file >> w >> l >> h;
      RectPrism* rprism = new RectPrism(w,l,h);
      vector.push_back(rprism);
    }
  }
  file.close();
	return vector; // please remeber to modify this line to return the correct value
}

// call getArea() of each object
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
  for(int i = 0; i < shapes.size(); i++){
    if(shapes[i]->getArea() > max_area){
      max_area = shapes[i]->getArea();
    }
  }
	return max_area;
}


// call getVolume() of each object
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
	for(int i = 0; i < shapes.size(); i++){
	  if(shapes[i]->getVolume() > max_volume){
	    max_volume = shapes[i]->getVolume();
	  }
	}
	return max_volume;
}

