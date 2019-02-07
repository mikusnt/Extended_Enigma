/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "rotor.hpp"

vector<vector<string>> rotorDict;
const unsigned int DICT_SIZE =  rotorDict[0][0].size();
const string rotorPos[] = {"R", "F", "W", "K", "A", "AN", "AN", "AN"};
const unsigned int BETA_POS = 8;
const unsigned int GAMMA_POS = 9;

bool RotorParams::areParamsCorrect() {
    if (number < rotorDict.size())
        return true;
    else return false;
}

RotorParams::RotorParams() {
    this->type = rotorTypeRegular;
    this->number = 0;
}

Rotor::Rotor(RotorParams params) : shift(0) {
    if (params.areParamsCorrect()) {
        this->params = params;
        if (params.type == rotorTypeBeta) 
            this->params.number = BETA_POS;
        if (params.type == rotorTypeGamma) 
            this->params.number = GAMMA_POS; 
    }
        
    else {
        params.RotorParams();
        this->params = params;
    }
}

Rotor::Rotor(const Rotor& rotor) 
: params(RotorParams(rotor.params)), rotatePosition(rotor.rotatePosition), shift(rotor.shift)
{}

void Rotor::rotate(unsigned int position) {
    this->rotatePosition = position;
}

void Rotor::tryRotate() {
    
}

char Rotor::translate(char input, TranslateDirection direction = directionLeft) {
    //if ((params.moveEvery > 0) && (++rotatePosition >= params.moveEvery)) 
    //    shift = (++shift % DICT_SIZE);
    
    if ((input >= '0') && (input <= '9')) return rotorDict[this->params.number][direction][(input - 48 + shift) % DICT_SIZE];
    else  if ((input >= 'A') && (input <= 'Z')) return rotorDict[this->params.number][direction][(input - 54 + shift) % DICT_SIZE];
    else  if ((input >= 'a') && (input <= 'z')) return rotorDict[this->params.number][direction][input - 60 + shift % DICT_SIZE];
    else return rotorDict[this->params.number][direction][shift];
}




