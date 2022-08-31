//
//  HunPolynomial.hpp
//  Project 4
//
//  Created by Sal on 5/9/22.
//

#ifndef HunPolynomial_h
#define HunPolynomial_h

#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>

class HunPolynomial {
public:
    friend std::ostream& operator<< (std::ostream& out, HunPolynomial Hun);
    std::vector<int> vect;
    HunPolynomial();// construct an empty polynomial
    HunPolynomial(const std::vector<int> polynomial);
    void Set(std::vector<int>polynomial);
    HunPolynomial operator+(HunPolynomial& H);
    HunPolynomial operator-(HunPolynomial& H);
    HunPolynomial operator*(const HunPolynomial& H);
    float operator()(float var);
};


#endif /* HunPolynomial_h */
