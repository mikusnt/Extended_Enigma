/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rotor_tests.cpp
 * Author: MS-1
 *
 * Created on 14 lutego 2019, 17:47
 */

#include <stdlib.h>
#include <iostream>
#include "rotor.hpp"

/*
 * Simple C++ Test Suite
 */

void testTranslateIAALR() {
    Rotor *rotor = new Rotor(rotorTypeRegular, 1, 'A', 'A');
    char result;
    result = rotor->translate('a', directionLeft);
    if (result != 'E') {
        std::cout << "%TEST_FAILED% -------------------- regular I AA directionLeft with result=" << result << std::endl;
    }
    rotor->autoRotate();
    result = rotor->translate('a', directionLeft);
    if (result != 'J') {
       std::cout << "%TEST_FAILED% -------------------- regular I AB directionLeft with result=" << result << std::endl;
    }
    
    //delete rotor;
    //rotor = new Rotor(rotorTypeRegular, 1, 'A', 'A');
    rotor->autoRotate();
    result = rotor->translate('A', directionRight);
    if (result != 'W') {
        std::cout << "%TEST_FAILED% -------------------- regular I AC directionRight with result=" << result << std::endl;
    }
    rotor->autoRotate();
    result = rotor->translate('A', directionRight);
    if (result != 'D') {
       std::cout << "%TEST_FAILED% -------------------- regular I AD directionRight with result=" << result << std::endl;
    }
    delete rotor;
}

void testTranslateIBA() {
    TranslateDirection direction = directionLeft;
    Rotor rotor(rotorTypeRegular, 1, 'B', 'A');
    char result = rotor.translate('a', direction);
    if (result != 'K') {
        std::cout << "%TEST_FAILED% -------------------- regular I BA directionLeft with result=" << result << std::endl;
    } 
}

void testTranslateIFY() {
    TranslateDirection direction = directionLeft;
    Rotor rotor(rotorTypeRegular, 1, 'F', 'Y');
    char result = rotor.translate('a', direction);
    if (result != 'W') {
        std::cout << "%TEST_FAILED% -------------------- regular I FY directionLeft with result=" << result << std::endl;
    } 
}

void testTranslateRotate() {
    TranslateDirection direction = directionLeft;
    Rotor rotor(rotorTypeRegular, 1, 'A', 'Y');
    rotor.autoRotate();
    int position = rotor.getPosition();
    if (position != 26) {
        std::cout << "%TEST_FAILED% -------------------- regular I AY directionLeft with rotor position=" << position << std::endl;
    } 
    
    rotor.autoRotate();
    position = rotor.getPosition();
    if (position != 1) {
        std::cout << "%TEST_FAILED% -------------------- regular I AZ with rotor position=" << position << std::endl;
    } 
    
    rotor.autoRotate();
    position = rotor.getPosition();
    if (position != 2) {
        std::cout << "%TEST_FAILED% -------------------- regular I AA with rotor position=" << position << std::endl;
    } 
}

void testAlternateAllReflector() {
    char result0, result1;
    for (int j = 1; j <= Rotor::MAX_INPUT_REFLECTOR_ID; j++) {
        Rotor rotor(rotorTypeReflector, j, 'B', 'C');
        
        for (int i = 0; i < Rotor::DICT_SIZE; i++) {
            result0 = rotor.translate(i + 'A', directionLeft);
            result1 = rotor.translate(result0, directionLeft);
            if (result1 != (i + 'A')) {
                std::cout << "%TEST_FAILED% -------------------- reflector between " << char(i + 'A') << " and " << result0 << " with result=" << result1 << std::endl;
            }
        }
    }   
}

void testNoDiffReflector() {
    Rotor one(rotorTypeReflector, 3, 'C', 'F');
    Rotor two(rotorTypeReflector, 3, 1, 1);
    char resultOne, resultTwo;
    for(int i = 0; i < Rotor::DICT_SIZE; i++) {
        resultOne = one.translate(i, directionLeft);
        one.autoRotate();
        resultTwo = two.translate(i, directionRight);
        two.autoRotate();
        if (resultOne != resultTwo)
            std::cout << "%TEST_FAILED% -------------------- reflector 1 CF and 1 AA with results=" << resultOne << resultTwo << std::endl;
    }
}

void testTranslateReflector() {
    char result;
    Rotor refl(rotorTypeReflector, 1, 'A', 'A');
    result = refl.translate('N', directionRight);
    if (result != 'K')
        std::cout << "%TEST_FAILED% -------------------- reflector 'B' translate N with results=" << result << std::endl;
    
    Rotor refl2(rotorTypeReflector, 2, 'A', 'A');
    result = refl2.translate('O', directionRight);
    if (result != 'G')
        std::cout << "%TEST_FAILED% -------------------- reflector 'C' translate O with results=" << result << std::endl;
    
    Rotor refl3(rotorTypeReflector, 3, 'A', 'A');
    result = refl3.translate('P', directionRight);
    if (result != 'M')
        std::cout << "%TEST_FAILED% -------------------- reflector 'B thin' translate P with results=" << result << std::endl;
    
    Rotor refl4(rotorTypeReflector, 4, 'A', 'A');
    result = refl4.translate('Q', directionRight);
    if (result != 'Z')
        std::cout << "%TEST_FAILED% -------------------- reflector 'C thin' translate Q with results=" << result << std::endl;

}



int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTED% Rotor tests" << std::endl;

    std::cout << "%TEST_STARTED% testTranslate I AA left right (translate_tests)" << std::endl;
    testTranslateIAALR();
    std::cout << "%TEST_FINISHED% testTranslate I AA left right (translate_tests)" << std::endl;
    
    std::cout << "%TEST_STARTED% testTranslate I BA (translate_tests)" << std::endl;
    testTranslateIBA();
    std::cout << "%TEST_FINISHED% testTranslate I BA (translate_tests)" << std::endl;
    
    std::cout << "%TEST_STARTED% testTranslate I FY (translate_tests)" << std::endl;
    testTranslateIFY();
    std::cout << "%TEST_FINISHED% testTranslate I FY (translate_tests)" << std::endl;
    
    std::cout << "%TEST_STARTED% testTranslateIRotate (translate_tests)" << std::endl;
    testTranslateRotate();
    std::cout << "%TEST_FINISHED% testTranslateIRotate (translate_tests)" << std::endl;
    
    std::cout << "%TEST_STARTED% testAlternateAllReflector (reflector_tests)" << std::endl;
    testAlternateAllReflector();
    std::cout << "%TEST_FINISHED% testAlternateAllReflector (reflector_tests)" << std::endl;
    
    std::cout << "%TEST_STARTED% testNoDiffReflector (reflector_tests)" << std::endl;
    testNoDiffReflector();
    std::cout << "%TEST_FINISHED% testNoDiffReflector (reflector_tests)" << std::endl;
    
    std::cout << "%TEST_STARTED% testTranslateReflector (reflector_tests)" << std::endl;
    testTranslateReflector();
    std::cout << "%TEST_FINISHED% testTranslateReflector (reflector_tests)" << std::endl;

    std::cout << "%SUITE_FINISHED% Rotor tests" << std::endl;
    return (EXIT_SUCCESS);
}

