/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "enigma.hpp"

Enigma::Enigma(Plugboard plugboard, vector<Rotor> rotors) : plugboard(plugboard), rotors(rotors) {}

char Enigma::translate(char input) {
    char translated = plugboard.translate(input);
    
    // try to rotate
    bool canNextRotate = rotors.back().canNextRotate(*(rotors.end() - 2));
    rotors.back().autoRotate();
    for (vector<Rotor>::iterator i = rotors.end() - 2; i > rotors.begin(); i--) {
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
    for (vector<Rotor>::iterator i = rotors.end() - 1; i >= rotors.begin(); i--) {
        translated = (*i).translate(translated, directionLeft);
    }
    
    // translate from left to right without reflector
    for (vector<Rotor>::iterator i = rotors.begin() + 1; i < rotors.end(); i++) {
        translated = (*i).translate(translated, directionLeft);
    }
    return translated;
}

