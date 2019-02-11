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
    const string REGULAR = "regular";
    const string REFLECTOR = "reflector";
    const string ID = "id";
    const string BETA_ID = "beta";
    const string GAMMA_ID = "gamma";
    const string POSITION = "position";
    
    const string EMPTY = "_empty";
    
    Plugboard plugboard;
    vector<Rotor> rotors;
public:
    int parseError;
    EnigmaReader(string filename);
    
    Plugboard getPlugboard();
    vector<Rotor> getRotors();
};


#endif /* ENIGMA_READER_HPP */

