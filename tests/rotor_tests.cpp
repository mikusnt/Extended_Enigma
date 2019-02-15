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

void testTranslateIAA() {
    TranslateDirection direction = directionLeft;
    Rotor rotor(rotorTypeRegular, 1, 'A', 'A');
    char result = rotor.translate('a', direction);
    if (result != 'E') {
        std::cout << "%TEST_FAILED% -------------------- regular I AA with result=" <<result << std::endl;
    }
    rotor.autoRotate();
    result = rotor.translate('a', direction);
    if (result != 'J') {
       std::cout << "%TEST_FAILED% -------------------- regular I AB with result=" << result << std::endl;
    }   
}

void testTranslateIBA() {
    TranslateDirection direction = directionLeft;
    Rotor rotor(rotorTypeRegular, 1, 'B', 'A');
    char result = rotor.translate('a', direction);
    if (result != 'K') {
        std::cout << "%TEST_FAILED% -------------------- regular I BA with result=" <<result << std::endl;
    } 
}

void testTranslateIFY() {
    TranslateDirection direction = directionLeft;
    Rotor rotor(rotorTypeRegular, 1, 'F', 'Y');
    char result = rotor.translate('a', direction);
    if (result != 'W') {
        std::cout << "%TEST_FAILED% -------------------- regular I FY with result=" <<result << std::endl;
    } 
}

void testTranslateRotate() {
    TranslateDirection direction = directionLeft;
    Rotor rotor(rotorTypeRegular, 1, 'A', 'Y');
    rotor.autoRotate();
    int position = rotor.getPosition();
    if (position != 25) {
        std::cout << "%TEST_FAILED% -------------------- regular I AY with rotor position=" <<position << std::endl;
    } 
    
    rotor.autoRotate();
    position = rotor.getPosition();
    if (position != 0) {
        std::cout << "%TEST_FAILED% -------------------- regular I AZ with rotor position=" <<position << std::endl;
    } 
    
    rotor.autoRotate();
    position = rotor.getPosition();
    if (position != 1) {
        std::cout << "%TEST_FAILED% -------------------- regular I AA with rotor position=" <<position << std::endl;
    } 
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTED% rotor_tests" << std::endl;

    std::cout << "%TEST_STARTED% testTranslate I AA (rotor_tests)" << std::endl;
    testTranslateIAA();
    std::cout << "%TEST_FINISHED% testTranslate I AA(rotor_tests)" << std::endl;
    
    std::cout << "%TEST_STARTED% testTranslate I BA (rotor_tests)" << std::endl;
    testTranslateIBA();
    std::cout << "%TEST_FINISHED% testTranslate I BA (rotor_tests)" << std::endl;
    
    std::cout << "%TEST_STARTED% testTranslate I FY (rotor_tests)" << std::endl;
    testTranslateIFY();
    std::cout << "%TEST_FINISHED% testTranslate I FY (rotor_tests)" << std::endl;
    
    std::cout << "%TEST_STARTED% testTranslateIRotate (rotor_tests)" << std::endl;
    testTranslateRotate();
    std::cout << "%TEST_FINISHED% testTranslateIRotate (rotor_tests)" << std::endl;

    std::cout << "%SUITE_FINISHED% rotor_tests" << std::endl;
    return (EXIT_SUCCESS);
}

