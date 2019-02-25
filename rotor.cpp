/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "rotor.hpp"
#include "rotor.hpp"
#include "enigma_reader.hpp"

namespace enigma {
    int Rotor::rotaryPos(int position) {
        while (position >= DICT_SIZE) position -= DICT_SIZE;
        while (position < 0) position += DICT_SIZE;
        return position;
    }

    char Rotor::rotaryASCII(char sign) {
        while (sign < 'A') sign += DICT_SIZE;
        while (sign > 'Z') sign -= DICT_SIZE;
        return sign;
    }

    int Rotor::normalizePosition(int value) {
        if ((toupper(value) >= 'A') && (toupper(value) <= 'Z'))
            return toupper(value) - 'A';
        else return rotaryPos(value - 1);
    }

    int Rotor::denormalizePosition(int value) {
        return value + 1;
    }

    std::string Rotor::getStringFromAddr(int value) {
        std::stringstream temp;
        temp << value + 1 << "(" << (char)(value + 'A') << ")";
        return temp.str();
    }
    
    Rotor::Rotor() {
        id = 1;
        ringShift = 0;
        position = 0;
        initialized = true;
    }
    
    Rotor::Rotor(const Rotor& rotor) {
        this->id = rotor.id;
        this->position = rotor.position;
        this->ringShift = rotor.ringShift;
        this->initialized = rotor.initialized;
    }

    RegularRotor::RegularRotor(RegularRotorId id, int ringShift, int position) {
        initialized = false;
        this->id = id;

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

    RegularRotor::RegularRotor(std::string idS, int ringShift, int position) : RegularRotor(RegularID_I, ringShift, position) {
        initialized = false;
        idS = EnigmaDicts::toLower(idS);
        std::map<std::string, RegularRotorId>::iterator pos;
        pos = translator.find(idS);
        if (pos == translator.end()) {
            return;
        }
        this->id = translator[idS];
        initialized = true;
    }

    void RegularRotor::rotate(int newPosition) {
        this->position = normalizePosition(newPosition);
    }

    void RegularRotor::rotateBy(int move) {
        this->position = normalizePosition(this->position + move + 1);
    }

    bool RegularRotor::canNextRotate(const Rotor& nextRotor) {
        if ((id < RegularID_BETA)
                && (nextRotor.getType() == rotorTypeRegular) 
                && (nextRotor.getId() < RegularID_BETA)) {
            char toFind = rotaryASCII(position + 65);
            if (CHANGE_POS[id].find(toFind) != std::string::npos)
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

    std::string RegularRotor::toString() const {
        std::stringstream concat;
        concat << "{ type: regular, id: " << translatorReversed.at((RegularRotorId)id) << ", ring shift: " <<  getStringRingShift() << ", position: " << getStringPosition() << " }";
        return concat.str();
    }
    
    ReflectorRotor::ReflectorRotor() : Rotor() {

    }

    ReflectorRotor::ReflectorRotor(ReflectorRotorId id) : ReflectorRotor() { 
        this->id = id;
    }

    ReflectorRotor::ReflectorRotor(std::string idS) : ReflectorRotor(ReflectorID_B) {
        initialized = false;
        std::map<std::string, ReflectorRotorId>::iterator pos;
        idS = EnigmaDicts::toLower(idS);
        pos = translator.find(idS);
        if (pos == translator.end()) {
            return;
        }
        this->id = translator[idS];
        initialized = true;
    }

    char ReflectorRotor::translate(char input, TranslateDirection direction) {
        input = normalizePosition(input);
        if (input < DICT_SIZE) 
            return rotaryASCII(DICT[id][input]);
        else return ERROR_CHAR;
    }

    std::string ReflectorRotor::toString() const {
        std::stringstream concat;
        concat << "{ type: reflector, id: " << translatorReversed.at((ReflectorRotorId)id) << " }";
        return concat.str();
    }
}

