/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "enigma_reader.hpp"

const string EnigmaReader::REGULAR = "regular";
const string EnigmaReader::REFLECTOR = "reflector";
const string EnigmaReader::BETA = "beta";
const string EnigmaReader::GAMMA = "gamma";

EnigmaReader::EnigmaReader(string filename) {
    INIReader reader(filename);
    parseError = reader.ParseError();
    
    if (parseError < 0)
        return;
    string temp;
    
    // plugboard
    temp = reader.GetString(PLUGBOARD, RULES, EMPTY);
    if (temp == EMPTY) {
        parseError = -1;
        return;
    }
    
    
    
    for(int i=0; i<temp.length(); i++)
        if(temp[i] == ' ') temp.erase(i,1);
    
    plugboard.addConnect(temp[0], temp[1]);
    int commaPos = temp.find(",");
    while (commaPos != string::npos) {
        temp = temp.substr(commaPos+1);
        if (!plugboard.addConnect(temp[0], temp[1])) {
            parseError = -1;
            return;
        }
        commaPos = temp.find(",");  
    }
    
    stringstream concat;
    // rotors
    for (int i = 0; temp != EMPTY; i++) {
        concat << ROTOR << i;
        temp = reader.GetString(concat.str(), TYPE, EMPTY);
        if (temp == EMPTY)
            break;
        
        RotorType type = rotorTypeRegular;
        if (temp == REGULAR)
            type = rotorTypeRegular;
        if (temp == REFLECTOR)
            type = rotorTypeReflector;
        
        
        temp = reader.GetString(concat.str(), ID, EMPTY);
        int id = 0;
        if (temp == BETA)
            id = Rotor::BETA_POS;
        else if (temp == GAMMA)
            id = Rotor::GAMMA_POS;
        else id = stoi(temp);

        int position = reader.GetInteger(concat.str(), POSITION, 0) % Rotor::DICT_SIZE;
        Rotor rotor(type, id, position);
        rotors.push_back(rotor);
        concat.str("");
    }
    
    rotors.back().setType(rotorTypeReflector);
    
}

Plugboard EnigmaReader::getPlugboard() {
    return plugboard;
}

vector<Rotor> EnigmaReader::getRotors() {
    return rotors;
}


