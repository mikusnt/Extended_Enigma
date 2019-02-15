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

using namespace std;

class EnigmaDicts {
public:
    const string regularIDMap[10] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "beta", "gamma" };
    const string reflectorIDMap[4] = { "B", "C", "B_thin", "C_thin" };
    const string rotorTypeMap[2] = { "regular", "reflector" };
    static const int end = -1;
    static const int REFLECTOR_THIN_SIZE = 6;
    
    unsigned int idMap(const string map[], string value);
};

class EnigmaReader {
private:
    const string PLUGBOARD = "plugboard";
    const string RULES = "rules";
    
    const string ROTOR = "rotor_";
    const string TYPE = "type";

    const string ID = "id";
    const string RING_SHIFT = "ring_shift";
    const string POSITION = "position";
    
    const string EMPTY = "_empty";
    const int REGULAR_ROTORS_NUM = 4;
    const int THIN_ROTOR_NUM = 5;
   
    string filename;
    Plugboard plugboard;
    vector<Rotor> rotors;
    bool parsed;
    
    bool haveDuplicates();
    unsigned int parsePosition(string pos);
public:
    EnigmaReader() {}
    EnigmaReader(string filename);
    bool wasParsed() const { return parsed; }
    bool tryParseFile(string filename);
    static void writeDefaultFile(string filename);
    
    Plugboard getPlugboard();
    vector<Rotor> getRotors();
};


#endif /* ENIGMA_READER_HPP */

