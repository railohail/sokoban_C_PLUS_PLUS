#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
class sokoban
{
private:
public:
    void which(int *height,int *width,std::string *target);
    void print(std::string *target,int height,int width);
    void generatemap(std::string *oldtarget,std::string *newtraget, int height,int width);
    void end(std::string *target);
    std::string sokoban_read_input(int input,int *flag);
    void controlmapgenerate(std::vector<std::string> (&control_map)[100],int *player_x,int *player_y,std::string *target,int height,int width);
    void moveornot(std::vector<std::string> (&control_map)[100],int *player_x,int *player_y,int height,int width,std::string input);
    void showcurrent(std::vector<std::string> (&control_map)[100],int height,int width);
    int did_you_win(std::vector<std::string> (&control_map)[100],int height,int width);
};
const std::vector<std::string> split(const std::string &str, const std::string pattern)
{
    std::vector<std::string> result;
    std::string::size_type begin,end;
    end = str.find(pattern);
    begin = 0;
    while(end != std::string::npos)
    {
        if(end - begin != 0)
        {
            result.push_back(str.substr(begin, end-begin));
        }
        begin = end + pattern.size();
        end = str.find(pattern,begin);
    }
    if(begin != str.length())
    {
        result.push_back(str.substr(begin));
    }
    return result;
}
void sokoban::which(int *height,int *width,std::string *target)
{
    std::cout << "Type the target.txt file  (mission)\n";
    std::cin >> *target; 
    std::ifstream infile;
    infile.open(*target);
    if(infile.fail()) std::cout << "the file failed to open";
    std::string str;// us a string to contain the first sentence;
    getline(infile,str);
    // std::cout << str;
    std::string pattern = " ";// the skip is space
    std::vector<std::string> results = split(str,pattern);
    // std::cout << results[0];
    // std::cout << std::endl;
    // std::cout << "now this is the second thingy\N";
    // std::cout << results[1];
    *height = std::stoi(results[0]);
    *width = std::stoi(results[1]);
    return ;
}
void sokoban::generatemap(std::string *oldtarget,std::string *newtarget, int height, int width)
{
    std::ifstream infile;
    std::ofstream outfile;
    infile.open(*oldtarget);
    outfile.open(*newtarget);
    std::string str;
    getline(infile,str);//ignore the first row of the txt file 
    for(int j = 0; j < height; j++)
    {
        getline(infile,str);
        for(int i = 0; i < width; i++) outfile << str[i];
        outfile << std::endl;
    }
    *oldtarget =*newtarget;
}
void sokoban::print(std::string *target,int height, int width)
{    
    std::cout << "map generating for you";
    // Sleep(2000);
    system("cls");
    std::ifstream infile;
    infile.open(*target);
    if(infile.fail()) std::cout << " ERROR the file has failed to open";
    std::string str;
    for(int j = 0; j < height; j++)
    {
        getline(infile,str);
        for(int i = 0; i < width; i++) std::cout << str[i];
        std::cout << std::endl;
    }
    
}
void sokoban::end(std::string *target)
{
    std::cout << "deleting aditional cache\n";
    system("cls");
    std::ofstream outfile;
    outfile.open(*target);
    return;
    
}
std::string sokoban::sokoban_read_input(int input,int *flag)
{
    std::string output;
    switch(input)
    {

        case KEY_UP:
            output = "Up";//key up
            return output;
            break;
        case KEY_DOWN:
            output = "Down";   // key down
            return output;
            break;
        case KEY_LEFT:
            output = "Left";  // key left
            return output;
            break;
        case KEY_RIGHT:
            output = "Right";  // key right
            return output;
            break;
        case KEY_ESC:
        {
            output = "NULL";
            *flag = 1;
            return output;
            break;
        }
         
    }
    output = "0";
    return output;   
    
}
void sokoban::controlmapgenerate(std::vector<std::string> (&control_map)[100],int *player_x,int *player_y,std::string *target,int height,int width)
{
    std::ifstream infile;
    infile.open(*target);
    if(infile.fail()) std::cout << "infile failed to load in at control map generate";
    std::string line;
    for(int j = 0; j < height; j++)
    {
        getline(infile,line);
        std::string str;
        // std::cout << width << "= width \n";
        for(int i = 0; i < width; i++)
        {
            str = line[i];
            if(str == "0")
            {
                // std::cout << "str = " << str << "\n";
                // std::cout << "i = " << i << "\n";
                *player_x = i;
                *player_y = j;
            }
            control_map[j].push_back(str);
        }
        line = "NULL";
    }
}
void movement(std::vector<std::string>(&control_map)[100],int *player_x,int *player_y,int x,int y)
{
    
    
    std::string temp,temp2;
    int x_two = x*2;
    int y_two = y*2;
    if(control_map[*player_y+y][*player_x+x] == "-")
    {
        
        temp = control_map[*player_y][*player_x];
        if(temp != "4")//nleave the check point
        {
            control_map[*player_y][*player_x] = control_map[*player_y+y][*player_x+x];
            control_map[*player_y+y][*player_x+x] = temp;
        }
        else//leave check
        {
            control_map[*player_y][*player_x] = "2";
            control_map[*player_y+y][*player_x+x] = "0";
        }
        if(y > 0 || y < 0)
        {
            *player_y += y;
        }
        else if(x < 0|| x > 0)
        {
            *player_x += x;
        }

    }
    else if(control_map[*player_y+y][*player_x+x] == "1" &&(control_map[*player_y+y_two][*player_x+x_two] == "-" || control_map[*player_y+y_two][*player_x+x_two] == "2"))
    {
        
        temp = control_map[*player_y][*player_x];
        temp2 = control_map[*player_y+y][*player_x+x];
        //three scenarios
        //1.with 2 out
        //1.with 2 in
        //1.without 2
        if(control_map[*player_y+y_two][*player_x+x_two] == "2")// into end
        {
            control_map[*player_y+y_two][*player_x+x_two] = "3";
            if(temp != "4")
            {
                control_map[*player_y][*player_x] = "-";
                control_map[*player_y+y][*player_x+x] = temp;
            }
            else 
            {
                control_map[*player_y][*player_x] = "2";
                control_map[*player_y+y][*player_x+x] = "0";
            }
            
        }
        else if(control_map[*player_y+y_two][*player_x+x_two] == "-")//into space
        {
            control_map[*player_y+y_two][*player_x+x_two] = "1";
            if(temp != "4")
            {
                control_map[*player_y][*player_x] = "-";
                control_map[*player_y+y][*player_x+x] = temp;
            }
            else 
            {
                control_map[*player_y][*player_x] = "2";
                control_map[*player_y+y][*player_x+x] = "0";
            }
        }
        
        if(y > 0 || y < 0)
        {
            *player_y += y;
        }
        else if(x < 0|| x > 0)
        {
            *player_x += x;
        }
            
    }
    else if(control_map[*player_y+y][*player_x+x] == "2")// check point
    {
        temp = control_map[*player_y][*player_x];
        if(temp != "4")
        {
            control_map[*player_y][*player_x] = "-";
            control_map[*player_y+y][*player_x+x] = "4";
        }
        else
        {
            control_map[*player_y][*player_x] = "2";
            control_map[*player_y+y][*player_x+x] = "4";
        }
        if(y > 0 || y < 0)
        {
            *player_y += y;
        }
        else if(x < 0|| x > 0)
        {
            *player_x += x;
        }
    }
    else if(control_map[*player_y+y][*player_x+x] == "3" && control_map[*player_y+y_two][*player_x+x_two] == "-")//meet already done stuff
    {
        temp = control_map[*player_y][*player_x];
        if(temp != "4")
        {
            control_map[*player_y+y][*player_x+x] = "4";
            control_map[*player_y][*player_x] = "-";
            control_map[*player_y+y_two][*player_x+x_two] = "1";
        }
        else
        {
            control_map[*player_y+y][*player_x+x] = "4";
            control_map[*player_y][*player_x] = "2";
            control_map[*player_y+y_two][*player_x+x_two] = "1";// 1 is box 

        }
        if(y > 0 || y < 0)
        {
            *player_y += y;
        }
        else if(x < 0|| x > 0)
        {
            *player_x += x;
        }
    }
    else if(control_map[*player_y+y][*player_x+x] == "3" && control_map[*player_y+y_two][*player_x+x_two] == "2")//meet already done stuff
    {
        temp = control_map[*player_y][*player_x];
        if(temp != "4")
        {
            control_map[*player_y+y][*player_x+x] = "4";
            control_map[*player_y][*player_x] = "-";
            control_map[*player_y+y_two][*player_x+x_two] = "3";
        }
        else
        {
            control_map[*player_y+y][*player_x+x] = "4";
            control_map[*player_y][*player_x] = "2";
            control_map[*player_y+y_two][*player_x+x_two] = "3";
        }
        if(y > 0 || y < 0)
        {
            *player_y += y;
        }
        else if(x < 0|| x > 0)
        {
            *player_x += x;
        }
    }
}
void sokoban::moveornot(std::vector<std::string> (&control_map)[100],int *player_x,int *player_y,int height,int width,std::string input)
{
   
    // std::cout << *player_x << " "<< *player_y << "\n";
    //  Sleep(1000);
    //there are four scenarios
    //1. no box nor wall swap with air -> move
    //2. yes box and nothing behind it -> move
    //3. yes box and somethings behind it -> no move
    //4. no box but theres a wall -> no move
    //5.no box but it's a finish ->move
    //6.box but its already in the finish line
    //
    //BTW up is negative left is negative
    std::string temp,temp2;//1 is box 2 is check point 3 is checked box 4 is human in check point 
    int x,y;
    if(input == "Up")
    { 
        x = 0;
        y = -1;
        movement(control_map,player_x,player_y,x,y);
        
    }
    else if(input == "Down")
    {
        x = 0;
        y = +1;
        movement(control_map,&*player_x,&*player_y,x,y);
    }
    else if(input == "Left")
    {
        x = -1;
        y = 0;
        movement(control_map,player_x,player_y,x,y);
    }
    else if(input == "Right")
    {
        x = +1;
        y = 0;
        movement(control_map,player_x,player_y,x,y);
    }
    
}
void sokoban::showcurrent(std::vector<std::string> (&control_map)[100],int height,int width)
{
    system("cls");
    
    for(int j = 0; j < height; j++)
    {
        for(int i = 0; i < width; i++)
        {
            std::cout << control_map[j][i];
        }
        std::cout << std::endl;
    
    }
}
int sokoban::did_you_win(std::vector<std::string> (&control_map)[100],int height,int width)
{
    int flagwin;
    flagwin =1;
    for(int j = 0; j < height; j++)
    {
        for(int i = 0; i < width; i++)
        {
            if(control_map[j][i] == "1")
                flagwin = 0;
        }
        std::cout << std::endl;
    }
    return flagwin;
}


//new stuff