/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   enigma_tests.cpp
 * Author: MS-1
 *
 * Created on 14 lutego 2019, 19:24
 */

#include <stdlib.h>
#include <iostream>
#include "enigma.hpp"
#include "enigma_reader.hpp"
#include <exception>

/*
 * Simple C++ Test Suite
 */

void testRotateDS_KDO() {
    try {
        EnigmaReader reader("testRotateDS_KDO.ini");
        Plugboard plugboard = reader.getPlugboard();
        vector<Rotor> rotors = reader.getRotors();
        Enigma enigma(plugboard, rotors);
        
        string results;
        string positions;
        
        results = enigma.translate('A');
        positions = Rotor::getPositions(enigma.rotors);
        if (positions != "1(A) 11(K) 4(D) 16(P)") {
            std::cout << "%TEST_FAILED% -------------------- I KDO to I KDP on result=" << positions << std::endl;
        }
        
        results = enigma.translate('A');
        positions = Rotor::getPositions(enigma.rotors);
        if (positions != "1(A) 11(K) 4(D) 17(Q)") {
            std::cout << "%TEST_FAILED% -------------------- I KDP to I KDQ on result=" << positions << std::endl;
        }
        
        results = enigma.translate('A');
        positions = Rotor::getPositions(enigma.rotors);
        if (positions != "1(A) 11(K) 5(E) 18(R)") {
            std::cout << "%TEST_FAILED% -------------------- I KDQ to I KER on result=" << positions << std::endl;
        }
        
        results = enigma.translate('A');
        positions = Rotor::getPositions(enigma.rotors);
        if (positions != "1(A) 12(L) 6(F) 19(S)") {
            std::cout << "%TEST_FAILED% -------------------- I KER to I LFS on result=" << positions << std::endl;
        }
        
        results = enigma.translate('A');
        positions = Rotor::getPositions(enigma.rotors);
        if (positions != "1(A) 12(L) 6(F) 20(T)") {
            std::cout << "%TEST_FAILED% -------------------- I LFS to I LFT on result=" << positions << std::endl;
        }
        
        results = enigma.translate('A');
        positions = Rotor::getPositions(enigma.rotors);
        if (positions != "1(A) 12(L) 6(F) 21(U)") {
            std::cout << "%TEST_FAILED% -------------------- I LFT to I LFU on result=" << positions << std::endl;
        }
    } catch (exception& e) {
        
        std::cout << "%TEST_FAILED% -------------------- exception message=" << e.what() << std::endl;
    }
}

void testRotateDS_UDO() {
    try {
        EnigmaReader reader("testRotateDS_UDO.ini");
        Plugboard plugboard = reader.getPlugboard();
        vector<Rotor> rotors = reader.getRotors();
        Enigma enigma(plugboard, rotors);
        
        string results;
        string positions;
        
        results = enigma.translate('A');
        positions = Rotor::getPositions(enigma.rotors);
        if (positions != "1(A) 21(U) 4(D) 16(P)") {
            std::cout << "%TEST_FAILED% -------------------- I UDO to I UDP on result=" << positions << std::endl;
        }
        
        results = enigma.translate('A');
        positions = Rotor::getPositions(enigma.rotors);
        if (positions != "1(A) 21(U) 4(D) 17(Q)") {
            std::cout << "%TEST_FAILED% -------------------- I UDP to I UDQ on result=" << positions << std::endl;
        }
        
        results = enigma.translate('A');
        positions = Rotor::getPositions(enigma.rotors);
        if (positions != "1(A) 21(U) 5(E) 18(R)") {
            std::cout << "%TEST_FAILED% -------------------- I UDQ to I UER on result=" << positions << std::endl;
        }
        
        results = enigma.translate('A');
        positions = Rotor::getPositions(enigma.rotors);
        if (positions != "1(A) 22(V) 6(F) 19(S)") {
            std::cout << "%TEST_FAILED% -------------------- I UER to I VFS on result=" << positions << std::endl;
        }
        
        results = enigma.translate('A');
        positions = Rotor::getPositions(enigma.rotors);
        if (positions != "1(A) 22(V) 6(F) 20(T)") {
            std::cout << "%TEST_FAILED% -------------------- I VFS to I VFT on result=" << positions << std::endl;
        }
        
        results = enigma.translate('A');
        positions = Rotor::getPositions(enigma.rotors);
        if (positions != "1(A) 22(V) 6(F) 21(U)") {
            std::cout << "%TEST_FAILED% -------------------- I VFT to I VFU on result=" << positions << std::endl;
        }
    } catch (exception& e) {
        
        std::cout << "%TEST_FAILED% -------------------- exception message=" << e.what() << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTED% testRotate" << std::endl;

    std::cout << "%TEST_STARTED% testRotateDS_KDO (enigma_tests)" << std::endl;
    testRotateDS_KDO();
    std::cout << "%TEST_FINISHED% testRotateDS_KDO (enigma_tests)" << std::endl;
    
    std::cout << "%TEST_STARTED% testRotateDS_UDO (enigma_tests)" << std::endl;
    testRotateDS_UDO();
    std::cout << "%TEST_FINISHED% testRotateDS_UDO (enigma_tests)" << std::endl;

    std::cout << "%SUITE_FINISHED% testRotate" << std::endl;

    return (EXIT_SUCCESS);
}

