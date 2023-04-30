#include "Fraction.hpp"
#include <stdexcept>
#include <cmath>

#define EPSILON 0.001
using namespace std;

int gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    return gcd(b, a % b);
}

int least_common_multiple(int a, int b)
{
    return (a * b) / gcd(a, b);
}

namespace ariel
{
    // Constructors
    Fraction::Fraction() : m_numerator(0), m_denominator(1) {}

    Fraction::Fraction(int numerator, int denominator)
    {
        if (denominator == 0)
        {
            throw invalid_argument("Denominator cannot be zero!");
        }
        // float res = static_cast<float>(m_numerator) / static_cast<float>(m_denominator);

        m_numerator = numerator;
        m_denominator = denominator;
        this->reduce();
    }

    Fraction::Fraction(float value)
    {
        // Multiply the float by 1000 to get 3 decimal places
        int multiplier = 1000;
        int numerator = static_cast<int>(value * multiplier);
        int denominator = multiplier;

        if (fabs(value) < EPSILON)
        {
            numerator = 0;
            denominator = 1;
        }

        m_numerator = numerator;
        m_denominator = denominator;
        this->reduce();
    }

    // Fraction::~Fraction() {}

    // Private methods

    void Fraction::reduce()
    {
        int gcd_res = gcd(m_numerator, m_denominator);
        m_numerator /= gcd_res;
        m_denominator /= gcd_res;

        if (m_denominator < 0)
        {
            m_numerator = -m_numerator;
            m_denominator = -m_denominator;
        }
    }

    // Public methods

    // Helper function to check for addition overflow
    bool add_overflow(int a, int b, int &result)
    {
        if (((b > 0) && (a > (std::numeric_limits<int>::max() - b))) ||
            ((b < 0) && (a < (std::numeric_limits<int>::min() - b))))
        {
            return true;
        }
        result = a + b;
        return false;
    }

    // Helper function to check for subtraction overflow
    bool sub_overflow(int a, int b, int &result)
    {
        if (((b > 0) && (a < (std::numeric_limits<int>::min() + b))) ||
            ((b < 0) && (a > (std::numeric_limits<int>::max() + b))))
        {
            return true;
        }
        result = a - b;
        return false;
    }

    // Helper function to check for multiplication overflow
    bool mul_overflow(int a, int b, int &result)
    {
        if (a > 0)
        {
            if ((b > 0) && (a > (std::numeric_limits<int>::max() / b)) ||
                (b < 0) && (b < (std::numeric_limits<int>::min() / a)))
            {
                return true;
            }
        }
        else
        {
            if ((b > 0) && (a < (std::numeric_limits<int>::min() / b)) ||
                (b < 0) && (a != 0) && (b < (std::numeric_limits<int>::max() / a)))
            {
                return true;
            }
        }
        result = a * b;
        return false;
    }

    // Public methods
    Fraction Fraction::operator+(const Fraction &other) const
    {
        int new_numerator;
        if (add_overflow(m_numerator * other.m_denominator, other.m_numerator * m_denominator, new_numerator))
        {
            throw std::overflow_error("Numerator overflow during addition!");
        }
        int new_denominator = m_denominator * other.m_denominator;
        return Fraction(new_numerator, new_denominator);
    }

    Fraction Fraction::operator-(const Fraction &other) const
    {
        int new_numerator;
        if (sub_overflow(m_numerator * other.m_denominator, other.m_numerator * m_denominator, new_numerator))
        {
            throw std::overflow_error("Numerator overflow during subtraction!");
        }
        int new_denominator = m_denominator * other.m_denominator;
        return Fraction(new_numerator, new_denominator);
    }

    Fraction Fraction::operator*(const Fraction &other) const
    {
        int new_numerator;
        if (mul_overflow(m_numerator, other.m_numerator, new_numerator))
        {
            throw std::overflow_error("Numerator overflow during multiplication!");
        }
        int new_denominator;
        if (mul_overflow(m_denominator, other.m_denominator, new_denominator))
        {
            throw std::overflow_error("Denominator overflow during multiplication!");
        }
        return Fraction(new_numerator, new_denominator);
    }

    Fraction Fraction::operator/(const Fraction &other) const
    {
        if (other.m_numerator == 0)
        {
            throw std::runtime_error("Cannot divide by zero!");
        }

        int new_numerator;
        if (mul_overflow(m_numerator, other.m_denominator, new_numerator))
        {
            throw std::overflow_error("Numerator overflow during division!");
        }
        int new_denominator;
        if (mul_overflow(m_denominator, other.m_numerator, new_denominator))
        {
            throw std::overflow_error("Denominator overflow during division!");
        }
        return Fraction(new_numerator, new_denominator);
    }

    Fraction operator+(const Fraction &fraction, const float &float_val)
    {
        return fraction + Fraction(float_val);
    }

    Fraction operator-(const Fraction &fraction, const float &float_val)
    {
        return fraction - Fraction(float_val);
    }

    Fraction operator*(const Fraction &fraction, const float &float_val)
    {
        return fraction * Fraction(float_val);
    }

