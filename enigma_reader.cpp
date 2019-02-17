/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include <fstream>
#include <sstream>

#include "enigma_reader.hpp"
#include "enigma.hpp"

int EnigmaDicts::idMap(const string map[], string value) {
    int length;
    if (map == regularIDMap)
        length = sizeof(regularIDMap)/sizeof(regularIDMap[0]);
    if (map == reflectorIDMap)
        length = sizeof(reflectorIDMap)/sizeof(reflectorIDMap[0]);
    if (map == rotorTypeMap)
        length = sizeof(rotorTypeMap)/sizeof(rotorTypeMap[0]);
    
    
    for (int i = 0; i < length; i++) {
        if ((map[i] == value) && (map[i] != EMPTY))
            return i;
    }
    return EnigmaDicts::end;
}

int EnigmaReader::parsePosition(string pos) {
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
    tryParseFile(filename);
}

bool EnigmaReader::tryParseFile(string filename) {
    this->filename = filename;
    parsed = false;
    rotors.clear();
    plugboard.clear();
    
    INIReader reader(filename);
    
    if (reader.ParseError() < 0)
        return false;
    string temp;
    
    // plugboard
    temp = reader.GetString(PLUGBOARD, RULES, EMPTY);
    if (temp != EMPTY) {
        if (!plugboard.loadRules(temp))
            return false;
    }
    
    stringstream concat;
    int rotorLimit = Enigma::REGULAR_ROTORS_NUM;
    // rotors
    int i;
    temp = "";
    for (i = 0; (temp != EMPTY); i++) {
        concat << ROTOR << i;
        temp = reader.GetString(concat.str(), TYPE, EMPTY);
        if (temp == EMPTY)
            break;
        
        RotorType type = rotorTypeRegular;
        EnigmaDicts dicts;
        type = (RotorType)dicts.idMap(dicts.rotorTypeMap, temp);
//        if ((type == EnigmaDicts::end) 
//            || ((type != rotorTypeReflector) && (i == 0))
//                    || ((type != rotorTypeRegular) && (i > 0)))
//            return false;  
        
        temp = reader.GetString(concat.str(), ID, EMPTY);
        int id = 1;
        if (type == rotorTypeRegular) {
            id = dicts.idMap(dicts.regularIDMap, temp);
//            if ((id == EnigmaDicts::end) 
//                    || ((id > Rotor::MAX_INPUT_GAMMA_ID) && (rotorLimit == Enigma::REGULAR_ROTORS_NUM) && (i == 1)) 
//                    || ((id > Rotor::MAX_INPUT_GAMMA_ID) && (i != 1))
//                    || ((id < Rotor::MAX_INPUT_BETA_ID) && (rotorLimit == Enigma::THIN_ROTOR_NUM) && (i == 1)))
//                return false;
        }
        if (type == rotorTypeReflector) {
            id = dicts.idMap(dicts.reflectorIDMap, temp);
//            if (id == EnigmaDicts::end)
//                return false;
//            if (dicts.reflectorIDMap[id - 1].length() == dicts.REFLECTOR_THIN_SIZE)
//                rotorLimit = Enigma::THIN_ROTOR_NUM;
        }

        
        string inputShift = reader.GetString(concat.str(), RING_SHIFT, "1");
        int ringShift = parsePosition(inputShift);
        
        string inputPosition = reader.GetString(concat.str(), POSITION, "1");
        int position = parsePosition(inputPosition);
        
        Rotor rotor(type, id, ringShift, position);
        if (!rotor.wasInitialized())
            return false;
        rotors.push_back(rotor);
        concat.str("");
    }
//    if (i != rotorLimit) {
//        
//    }
    rotors.front().setType(rotorTypeReflector);
    parsed = true;
    return parsed;
}


void EnigmaReader::writeDefaultFile(string filename) {
    fstream file;
    file.open(filename, ios::out);
    if (file.is_open()) {
        //file << "[plugboard]\nrules = AC, BG, TU\n\n";
        file << "[rotor_0]\ntype = reflector\nid = B\n\n";
        file << "[rotor_1]\ntype = regular\nid = III\nposition = A\n\n";
        file << "[rotor_2]\ntype = regular\nid = II\nposition = A\n\n";
        file << "[rotor_3]\ntype = regular\nid = I\nposition = A\n\n";
        
        file.close();
    } else {
    }
}

ostream& operator<<(ostream& os, const EnigmaReader& reader) {
    os << "Translation on plugboard:\n";
    os << reader.plugboard << "\n\n";

    os << "Rotors settings: \n";
    stringstream output;
    for(int i = 0; i < reader.rotors.size() - 1; i++) {
        os << reader.rotors[i] << endl;
    }
    os << reader.rotors.back();
    return os;
}


