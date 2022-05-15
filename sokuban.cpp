#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "sokuban.h"


int main()
{
    
    std::vector<std::string> control_map[100]; 
    int player_x,player_y;
    std::fstream map;// this will be the new map for watching the whole thing 
    map.open("map.txt");
    if(map.fail()) std::cout << "the map has failed to open\nThis error is normal if you are on your first try\n";
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
    // now it's time to let the target start to move 
    int input = 0;
    std::string output;
    int flag = 0;
    sokuban_test.controlmapgenerate(control_map,&player_x,&player_y,&target,height,width);
    // we now have the player x and player y and vector map;
    int win;
    while(1)
    {
        input = getch();
        if(input != 0)// get rid of the NULL input
        {    
            // std::cout << "the input is " << input << "\n";
            output = sokuban_test.sokuban_read_input(input,&flag);
            if(flag == 1) break;//when you type ESC button you could leave right away     
            // std::cout << "the output is " << output << "\n";
            // std::cout << "the flag is " << flag << "\n";
            //you now got the output of your arrow sign now change the map
            
            // std::cout << "you are at x = " << player_x << " y = "<< player_y <<"\n";
            
            sokuban_test.moveornot(control_map,&player_x,&player_y,height,width,output);
            
            

            //this moves with every switch
            //now write a something to show the vector
            sokuban_test.showcurrent(control_map,height,width);
            win = sokuban_test.did_you_win(control_map,height,width);
            if(win == 1)
            {
                system("cls");
                std::cout << "You win!!!\n";
                return 0;
            }
            
        
        
        
        }
    }
    Sleep(3000);
    sokuban_test.end(&target);
}
