/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <typeinfo>

#include "rotor.hpp"
#include "enigma_reader.hpp"

 unsigned short Rotor::rotaryPos(short position) {
    while (position >= (short)DICT_SIZE) position -= DICT_SIZE;
    while (position < 0) position += DICT_SIZE;
    return position;
}

char Rotor::rotaryASCII(char sign) {
    sign = toupper(sign);
    while (sign < 'A') sign += DICT_SIZE;
    while (sign > 'Z') sign -= DICT_SIZE;
    return sign;
}

int Rotor::normalizePosition(int value) {
    if ((toupper(value) >= 'A') && (toupper(value <= 'Z')))
        return toupper(value) - 'A';
    else return rotaryPos(value - 1);
}

int Rotor::denormalizePosition(int value) const {
    return value + 1;
}



string Rotor::getStringFromAddr(int value) const {
    stringstream temp;
    temp << value + 1 << "(" << (char)(value + 'A') << ")";
    return temp.str();
}

Rotor::Rotor(RotorType type, int id) : type(type), id(normalizePosition(id)), ringShift(0), position(0) {
    initialized = false;
    if (type == rotorTypeRegular) {
        if ((id < 1) || (id > RegularID_GAMMA)) {
            initialized = false;
            return;
        }
    }
    if (type == rotorTypeReflector) {
        if ((id < 1) || (id > Rotor::MAX_INPUT_REFLECTOR_ID)) {
            initialized = false;
            return;
        }
    }
    initialized = true;
}

Rotor::Rotor(RotorType type, int id, int ringShift, int position) : Rotor(type, id) {
    // if rotorTypeReflector, rotor have static position and ringShift
    initialized = false;
    if (type == rotorTypeRegular) {
        if ((toupper(ringShift) > 'Z')
                || (ringShift < 1)
                || ((ringShift > DICT_SIZE) && (toupper(ringShift) < 'A'))) {
            return;
        }
        if ((toupper(position) > 'Z')
                || (position < 1)
                || ((position > DICT_SIZE) && (toupper(position) < 'A'))) {
            return;
        }   
        //this->position = toupper(position) >= 'A' ? toupper(position) - 'A' : position - 1;
        this->ringShift = normalizePosition(ringShift);
        this->position = normalizePosition(position);
        //this->ringShift = RotaryPos(toupper(ringShift) >= 'A' ? toupper(ringShift) - 'A' : ringShift - 1);
        
    } else {
        this->position = 0;
        this->ringShift = 0;
    }
    initialized = true;
}

Rotor::Rotor(const Rotor& rotor) 
: position(rotor.position), type(rotor.type), id(rotor.id), ringShift(rotor.ringShift) {}

void Rotor::setType(RotorType type) { this->type = type; }

void Rotor::autoRotate() {
    if ((id < 8) && (type == rotorTypeRegular))
        position = rotaryPos(++position);
}

void Rotor::rotate(unsigned short newPosition) {
    if (type == rotorTypeRegular)
        this->position = normalizePosition(newPosition - 1);
}

bool Rotor::canNextRotate(const Rotor& nextRotor) {
    if ((type == rotorTypeRegular) 
            && (id < 8) 
            && (nextRotor.type == rotorTypeRegular) 
            && (nextRotor.id < 8)) {
        char toFind = rotaryASCII(position + 65);
        if (ROTOR_CHANGE_POS[id].find(toFind) != string::npos)
            return true;
    } else if (type == rotorTypeReflector) {
        // no rotate
    }
    return false;
}

char Rotor::translate(char input, TranslateDirection direction) {
    //if ((params.moveEvery > 0) && (++rotatePosition >= params.moveEvery)) 
    //    shift = (++shift % DICT_SIZE);
    input = toupper(input) >= 'A' ? toupper(input) : input + 'A';
    if (type == rotorTypeRegular) {
        if ((input >= 'A') && (input <= 'Z')) return rotaryASCII(ROTOR_DICT[id][direction][rotaryPos(input - 'A' + position - ringShift)] - position + ringShift);
        else return ERROR_CHAR;
    } else if (type == rotorTypeReflector) {
        if ((input >= 'A') && (input <= 'Z')) return rotaryASCII(REFLECTOR_DICT[id][rotaryPos(input - 'A' + position - ringShift)] - position + ringShift);
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
        idS = dicts.regularIDMap[rotor.id+1];
    if (rotor.type == rotorTypeReflector) 
        idS = dicts.reflectorIDMap[rotor.id+1];  
    

    os << "{ type: " << typeS << ", id: " << idS << ", ring shift: " <<  rotor.getStringRingShift() << ", position: " << rotor.getStringPosition() << " }";
    return os;
}



