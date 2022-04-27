/*  
	This code contains functions used in main.cpp. The code below contains classes and subclasses, specifically of shapes. The shapes
	are rectangle, circle, sphere, and rectangular prism. This code mainly contains the code which initializes said classes. Shape has
	a name function and each shape has getter functions for its dimensions, area, and volume as well as plus and minus functions to be
	used on its dimensions. There is also a function to initialize a list with shapes from a file and two funcitons which returns the
	maximum area and volume of a list of shapes. A list of classes and functions are given below:
	
	Classes:
		1. Shape
		2. Rectangle
		3. Circle
		4. Sphere
		5. RectPrism
		Functions in classes:
			1. getName
			2. getWidth
			3. getLength
			4. getHeight
			5. getRadius
			6. getArea
			7. getVolume
			8. operator +
			9. operator -
	Functions:
		1. CreateShapes
		2. MaxArea
		3. MaxVolume
    
    Explanations for each function and class as well as their inputs, outputs, and effects are detailed in code below.
    Algorithms used for functions:
		1. CreateShapes
			Uses ifstream to access file. Afterwards, it stores the total number of shapes to use in a for loop to iterate through
			the file. Then, it goes through each line and checks the shape in the file. If statements are used to determine
			which shape is detected and from their it stores the dimensions of the shape from the file into variables and creates the
			shape. That new shape is then stored into the list which contains all the shapes in the file. For rectangles specifically,
			you have to check the varible type as well because it can take ints, float, or doubles. Additional if statements were
			included to check the variable type and make the corresponding rectangle.
		2. MaxArea
			Since the parameter is a list of shapes, a loop is needed to iterate through the entire list to find the maximum area
			value. A variable holds the current maximum value and an if statement inside the loop checks the current shapes area.
			If the area is bigger than the current maximum value, then it replaces it.
		3. MaxVolume
			Same exact algorithm as above except with volume.
		4. Getter functions
			Simple return statement returning the private variable of whatever was called. If calling for area or volume, then it
			returns the area or volume with all the dimensions of the shape plugged into an equation which will yeild the answer.
		5. Operator functions
			Simply adds the dimension of the current shape with the dimension of the shape in the parameter and returns a new shape
			with the new dimension. For the subtraction operator, same thing is done except it returns 0 if the value ends up being
			negative.

    Matthew Wei
    mswei2
    April 26, 2022
*/

#ifndef SHAPE_H_
#define SHAPE_H_

#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<list>
#include<fstream>
#include <iomanip>    

using namespace std;

//Base class
//Please implement Shape's member functions
//constructor, getName()
class Shape{
public:
	//Base class' constructor should be called in derived classes'
	//constructor to initizlize Shape's private variable 
  	Shape(string name) {
		  name_ = name;
	}	
  	string getName() {
		  return name_;
	}
  	virtual double getArea() const = 0;
  	virtual double getVolume() const = 0;	
private:
  string name_;
};

//Rectangle
//Rectangle shape class
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
template <class T>
class Rectangle : public Shape{
public:
  	Rectangle<T>(T width = 0, T length = 0):Shape("Rectangle") {
		  width_ = width;
		  length_ = length;
	}	
  	double getArea() const {
		  return (double)width_*length_;
	}	
  	double getVolume() const {
		  return 0.0;
	}
	Rectangle<T> operator + (const Rectangle<T>& rec) {
		T w = width_ + rec.getWidth();
		T l = length_ + rec.getLength();
		return Rectangle(w, l);
	}	
	Rectangle<T> operator - (const Rectangle<T>& rec) {
		T w = fmax(0.0, width_ - rec.getWidth());
		T l = fmax(0.0, length_ - rec.getLength());
		return Rectangle(w, l);
	} 	
	T getWidth() const { 
		return width_;
	}	
	T getLength() const { 
		return length_;
	}
private:
	T width_;
    T length_;
};

