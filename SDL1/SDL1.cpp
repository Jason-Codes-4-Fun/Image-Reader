// SDL1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <vector>
#include <SDL.h>
#include <cmath>
#include "ReadBMP.cpp"
#include <string>




int main(int argc, char*args[])
{
    while (true) {
        std::cout << "please give a file url to a bmp file: ";
        std::string input = "";
        std::cin >> input;
        for (int i = 0; i < input.length();i++) {
            if (input[i]=='/') {
                input[i]='\\';
            }
        }
        std::ifstream file(input);
        if (file) {
            Read(input);
        }
        else { std::cout << "invalid locaton, please try again"; }
    }

    
    return 0;
}



