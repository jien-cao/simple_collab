#include "Fraction.hpp"

#include <cassert>
#include <iostream>
#include <string>

int main()
{
    using namespace interview;
    using IntFraction = Fraction<int>;

    // c'tor tests
    IntFraction(1, 3).display();
    assert(IntFraction(1, 3).toString() == std::string("Fraction(1, 3)"));
    assert(IntFraction(2, 6).toString() == std::string("Fraction(1, 3)"));
    assert(IntFraction(-1, -3).toString() == std::string("Fraction(1, 3)"));
    // EXPECT_THROW(IntFraction(1, 0), std::runtime_error);

    // add
    assert((IntFraction(1, 3) + IntFraction(1, 3)).toString() == std::string("Fraction(2, 3)"));
    assert((IntFraction(1, 3) + IntFraction(-1, 3)).toString() == std::string("Fraction(0, 1)"));
    assert((IntFraction(1, 3) + IntFraction(2, 3)).toString() == std::string("Fraction(1, 1)"));
    assert((IntFraction(1, 3) + IntFraction(5, 3)).toString() == std::string("Fraction(2, 1)"));

    // minus
    assert((IntFraction(1, 3) - IntFraction(1, 3)).toString() == std::string("Fraction(0, 1)"));
    assert((IntFraction(1, 3) - IntFraction(-1, 3)).toString() == std::string("Fraction(2, 3)"));
    assert((IntFraction(1, 3) - IntFraction(2, 3)).toString() == std::string("Fraction(-1, 3)"));
    assert((IntFraction(-1, 3) - IntFraction(5, 3)).toString() == std::string("Fraction(-2, 1)"));

    // multiply
    assert((IntFraction(0, -3) * IntFraction(1, 3)).toString() == std::string("Fraction(0, 1)"));
    assert((IntFraction(1, 3) * IntFraction(0, 3)).toString() == std::string("Fraction(0, 1)"));
    assert((IntFraction(1, 3) * IntFraction(1, 3)).toString() == std::string("Fraction(1, 9)"));
    assert((IntFraction(1, 3) * IntFraction(-1, 3)).toString() == std::string("Fraction(-1, 9)"));
    assert((IntFraction(2, 6) * IntFraction(3, 6)).toString() == std::string("Fraction(1, 6)"));

    // division
    assert((IntFraction(0, -3) / IntFraction(1, 3)).toString() == std::string("Fraction(0, 1)"));
    assert((IntFraction(1, 3) / IntFraction(3, 3)).toString() == std::string("Fraction(1, 3)"));
    assert((IntFraction(1, 3) / IntFraction(-1, 3)).toString() == std::string("Fraction(-1, 1)"));
    assert((IntFraction(-1, 3) / IntFraction(1, 3)).toString() == std::string("Fraction(-1, 1)"));
    assert((IntFraction(1, 3) / IntFraction(1, 3)).toString() == std::string("Fraction(1, 1)"));
    assert((IntFraction(1, 3) / IntFraction(3, 1)).toString() == std::string("Fraction(1, 9)"));

    // comparison
    assert(IntFraction(-10, 1) < IntFraction(1, 3));
    assert(IntFraction(-1, 5) < IntFraction(1, 3));
    assert(IntFraction(1, 5) < IntFraction(1, 3));
    assert(IntFraction(1, 3) == IntFraction(1, 3));
    assert(IntFraction(1, 3) == IntFraction(-1, -3));
    assert(IntFraction(-1, 3) == IntFraction(1, -3));
    assert(IntFraction(1, 3) == IntFraction(2, 6));
    assert(IntFraction(1, 3) > IntFraction(1, 5));
    assert(IntFraction(1, 3) > IntFraction(-1, 5));
    assert(IntFraction(1, 3) > IntFraction(-10, 1));

    // design choice: should the underlying type participate in equality-check?
    using LongFraction = Fraction<long>;
    assert(LongFraction(1, 3).toString() == IntFraction(1, 3).toString());

    return 0;
}