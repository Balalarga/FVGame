#ifndef FILES_H
#define FILES_H


#include <string>

class Files
{
public:
    static std::string ReadFile(const std::string& path);


    Files() = delete;
};

#endif // FILES_H
