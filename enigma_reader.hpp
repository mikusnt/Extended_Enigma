/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   enigma_reader.hpp
 * Author: MS-1
 *
 * Created on 10 lutego 2019, 18:57
 */

#ifndef ENIGMA_READER_HPP
#define ENIGMA_READER_HPP

#include "rotor.hpp"
#include "plugboard.hpp"
#include "INIReader.h"
#include <iostream>
#include <sstream>
#include <string>
#include <map>

namespace enigma {
    class EnigmaDicts {
    public:
        static const char ERROR_CHAR = 'X';
        static std::string toLower(std::string input);
    };

    class EnigmaReader {
    private:
        const std::string PLUGBOARD = "plugboard";
        const std::string RULES = "rules";

        const std::string REGULAR = "rotor_";
        const std::string REFLECTOR = "reflector";

        const std::string ID = "id";
        const std::string RING_SHIFT = "ring_shift";
        const std::string POSITION = "position";

        const std::string EMPTY = "_empty";

        std::string filename;
        Plugboard plugboard;
        std::vector<RegularRotor> rotors;
        ReflectorRotor reflector;
        bool parsed;

        int parsePosition(std::string pos);
    public:
        EnigmaReader();
        EnigmaReader(std::string filename);
        bool wasParsed() const { return parsed; }
        bool tryParseFile(std::string filename);
        static void writeDefaultFile(std::string filename);


        Plugboard getPlugboard() const { return plugboard; }
        std::vector<RegularRotor> getRotors() const { return rotors; }
        ReflectorRotor getReflector() const { return reflector; }
        std::string getFilename() const { return filename; }

        friend std::ostream& operator<<(std::ostream& os, const EnigmaReader& reader);
    };
}


#endif /* ENIGMA_READER_HPP */

