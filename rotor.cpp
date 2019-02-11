/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "rotor.hpp"
#include "enigma_reader.hpp"

Rotor::Rotor(RotorType type, unsigned int id) : shift(0), type(type), id(id) {}

Rotor::Rotor(RotorType type, unsigned int id, unsigned int poosition) : Rotor(type, id) {
    this->shift = poosition;
}

Rotor::Rotor(const Rotor& rotor) 
: shift(rotor.shift), type(rotor.type), id(rotor.id) {}

void Rotor::setType(RotorType type) { this->type = type; }

void Rotor::rotate() {
    shift = (++shift % DICT_SIZE);
}

void Rotor::rotate(unsigned int newPosition) {
    this->shift = newPosition;
}

bool Rotor::canNextRotate() {
    if ((type == rotorTypeRegular) && (id < 8)) {
        char toFind = (char)(shift + 65);
        if (ROTOR_POS[id].find(toFind))
            return true;
    } else if (type == rotorTypeReflector) {
        
    }
    return false;
}

char Rotor::translate(char input, TranslateDirection direction) {
    //if ((params.moveEvery > 0) && (++rotatePosition >= params.moveEvery)) 
    //    shift = (++shift % DICT_SIZE);
    input = toupper(input);
    if (type == rotorTypeRegular) {
        if ((input >= 'A') && (input <= 'Z')) return ROTOR_DICT[id][direction][(input - 65 + shift) % DICT_SIZE];
        else return ERROR_CHAR;
    } else if (type == rotorTypeReflector) {
        if ((input >= 'A') && (input <= 'Z')) return REFLECTOR_DICT[id][(input - 65 + shift) % DICT_SIZE];
        else return ERROR_CHAR;
    }
    /*
    else  if ((input >= 'A') && (input <= 'Z')) return rotorDict[this->params.id][direction][(input - 54 + shift) % DICT_SIZE];
    else  if ((input >= 'a') && (input <= 'z')) return rotorDict[this->params.id][direction][input - 60 + shift % DICT_SIZE];
    else return rotorDict[this->params.id][direction][shift];*/
}

ostream& operator<<(ostream& os, const Rotor& rotor) {
        string typeS = rotor.type == 0 ? EnigmaReader::REGULAR : EnigmaReader::REFLECTOR;
        string idS;// = (id == Rotor::BETA_POS ? id = EnigmaReader::BETA : (id == Rotor::GAMMA_POS ? id = EnigmaReader::GAMMA : to_string(id)));
        if (rotor.id == Rotor::BETA_POS)
            idS = EnigmaReader::BETA;
        else if (rotor.id == Rotor::GAMMA_POS)
            idS = EnigmaReader::GAMMA;
        else {
            stringstream temp;
            temp << rotor.id;
            idS = temp.str();
        }

        os << "{ type: " << typeS << ", id: " << idS << ", position: " << rotor.shift << " }";
        return os;
     }



