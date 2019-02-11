/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   plugboard.hpp
 * Author: user
 *
 * Created on 8 lutego 2019, 10:27
 */

#ifndef PLUGBOARD_HPP
#define PLUGBOARD_HPP

#include <iostream>
#include <string>

using namespace std;

class Plugboard {
private:
    const char ERROR_CHAR = 'X';
protected:
    const string ORIGINAL = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string actual;
    bool haveDuplicates(string word);
public:
    Plugboard();
    //Plugboard(string rules);
    bool addConnect(char input, char output);
    bool removeConnect(char input);
    char translate(char input);
    
    friend ostream& operator<<(ostream& os, const Plugboard& plugboard);
};

#endif /* PLUGBOARD_HPP */

