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
public:
    Plugboard plugboard;
    vector<Rotor> rotors;
    Enigma(Plugboard plugboard, vector<Rotor> rotors);
    char translate(char input);
};

#endif /* ENIGMA_HPP */

