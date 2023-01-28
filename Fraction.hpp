#include <iostream>
#include <numeric>
#include <sstream>
#include <string>

#pragma once

// class Fraction: provides basic operations for fraction type.
// @note Main Edge Cases that are considered:
// @     - invalid (div_by_0);
// @     - negative value: need be careful with all gcd, lcm, or modulo operations;
// @     - zero value: some math may be simplified when there is a 0;
// @tparam T: an integral type; TODO: use enable_if if this becomes a shared lib.

namespace interview {

template <typename T>
class Fraction
{
public:
    /**
     * c'tor.
     * @param numerator: numerator of the fraction.
     * @param denominator: denominator of the fraction.
     */
    Fraction(T numerator, T denominator) : numerator_{numerator}, denominator_{denominator}
    {
        assert(denominator != 0 && "Fraction requires a non-zero denominator");
        // implementation detail:
        // internally, always call normalize() to ensure that,
        // 1) gcd(numerator, denominator) == 1;
        // 2) denominator is always positive.
        normalize();
    }
    /**
     * += to add another fraction to this.
     * @param other: another Fraction type.
     */
    Fraction<T>& operator+=(const Fraction<T>& other)
    {
        if (other.isZero()) {
            return *this;
        }
        if (isZero()) {
            numerator_ = other.numerator_;
            denominator_ = other.denominator_;
            return *this;
        }
        const auto newDenominator = std::lcm(denominator_, other.denominator_);
        const auto scalarThis = newDenominator / denominator_;
        const auto scalarOther = newDenominator / other.denominator_;
        assert(scalarThis > static_cast<T>(0) && scalarOther > static_cast<T>(0) && "negative denominator encountered");

        numerator_ = numerator_ * scalarThis + other.numerator_ * scalarOther;
        denominator_ = newDenominator;
        normalize();
        return *this;
    }
     /**
     * compute the sum of two fractions.
     * @param rhs: the other fraction on the right hand side;
     * @return a fraction type as the sum of the two.
     */
    Fraction<T> operator+(const Fraction<T>& rhs)
    {
        Fraction<T> lhs = *this;
        lhs += rhs;
        return lhs;
    }
    /**
     * -= to subtract another fraction from this.
     * @param other: another Fraction type.
     */
    Fraction<T>& operator-=(const Fraction<T>& other)
    {
        const auto negativeOther = -other;
        *this += negativeOther;
        return *this;
    }
    /**
     * compute the difference of two fractions.
     * @param rhs: the other fraction on the right hand side;
     * @return a fraction type as the difference of the two.
     */
    Fraction<T> operator-(const Fraction<T>& rhs)
    {
        Fraction<T> lhs = *this;
        lhs -= rhs;
        return lhs;
    }
    /**
     * *= to multiply another fraction to this.
     * @param other: another Fraction type.
     */
    Fraction<T>& operator*=(const Fraction<T>& other)
    {
        if (isZero()) {
            return *this;
        }
        if (other.isZero()) {
            numerator_ = static_cast<T>(0);
            denominator_ = static_cast<T>(1);
            return *this;
        }
        numerator_ *= other.numerator_;
        denominator_ *= other.denominator_;
        normalize();
        return *this;
    }
    /**
     * compute the product of two fractions.
     * @param rhs: the other fraction on the right hand side;
     * @return a fraction type as the product of the two.
     */
    Fraction<T> operator*(const Fraction<T>& rhs)
    {
        Fraction<T> lhs = *this;
        lhs *= rhs;
        return lhs;
    }
   /**
     * /= to divide another fraction from this.
     * @param other: another Fraction type.
     */
    Fraction<T>& operator/=(const Fraction<T>& other)
    {
        *this *= other.inv();
        return *this;
    }
    /**
     * compute the division of two fractions.
     * @param rhs: the other fraction on the right hand side;
     * @return a fraction type as the division of the two.
     */
    Fraction<T> operator/(const Fraction<T>& rhs)
    {
        Fraction<T> lhs = *this;
        lhs /= rhs;
        return lhs;
    }
    /**
     * == to test equality against another fraction.
     * @param other: another Fraction type.
     */
    bool operator==(const Fraction<T>& other) const
    {
        return (
            (isZero() && other.isZero())
            || (numerator_ == other.numerator_ && denominator_ == other.denominator_)
        );
    }
    /**
     * != to test non-equality against another fraction.
     * @param other: another Fraction type.
     */
    bool operator!=(const Fraction<T>& other) const
    {
        return !(operator==(other));
    }
    /**
     * < to test less than another fraction.
     * @note when both are positive, a1 / b1 < a2 / b2 <==> a1 * b2 < a2 * b1
     * @param other: another Fraction type.
     */
    bool operator<(const Fraction<T>& other) const
    {
        // if one and only one of (this, other) is negative, then
        // "this < other" is true when "this" is the negative one.
        if (isNegative() != other.isNegative()) {
            return isNegative();
        }
        return isNegative()
               ? numerator_ * other.denominator_ > other.numerator_ * denominator_
               : numerator_ * other.denominator_ < other.numerator_ * denominator_;
    }
    /**
     * > to test larger than another fraction.
     * @param other: another Fraction type.
     */
    bool operator>(const Fraction<T>& other) const
    {
       return !((*this < other) || (*this == other));
    }
    /**
     * convert fraction to a string
     * @return a std::string representation of the fraction
     */
    std::string toString() const
    {
        std::stringstream oss;
        oss << "Fraction(" << numerator_ << ", " << denominator_ << ")";
        return oss.str();
    }
    /**
     * display fraction to console
     */
    void display() const
    {
        std::cout << toString() << std::endl;
    }

private:
    // return a new fraction that is the negation of this.
    Fraction<T> operator-() const
    {
        return {-numerator_, denominator_};
    }
    // return the inverse of a fractioin.
    Fraction<T> inv() const
    {
        assert(numerator_ != 0 && "Fraction inverse is undefined when numerator == 0");
        return {denominator_, numerator_};
    }
    // return if the fraction is 0
    bool isZero() const
    {
        return numerator_ == static_cast<T>(0);
    }
    // return if the fraction is negative
    bool isNegative() const
    {
        return numerator_ < static_cast<T>(0);
    }
    // normalize the fraction so that:
    // 1) gcd(numerator, denominator) == 1;
    // 2) denominator is always positive.
    void normalize()
    {
        if (isZero()) {
            denominator_ = static_cast<T>(1);
            return;
        }
        if (denominator_ < static_cast<T>(0)) {
            denominator_ = -denominator_;
            numerator_ = -numerator_;
        }
        const auto div = std::gcd(numerator_, denominator_);
        numerator_ /= div;
        denominator_ /= div;
    }

private:
    T numerator_{};
    T denominator_{};
};


} // namespace interview