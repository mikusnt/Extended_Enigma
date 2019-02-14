/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "enigma.hpp"

Enigma::Enigma(Plugboard plugboard, vector<Rotor> rotors) : plugboard(plugboard), rotors(rotors) {}

char Enigma::translate(char input) {
    char plugboarded = plugboard.translate(input);
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
    
    return plugboarded;
}

