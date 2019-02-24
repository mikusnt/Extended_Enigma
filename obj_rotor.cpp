/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "obj_rotor.hpp"
#include "rotor.hpp"

int oRotor::rotaryPos(int position) {
    while (position >= DICT_SIZE) position -= DICT_SIZE;
    while (position < 0) position += DICT_SIZE;
    return position;
}

char oRotor::rotaryASCII(char sign) {
    while (sign < 'A') sign += DICT_SIZE;
    while (sign > 'Z') sign -= DICT_SIZE;
    return sign;
}

int oRotor::normalizePosition(int value) {
    if ((toupper(value) >= 'A') && (toupper(value <= 'Z')))
        return toupper(value) - 'A';
    else return rotaryPos(value - 1);
}

int oRotor::denormalizePosition(int value) {
    return value + 1;
}

std::string oRotor::getStringFromAddr(int value) {
    std::stringstream temp;
    temp << value + 1 << "(" << (char)(value + 'A') << ")";
    return temp.str();
}

RegularRotor::RegularRotor(RegularRotorId id, int ringShift, int position) {
    this->id = id;
    initialized = false;
    
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

    this->ringShift = normalizePosition(ringShift);
    this->position = normalizePosition(position);
    initialized = true;
}

void RegularRotor::rotate(int newPosition) {
    this->position = normalizePosition(newPosition);
}

void RegularRotor::rotateBy(int move) {
    this->position = normalizePosition(this->position + move + 1);
}

bool RegularRotor::canNextRotate(const oRotor& nextRotor) {
    if ((id < RegularID_BETA)
            && (nextRotor.getType() == rotorTypeRegular) 
            && (nextRotor.getId() < RegularID_BETA)) {
        char toFind = rotaryASCII(position + 65);
        if (CHANGE_POS[id].find(toFind) != string::npos)
            return true;
    }
    return false;
}

void RegularRotor::autoRotate() {
    if (id < RegularID_BETA)
        position = rotaryPos(++position);
}

char RegularRotor::translate(char input, TranslateDirection direction) {
    input = normalizePosition(input);
    int pos = input + position - ringShift;
    int translated = DICT[id][direction][rotaryPos(pos)];
    if (input < DICT_SIZE) 
        return rotaryASCII(translated - position + ringShift);
    else return ERROR_CHAR;
}

ReflectorRotor::ReflectorRotor(ReflectorRotorId id) { 
    this->id = id;
    initialized = true; 
}

char ReflectorRotor::translate(char input, TranslateDirection direction) {
    input = normalizePosition(input);
    if (input < DICT_SIZE) 
        return rotaryASCII(DICT[id][input]);
    else return ERROR_CHAR;
}
