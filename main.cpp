/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Mikolaj Stankowiak
 *
 * Created on 7 lutego 2019, 11:22
 */

#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <exception>
#include <fstream>
#include "enigma.hpp"
#include "enigma_reader.hpp"
#include "rotor.hpp"


using namespace std;
using namespace enigma;

int main(int argc, char** argv) {
     vector<enigma::Rotor> rotors;
    const string FILENAME = "enigma.ini";
    const string DEFAULT_FILENAME = "default.ini";
    EnigmaReader reader;

    if (!reader.tryParseFile("enigma.ini")) {
        cout << "Cannot parse " << FILENAME << ", trying with " << DEFAULT_FILENAME << endl;
        EnigmaReader::writeDefaultFile("default.ini");
        reader.tryParseFile("default.ini");
    }
    
    if (!reader.wasParsed()) {
        cout << "Error on parsing " << FILENAME << " and later " << DEFAULT_FILENAME << endl;
        return EXIT_FAILURE;
    } 
    cout << "Data parsed from " << reader.getFilename() << endl;
    //cout << reader << endl;
    Enigma enigma(reader.getPlugboard(), reader.getRotors(), reader.getReflector());
    if (!enigma.wasInitialized()) {
        cout << "Error on validating arguments on initializing enigma\n";
        return EXIT_FAILURE;
    }
        
    cout << enigma << endl;
//    
//    char sign = 0;
//    while (sign != 27) {
//        sign = getch();
//        if (sign == 27)
//            continue;
//        if ((sign >= '2') && (sign <= '5')) 
//            enigma.rotateBy(sign - '2' + 2, 1);
//        else if ((sign >= '6') && (sign <= '9')) 
//            enigma.rotateBy(sign - '6' + 2, -1);
//        else {
//            cout << "----------------------- " << sign << " -> " << enigma.translate(sign) << endl; 
//        }
//                  
//        cout << "New positions of rotors: " << endl;
//        cout << enigma.getStringRotorsPosition() << endl;
//    }   
    return 0;
}

