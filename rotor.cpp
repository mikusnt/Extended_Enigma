/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <ios>

#include "rotor.hpp"

vector<vector<string>> rotorDict = {{ "EKMFLGDQVZNTOWYHXUSPAIBRCJ", "UWYGADFPVZBECKMTHXSLRINQOJ" },
        { "AJDKSIRUXBLHWTMCQGZNPYFVOE", "AJPCZWRLFBDKOTYUQGENHXMIVS" },
        { "BDFHJLCPRTXVZNYEIWGAKMUSQO", "TAGBPCSDQEUFVNZHYIXJWLRKOM" },
        { "ESOVPZJAYQUIRHXLNFTGKDCMWB", "HZWVARTNLGUPXQCEJMBSKDYOIF" },
        { "VZBRGITYUPSDNHLXAWMJQOFECK", "QCYLXWENFTZOSMVJUDKGIARPHB" },
        { "JPGVOUMFYQBENHZRDKASXLICTW", "SKXQLHCNWARVGMEBJPTYFDZUIO" },
        { "NZJHGRCXMYSWBOUFAIVLPEKQDT", "QMGYVPEDRCWTIANUXFKZOSLHJB" },
        { "FKQHTLXOCBJSPDZRAMEWNIUYGV", "QJINSAYDVKBFRUHMCPLEWZTGXO" },
        { "LEYJVCNIXWPBQMDRTAKZGFUHOS", "RLFOBVUXHDSANGYKMPZQWEJICT" },
        { "FSOKANUERHMBTIYCWLQPZXVGJD", "ELPZHAXJNYDRKFCTSIBMGWQVOU" }
};

string reflectorDict[] = { 
    "YRUHQSLDPXNGOKMIEBFZCWVJAT", 
    "FVPJIAOYEDRZXWGCTKUQSBNMHL", 
    "ENKQAUYWJICOPBLMDXZVFTHRGS", 
    "RDOBJNTKVEHMLFCWZAXGYIPSUQ"
};

const unsigned int DICT_SIZE =  26;
const string rotorPos[] = {"R", "F", "W", "K", "A", "AN", "AN", "AN"};
const unsigned int BETA_POS = 8;
const unsigned int GAMMA_POS = 9;

//bool RotorParams::areParamsCorrect() {
//    if (id < rotorDict.size())
//        return true;
//    else return false;
//}
//
//RotorParams::RotorParams() {
//    this->type = rotorTypeRegular;
//    this->id = 0;
//}

Rotor::Rotor(RotorType type, unsigned int id) : shift(0), id(id) {
    this->type = type;
}

Rotor::Rotor(RotorType type, unsigned int id, unsigned int poosition) : Rotor(type, id) {
    this->shift = poosition;
}

Rotor::Rotor(const Rotor& rotor) 
: shift(rotor.shift), type(rotor.type), id(rotor.id) {}

void Rotor::setType(RotorType type) { this->type = type; }

void Rotor::rotate() {
    shift = (++shift % DICT_SIZE);
}

void Rotor::rotate(unsigned int newPosition) {
    this->shift = newPosition;
}

bool Rotor::canNextRotate() {
    if ((type == rotorTypeRegular) && (id < 8)) {
        char toFind = (char)(shift + 65);
        if (rotorPos[id].find(toFind))
            return true;
    } else if (type == rotorTypeReflector) {
        
    }
    return false;
}

char Rotor::translate(char input, TranslateDirection direction) {
    //if ((params.moveEvery > 0) && (++rotatePosition >= params.moveEvery)) 
    //    shift = (++shift % DICT_SIZE);
    input = toupper(input);
    if (type == rotorTypeRegular) {
        if ((input >= 'A') && (input <= 'Z')) return rotorDict[id][direction][(input - 65 + shift) % DICT_SIZE];
        else return rotorDict[id][direction][0];
    } else if (type == rotorTypeReflector) {
        if ((input >= 'A') && (input <= 'Z')) return reflectorDict[id][(input - 65 + shift) % DICT_SIZE];
        else return reflectorDict[id][0];
    }
    /*
    else  if ((input >= 'A') && (input <= 'Z')) return rotorDict[this->params.id][direction][(input - 54 + shift) % DICT_SIZE];
    else  if ((input >= 'a') && (input <= 'z')) return rotorDict[this->params.id][direction][input - 60 + shift % DICT_SIZE];
    else return rotorDict[this->params.id][direction][shift];*/
}




