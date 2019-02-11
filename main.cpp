/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Mikolaj Stankowiak
 *
 * Created on 7 lutego 2019, 11:22
 */

#include <iostream>
#include <cstdlib>
#include <conio.h>
#include "rotor.hpp"
#include "plugboard.hpp"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    Rotor rotor(rotorTypeRegular, 0, 0);
    
    string text;
    char sign;
    do {
        //cin >> text;
        sign = toupper(getch());
        //for (int i = 0; i < text.length(); i++) {
            //rotor.rotate();
        //cout << 
            //cout << text[i];
        //}
        rotor.rotate();
        cout << sign << " >> " << rotor.translate(sign, directionLeft) << endl;
        
    } while (sign != 27);
    return 0;
}

