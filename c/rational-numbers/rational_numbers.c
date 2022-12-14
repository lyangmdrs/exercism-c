#include "rational_numbers.h"

int greatest_common_divisor(rational_t r)
{
    for (int i = MAX_GCD_VALUE; i > 0; i--)
    {
        if (((r.numerator % i) == 0) && ((r.denominator % i) == 0))
        {
            return i;
        }
    }

    return 1;
}

rational_t reduce(rational_t r)
{
    rational_t result = r;
    int gdc = greatest_common_divisor(result);
    
    result.numerator /= gdc;
    result.denominator /= gdc;

    if ((result.denominator < 0)  && (result.numerator > 0))
    {
        result.numerator *= -1;
        result.denominator *= -1;
    }

    return result;
}

rational_t add(rational_t r1, rational_t r2)
{
    rational_t result;
    result.numerator = r1.numerator * r2.denominator + r2.numerator * r1.denominator;

    if (result.numerator == 0)
    {
        result.denominator = 1;
    }
    else
    {
        result.denominator = r1.denominator * r2.denominator;
    }
    
    result = reduce(result);

    return result;
}

rational_t subtract(rational_t r1, rational_t r2)
{
    rational_t result;
    result.numerator = r1.numerator * r2.denominator - r2.numerator * r1.denominator;
    
    if (result.numerator == 0)
    {
        result.denominator = 1;
    }
    else
    {
        result.denominator = r1.denominator * r2.denominator;
    }

    result = reduce(result);

    return result;
}

rational_t multiply(rational_t r1, rational_t r2)
{
    rational_t result;
    
    result.numerator = (r1.numerator * r2.numerator);
    result.denominator = r1.denominator * r2.denominator;

    result = reduce(result);
    
    return result;
}

rational_t divide(rational_t r1, rational_t r2)
{
    rational_t result;
    
    if (r2.numerator == 0)
    {
        result.numerator = 0;
        result.denominator = 0;
        return result;
    }

    result.numerator = r1.numerator * r2.denominator;
    result.denominator = r2.numerator * r1.denominator;
    
    result = reduce(result);

    if ((result.denominator < 0))
    {
        result.denominator *= -1;
        if (result.numerator > 0)
        {
            result.numerator *= -1;
        }
    }

    if ((r1.numerator < 0) && (r2.numerator < 0) && (result.numerator < 0))
    {
        result.numerator *= -1;
    }

    return result;
}

rational_t absolute(rational_t r)
{
    rational_t result = r;

    result = reduce(result);
    
    if (result.numerator < 0)
    {
        result.numerator *= -1;
    }

    if (result.denominator < 0)
    {
        result.denominator *= -1;
    }
    
    return result;
}

rational_t exp_rational(rational_t r, int16_t n)
{
    rational_t result;

    if (n < 0)
    {
        if ((n % 2) != 0)
        {
            r.numerator *= -1;
            r.denominator *= -1;
        }

        int holder = r.denominator;
        r.denominator = r.numerator;
        r.numerator = holder;
        n *= -1;
    }

    result.numerator = pow(r.numerator, n);
    result.denominator = pow(r.denominator, n);

    result = reduce(result);

    return result;
}

float exp_real(uint16_t real, rational_t rational)
{
    float result = pow(pow(real, rational.numerator), 1./rational.denominator);
    return result;
}
