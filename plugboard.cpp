/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "plugboard.hpp"

Plugboard::Plugboard() { actual = ORIGINAL; }

Plugboard::Plugboard(string rules) : Plugboard() {
    for (int i = 0; i < rules.length(); i += 2){
        addConnect(toupper(rules[i]), toupper(rules[i+1]));
    }
}

bool Plugboard::addConnect(char input, char output) {
    input = toupper(input);
    output = toupper(output);
    if ((input >= 'A') && (input <= 'Z') && (output >= 'A') && (output <= 'Z')) {
        actual[input - 65] = output;
        actual[output - 65] = input;
        return true;
    } else return false;
}

bool Plugboard::removeConnect(char input) {
    input = toupper(input);
    if ((input >= 'A') && (input <= 'Z')) {
        actual[actual[input - 65] - 65] = ORIGINAL[actual[input - 65] - 65];
        actual[input - 65] = ORIGINAL[input - 65];
        return true;
    } else return false;
}

char Plugboard::translate(char input) {
    input = toupper(input);
    if ((input >= 'A') && (input <= 'Z')) {
        return actual[input];
    } else return ERROR_CHAR;
}


