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
    
    Plugboard plugboard;
    vector<Rotor> rotors;
    
    bool haveDuplicates();
public:
    
    
    int parseError;
    EnigmaReader(string filename);
    static void writeDefaultFile(string filename);
    
    Plugboard getPlugboard();
    vector<Rotor> getRotors();
};


#endif /* ENIGMA_READER_HPP */

