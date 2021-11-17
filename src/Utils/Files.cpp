#include "Files.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;


std::string Files::ReadFile(const std::string &path)
{
    ifstream file(path);
    if(!file)
    {
        cout<<"File "<<path<<" not found\n";
        return "";
    }

    stringstream stream;
    stream << file.rdbuf();

    file.close();

    return stream.str();
}
