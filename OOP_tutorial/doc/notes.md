
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