    Fraction operator/(const Fraction &fraction, const float &float_val)
    {
        return fraction / Fraction(float_val);
    }

    Fraction operator+(const float &float_val, const Fraction &fraction)
    {
        return Fraction(float_val + (static_cast<float>(fraction.getNumerator()) / static_cast<float>(fraction.getDenominator())));
    }

    Fraction operator-(const float &float_val, const Fraction &fraction)
    {
        return Fraction(float_val - (static_cast<float>(fraction.getNumerator()) / static_cast<float>(fraction.getDenominator())));
    }

    Fraction operator*(const float &float_val, const Fraction &fraction)
    {
        return Fraction(float_val) * fraction;
    }

    Fraction operator/(const float &float_val, const Fraction &fraction)
    {
        return Fraction(float_val) / fraction;
    }

    Fraction &Fraction::operator++()
    {
        m_numerator += m_denominator;
        return *this;
    }

    Fraction &Fraction::operator--()
    {
        m_numerator -= m_denominator;
        return *this;
    }
    // postfix increment operator
    Fraction Fraction::operator++(int dummy_flag_for_postfix_increment)
    {
        Fraction temp(*this);
        ++(*this);
        return temp;
    }

    // postfix decrement operator
    Fraction Fraction::operator--(int dummy_flag_for_postfix_increment)
    {
        Fraction temp(*this);
        --(*this);
        return temp;
    }

    // comparison operators
    bool operator==(const Fraction &fraction1, const Fraction &fraction2)
    {
        float first = static_cast<float>(fraction1.getNumerator()) / static_cast<float>(fraction1.getDenominator());
        float second = static_cast<float>(fraction2.getNumerator()) / static_cast<float>(fraction2.getDenominator());
        return (fabs(first - second) < EPSILON);
    }

    bool operator!=(const Fraction &fraction1, const Fraction &fraction2)
    {
        return !(fraction1 == fraction2);
    }

    bool operator<(const Fraction &fraction1, const Fraction &fraction2)
    {
        int lcm = least_common_multiple(fraction1.m_denominator, fraction2.m_denominator);
        int fraction1_numerator = fraction1.m_numerator * (lcm / fraction1.m_denominator);
        int fraction2_numerator = fraction2.m_numerator * (lcm / fraction2.m_denominator);
        return (fraction1_numerator < fraction2_numerator);
    }

    bool operator>(const Fraction &fraction1, const Fraction &fraction2)
    {
        return (fraction2 < fraction1);
    }

    bool operator<=(const Fraction &fraction1, const Fraction &fraction2)
    {
        return !(fraction1 > fraction2);
    }

    bool operator>=(const Fraction &fraction1, const Fraction &fraction2)
    {
        return !(fraction1 < fraction2);
    }

    bool operator==(const float &fraction1, const Fraction &fraction2)
    {
        return (fabs(fraction1 - ((float)fraction2.m_numerator / (float)fraction2.m_denominator)) < EPSILON);
    }

    bool operator!=(const float &fraction1, const Fraction &fraction2)
    {
        return !(fraction1 == fraction2);
    }

    bool operator<(const Fraction &fraction, const float &float_val)
    {
        return (fraction < Fraction(float_val));
    }

    bool operator<(const float &float_val, const Fraction &fraction)
    {
        return (Fraction(float_val) < fraction);
    }

    bool operator<=(const Fraction &fraction, const float &float_val)
    {
        return !(fraction > float_val);
    }

    bool operator<=(const float &float_val, const Fraction &fraction)
    {
        return !(Fraction(float_val) > fraction);
    }

    bool operator==(const Fraction &fraction1, const float &fraction2)
    {
        return (fabs(((float)fraction1.m_numerator / (float)fraction1.m_denominator) - fraction2) < EPSILON);
    }

    bool operator!=(const Fraction &fraction1, const float &fraction2)
    {
        return !(fraction1 == fraction2);
    }

    bool operator>(const Fraction &fraction, const float &float_val)
    {
        return (fraction > Fraction(float_val));
    }

    bool operator>(const float &float_val, const Fraction &fraction)
    {
        return (Fraction(float_val) > fraction);
    }

    bool operator>=(const Fraction &fraction, const float &float_val)
    {
        return !(fraction < float_val);
    }

    bool operator>=(const float &float_val, const Fraction &fraction)
    {
        return !(float_val < fraction);
    }

    ostream &operator<<(ostream &output, const Fraction &float_val)
    {
        output << float_val.m_numerator << "/" << float_val.m_denominator;
        return output;
    }

    istream &operator>>(istream &input, Fraction &float_val)
    {
        int numerator, denominator;
        char slash;

        // Read numerator
        input >> numerator;

        input >> denominator;
        if (input.fail())
        {
            throw runtime_error("Two numbers needed!");
        }
        if (denominator == 0)
        {
            throw runtime_error("Denominator cannot be zero!");
        }

        // Set the fraction object
        float_val.m_numerator = numerator;
        float_val.m_denominator = denominator;
        float_val.reduce();

        return input;
    }

}
