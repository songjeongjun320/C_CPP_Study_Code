#include <iostream>
#include "geometry.h"

using namespace std;

int main(int argc, char** argv){
    Circle stackCirc(5.0);
    Circle* heapCirc = new Circle(2,2,10.0);

    cout << &stackCirc << " " << stackCirc.getArea() << endl;
    cout << heapCirc << " " << heapCirc->getCircumference() << endl;

    delete heapCirc; // explicity calls the destructor and free the memory
} // end of scope ... any stack object will have its destructor called