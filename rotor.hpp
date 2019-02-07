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
#include <iostream>

using namespace std;

typedef enum {
    rotorTypeRegular = 0,
    rotorTypeReflector = 1     
} RotorType;

typedef enum {
    directionLeft = 0,
    directionRight = 1
} TranslateDirection;

typedef struct {

    RotorParams();
    bool areParamsCorrect();
} RotorParams;

class Rotor {
private:
    RotorType type;
    unsigned int id;
    unsigned int shift;
public:
    Rotor(RotorType type, unsigned int id);
    Rotor(RotorType type, unsigned int id, unsigned int newPosition);
    Rotor(const Rotor& rotor);
    
    void rotate();
    void rotate(unsigned int newPosition);
    bool canNextRotate();
    char translate(char input, TranslateDirection direction);
};

#endif /* ROTOR_HPP */

