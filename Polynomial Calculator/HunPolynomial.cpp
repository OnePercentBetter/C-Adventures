//
//  HunPolynomial.cpp
//  Project 4
//
//  Created by Sal on 5/9/22.
//

#include "HunPolynomial.h"

HunPolynomial::HunPolynomial() : vect(0){};

HunPolynomial::HunPolynomial(const std::vector<int> polynomial) : vect{std::move(polynomial)}{};

void HunPolynomial::Set(std::vector<int>polynomial){
    this->vect.clear();
    this->vect.shrink_to_fit();
    vect = std::move(polynomial);
}

HunPolynomial HunPolynomial::operator+(HunPolynomial& H){
    HunPolynomial P;
    int check = 0;
    if(H.vect.empty()){
        return *this;
    }else if(this->vect.empty()){
        return H;
    }
    std::vector<int> s;
    if(H.vect.size() > this->vect.size()){
        check = int(H.vect.size());
        s.resize(check);
        for(int i = 0; i < H.vect.size();i++){
            s[i] = H.vect[i];
        }
        for(int i = int(check - this->vect.size()-1); i < int(this->vect.size());i++){
            s[i] += this->vect[i-1];
        }
    }else if(H.vect.size() < this->vect.size()){
        check = int(this->vect.size());
        s.resize(check);
        for(int i = 0; i < this->vect.size();i++){
            s[i] = this->vect[i];
        }
        for(int i = int(check - H.vect.size()); i < int(H.vect.size());i++){
            s[i] += H.vect[i-1];
        }
    }else if(H.vect.size() == this->vect.size()){
        check = int(this->vect.size());
        s.resize(check);
        for(int i = 0; i < int(H.vect.size());i++){
            s[i] = H.vect[i];
            s[i] += this->vect[i];
        }
    }
    P.vect = s;
    return P;
}
HunPolynomial HunPolynomial::operator-(HunPolynomial& H){
    HunPolynomial P;
    size_t check = 0;
    std::vector<int> s;
    //Checks if either inputs is empty;
    if(H.vect.empty()){
        return *this;
    }else if(this->vect.empty()){
        for(int i = 0; i < H.vect.size();i++){
            H.vect[i] = H.vect[i] * -1;
        }
        return H;
    }
    if(H.vect.size() > this->vect.size()){
        check = H.vect.size();
        for(int i = 0; i < check; i++){
            s.push_back(H.vect[i] * -1);
        }
        int counter = 0;
        for(size_t i = H.vect.size() - this->vect.size(); i <= (H.vect.size() - this->vect.size()) + H.vect.size() ;i++){
            s[i] += this->vect[counter];
            counter++;
        }
    }else if (H.vect.size() < this->vect.size()){
        check = this->vect.size();
        for(int i = 0; i < check; i++){
            s.push_back(this->vect[i]);
        }
        int counter = 0;
        for(size_t j = this->vect.size() - H.vect.size(); j < check;j++){
            s[j] -= H.vect[counter];
            counter++;
        }
    }else {
        check = this->vect.size();
        for(int i= 0; i < check; i ++){
            s.push_back(this->vect[i] - H.vect[i]);
        }
    }
    // 1 2 3 4 5
    //   1 2 3 4
    P.vect = s;
    return P;
}
HunPolynomial HunPolynomial::operator*(const HunPolynomial& H){
    HunPolynomial P;
    std::vector<int> n(this->vect.size()+H.vect.size()-1,0);
    /*
    (1,2,3,4)
    (1,2,3,4)
    x^6 + 2x^5 + 3x^4 + 4x^3
          2x^5 + 4x^4 + 6x^3 + 8x^2
                  3x^4 + 6x^3 + 9x^2 + 12x
                        4x6^3  + 8x^2 + 12x + 16 */
    //Algorithm is to update the values while skipping the ones we've iterated over
    for(int i = 0; i < this->vect.size();i++){
        for(int j = 0; j < H.vect.size();j++){
            n[i+j] += this->vect[i] * H.vect[j];
        }
        
    }
    P.vect.clear();
    P.vect = n;
    return P;
}
std::ostream& operator<< (std::ostream& out, HunPolynomial Hun){
    int counter = 0;
    for(int i = int(Hun.vect.size())-1; i >= 0 ;i--){
        //Catches x0
        if(Hun.vect[counter] == 0){
            counter++;
            continue;
        }
        // Positive
        if(Hun.vect[counter] > 0){
            //first one and 1
            if(Hun.vect[counter] == 1 && counter == 0){
                out<< "x^" << i;
                counter++;
                continue;
            }
            //first one but greater than 1
            if(Hun.vect[counter] != 1 && counter == 0){
                out<< Hun.vect[counter] << "*x^" << i;
                counter++;
                continue;
            }
            // not first but equal to 1 and not 2nd to last
            if(counter > 0 && Hun.vect[counter] == 1 && counter < Hun.vect.size()-2){
                out << " + " << "x^" << i;
                counter++;
                continue;
            // not first, not equal to 1 and not 2nd to last
            }else if(counter > 0 && Hun.vect[counter] != 1 && counter < Hun.vect.size()-2){
                out << " + " << Hun.vect[counter] << "*x^" << i;
                counter++;
                continue;
            }else if(counter == Hun.vect.size() -2 && Hun.vect[counter] == 1){
                out << " + "  << "x";
                counter++;
                continue;
            }else if(counter == Hun.vect.size()-1){
                out << " + " << Hun.vect[counter];
                counter++;
                continue;
            }
        }
        // Negative
        if(Hun.vect[counter] < 0){
            
            // last place
            if(counter == Hun.vect.size()-1 && i == 0){
                std::cout <<" - " <<  -1*Hun.vect[counter];
                break;
            }
            //first one and -1
            if(Hun.vect[counter] == -1 && counter == 0){
                out<< "- x^" << i;
                counter++;
                continue;
            }
            //first one but less than -1
            if(Hun.vect[counter] != 1 && counter == 0){
                out<< "- " << -1*Hun.vect[counter] << "*x^" << i;
                counter++;
                continue;
            }
            // if index is 1 and is -1
            if(counter == Hun.vect.size()-2 && Hun.vect[counter] == -1){
                out<<" - "<< "x";
                counter++;
                continue;
            }
            if(counter != 0 && counter != Hun.vect.size()-2 && counter !=Hun.vect[counter] -1 && Hun.vect[counter] != -1){
                out << " - " << -1*Hun.vect[counter] << "*x^" << i;
                counter++;
                continue;
            }
            if(Hun.vect[counter] == -1){
                out << "- " << "x^" << i;
                counter++;
                continue;
            }
            if(i == 1){
                std::cout << " - " << -1*Hun.vect[counter] << "*x";
                counter++;
                continue;
            }
            std::cout << " - " << -1*Hun.vect[counter] << "*x^" << i;
        }
    }
    return out;
}
float HunPolynomial::operator()(float var){
    float calculator = 0.0;
    int counter = 0;
    int reverse = int(this->vect.size());
    while(reverse-1 >= 0){
        if(counter == reverse-1){
            calculator += this->vect[counter];
            break;
        }
        calculator += this->vect[counter]*(pow(var,reverse-1));
        counter++;
    }
    return calculator;
}
