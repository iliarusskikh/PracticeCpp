//interface
//abstract class with only pure virtual functions
//defines a contract for derived classes
//cannot be instantiated directly
//enables polymorphic nehaviour
//supports multiple inheritance

#include <iostream>
#include <string>

// ────────────────────────────────────────────────
// Interface 1: Shape (pure abstract class)
class Shape {
public:
    virtual double area()      const = 0;
    virtual double perimeter() const = 0;
    
    // Very important when using pointers/references to base class
    virtual ~Shape() = default;   // or { }
};

// ────────────────────────────────────────────────
// Interface 2: Printable (another independent interface)
class Printable {
public:
    virtual std::string toString() const = 0;
    
    virtual ~Printable() = default;
};

// ────────────────────────────────────────────────
// Concrete class implementing **both** interfaces
class Rectangle : public Shape, public Printable
{
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {
        if (w <= 0 || h <= 0) throw std::invalid_argument("Dimensions must be positive");
    }

    // Implement Shape interface
    double area() const override {
        return width * height;
    }

    double perimeter() const override {
        return 2 * (width + height);
    }

    // Implement Printable interface
    std::string toString() const override {
        return "Rectangle " + std::to_string(width) + " × " + std::to_string(height);
    }
};

// ────────────────────────────────────────────────
// Another class implementing only one interface
class Circle : public Shape
{
private:
    double radius;

public:
    explicit Circle(double r) : radius(r) {
        if (r <= 0) throw std::invalid_argument("Radius must be positive");
    }

    double area() const override {
        return 3.141592653589793 * radius * radius;
    }

    double perimeter() const override {
        return 2 * 3.141592653589793 * radius;
    }
};

int main()
{
    // Using polymorphism through Shape*
    Shape* shapes[2] = {
        new Rectangle(5.0, 3.0),
        new Circle(4.0)
    };

    for (int i = 0; i < 2; ++i) {
        std::cout << "Area      = " << shapes[i]->area()      << "\n";
        std::cout << "Perimeter = " << shapes[i]->perimeter() << "\n";

        // Can we call toString()? Only if we know it's Printable
        // → we need to downcast or use dynamic_cast
        if (auto* printable = dynamic_cast<Printable*>(shapes[i])) {
            std::cout << "Description: " << printable->toString() << "\n";
        }
        std::cout << "------------------------\n";
    }

    // Cleanup (because we used new)
    for (auto* s : shapes) delete s;

    // ── More modern & safer style ──────────────────────────────
    std::cout << "\nModern style (no raw pointers):\n";

    Rectangle rect(10, 4);
    std::cout << rect.toString() << "\n";
    std::cout << "area = " << rect.area() << "\n";

    return 0;
}


