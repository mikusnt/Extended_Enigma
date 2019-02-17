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
private:
    const string EMPTY = "empty";
public:
    const string regularIDMap[11] = { EMPTY, "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "beta", "gamma" };
    const string reflectorIDMap[5] = { EMPTY, "B", "C", "B_thin", "C_thin" };
    const string rotorTypeMap[2] = { "regular", "reflector" };
    static const int end = -1;
    static const int REFLECTOR_THIN_SIZE = 6;
    static const int REFLECTOR_SIZE = 1;
    
    int idMap(const string map[], string value);
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
   
    string filename;
    Plugboard plugboard;
    vector<Rotor> rotors;
    bool parsed;
    
    bool haveDuplicates();
    int parsePosition(string pos);
public:
    EnigmaReader() {}
    EnigmaReader(string filename);
    bool wasParsed() const { return parsed; }
    bool tryParseFile(string filename);
    static void writeDefaultFile(string filename);
    
    
    Plugboard getPlugboard() const { return plugboard; }
    vector<Rotor> getRotors() const { return rotors; }
    string getFilename() const { return filename; }
    
    friend ostream& operator<<(ostream& os, const EnigmaReader& reader);
};


#endif /* ENIGMA_READER_HPP */

