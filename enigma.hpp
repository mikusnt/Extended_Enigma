/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   enigma.hpp
 * Author: MS-1
 *
 * Created on 14 lutego 2019, 19:08
 */

#ifndef ENIGMA_HPP
#define ENIGMA_HPP

#include "plugboard.hpp"
#include "rotor.hpp"
#include <sstream>

namespace enigma {
    class Enigma {
    private:
        Plugboard plugboard;
        std::vector<RegularRotor> rotors;
        ReflectorRotor reflector;
        bool initialized;
        bool areCorrectRotors(std::vector<RegularRotor>& rotors, ReflectorRotor& reflector);
        char normalizeChar(char input);
    public:
        static const int REGULAR_ROTORS_NUM = 3;
        static const int THIN_ROTOR_NUM = 4;
        static std::string groupString(std::string input, int groupSize);

        Enigma(Plugboard plugboard, std::vector<RegularRotor> rotors, ReflectorRotor reflector);
        bool wasInitialized() const { return initialized; }
        std::string getStringRotorsPosition() const;
        std::string getStringRotorsInfo() const;
        char translate(char input);
        bool rotate(int rotorNumber, int newPosition);
        bool rotateBy(int rotorNumber, int move); 

        friend std::ostream& operator<<(std::ostream& os, const Enigma& enigma);
    };
}

#endif /* ENIGMA_HPP */

