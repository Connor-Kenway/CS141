#include <malloc.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <math.h>

typedef double (*double_method_type)(void *);
typedef void (*void_method_type)(void *);

typedef union {
    double_method_type double_method; // this is for area()
    void_method_type void_method;     // this is for draw()
} VirtualTableEntry;

typedef VirtualTableEntry * VTableType;

#define DRAW_INDEX 0
#define AREA_INDEX 1
#define PRINT_INDEX 2

#define PI 3.14159

struct Shape {
    VTableType VPointer;
    std::string name;
    int width, length;
};

double Shape_draw(Shape * _this) {
    std::cout << "this should never happen";
    return 6.9;
}

double Shape_area(Shape * _this) {
    return 0.0;
}

void Shape_print(Shape * _this) {
    std::cout << _this->name << "(" << _this->width << ", " << _this->length << ") : " << Shape_area(_this) << std::endl;
}

VirtualTableEntry Shape_VTable [] =
{
    {.void_method=(void_method_type)Shape_draw},
    {.double_method=(double_method_type)Shape_area},
    {.void_method=(void_method_type)Shape_print},
};

Shape* Shape_Shape(Shape* _this, std::string newName) {
    _this->VPointer = Shape_VTable;
    _this->name = newName;
    return _this;
}

struct Circle {
    VTableType VPointer;
    std::string name;
    double radius = 0.0;
};

void Circle_draw(Circle * _this) {
    double threshold = 0.5;

    for (int i = -_this->radius; i <= _this->radius; i++) {
        for (int j = -_this->radius; j <= _this->radius; j++) {
            double distance = sqrt(i * i + j * j);

            if (distance > _this->radius - threshold && distance < _this->radius + threshold)
                std::cout << "*";
            else
                std::cout << " ";
        }
        std::cout << '\n';
    }
}

double Circle_area(Circle * _this)
{
    return PI * _this->radius * _this->radius;
}

void Circle_print(Circle * _this) {
    std::cout << _this->name << "(" << _this->radius << ") : " << Circle_area(_this) << std::endl;
}

VirtualTableEntry Circle_VTable [] =
{
    {.void_method=(void_method_type)Circle_draw},
    {.double_method=(double_method_type)Circle_area},
    {.void_method=(void_method_type)Circle_print},

};

Circle * Circle_Circle(Circle * _this, std::string newName, double newRadius)
{
    Shape_Shape((Shape *)_this, newName);  //call parents constructor
    _this->VPointer = Circle_VTable; // set the vpointer AFTER parent
    _this->name = newName;
    _this->radius = newRadius;
    return _this;
}

struct Square {
    VTableType VPointer;
    std::string name;
    int side = 0;
};

void Square_draw(Square * _this) {
    int size = 5;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == 0 || i == size - 1 || j == 0 || j == size - 1) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
        }
        std::cout << '\n';
    }
}

double Square_area(Square * _this) {
    return _this->side * _this->side;
}

void Square_print(Square * _this) {
    std::cout << _this->name << "(" << _this->side << ") : " << Square_area(_this) << std::endl;
}

VirtualTableEntry Square_VTable [] =
{
    {.void_method=(void_method_type)Square_draw},
    {.double_method=(double_method_type)Square_area},
    {.void_method=(void_method_type)Square_print},

};

Square * Square_Square(Square * _this, std::string newName, int newSide)
{
    Shape_Shape((Shape *)_this, newName);  //call parents constructor
    _this->VPointer = Square_VTable; // set the vpointer AFTER parent
    _this->name = newName;
    _this->side = newSide;
    return _this;
}

struct Triangle {
    VTableType VPointer;
    std::string name;
    int base, height;
};

void Triangle_draw(Triangle * _this) {
    for (int i = 1; i <= _this->height; i++) {
        for (int j = i; j < _this->height; j++) {
            std::cout << " ";
        }

        for (int j = 1; j < 2 * i; j++) {
            if (j > 1 && j < (2 * i - 1)) {
                std::cout << " ";
            } else {
                std::cout << "*";
            }
        }

        std::cout << '\n';
        }
}

double Triangle_area(Triangle * _this) {
    return _this->base * _this->height / 2;
}

void Triangle_print(Triangle * _this) {
    std::cout << _this->name << "(" << _this->base << ", " << _this->height << ") : " << Triangle_area(_this) << std::endl;
}

