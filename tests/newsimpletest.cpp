/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newsimpletest.cpp
 * Author: MS-1
 *
 * Created on 7 lutego 2019, 19:54
 */

#include <stdlib.h>
#include <iostream>
#include "rotor.hpp"

/*
 * Simple C++ Test Suite
 */

void testRotor() {
    RotorType type;
    unsigned int id;
    Rotor rotor(type, id);
    if (true /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testRotor (newsimpletest) message=error message sample" << std::endl;
    }
}

void testRotor2() {
    RotorType type;
    unsigned int id;
    unsigned int newPosition;
    Rotor rotor(type, id, newPosition);
    if (true /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testRotor2 (newsimpletest) message=error message sample" << std::endl;
    }
}

void testRotor3() {
    const Rotor& rotor;
    Rotor rotor(rotor);
    if (true /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testRotor3 (newsimpletest) message=error message sample" << std::endl;
    }
}

void testRotate() {
    Rotor rotor;
    rotor.rotate();
    if (true /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testRotate (newsimpletest) message=error message sample" << std::endl;
    }
}

void testRotate2() {
    unsigned int newPosition;
    Rotor rotor;
    rotor.rotate(newPosition);
    if (true /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testRotate2 (newsimpletest) message=error message sample" << std::endl;
    }
}

void testCanNextRotate() {
    Rotor rotor;
    bool result = rotor.canNextRotate();
    if (true /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testCanNextRotate (newsimpletest) message=error message sample" << std::endl;
    }
}

void testTranslate() {
    char input;
    TranslateDirection direction;
    Rotor rotor;
    char result = rotor.translate(input, direction);
    if (true /*check result*/) {
        std::cout << "%TEST_FAILED% time=0 testname=testTranslate (newsimpletest) message=error message sample" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% newsimpletest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testRotor (newsimpletest)" << std::endl;
    testRotor();
    std::cout << "%TEST_FINISHED% time=0 testRotor (newsimpletest)" << std::endl;

    std::cout << "%TEST_STARTED% testRotor2 (newsimpletest)" << std::endl;
    testRotor2();
    std::cout << "%TEST_FINISHED% time=0 testRotor2 (newsimpletest)" << std::endl;

    std::cout << "%TEST_STARTED% testRotor3 (newsimpletest)" << std::endl;
    testRotor3();
    std::cout << "%TEST_FINISHED% time=0 testRotor3 (newsimpletest)" << std::endl;

    std::cout << "%TEST_STARTED% testRotate (newsimpletest)" << std::endl;
    testRotate();
    std::cout << "%TEST_FINISHED% time=0 testRotate (newsimpletest)" << std::endl;

    std::cout << "%TEST_STARTED% testRotate2 (newsimpletest)" << std::endl;
    testRotate2();
    std::cout << "%TEST_FINISHED% time=0 testRotate2 (newsimpletest)" << std::endl;

    std::cout << "%TEST_STARTED% testCanNextRotate (newsimpletest)" << std::endl;
    testCanNextRotate();
    std::cout << "%TEST_FINISHED% time=0 testCanNextRotate (newsimpletest)" << std::endl;

    std::cout << "%TEST_STARTED% testTranslate (newsimpletest)" << std::endl;
    testTranslate();
    std::cout << "%TEST_FINISHED% time=0 testTranslate (newsimpletest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

