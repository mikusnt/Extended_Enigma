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
    const string ROTOR_DICT[10][2] = {{ "EKMFLGDQVZNTOWYHXUSPAIBRCJ", "UWYGADFPVZBECKMTHXSLRINQOJ" },
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
    const unsigned int DICT_SIZE =  26;
    const string ROTOR_POS[8] = {"R", "F", "W", "K", "A", "AN", "AN", "AN"};
    const unsigned int BETA_POS = 8;
    const unsigned int GAMMA_POS = 9;
    const char ERROR_CHAR = 'X';

    RotorType type;
    unsigned int id;
    unsigned int shift;
public:
    Rotor(RotorType type, unsigned int id);
    Rotor(RotorType type, unsigned int id, unsigned int newPosition);
    Rotor(const Rotor& rotor);
    
    void rotate();
    void rotate(unsigned int newPosition);
    bool canNextRotate();
    char translate(char input, TranslateDirection direction);
};

#endif /* ROTOR_HPP */