VirtualTableEntry Triangle_VTable [] =
{
    {.void_method=(void_method_type)Triangle_draw},
    {.double_method=(double_method_type)Triangle_area},
    {.void_method=(void_method_type)Triangle_print},

};

Triangle * Triangle_Triangle(Triangle * _this, std::string newName, int newBase, int newHeight)
{
    Shape_Shape((Shape *)_this, newName);  //call parents constructor
    _this->VPointer = Triangle_VTable; // set the vpointer AFTER parent
    _this->name = newName;
    _this->base = newBase;
    _this->height = newHeight;
    return _this;
}

struct Rectangle {
    VTableType VPointer;
    std::string name;
    int base, height;
};

void Rectangle_draw(Rectangle * _this) {
    int size = 5;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == 0 || i == size - 1 || j == 0 || j == size - 1) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
        }
        std::cout << '\n';
    }
}

double Rectangle_area(Rectangle * _this) {
    return _this->base * _this->height;
}

void Rectangle_print(Rectangle * _this) {
    std::cout << _this->name << "(" << _this->base << ", " << _this->height << ") : " << Rectangle_area(_this) << std::endl;
}

VirtualTableEntry Rectangle_VTable [] =
{
    {.void_method=(void_method_type)Rectangle_draw},
    {.double_method=(double_method_type)Rectangle_area},
    {.void_method=(void_method_type)Rectangle_print},

};

Rectangle * Rectangle_Rectangle(Rectangle * _this, std::string newName, int newSide, int newHeight)
{
    Square_Square((Square *)_this, newName, newSide);  //call parents constructor
    _this->VPointer = Rectangle_VTable; // set the vpointer AFTER parent
    // _this->name = newName;
    // _this->base = newBase;
    _this->height = newHeight;
    return _this;
}

struct Picture {
    VTableType VPointer;
};

void drawAll(Shape * picture[], int size) {
    for (int i = 0; i < size; ++i) {
        (picture[i]->VPointer[DRAW_INDEX]).void_method(picture[i]);
    }
}

double totalArea(Shape * picture[], int size) {
    double total;
    for (int i = 0; i < size; ++i) {
        total = total + (picture[i]->VPointer[AREA_INDEX]).double_method(picture[i]);
    }
    return total;
}

void printAll(Shape * picture[], int size) {
    for (int i = 0; i < size; ++i) {
        (picture[i]->VPointer[PRINT_INDEX]).void_method(picture[i]);
    }
}

int main(int argc, char *argv[]) {

    double x = atoi(argv[1]);
    double y = atoi(argv[2]);

    Shape * a [] = {
        (Shape *)Triangle_Triangle((Triangle *)malloc(sizeof(Triangle)), "FirstTriangle", x, y),
        (Shape *)Triangle_Triangle((Triangle *)malloc(sizeof(Triangle)), "SecondTriangle", x - 1, y - 1),
        // Triangle firstTriangle = {"FirstTriangle", x, y};
        // Triangle secondTriangle = {"SecondTriangle", x - 1, y - 1};
        (Shape *)Circle_Circle((Circle *)malloc(sizeof(Circle)),  "FirstCircle", x),
        (Shape *)Circle_Circle((Circle *)malloc(sizeof(Circle)),  "SecondCircle", x - 1),
        // Circle firstCircle = {"FirstCircle", x};
        // Circle secondCircle = {"SecondCircle", x - 1};
        (Shape *)Square_Square((Square *)malloc(sizeof(Square)), "FirstSquare", x),
        (Shape *)Square_Square((Square *)malloc(sizeof(Square)), "SecondSquare", x - 1),
        // Square firstSquare = {"FirstSquare", x};
        // Square secondSquare = {"SecondSquare", x - 1};
        (Shape *)Rectangle_Rectangle((Rectangle *)malloc(sizeof(Rectangle)), "FirstRectangle", x, y),
        (Shape *)Rectangle_Rectangle((Rectangle *)malloc(sizeof(Rectangle)), "SecondRectangle", x - 1, y - 1),
        // Rectangle firstRectangle = {"FirstRectangle", x, y};
        // Rectangle secondRectangle = {"SecondRectangle", x - 1, y - 1};
    };
    
    printAll(a, 8);
    drawAll(a, 8);
    std::cout << "Total: " << totalArea(a, 8) << std::endl;

    return 0;
}
