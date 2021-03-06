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

using namespace std;
using namespace enigma;
/*
 * Simple C++ Test Suite
 */

void testRotateDS_KDO() {
    try {
        EnigmaReader reader("tests/config/testRotateDS_KDO.ini");
        Enigma enigma(reader.getPlugboard(), reader.getRotors(), reader.getReflector());
        
        string results;
        string positions;
        
        results = enigma.translate('A');
        positions = enigma.getStringRotorsPosition();
        if (positions != "11(K) 4(D) 16(P)") {
            std::cout << "%TEST_FAILED% -------------------- I KDO to I KDP on result=" << positions << std::endl;
        }
        
        results = enigma.translate('A');
        positions = enigma.getStringRotorsPosition();
        if (positions != "11(K) 4(D) 17(Q)") {
            std::cout << "%TEST_FAILED% -------------------- I KDP to I KDQ on result=" << positions << std::endl;
        }
        
        results = enigma.translate('A');
        positions = enigma.getStringRotorsPosition();
        if (positions != "11(K) 5(E) 18(R)") {
            std::cout << "%TEST_FAILED% -------------------- I KDQ to I KER on result=" << positions << std::endl;
        }
        
        results = enigma.translate('A');
        positions = enigma.getStringRotorsPosition();
        if (positions != "12(L) 6(F) 19(S)") {
            std::cout << "%TEST_FAILED% -------------------- I KER to I LFS on result=" << positions << std::endl;
        }
        
        results = enigma.translate('A');
        positions = enigma.getStringRotorsPosition();
        if (positions != "12(L) 6(F) 20(T)") {
            std::cout << "%TEST_FAILED% -------------------- I LFS to I LFT on result=" << positions << std::endl;
        }
        
        results = enigma.translate('A');
        positions = enigma.getStringRotorsPosition();
        if (positions != "12(L) 6(F) 21(U)") {
            std::cout << "%TEST_FAILED% -------------------- I LFT to I LFU on result=" << positions << std::endl;
        }
    } catch (exception& e) {
        
        std::cout << "%TEST_FAILED% -------------------- exception message=" << e.what() << std::endl;
    }
}

void testRotateDS_UDO() {
    try {
        EnigmaReader reader("tests/config/testRotateDS_UDO.ini");
        Enigma enigma(reader.getPlugboard(), reader.getRotors(), reader.getReflector());

        
        string results;
        string positions;
        
        results = enigma.translate('A');
        positions = enigma.getStringRotorsPosition();
        if (positions != "21(U) 4(D) 16(P)") {
            std::cout << "%TEST_FAILED% -------------------- I UDO to I UDP on result=" << positions << std::endl;
        }
        
        results = enigma.translate('A');
        positions = enigma.getStringRotorsPosition();
        if (positions != "21(U) 4(D) 17(Q)") {
            std::cout << "%TEST_FAILED% -------------------- I UDP to I UDQ on result=" << positions << std::endl;
        }
        
        results = enigma.translate('A');
        positions = enigma.getStringRotorsPosition();
        if (positions != "21(U) 5(E) 18(R)") {
            std::cout << "%TEST_FAILED% -------------------- I UDQ to I UER on result=" << positions << std::endl;
        }
        
        results = enigma.translate('A');
        positions = enigma.getStringRotorsPosition();
        if (positions != "22(V) 6(F) 19(S)") {
            std::cout << "%TEST_FAILED% -------------------- I UER to I VFS on result=" << positions << std::endl;
        }
        
        results = enigma.translate('A');
        positions = enigma.getStringRotorsPosition();
        if (positions != "22(V) 6(F) 20(T)") {
            std::cout << "%TEST_FAILED% -------------------- I VFS to I VFT on result=" << positions << std::endl;
        }
        
        results = enigma.translate('A');
        positions = enigma.getStringRotorsPosition();
        if (positions != "22(V) 6(F) 21(U)") {
            std::cout << "%TEST_FAILED% -------------------- I VFT to I VFU on result=" << positions << std::endl;
        }
    } catch (exception& e) {
        
        std::cout << "%TEST_FAILED% -------------------- exception message=" << e.what() << std::endl;
    }
}

