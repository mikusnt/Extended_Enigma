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

using namespace std;

class EnigmaReader {
private:
    const string PLUGBOARD = "plugboard";
    const string RULES = "rules";
    
    const string ROTOR = "rotor_";
    const string TYPE = "type";

    const string ID = "id";
    const string POSITION = "position";
    
    const string EMPTY = "_empty";
    
    Plugboard plugboard;
    vector<Rotor> rotors;
    
    bool haveDuplicates();
public:
    static const string REGULAR;
    static const string REFLECTOR;;
    static const string BETA;
    static const string GAMMA;
    
    int parseError;
    EnigmaReader(string filename);
    
    Plugboard getPlugboard();
    vector<Rotor> getRotors();
};


#endif /* ENIGMA_READER_HPP */

