#include <cassert>
#include <stdexcept>
#include <string>
#include <iostream>

// TODO: Define "Student" class
class Student {
 public:
  // constructor
    Student(std::string name, int grade, float gpa) : name_(name){
        Grade(grade);
        Gpa(gpa);
    } 

  // accessors
    std::string Name() {return name_;}
    int Grade() { return grade_;}
    float Gpa() { return gpa_;}
  // mutators
    void Name(int n) { name_ = n;}
    void Grade(int g) {
        if (g < 0 || g > 12) 
            throw std::invalid_argument("non valid grade");
        else
            grade_ = g;
    }
    void Gpa(int gpa){
        if (gpa <0 || gpa > 4)
            throw std::invalid_argument("non valid gpa");
        else
            gpa_ = gpa;
    }

 private:
  // name
    std::string name_;
  // grade
    int grade_;
  // GPA
    float gpa_;
};

// TODO: Test
int main() {
    Student jhon("jhon", 3, 3.3);
    try{
        Student fake("fake", 5, -8);
    }
    catch(...)
    {
        std::cout << "Error\n";
    }
    return 0;
}