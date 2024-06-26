#pragma once
// #ifndef GEOM_H
#define GEOM_H

class Point2D{
    private:
        int x;
        int y;

    public:
        Point2D();
        Point2D(int, int);
        Point2D(Point2D*);
};

class Circle{
    private:
        Point2D* center;
        float radius;

    public:
        Circle();
        Circle(int, int, float);
        Circle(float);
        ~Circle();

        void setRadius(float);
        float getDiameter();
        float getCircumference();
        float getArea();
        void rebuildCenter(int, int);
};