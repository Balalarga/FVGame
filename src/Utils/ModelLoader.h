#ifndef MODELLOADER_H
#define MODELLOADER_H


#include "Files.h"

class ModelLoader
{
public:
    ModelLoader() = delete;

    template<class T>
    static T* LoadFromFile(const std::string& file);

};

#endif // MODELLOADER_H
