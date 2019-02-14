/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "rotor.hpp"
#include "enigma_reader.hpp"

 unsigned short Rotor::RotaryPos(short position) {
    while (position >= (short)DICT_SIZE) position -= DICT_SIZE;
    while (position < 0) position += DICT_SIZE;
    return position;
}

char Rotor::RotaryASCII(char sign) {
    sign = toupper(sign);
    while (sign < 'A') sign += DICT_SIZE;
    while (sign > 'Z') sign -= DICT_SIZE;
    return sign;
}

Rotor::Rotor(RotorType type, unsigned int id) : position(0), type(type), id(RotaryPos(id)), ringShift(0) {}

Rotor::Rotor(RotorType type, unsigned int id, unsigned int ringShift, unsigned int position) : Rotor(type, id) {
    this->position = toupper(position) >= 'A' ? toupper(position) - 'A' : position - 1;
    this->ringShift = RotaryPos(toupper(ringShift) >= 'A' ? toupper(ringShift) - 'A' : ringShift - 1);
}

Rotor::Rotor(const Rotor& rotor) 
: position(rotor.position), type(rotor.type), id(rotor.id), ringShift(rotor.ringShift) {}

void Rotor::setType(RotorType type) { this->type = type; }

void Rotor::autoRotate() {
    if (id < 8)
        position = RotaryPos(++position);
}

void Rotor::rotate(unsigned short newPosition) {
    this->position = RotaryPos(newPosition);
}

bool Rotor::canNextRotate() {
    if ((type == rotorTypeRegular) && (id < 8)) {
        char toFind = RotaryASCII(position + 65 + 1);
        if (ROTOR_CHANGE_POS[id].find(toFind))
            return true;
    } else if (type == rotorTypeReflector) {
        // no rotate
    }
    return false;
}

char Rotor::translate(char input, TranslateDirection direction) {
    //if ((params.moveEvery > 0) && (++rotatePosition >= params.moveEvery)) 
    //    shift = (++shift % DICT_SIZE);
    input = toupper(input);
    if (type == rotorTypeRegular) {
        if ((input >= 'A') && (input <= 'Z')) return RotaryASCII(ROTOR_DICT[id][direction][RotaryPos(input - 'A' + position - ringShift)] - position + ringShift);
        else return ERROR_CHAR;
    } else if (type == rotorTypeReflector) {
        if ((input >= 'A') && (input <= 'Z')) return RotaryASCII(REFLECTOR_DICT[id][RotaryPos(input - 'A' + position - ringShift)] - position + ringShift);
        else return ERROR_CHAR;
    }
    /*
    else  if ((input >= 'A') && (input <= 'Z')) return rotorDict[this->params.id][direction][(input - 54 + shift) % DICT_SIZE];
    else  if ((input >= 'a') && (input <= 'z')) return rotorDict[this->params.id][direction][input - 60 + shift % DICT_SIZE];
    else return rotorDict[this->params.id][direction][shift];*/
}

ostream& operator<<(ostream& os, const Rotor& rotor) {
    EnigmaDicts dicts;
    string typeS = dicts.rotorTypeMap[rotor.type];
    string idS;// = (id == Rotor::BETA_POS ? id = EnigmaReader::BETA : (id == Rotor::GAMMA_POS ? id = EnigmaReader::GAMMA : to_string(id)));
    
    if (rotor.type == rotorTypeRegular) 
        idS = dicts.regularIDMap[rotor.id];
    if (rotor.type == rotorTypeReflector) 
        idS = dicts.reflectorIDMap[rotor.id];  
    
    stringstream ringShift;
    stringstream position;
    ringShift << rotor.ringShift + 1 << "(" << (char)(rotor.ringShift + 'A') << ")";
    position << rotor.position + 1<< "(" << (char)(rotor.position + 'A') << ")";

    os << "{ type: " << typeS << ", id: " << idS << ", ring shift: " << ringShift.str() << ", position: " << position.str() << " }";
    return os;
}



