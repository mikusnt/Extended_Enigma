/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "enigma_reader.hpp"


EnigmaReader::EnigmaReader(string filename) {
    INIReader reader(filename);
    parseError = reader.ParseError();
    
    if (parseError < 0)
        return;
    string temp;
    stringstream concat;
    
    // plugboard
    temp = reader.GetString(PLUGBOARD, RULES, EMPTY);
    if (temp == EMPTY)
        return;
    
    for(int i=0; i<temp.length(); i++)
        if(temp[i] == ' ') temp.erase(i,1);
    
    plugboard.addConnect(temp[0], temp[1]);
    int commaPos = temp.find(",");
    while (commaPos != string::npos) {
        temp = temp.substr(commaPos+1);
         plugboard.addConnect(temp[0], temp[1]);
        commaPos = temp.find(",");  
    }
    
    // rotors
    for (int i = 0; temp != EMPTY; i++) {
        concat << ROTOR << i;
        temp = reader.GetString(concat.str(), TYPE, EMPTY);
        if (temp == EMPTY)
            return;
        
        RotorType type = rotorTypeRegular;
        if (temp == REGULAR)
            type = rotorTypeRegular;
        if (temp == REFLECTOR)
            type = rotorTypeReflector;
        
        
        temp = reader.GetString(concat.str(), ID, EMPTY);
        int id = 0;
        // TODO rename
        if (temp == BETA_ID)
            id = Rotor::BETA_ID;
        else if (temp == GAMMA_ID)
            id = Rotor::GAMMA_ID;
        else id = stoi(temp);
        
        // TODO rename 26 to dict size
        int position = reader.GetInteger(concat.str(), POSITION, 0) % 26;
        Rotor rotor(type, id, position);
        rotors.push_back(rotor);
        concat.clear();
    }
    
    rotors.back().setType(rotorTypeReflector);
    
}


