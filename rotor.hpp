/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rotor.hpp
 * Author: Mikolaj Stankowiak
 *
 * Created on 7 lutego 2019, 11:39
 */

#ifndef ROTOR_HPP
#define ROTOR_HPP


#include <string>
#include <vector>
#include <iostream>
#include <map>

using namespace std;

typedef enum {
    rotorTypeRegular = 0,
    rotorTypeReflector = 1     
} RotorType;

typedef enum {
    directionLeft = 0,
    directionRight = 1
} TranslateDirection;

class Rotor {
private:
    const string ROTOR_DICT[10][2] = {
            { "EKMFLGDQVZNTOWYHXUSPAIBRCJ", "UWYGADFPVZBECKMTHXSLRINQOJ" },
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
    const string REFLECTOR_DICT[4] = { 
        "YRUHQSLDPXNGOKMIEBFZCWVJAT", 
        "FVPJIAOYEDRZXWGCTKUQSBNMHL", 
        "ENKQAUYWJICOPBLMDXZVFTHRGS", 
        "RDOBJNTKVEHMLFCWZAXGYIPSUQ"
    };
    
    const string ROTOR_CHANGE_POS[8] = {"Q", "E", "V", "J", "Z", "ZM", "ZM", "ZM"};
    const char ERROR_CHAR = 'X';

    RotorType type;
    unsigned int id;
    unsigned int ringShift;
    unsigned int position;
    unsigned short RotaryPos(short position);
    char RotaryASCII(char sign);
public:
    //static const unsigned int BETA_POS = 8;
    //static const unsigned int GAMMA_POS = 9;
    static const unsigned int DICT_SIZE = 26;
    
    Rotor(RotorType type, unsigned int id);
    Rotor(RotorType type, unsigned int id, unsigned int position, unsigned int ringShift);
    Rotor(const Rotor& rotor);
    
    void setType(RotorType type);
    void autoRotate();
    void rotate(unsigned short newPosition);
    bool canNextRotate();
    char translate(char input, TranslateDirection direction);

    friend ostream& operator<<(ostream& os, const Rotor& rotor);
};

    

#endif /* ROTOR_HPP */

