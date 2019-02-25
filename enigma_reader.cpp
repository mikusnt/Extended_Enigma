/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include <fstream>
#include <sstream>

#include "enigma_reader.hpp"
#include "enigma.hpp"

namespace enigma {
    std::string EnigmaDicts::toLower(std::string input) {
        for(int i = 0; i < input.length(); i++)
            input[i] = tolower(input[i]);
        return input;
    }

//    int EnigmaDicts::idMap(const std::string map[], std::string value) {
//        int length;
//        if (map == regularIDMap)
//            length = sizeof(regularIDMap)/sizeof(regularIDMap[0]);
//        if (map == reflectorIDMap)
//            length = sizeof(reflectorIDMap)/sizeof(reflectorIDMap[0]);
//        if (map == rotorTypeMap)
//            length = sizeof(rotorTypeMap)/sizeof(rotorTypeMap[0]);
//
//
//        for (int i = 0; i < length; i++) {
//            if ((map[i] == value) && (map[i] != EMPTY))
//                return i;
//        }
//        return EnigmaDicts::end;
//    }

    int EnigmaReader::parsePosition(std::string pos) {
        unsigned int output = 0;
        char first = toupper(pos[0]);
        if ((first >= 'A') && (first <= 'Z')) {
            output = first - 'A' + 1;
        } else {
            std::stringstream conv(pos);
            conv >> output;
            while (output > (Rotor::DICT_SIZE)) output -= Rotor::DICT_SIZE;
            while (output < 1) output += Rotor::DICT_SIZE;
        }
        return output;
    }
    
    EnigmaReader::EnigmaReader() {
        filename = "";
        parsed = false;
    }

    EnigmaReader::EnigmaReader(std::string filename) : EnigmaReader() {
        tryParseFile(filename);
    }

    bool EnigmaReader::tryParseFile(std::string filename) {
        this->filename = filename;
        parsed = false;
        rotors.clear();
        plugboard.clear();

        INIReader reader(filename);

        if (reader.ParseError() < 0)
            return false;
        std::string temp;

        // plugboard
        temp = reader.GetString(PLUGBOARD, RULES, EMPTY);
        if (temp != EMPTY) {
            if (!plugboard.loadRules(temp))
                return false;
        }

        std::stringstream concat;
        
        temp = reader.GetString(REFLECTOR, ID, EMPTY);
        if (temp == EMPTY)
            return false;
        
        ReflectorRotor tempReflector(temp);
        if (!tempReflector.wasInitialized())
            return false;
        this->reflector = tempReflector;
        ReflectorRotorId reflectorId = reflector.getId();
        int rotorLimit = Enigma::REGULAR_ROTORS_NUM;
        if ((reflectorId == ReflectorID_Bthin) || (reflectorId == ReflectorID_Cthin))
            rotorLimit = Enigma::THIN_ROTOR_NUM;
        
        // rotors
        for (int i = 1; i <= rotorLimit; i++) {
            concat << REGULAR << i;
            
            std::string id = reader.GetString(concat.str(), ID, EMPTY);
            if (temp == EMPTY)
                return false;
            
            
            std::string inputShift = reader.GetString(concat.str(), RING_SHIFT, "1");
            int ringShift = parsePosition(inputShift);

            std::string inputPosition = reader.GetString(concat.str(), POSITION, "1");
            int position = parsePosition(inputPosition);

            RegularRotor rotor(id, ringShift, position);
            if (!rotor.wasInitialized())
                return false;
            rotors.push_back(rotor);
            concat.str("");
        }
        parsed = true;
        return parsed;
    }


    void EnigmaReader::writeDefaultFile(std::string filename) {
        std::fstream file;
        file.open(filename, std::ios::out);
        if (file.is_open()) {
            //file << "[plugboard]\nrules = AC, BG, TU\n\n";
            file << "[reflector]\nid = B\n\n";
            file << "[rotor_3]\ntype = regular\nid = I\nposition = A\n\n";
            file << "[rotor_2]\ntype = regular\nid = II\nposition = A\n\n";
            file << "[rotor_1]\ntype = regular\nid = III\nposition = A\n\n";

            file.close();
        } else {
        }
    }

    std::ostream& operator<<(std::ostream& os, const EnigmaReader& reader) {
        os << "Translation on plugboard:\n";
        os << reader.plugboard << "\n\n";

        os << "Rotors settings: \n";
        std::stringstream output;
        os << reader.reflector.toString() << std::endl;
        for(int i = reader.rotors.size() - 1; i > 0; i--) {
            os << reader.rotors[i].toString() << std::endl;
        }
        os << reader.rotors.front().toString();
        return os;
    }
}


