#pragma once

#include <iostream>

namespace ariel
{
    class Fraction
    {
    private:
        int m_numerator;
        int m_denominator;
        void reduce();
    
    public:
        Fraction();
        // Copy constructor
        //Fraction(const Fraction &other);
        Fraction(float value);
        Fraction(int numerator,int denominator);
        // ~Fraction();
        int getNumerator() const {return m_numerator;}
        int getDenominator() const {return m_denominator;}

       
        Fraction operator+ (const Fraction& other) const;
        Fraction operator- (const Fraction& other) const;
        Fraction operator/ (const Fraction& other) const;
        Fraction operator* (const Fraction& other) const;

        // Fraction and flout
        friend Fraction operator+ (const Fraction& fraction,const float& float_val);
        friend Fraction operator- (const Fraction& fraction,const float& float_val);
        friend Fraction operator/ (const Fraction& fraction,const float& float_val);
        friend Fraction operator* (const Fraction& fraction,const float& float_val);
        
        // Flout and fraction
        friend Fraction operator+ (const float& float_val,const Fraction& fraction);
        friend Fraction operator- (const float& float_val,const Fraction& fraction);
        friend Fraction operator/ (const float& float_val,const Fraction& fraction);
        friend Fraction operator* (const float& float_val,const Fraction& fraction);
        
        // prefix
        Fraction& operator++();
        Fraction& operator--();
        // postfix
        Fraction operator++(int dummy_flag_for_postfix_increment);
        Fraction operator--(int dummy_flag_for_postfix_increment);


        friend bool operator==(const Fraction& fraction1, const Fraction& fraction2);
        friend bool operator!=(const Fraction& fraction1, const Fraction& fraction2);
        friend bool operator<(const Fraction& fraction1, const Fraction& fraction2);
        friend bool operator>(const Fraction& fraction1, const Fraction& fraction2);
        friend bool operator<=(const Fraction& fraction1, const Fraction& fraction2);
        friend bool operator>=(const Fraction& fraction1, const Fraction& fraction2);
        
        friend bool operator==(const float& fraction1, const Fraction& fraction2);
        friend bool operator!=(const float& fraction1, const Fraction& fraction2);
        friend bool operator<(const Fraction& fraction, const float& float_val);
        friend bool operator<(const float& float_val, const Fraction& fraction);
        friend bool operator<=(const Fraction& fraction, const float& float_val);
        friend bool operator<=(const float& float_val, const Fraction& fraction);

        friend bool operator==(const Fraction& fraction1, const float& fraction2);
        friend bool operator!=(const Fraction& fraction1, const float& fraction2);
        friend bool operator>(const Fraction& fraction, const float& float_val);
        friend bool operator>(const float& float_val, const Fraction& fraction);
        friend bool operator>=(const Fraction& fraction, const float& float_val);
        friend bool operator>=(const float& float_val, const Fraction& fraction);
        

        friend std::ostream& operator<< (std::ostream& output, const Fraction& float_val);
        friend std::istream& operator>> (std::istream& input , Fraction& float_val); 
    };
    
}