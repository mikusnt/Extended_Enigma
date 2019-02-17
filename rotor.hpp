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
#include <sstream>
#include <exception>

using namespace std;

typedef enum {
    rotorTypeRegular = 0,
    rotorTypeReflector = 1     
} RotorType;

typedef enum {
    directionLeft = 0,
    directionRight = 1
} TranslateDirection;

typedef enum {
    RegularID_I = 1,
    RegularID_II,
    RegularID_III,
    RegularID_IV,
    RegularID_V,
    RegularID_VI,
    RegularID_VII,
    RegularID_VIII,
    RegularID_BETA,
    RegularID_GAMMA
} RotorRegularId;

typedef enum {
    ReflectorID_B = 1,
    ReflectorID_C,
    ReflectorID_Bthin,
    ReflectorID_Cthin
} RotorReflectorId;

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
    unsigned short rotaryPos(short position);
    char rotaryASCII(char sign);
    int normalizePosition(int value);
    int denormalizePosition(int value) const;
    string getStringFromAddr(int value) const;
    bool initialized;
public:
    static const int MAX_INPUT_REFLECTOR_ID = 4;
    static const int DICT_SIZE = 26;
    
    Rotor(RotorType type, int id);
    Rotor(RotorType type, int id, int ringShift, int position);
    Rotor(const Rotor& rotor);
    bool wasInitialized() const { return initialized; }
    
    int getPosition() const { return denormalizePosition(position); }
    void rotate(unsigned short newPosition);
    bool canNextRotate(const Rotor& nextRotor);
    string getStringPosition() const { return getStringFromAddr(position); }
    
    int getRingShift() const { return denormalizePosition(ringShift); }
    string getStringRingShift() const { return getStringFromAddr(ringShift); }
    
    RotorType getType() const { return type; };
    int getId() const { return denormalizePosition(id); };
    void setType(RotorType type);
    void autoRotate();
    char translate(char input, TranslateDirection direction);


    friend ostream& operator<<(ostream& os, const Rotor& rotor);
};

    

#endif /* ROTOR_HPP */

