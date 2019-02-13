/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include <regex>
#include <fstream>

#include "enigma_reader.hpp"

unsigned int EnigmaDicts::idMap(const string map[], string value) {
    int length;
    if (map == regularIDMap)
        length = sizeof(regularIDMap)/sizeof(regularIDMap[0]);
    if (map == reflectorIDMap)
        length = sizeof(reflectorIDMap)/sizeof(reflectorIDMap[0]);
    if (map == rotorTypeMap)
        length = sizeof(rotorTypeMap)/sizeof(rotorTypeMap[0]);
    
    
    for (int i = 0; i < length; i++) {
        if (map[i] == value)
            return i;
    }
    return EnigmaDicts::end;
}

EnigmaReader::EnigmaReader(string filename) {
    INIReader reader(filename);
    parseError = reader.ParseError();
    
    if (reader.ParseError() < 0)
        throw invalid_argument("Error on parsing file");
    string temp;
    
    // plugboard
    temp = reader.GetString(PLUGBOARD, RULES, EMPTY);
    if (temp == EMPTY) {
        throw invalid_argument("no plugboard found");
    }
    
    
    
    for(int i=0; i<temp.length(); i++)
        if(temp[i] == ' ') temp.erase(i,1);
    
    plugboard.addConnect(temp[0], temp[1]);
    int commaPos = temp.find(",");
    while (commaPos != string::npos) {
        temp = temp.substr(commaPos+1);
        if (!plugboard.addConnect(temp[0], temp[1])) {
            throw invalid_argument("error on parsing plugboard rules");
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
        EnigmaDicts dicts;
        type = (RotorType)dicts.idMap(dicts.rotorTypeMap, temp);
        if (type == EnigmaDicts::end)
            throw invalid_argument("bad rotor type");    
        
        temp = reader.GetString(concat.str(), ID, EMPTY);
        int id = 0;
        if (type == rotorTypeRegular) {
            id = dicts.idMap(dicts.regularIDMap, temp);
            if (id == EnigmaDicts::end)
                throw invalid_argument("bad regular rotor id");
        }
        
        if (type == rotorTypeReflector) {
            id = dicts.idMap(dicts.reflectorIDMap, temp);
            if (id == EnigmaDicts::end)
                throw invalid_argument("ebad reflector rotor id");
        }
        
        int ringShift = reader.GetInteger(concat.str(), RING_SHIFT, 0 % Rotor::DICT_SIZE);
        int position = reader.GetInteger(concat.str(), POSITION, 0) % Rotor::DICT_SIZE;
        
        Rotor rotor(type, id, position, ringShift);
        rotors.push_back(rotor);
        concat.str("");
    }
    rotors.back().setType(rotorTypeReflector);
    
}

void EnigmaReader::writeDefaultFile(string filename) {
    fstream file;
    file.open(filename, ios::out);
    if (file.is_open()) {
        file << "[plugboard]\nrules = AC, BG, TU\n\n";
        file << "[rotor_0]\ntype = reflector\nid = C_thin\n\n";
        file << "[rotor_1]\ntype = regular\nid = VII\nposition = 25\n\n";
        
        file.close();
    } else {
    }
}


Plugboard EnigmaReader::getPlugboard() {
    return plugboard;
}

vector<Rotor> EnigmaReader::getRotors() {
    return rotors;
}


