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

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTED% plugboard_tests" << std::endl;

    std::cout << "%TEST_STARTED% addRules (plugboard_tests)" << std::endl;
    addRules();
    std::cout << "%TEST_FINISHED% addRules (plugboard_tests)" << std::endl;
    
    std::cout << "%TEST_STARTED% removeConnect (plugboard_tests)" << std::endl;
    removeConnect();
    std::cout << "%TEST_FINISHED% removeConnect (plugboard_tests)" << std::endl;

    std::cout << "%SUITE_FINISHED% plugboard_tests" << std::endl;

    return (EXIT_SUCCESS);
}

