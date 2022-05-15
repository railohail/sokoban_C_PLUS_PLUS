#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
class sokuban
{
private:
public:
    void which(int *height,int *width,std::string *target);
    void print(std::string *target,int height,int width);
    void generatemap(std::string *oldtarget,std::string *newtraget, int height,int width);
    void end(std::string *target);
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
void sokuban::which(int *height,int *width,std::string *target)
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
void sokuban::generatemap(std::string *oldtarget,std::string *newtarget, int height, int width)
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
void sokuban::print(std::string *target,int height, int width)
{    
    std::cout << "map generating for you";
    Sleep(2000);
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
void sokuban::end(std::string *target)
{
    std::cout << "deleting aditional cache\n";
    Sleep(2000);
    system("cls");
    std::ofstream outfile;
    outfile.open(*target);
    return;
    
}