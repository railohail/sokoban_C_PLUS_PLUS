#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "sokuban.h"


int main()
{
    std::fstream map;// this will be the new map for watching the whole thing 
    map.open("map.txt");
    if(map.fail()) std::cout << "the map has failed to open\n";
    std::ofstream outfile;
    outfile.open("map.txt");// clears out the map.txt 
    int height,width;
    std::string target,temp_target;
    sokuban sokuban_test;
    sokuban_test.which(&height,&width,&target);// chooses the mission that we want to run
    temp_target = "map.txt"; 
    // std::cout << "the height is " << height;
    // std::cout << std::endl;
    // std::cout << "the width is " << width;
    
    //now we have the height and width of the map

    // now we are going to use a vector to store all the stuff
    //problem 1. need to figure out how to only get one item from the txt file
    sokuban_test.generatemap(&target,&temp_target,height,width);
    sokuban_test.print(&target,height,width);// the initial map that the  user gets 




    sokuban_test.end(&target);
}