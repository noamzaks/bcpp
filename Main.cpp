#include "Complex.h"

int main() {
    Complex x;
    x.print();
    x = Complex(2, -3);
    x.print();
    Complex y(4, 5);

    x += y;
    x.print();

    x -= y;
    x.print();

    x *= y;
    x.print();
    (x + y).print();
}