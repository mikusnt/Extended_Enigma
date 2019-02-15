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


using namespace std;

int main(int argc, char** argv) {
    const string FILENAME = "enigma.ini";
    const string DEFAULT_FILENAME = "default.ini";
    EnigmaReader reader;

    if (!reader.tryParseFile("enigma.ini")) {
        cout << "Cannot parse " << FILENAME << ", trying with " << DEFAULT_FILENAME << endl;
        EnigmaReader::writeDefaultFile("default.ini");
        reader.tryParseFile("default.ini");
    }
    
    if (reader.wasParsed()) {
        Plugboard plugboard = reader.getPlugboard();
        vector<Rotor> rotors = reader.getRotors();

        cout << "Translation on plugboard:\n";
        cout << plugboard << "\n\n";

        cout << "Rotors settings: \n";
        for(int i = 0; i < rotors.size(); i++) {
            cout << rotors[i] << endl;
        }
    } else {
        cout << "Error on parsing " << FILENAME << " and later " << DEFAULT_FILENAME << endl;
    }
    return 0;
}

