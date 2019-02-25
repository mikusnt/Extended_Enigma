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

namespace enigma {
    typedef enum {
        rotorTypeRegular = 0,
        rotorTypeReflector = 1     
    } RotorType;

    typedef enum {
        directionLeft = 0,
        directionRight = 1
    } TranslateDirection;

    typedef enum {
        RegularID_I = 0,
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

    typedef enum {
       ReflectorID_B = 0,
       ReflectorID_C,
       ReflectorID_Bthin,
       ReflectorID_Cthin
    } ReflectorRotorId; 
        
    class Rotor {
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
        static const int DICT_SIZE = 26;
        static const char ERROR_CHAR = 'X';

        Rotor();
        Rotor(const Rotor& rotor);
        virtual ~Rotor() {}

        bool wasInitialized() const { return initialized; }
        int getId() const { return id; }
        int getPosition() const { return denormalizePosition(position); }
        std::string getStringPosition() const { return getStringFromAddr(position); }
        int getRingShift() const { return denormalizePosition(ringShift); }
        std::string getStringRingShift() const { return getStringFromAddr(ringShift); }

        virtual void rotate(int newPosition) = 0;
        virtual void rotateBy(int move) = 0;
        virtual bool canNextRotate(const Rotor& nextRotor) = 0;
        virtual void autoRotate() = 0;

        virtual RotorType getType() const = 0;
        virtual char translate(char input, TranslateDirection direction = directionLeft) = 0;
    };

    class RegularRotor : public Rotor {
    private:
        std::map<std::string, RegularRotorId> translator = {
            {"i", RegularID_I},
            {"ii", RegularID_II},
            {"iii", RegularID_III},
            {"iv", RegularID_IV},
            {"v", RegularID_V},
            {"vi", RegularID_VI},
            {"vii", RegularID_VII},
            {"viii", RegularID_VIII},
            {"beta", RegularID_BETA},
            {"gamma", RegularID_GAMMA}
        };

        std::map<RegularRotorId, std::string> translatorReversed = {
            {RegularID_I, "I"},
            {RegularID_II, "II"},
            {RegularID_III, "III"},
            {RegularID_IV, "IV"},
            {RegularID_V, "V"},
            {RegularID_VI, "VI"},
            {RegularID_VII, "VII"},
            {RegularID_VIII, "VIII"},
            {RegularID_BETA, "beta"},
            {RegularID_GAMMA, "gamma"}
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
        RegularRotor(std::string idS, int ringShift = 1, int position = 1);
        
        ~RegularRotor() {}
        RegularRotorId getId() const { return (RegularRotorId)id; }
        void rotate(int newPosition) override; 
        void rotateBy(int move) override;
        bool canNextRotate(const Rotor& nextRotor) override;
        void autoRotate() override;

        RotorType getType() const override { return rotorTypeRegular; }
        char translate(char input, TranslateDirection direction = directionLeft) override;

        std::string toString() const;
    };

    class ReflectorRotor : public Rotor {
    private:
        std::map<std::string, ReflectorRotorId> translator = {
            {"b", ReflectorID_B},
            {"c", ReflectorID_C},
            {"b_thin", ReflectorID_Bthin},
            {"c_thin", ReflectorID_Cthin}
        };

        std::map<ReflectorRotorId, std::string> translatorReversed = {
            {ReflectorID_B, "B"},
            {ReflectorID_C, "C"},
            {ReflectorID_Bthin, "B_thin"},
            {ReflectorID_Cthin, "C_thin"}
        };

        const std::string DICT[4] = { 
            "YRUHQSLDPXNGOKMIEBFZCWVJAT", 
            "FVPJIAOYEDRZXWGCTKUQSBNMHL", 
            "ENKQAUYWJICOPBLMDXZVFTHRGS", 
            "RDOBJNTKVEHMLFCWZAXGYIPSUQ"
        };
    public:  
        ReflectorRotor();
        ReflectorRotor(ReflectorRotorId id);
        ReflectorRotor(std::string idS);

        ~ReflectorRotor() {}
        ReflectorRotorId getId() const { return (ReflectorRotorId)id; }
        void rotate(int newPosition) override {}
        void rotateBy(int move) override {}
        bool canNextRotate(const Rotor& nextRotor) override { return false; }
        void autoRotate() override {}

        RotorType getType() const override { return rotorTypeReflector; }
        char translate(char input, TranslateDirection direction = directionLeft) override;

        std::string toString() const;
        
        ReflectorRotor& operator=(const ReflectorRotor& rotor) {
            this->id = rotor.id;
            this->position = rotor.position;
            this->ringShift = rotor.ringShift;
            this->initialized = rotor.initialized;
            return *this;
        }
    };
}

#endif /* OBJ_ROTOR_HPP */

