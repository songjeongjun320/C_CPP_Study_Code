#include "geometry.h"
#include <iostream>
#include <math.h>

using namespace std;
# define M_PI 3.141592

Point2D::Point2D(){
    x = 0;
    y = 0;
}

Point2D::Point2D(int x, int y){
    this->x = x;
    this->y = y;
}

Circle::Circle(){
    center = new Point2D();
    radius = 1;
}

Circle::Circle(int x, int y, float r){
    center = new Point2D(x,y);
    this->radius = r;
}

Circle::Circle(float r){
    center = new Point2D();
    this->radius = radius;
}

Circle::~Circle(){
    cout << "destroying object" << endl;
    delete center;
}

void Circle::setRadius(float radius){
    this->radius = radius;
}

float Circle::getDiameter(){
    return radius + radius;
}

float Circle::getCircumference(){
    return M_PI * getDiameter();
}
float Circle::getArea(){
    return (radius * radius) * M_PI;
}