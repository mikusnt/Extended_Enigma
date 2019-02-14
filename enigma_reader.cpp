/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include <fstream>
#include <sstream>

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

unsigned int EnigmaReader::parsePosition(string pos) {
    unsigned int output = 0;
    char first = toupper(pos[0]);
    if ((first >= 'A') && (first <= 'Z')) {
        output = first - 'A' + 1;
    } else {
        stringstream conv(pos);
        conv >> output;
        while (output > (Rotor::DICT_SIZE)) output -= Rotor::DICT_SIZE;
        while (output < 1) output += Rotor::DICT_SIZE;
    }
    return output;
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
    int rotorLimit = 4;
    // rotors
    int i;
    for (i = 0; (temp != EMPTY) && (i < rotorLimit); i++) {
        concat << ROTOR << i;
        temp = reader.GetString(concat.str(), TYPE, EMPTY);
        if (temp == EMPTY)
            break;
        
        RotorType type = rotorTypeRegular;
        EnigmaDicts dicts;
        type = (RotorType)dicts.idMap(dicts.rotorTypeMap, temp);
        if ((type == EnigmaDicts::end) 
            || ((type != rotorTypeReflector) && (i == 0))
                    || ((type != rotorTypeRegular) && (i > 0)))
            throw invalid_argument("bad rotor type");    
        
        temp = reader.GetString(concat.str(), ID, EMPTY);
        int id = 1;
        if (type == rotorTypeRegular) {
            id = dicts.idMap(dicts.regularIDMap, temp) + 1;
            // HINT rename equation when changing beta and gamma rotor id
            if ((id == EnigmaDicts::end) 
                    || ((id >= 9) && (rotorLimit == 4) && (i == 1)) 
                    || ((id >= 9) && (i != 1))
                    || ((id < 9) && (rotorLimit == 5) && (i == 1)))
                throw invalid_argument("bad regular rotor id");
        }
        if (type == rotorTypeReflector) {
            id = dicts.idMap(dicts.reflectorIDMap, temp) + 1;
            if (id == EnigmaDicts::end)
                throw invalid_argument("bad reflector rotor id");
                    // HINT rename length of thin reflector name when changing name of thin reflector name
            if (dicts.reflectorIDMap[id - 1].length() > 1)
                rotorLimit = 5;
        }

        
        string inputShift = reader.GetString(concat.str(), RING_SHIFT, "1");
        int ringShift = parsePosition(inputShift);
        
        //int ringShift = reader.GetInteger(concat.str(), RING_SHIFT, 0) % Rotor::DICT_SIZE;
        string inputPosition = reader.GetString(concat.str(), POSITION, "1");
        int position = parsePosition(inputPosition);
        
        Rotor rotor(type, id, ringShift, position);
        rotors.push_back(rotor);
        concat.str("");
    }
    if (i != (rotorLimit)) {
        throw invalid_argument("incorrect number of rotors");
    }
    rotors.front().setType(rotorTypeReflector);
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