//Circle
//Circle shape class
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
class Circle : public Shape{
public:
  	Circle(double radius):Shape("Circle") {
		  radius_ = radius;
	}
  	double getArea() const{
		  return M_PI*radius_*radius_;
	}
 	double getVolume() const{
		 return 0;
	 }	
  	Circle operator + (const Circle& cir){
		double r = radius_ + cir.getRadius();
		return Circle(r);
	}	
	Circle operator - (const Circle& cir){
		double r = fmax(0.0, radius_ + cir.getRadius());
		return Circle(r);
	} 
	double getRadius() const { 
		return radius_;
	}	
private:
	double radius_;
};

//Sphere
//Sphere shape class
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
class Sphere : public Shape{
public:
  	Sphere(double radius):Shape("Sphere") {
		  radius_ = radius;
	}
  	double getVolume() const {
		  return 4.0/3*M_PI*pow(radius_, 3.0);
	}		
  	double getArea() const {
		  return 4*M_PI*radius_*radius_;
	}
	Sphere operator + (const Sphere& sph) {
		double r = radius_ + sph.getRadius();
		return Sphere(r);
	}
	Sphere operator - (const Sphere& sph) {
		double r = fmax(0.0, radius_ + sph.getRadius());
		return Sphere(r);
	} 
	double getRadius() const {
		return radius_;
	}
private:
	double radius_;
};

//Rectprism
//Rectangular Prism shape class
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
class RectPrism : public Shape{
public:
  	RectPrism(double width, double length, double height):Shape("RectPrism") {
		  width_ = width;
		  length_ = length;
		  height_ = height;
	}
  	double getVolume() const {
		return width_*length_*height_;
	}
	double getArea() const {
		return 2*((width_*length_) + (width_*height_) + (length_*height_));
	}
	RectPrism operator + (const RectPrism& rectp){
		double w = width_ + rectp.getWidth();
		double l = length_ + rectp.getLength();
		double h = height_ + rectp.getHeight();
		return RectPrism(w, l, h);
	}
	RectPrism operator - (const RectPrism& rectp){
		double w = fmax(0.0, width_ - rectp.getWidth());
		double l = fmax(0.0, length_ - rectp.getLength());
		double h = fmax(0.0, height_ - rectp.getHeight());
		return RectPrism(w, l, h);
	}	
	double getWidth() const { 
		return width_;
	}
	double getLength() const { 
		return length_;
	}
	double getHeight() const { 
		return height_;
	}
private:
  	double length_;
  	double width_;
  	double height_;
};

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
static list<Shape*> CreateShapes(char* file_name) {
	int total;
	double w,h,l,r;
	list<Shape*> shapes;
	Shape* shape;
	ifstream file (file_name);
	file>>total;
	for(int i = 0; i<total; i++) {
		string name;
		file>>name;
		if (name=="Rectangle") {
			if (sizeof(file.peek())==sizeof(int)) {
				file>>w>>l;
				shape = new Rectangle<int>((int)w,(int)l);
			} else if (sizeof(file.peek())==sizeof(double)) {
				file>>w>>l;
				shape = new Rectangle<double>(w,l);
			} else if (sizeof(file.peek())==sizeof(float)) {
				file>>w>>l;
				shape = new Rectangle<float>((float)w,(float)l);
			}
		} else if(name=="Circle") {
			file>>r;
			shape = new Circle(r);
		} else if(name=="Sphere") {
			file>>r;
			shape = new Sphere(r);
		} else if(name=="RectPrism") {
			file>>w>>l>>h;
			shape = new RectPrism(w,l,h);
		}
		shapes.push_back(shape);
	}
	file.close();
	return list<Shape*>(0, NULL);;
}

// call getArea() of each object 
// return the max area
static double MaxArea(list<Shape*> shapes){
	double max_area = 0;
	for (list<Shape*>::iterator it = shapes.begin(); it!=shapes.end(); it++) {
		double area = (*it)->getArea();
		if (area>max_area) {
			max_area = area;
		}
	}
	return max_area;
}

// call getVolume() of each object 
// return the max volume
static double MaxVolume(list<Shape*> shapes){
	double max_volume = 0;
	for (list<Shape*>::iterator it = shapes.begin(); it!=shapes.end(); it++) {
		double volume = (*it)->getVolume();
		if (volume>max_volume) {
			max_volume = volume;
		}
	}
	return max_volume;
}
#endif