void testTranslateWehrmacht() {
    EnigmaReader reader("tests/config/wechrmacht.ini");
    if (!reader.wasParsed()) {
       std::cout << "%TEST_FAILED% -------------------- error on parsing file"  << std::endl; 
       return;
    }
    Enigma enigma(reader.getPlugboard(), reader.getRotors(), reader.getReflector());
    if (!enigma.wasInitialized()){
        std::cout << "%TEST_FAILED% -------------------- error on initializing enigma"  << std::endl; 
       return;  
    }
    
    string input = "QBLTWLDAHHYEOEFPTWYBLENDPMKOXLDFAMUDWIJDXRJZ";
    string outputP = "DERFUEHRERISTTODXDERKAMPFGEHTWEITERXDOENITZX";
    stringstream output;
    for (int i = 0; i < input.size(); i++) {
        output << enigma.translate(input[i]);
    }
    string outputS = output.str();
    for (int i = 0; i < input.size(); i++) {
        if (outputP[i] != outputS[i]) 
            std::cout << "%TEST_FAILED% -------------------- translation from " << input[i] << " to " << outputP[i] << " with result=" 
                    << outputS[i] << " at position " << enigma.getStringRotorsPosition() << std::endl;   
    }
    //cout << Enigma::groupString(input, 5) << endl; 
    //cout << Enigma::groupString(output.str(), 5) << endl;    
    
}

void testTranslateAShift() {
    EnigmaReader reader("tests/config/ashift.ini");
    if (!reader.wasParsed()) {
       std::cout << "%TEST_FAILED% -------------------- error on parsing file"  << std::endl; 
       return;
    }
    Enigma enigma(reader.getPlugboard(), reader.getRotors(), reader.getReflector());
    if (!enigma.wasInitialized()){
        std::cout << "%TEST_FAILED% -------------------- error on initializing enigma"  << std::endl; 
       return;  
    }
    stringstream output;
    string outputP = "DZGOWCXLTKSBTMCDLPBMFQOFXYHCXT";
    for (int i = 0; i < outputP.size(); i++) {
        //cout << enigma.getStringRotorsPosition() << endl;
        char temp = enigma.translate('A');
        output << temp;
        if (outputP[i] != temp) 
            std::cout << "%TEST_FAILED% -------------------- translation from 'A' to " << outputP[i] << " with result=" 
                    << temp << " at position " << enigma.getStringRotorsPosition() << std::endl;  
    }  
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTED% Enigma tests" << std::endl;

    std::cout << "%TEST_STARTED% testRotateDS_KDO (rotate_tests)" << std::endl;
    testRotateDS_KDO();
    std::cout << "%TEST_FINISHED% testRotateDS_KDO (rotate_tests)" << std::endl;
    
    std::cout << "%TEST_STARTED% testRotateDS_UDO (rotate_tests)" << std::endl;
    testRotateDS_UDO();
    std::cout << "%TEST_FINISHED% testRotateDS_UDO (rotate_tests)" << std::endl;
    
    std::cout << "%TEST_STARTED% testTranslateWehrmacht (rotate_tests)" << std::endl;
    testTranslateWehrmacht();
    std::cout << "%TEST_FINISHED% testTranslateWehrmacht (rotate_tests)" << std::endl;
    
    std::cout << "%TEST_STARTED% testTranslateAShift (rotate_tests)" << std::endl;
    testTranslateAShift();
    std::cout << "%TEST_FINISHED% testTranslateAShift (rotate_tests)" << std::endl;

    std::cout << "%SUITE_FINISHED% Enigma tests" << std::endl;

    return (EXIT_SUCCESS);
}

