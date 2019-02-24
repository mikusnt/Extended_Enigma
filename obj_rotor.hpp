/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   obj_rotor.hpp
 * Author: MS-1
 *
 * Created on 24 lutego 2019, 11:52
 */

#ifndef OBJ_ROTOR_HPP
#define OBJ_ROTOR_HPP

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <sstream>

class oRotor {
protected:
    int id;
    bool initialized;
        
    int ringShift;
    int position;
    
    static int rotaryPos(int position);
    static char rotaryASCII(char sign);
    static int normalizePosition(int value);
    static int denormalizePosition(int value);
    static std::string getStringFromAddr(int value);
public:
    typedef enum {
        rotorTypeRegular = 0,
        rotorTypeReflector = 1     
    } RotorType;
    
    typedef enum {
        directionLeft = 0,
        directionRight = 1
    } TranslateDirection;
    static const int DICT_SIZE = 26;
    static const char ERROR_CHAR = 'X';
    
    oRotor() {}
    virtual ~oRotor() {}
    
    bool wasInitialized() const { return initialized; }
    int getId() const { return id; }
    int getPosition() const { return position; }
    std::string getStringPosition() const { return getStringFromAddr(position); }
    int getRingShift() const { return ringShift; }
    std::string getStringRingShift() const { return getStringFromAddr(ringShift); }
    
    virtual void rotate(int newPosition) = 0;
    virtual void rotateBy(int move) = 0;
    virtual bool canNextRotate(const oRotor& nextRotor) = 0;
    virtual void autoRotate() = 0;
    
    virtual RotorType getType() const = 0;
    virtual char translate(char input, TranslateDirection direction = directionLeft) = 0;
};

class RegularRotor : public oRotor {
private:
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
    } RegularRotorId;
    
    std::map<std::string, RegularRotorId> translator = {
        {"i", RegularID_I},
        {"ii", RegularID_II},
        {"iii", RegularID_III},
        {"iv", RegularID_IV},
        {"v", RegularID_V},
        {"vi", RegularID_VI},
        {"vii", RegularID_VII},
        {"viii", RegularID_VIII},
        {"beta", RegularID_GAMMA},
        {"gamma", RegularID_GAMMA}
    };
    
    const std::string DICT[10][2] = {
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
    const std::string CHANGE_POS[8] = {"Q", "E", "V", "J", "Z", "ZM", "ZM", "ZM"};
public:
    RegularRotor(RegularRotorId id, int ringShift = 1, int position = 1);
    ~RegularRotor() {}
    void rotate(int newPosition) override; 
    void rotateBy(int move) override;
    bool canNextRotate(const oRotor& nextRotor) override;
    void autoRotate() override;

    RotorType getType() const override { return rotorTypeRegular; }
    char translate(char input, TranslateDirection direction = directionLeft) override;
};

class ReflectorRotor : public oRotor {
private:
    typedef enum {
       ReflectorID_B = 1,
       ReflectorID_C,
       ReflectorID_Bthin,
       ReflectorID_Cthin
    } ReflectorRotorId;   
    
    std::map<std::string, ReflectorRotorId> translator = {
        {"b", ReflectorID_B},
        {"c", ReflectorID_C},
        {"b_thin", ReflectorID_Bthin},
        {"c_thin", ReflectorID_Cthin}
    };
    
    const std::string DICT[4] = { 
        "YRUHQSLDPXNGOKMIEBFZCWVJAT", 
        "FVPJIAOYEDRZXWGCTKUQSBNMHL", 
        "ENKQAUYWJICOPBLMDXZVFTHRGS", 
        "RDOBJNTKVEHMLFCWZAXGYIPSUQ"
    };
public:
    ReflectorRotor(ReflectorRotorId id);
    ~ReflectorRotor() {}
    void rotate(int newPosition) override {}
    void rotateBy(int move) override {}
    bool canNextRotate(const oRotor& nextRotor) override { return false; }
    void autoRotate() override {}

    RotorType getType() const override { return rotorTypeReflector; }
    char translate(char input, TranslateDirection direction = directionLeft) override;

};

#endif /* OBJ_ROTOR_HPP */

