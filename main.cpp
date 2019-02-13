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
#include "rotor.hpp"
#include "plugboard.hpp"
#include "enigma_reader.hpp"


using namespace std;

int main(int argc, char** argv) {
    EnigmaReader *reader;
    try {
        //EnigmaReader::writeDefaultFile("new.ini");
        reader = new EnigmaReader("enigma.ini");
    } catch (exception& e) {
        cout << e.what() << endl;     
    }
    
    Plugboard plugboard = reader->getPlugboard();
    vector<Rotor> rotors = reader->getRotors();
    
    cout << "Translation on plugboard:\n";
    cout << plugboard << "\n\n";
    
    cout << "Rotors settings: \n";
    for(int i = 0; i < rotors.size(); i++) {
        cout << rotors[i] << endl;
    }
    delete reader;
    return 0;
}

