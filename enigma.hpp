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
#include "sstream"

class Enigma {
private:
    Plugboard plugboard;
    vector<Rotor> rotors;
    bool initialized;
    bool correctRotors(vector<Rotor>& rotors);
public:
    static const int REGULAR_ROTORS_NUM = 4;
    static const int THIN_ROTOR_NUM = 5;
    
    Enigma(Plugboard plugboard, vector<Rotor> rotors);
    bool wasInitialized() const { return initialized; }
    string getStringRotorsPosition() const;
    string getStringRotorsInfo() const;
    char translate(char input);
    
    friend ostream& operator<<(ostream& os, const Enigma& enigma);
};

#endif /* ENIGMA_HPP */

