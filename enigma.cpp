/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "enigma.hpp"
#include "enigma_reader.hpp"

namespace enigma {
    bool Enigma::areCorrectRotors(std::vector<RegularRotor>& rotors, ReflectorRotor& reflector) {
        int i;
        EnigmaDicts dicts;
        
        int rotorLimit = REGULAR_ROTORS_NUM;
        ReflectorRotorId reflectorId = reflector.getId();
        if ((reflectorId == ReflectorID_Bthin) || (reflectorId == ReflectorID_Cthin))
            rotorLimit = THIN_ROTOR_NUM;
        
        if (!reflector.wasInitialized())
            return false;
        
        for (i = 0; i < rotorLimit; i++) {
            RegularRotorId id = rotors[i].getId();
            if (((id == RegularID_BETA) || (id == RegularID_GAMMA))
                    && (i != 3) || (rotorLimit != THIN_ROTOR_NUM))
                return false;
            if (!rotors[i].wasInitialized())
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

    std::string Enigma::groupString(std::string input, int groupSize) {
        if ((groupSize > 0) && (groupSize < input.size())) {
            std::stringstream concat;
            for (int i = 0; i < input.size(); i++) {
                if ((i > 0) && ((i % groupSize) == 0) && (i != (input.size() - 1)))
                        concat << " ";
                concat << input[i];
            }
            return concat.str();
        } else return input;
    }



    Enigma::Enigma(Plugboard plugboard, std::vector<RegularRotor> rotors, ReflectorRotor reflector) : plugboard(plugboard), rotors(rotors), reflector(reflector) {
        initialized = false;
        //this->plugboard = plugboard;
        if (!this->plugboard.wasLoadedRules())
            return;
        if(!areCorrectRotors(rotors, reflector))
            return;
        //this->rotors = rotors;
        initialized = true;
    }

    std::string Enigma::getStringRotorsPosition() const {
        std::stringstream positions;
        //positions << reflector.getStringPosition();
        for (int i = 0; i < rotors.size() - 1; i++) {
            positions << rotors[i].getStringPosition() << " ";
        }
        positions << rotors.back().getStringPosition();
        return positions.str();
    }

    std::string Enigma::getStringRotorsInfo() const {
        std::stringstream output;
        output << reflector.toString() << std::endl;
        for(int i = rotors.size() - 1; i > 0; i--) {
            output << rotors[i].toString() << std::endl;
        }
        output << rotors.front().toString();
        return output.str();
    }

    char Enigma::translate(char input) {
        input = normalizeChar(input);
        char translated = plugboard.translate(input);

        // try to rotate
        bool canNextRotate = rotors.back().canNextRotate(*(rotors.end() - 2));
        rotors.back().autoRotate();
        for (std::vector<RegularRotor>::iterator i = rotors.end() - 2; i >= rotors.begin(); i--) {
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
        for (std::vector<RegularRotor>::iterator i = rotors.end() - 1; i >= rotors.begin(); i--) {
            translated = (*i).translate(translated, directionLeft);
        }
        translated = reflector.translate(translated);
        // translate from left to right without reflector
        for (std::vector<RegularRotor>::iterator i = rotors.begin(); i < rotors.end(); i++) {
            translated = (*i).translate(translated, directionRight);
        }
        return plugboard.translate(translated);
    }

    bool Enigma::rotate(int rotorNumber, int newPosition) {
        if ((rotorNumber < 1) || (rotorNumber > rotors.size())) {
            return false;
        }
        rotors[rotorNumber - 1].rotate(newPosition);
        return true;
    }

    bool Enigma::rotateBy(int rotorNumber, int move) {
        if ((rotorNumber < 1) || (rotorNumber > rotors.size())) {
            return false;
        }
        rotors[rotorNumber - 1].rotateBy(move);
        return true;    
    }


    std::ostream& operator<<(std::ostream& os, const Enigma& enigma) {
        os << "Translation on plugboard:\n";
        os << enigma.plugboard << "\n\n";

        os << "Rotors settings: \n";
        os << enigma.getStringRotorsInfo();
        return os;
    }
}

