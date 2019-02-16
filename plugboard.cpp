/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "plugboard.hpp"
#include "rotor.hpp"

Plugboard::Plugboard() { actual = ORIGINAL; loadedRules = false; }

Plugboard::Plugboard(string rules) : Plugboard() {
    loadRules(rules);
}

bool Plugboard::loadRules(string rules) {
    for(int i=0; i<rules.length(); i++) {
        if(rules[i] == ' ') rules.erase(i > 0 ? i-- : i,1);
        if(rules[i] == ',') rules.erase(i > 0 ? i-- : i,1);
        if(rules[i] == ';') rules.erase(i > 0 ? i-- : i,1);
    }
    if ((rules.length() % 2) == 1) {
        loadedRules = false;
        return false;
    }
    
    for (int i = 0; i < rules.length(); i += 2){
        addConnect(toupper(rules[i]), toupper(rules[i+1]));
    }
    loadedRules = true;
    return true;
}

bool Plugboard::haveDuplicates(string word) {
    int counter[Rotor::DICT_SIZE] = {0};
    for (int  i = 0; i < word.length(); i++) {
        counter[toupper(word[i])-65]++;
    }
    for (int  i = 0; i < word.length(); i++) 
        if (counter[i] > 1) {
            return true;
        }
    return false;
}

bool Plugboard::addConnect(char input, char output) {
    input = toupper(input) >= 'A' ? toupper(input) : input + 'A';
    output = toupper(output) >= 'A' ? toupper(output) : output + 'A';
    
    string copy = actual;
    if ((input >= 'A') && (input <= 'Z') && (output >= 'A') && (output <= 'Z')) {
        copy[input - 65] = output;
        copy[output - 65] = input;
        if (!haveDuplicates(copy)) {
            actual = copy;
            loadedRules = true;
            return true;
        } else {
            loadedRules = false;
            return false;
        }
    } else {
        loadedRules = false;
        return false;
    }
}

bool Plugboard::removeConnect(char input) {
    input = toupper(input) >= 'A' ? toupper(input) : input + 'A';
    if ((input >= 'A') && (input <= 'Z')) {
        actual[actual[input - 65] - 65] = ORIGINAL[actual[input - 65] - 65];
        actual[input - 65] = ORIGINAL[input - 65];
        loadedRules = true;
        return true;
    } else {
        loadedRules = false;
        return false;
    }
}

char Plugboard::translate(char input) {
    input = toupper(input) >= 'A' ? toupper(input) : input + 'A';
    if ((input >= 'A') && (input <= 'Z'))
        return actual[input - 'A'];
    else return ERROR_CHAR;
}

ostream& operator<<(ostream& os, const Plugboard& plugboard) {
    if (plugboard.actual != plugboard.ORIGINAL) {
        for (int i = 0; i < Rotor::DICT_SIZE; i++)
            if ((plugboard.actual[i] != plugboard.ORIGINAL[i]) && (plugboard.actual[i] > (i + 'A')))
                os << plugboard.ORIGINAL[i] << " ";
        os << endl;
        for(int i = 0; i < Rotor::DICT_SIZE; i++)
            if ((plugboard.actual[i] != plugboard.ORIGINAL[i]) && (plugboard.actual[i] > (i + 'A')))
                os << "| ";
        os << endl;
        for (int i = 0; i < Rotor::DICT_SIZE; i++)
            if ((plugboard.actual[i] != plugboard.ORIGINAL[i]) && (plugboard.actual[i] > (i + 'A')))    
                os << plugboard.actual[i]<< " ";
    } else {
        os << "<default>";
    }
    return os;
}


