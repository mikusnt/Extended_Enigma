/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   plugboard_tests.cpp
 * Author: MS-1
 *
 * Created on 16 lutego 2019, 21:50
 */

#include <stdlib.h>
#include <iostream>

#include "plugboard.hpp"

using namespace std;
using namespace enigma;
/*
 * Simple C++ Test Suite
 */

void addRules() {
    Plugboard plugboard("PO, ML, IU, KJ, NH, YT, GB, VF, RE, DC");
    if (!plugboard.wasLoadedRules())
        std::cout << "%TEST_FAILED% -------------------- failure on load rules 'PO ML IU KJ NH YT GB VF RE DC'" << std::endl;
    char result;
    result = plugboard.translate('P');
    if (result != 'O')
        std::cout << "%TEST_FAILED% -------------------- translate P on 'PO ML IU KJ NH YT GB VF RE DC' with result=" << result << std::endl;
    
    result = plugboard.translate('V');
    if (result != 'F')
        std::cout << "%TEST_FAILED% -------------------- translate V on 'PO ML IU KJ NH YT GB VF RE DC' with result=" << result << std::endl;
    
    result = plugboard.translate('D');
    if (result != 'C')
        std::cout << "%TEST_FAILED% -------------------- translate D on 'PO ML IU KJ NH YT GB VF RE DC' with result=" << result << std::endl;

}

void removeConnect() {
    Plugboard plugboard("PO, ML, IU, KJ, NH, YT, GB, VF, RE, DC");
    plugboard.removeConnect('Y');
    char result;
    result = plugboard.translate('Y');
    if (result != 'Y')
        std::cout << "%TEST_FAILED% -------------------- translate Y on 'PO ML IU KJ NH YT GB VF RE DC' after del 'YT' with result=" << result << std::endl;
    
    result = plugboard.translate('T');
    if (result != 'T')
        std::cout << "%TEST_FAILED% -------------------- translate T on 'PO ML IU KJ NH YT GB VF RE DC' after del 'YT' with result=" << result << std::endl;
}

void validateArgument() {
    Plugboard plugboard("PO; ML; IU; KJ; NH; YT; GB; VF; RE; DC");
    if (!plugboard.wasLoadedRules()) {
        std::cout << "%TEST_FAILED% -------------------- rules 'PO; ML; IU; KJ; NH; YT; GB; VF; RE; DC' with error on load" << std::endl;
    }
    plugboard.clear();
    plugboard.loadRules("POMLIUKJNHYTGBVFREDC");
    if (!plugboard.wasLoadedRules()) {
        std::cout << "%TEST_FAILED% -------------------- rules 'POMLIUKJNHYTGBVFREDC' with error on load" << std::endl;
    }
    
    plugboard.clear();
    plugboard.loadRules("PO ML IU KJ NH YT G VF RE DC");
    if (plugboard.wasLoadedRules()) {
        std::cout << "%TEST_FAILED% -------------------- rules 'PO ML IU KJ NH YT G VF RE DC' without error on load" << std::endl;
    }
}

void originalOnError() {
    Plugboard plugboard("AB");
    plugboard.loadRules("ASDA");
    if (plugboard.getDict() != "BACDEFGHIJKLMNOPQRSTUVWXYZ") {
        std::cout << "%TEST_FAILED% -------------------- with error loaded only part of rules" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTED% plugboard_tests" << std::endl;

    std::cout << "%TEST_STARTED% addRules (plugboard_tests)" << std::endl;
    addRules();
    std::cout << "%TEST_FINISHED% addRules (plugboard_tests)" << std::endl;
    
    std::cout << "%TEST_STARTED% removeConnect (plugboard_tests)" << std::endl;
    removeConnect();
    std::cout << "%TEST_FINISHED% removeConnect (plugboard_tests)" << std::endl;
    
    std::cout << "%TEST_STARTED% validateArgument (plugboard_tests)" << std::endl;
    validateArgument();
    std::cout << "%TEST_FINISHED% validateArgument (plugboard_tests)" << std::endl;
    
    std::cout << "%TEST_STARTED% originalOnError (plugboard_tests)" << std::endl;
    originalOnError();
    std::cout << "%TEST_FINISHED% originalOnError (plugboard_tests)" << std::endl;

    std::cout << "%SUITE_FINISHED% plugboard_tests" << std::endl;

    return (EXIT_SUCCESS);
}

