/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "enigma.hpp"
#include "enigma_reader.hpp"

bool Enigma::areCorrectRotors(vector<Rotor>& rotors) {
    int i;
    EnigmaDicts dicts;
    int rotorLimit = REGULAR_ROTORS_NUM;
    for (i = 0; i < rotors.size(); i++) {
        RotorType type = rotors[i].getType();
        if ((type == EnigmaDicts::end)
            || ((type != rotorTypeReflector) && (i == 0))
            || ((type != rotorTypeRegular) && (i > 0)))
            return false;  
        
        int id = rotors[i].getId();
        if (type == rotorTypeRegular) {
            if ((id == EnigmaDicts::end) 
                    || ((id >= RegularID_BETA) && (rotorLimit == REGULAR_ROTORS_NUM)) 
                    || ((id < RegularID_BETA) && (rotorLimit == THIN_ROTOR_NUM) && (i == 1)))
                return false;
        } else if (type == rotorTypeReflector) {
            if (id == EnigmaDicts::end)
                return false;
            if (dicts.reflectorIDMap[id].length() != dicts.REFLECTOR_SIZE)
                rotorLimit = THIN_ROTOR_NUM;
        } else return false;
    }
    if (i != rotorLimit) {
        return false;
    }
    return true;
}

char Enigma::normalizeChar(char input) {
    input = toupper(input);
    if ((input < 'A') || (input > 'Z')) 
        return EnigmaDicts::ERROR_CHAR;
    else return input;
}

string Enigma::groupString(string input, int groupSize) {
    if ((groupSize > 0) && (groupSize < input.size())) {
        stringstream concat;
        for (int i = 0; i < input.size(); i++) {
            if ((i > 0) && ((i % groupSize) == 0) && (i != (input.size() - 1)))
                    concat << " ";
            concat << input[i];
        }
        return concat.str();
    } else return input;
}



Enigma::Enigma(Plugboard plugboard, vector<Rotor> rotors) : plugboard(plugboard), rotors(rotors) {
    initialized = false;
    //this->plugboard = plugboard;
    if (!this->plugboard.wasLoadedRules())
        return;
    if(!areCorrectRotors(rotors))
        return;
    //this->rotors = rotors;
    initialized = true;
}

string Enigma::getStringRotorsPosition() const {
    stringstream positions;
    for (int i = 0; i < rotors.size() - 1; i++) {
        positions << rotors[i].getStringPosition() << " ";
    }
    positions << rotors.back().getStringPosition();
    return positions.str();
}

string Enigma::getStringRotorsInfo() const {
    stringstream output;
    for(int i = 0; i < rotors.size() - 1; i++) {
        output << rotors[i] << endl;
    }
    output << rotors.back();
    return output.str();
}

char Enigma::translate(char input) {
    input = normalizeChar(input);
    char translated = plugboard.translate(input);
    
    // try to rotate
    bool canNextRotate = rotors.back().canNextRotate(*(rotors.end() - 2));
    rotors.back().autoRotate();
    for (vector<Rotor>::iterator i = rotors.end() - 2; i > rotors.begin(); i--) {
        if (canNextRotate) {
            canNextRotate = (*i).canNextRotate((*(i-1)));
            (*i).autoRotate();
        } else {
            if ((*i).canNextRotate((*(i-1)))) {
                canNextRotate = true;
                (*i).autoRotate();
            }
        }

    }
    
    // translate from right to left, first element is a reflector
    for (vector<Rotor>::iterator i = rotors.end() - 1; i >= rotors.begin(); i--) {
        translated = (*i).translate(translated, directionLeft);
    }
    
    // translate from left to right without reflector
    for (vector<Rotor>::iterator i = rotors.begin() + 1; i < rotors.end(); i++) {
        translated = (*i).translate(translated, directionRight);
    }
    return plugboard.translate(translated);
}

bool Enigma::rotate(int rotorNumber, int newPosition) {
    if ((rotorNumber < 2) || (rotorNumber > rotors.size())) {
        return false;
    }
    rotors[rotorNumber - 1].rotate(newPosition);
    return true;
}

bool Enigma::rotateBy(int rotorNumber, int move) {
    if ((rotorNumber < 2) || (rotorNumber > rotors.size())) {
        return false;
    }
    rotors[rotorNumber - 1].rotateBy(move);
    return true;    
}


ostream& operator<<(ostream& os, const Enigma& enigma) {
    os << "Translation on plugboard:\n";
    os << enigma.plugboard << "\n\n";

    os << "Rotors settings: \n";
    os << enigma.getStringRotorsInfo();
    return os;
}

