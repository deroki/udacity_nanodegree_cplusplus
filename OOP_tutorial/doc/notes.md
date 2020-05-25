
## construction list
useful when you want to initialize on creation, whithout validators

```cpp
className(var1, var2) : att1_(var1), att2_(var2) {}
```

## getter/setter

functions that use to be public that have access to the private attributes or methods.

## scope

- public
- private
- protected

## static

In case we want to use the same variable or function for all the instances, we can use static functión even without instantiating, just from the blueprint class

## composing

We can create a class pasing to constructor another class

## friends

When a class is a friend of another, it has access to the internal private members of its friend (otherwise they won't be friends!)
but friendship is unidirectional , like real life, sqare has no access to rectangle stuff.

```cpp
// Example solution for Rectangle and Square friend classes
#include <assert.h>

// Declare class Rectangle
class Rectangle;

// Define class Square as friend of Rectangle
class Square {
// Add public constructor to Square, initialize side
public:
    Square(int s) : side(s) {}

private:
    // Add friend class Rectangle
    friend class Rectangle;
    // Add private attribute side to Square
    int side;
};

// Define class Rectangle
class Rectangle {
// Add public functions to Rectangle: area() and convert()
public:
    Rectangle(const Square& a);
    int Area() const;

private:
    // Add private attributes width, height
    int width {0};
    int height {0};
};

// Define a Rectangle constructor that takes a Square
Rectangle::Rectangle(const Square& a) : width(a.side), height(a.side) {}

// Define Area() to compute area of Rectangle
int Rectangle::Area() const
{
    return width * height;
}
```


## overloading

Use a function differently depending on the parameters you got, hello behaves different in human cat or dog cases.

```cpp
#include <iostream>
// TODO: Write hello() function
void hello(){
    std::cout << "Hello, Wordl!\n";
}

class Human {};
class Dog {};
class Cat {};

void hello(Cat c){
    std::cout << "Hello, cat\n";
}

void hello(Dog d){
    std::cout << "Hello, Dog\n";
}

void hello(Human h){
    std::cout << "Hello, Human\n";
}
// TODO: Overload hello() three times

// TODO: Call hello() from main()
int main(){
    hello(Human());
    hello(Dog());
    hello(Cat());
}
```

## operator overloading

We can set + () [] <<<>>> for make whatever we want in out class!
we use **operator** keyword

```cpp
#include <assert.h>

// TODO: Define Point class
class Point {
public:
  // TODO: Define public constructor
  Point(int x = 0, int y = 0) : x(x), y(y) {}

  // TODO: Define + operator overload
  Point operator+(const Point& addend) {
    Point sum;
    sum.x = x + addend.x;
    sum.y = y + addend.y;
    return sum;
  }

  // TODO: Declare attributes x and y
  int x, y;
};

// Test in main()
int main() {
  Point p1(10, 5), p2(2, 4);
  Point p3 = p1 + p2; // An example call to "operator +";
  assert(p3.x == p1.x + p2.x);
  assert(p3.y == p1.y + p2.y);
}
```

## virtual functions

For creating blueprint classes, the class is only useful for derive another class from it.

```cpp
// Example solution for Shape inheritance
#include <assert.h>
#include <cmath>

// TODO: Define pi
#define PI 3.14159;

// TODO: Define the abstract class Shape
class Shape {
public:
  // TODO: Define public virtual functions Area() and Perimeter()
  // TODO: Append the declarations with = 0 to specify pure virtual functions
  virtual double Area() const = 0;
  virtual double Perimeter() const = 0;
};

// TODO: Define Rectangle to inherit publicly from Shape
class Rectangle : public Shape {
public:
  // TODO: Declare public constructor
  Rectangle(double width, double height) : width_(width), height_(height) {}
  // TODO: Override virtual base class functions Area() and Perimeter()
  double Area() const override { return width_ * height_; }
  double Perimeter() const override { return 2 * (width_ + height_); }

private:
  // TODO: Declare private attributes width and height
  double width_;
  double height_;
};

```

## templates

```cpp
template <typename Type> 
Type Sum(Type a, Type b) {
   return a + b; 
   }

int main() { 
  std::cout << Sum<double>(20.0, 13.7) << "\n"; 
  }
```
 templates with classes , with 2 generic types.

 ```cpp

// TODO: Add the correct template specification
template <typename KeyType, typename ValueType>
class Mapping {
public:
  Mapping(KeyType key, ValueType value) : key(key), value(value) {}
  std::string Print() const {
    std::ostringstream stream;
    stream << key << ": " << value;
    return stream.str();
  }
  KeyType key;
  ValueType value;
};
```
