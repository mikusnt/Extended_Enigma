/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rotor.hpp
 * Author: Mikolaj Stankowiak
 *
 * Created on 7 lutego 2019, 11:39
 */

#ifndef ROTOR_HPP
#define ROTOR_HPP


#include <string>
#include <vector>

using namespace std;

extern vector<vector<string>> rotorDict;
extern const unsigned int DICT_SIZE;

typedef enum {
    rotorTypeRegular,
    rotorTypeBeta,
    rotorTypeGamma
} RotorTypes;

typedef enum {
    directionLeft = 0,
    directionRight = 1
} TranslateDirection;

typedef struct {
    RotorTypes type;
    unsigned int number;
    unsigned int startPosition;
    unsigned int moveEvery;
    
    RotorParams();
    bool areParamsCorrect();
} RotorParams;

class Rotor {
private:
    RotorParams params;
    unsigned int rotatePosition;
    unsigned int shift;
public:
    Rotor(RotorParams params);
    Rotor(const Rotor& rotor);
    char translate(char input, TranslateDirection direction);
};

#endif /* ROTOR_HPP */

