#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <string>
#include <iostream>
#include <fstream>

#include "GameFramework/DrawableObject.h"
#include "Space/SpaceManager.h"


namespace ModelLoader
{

template<typename T, typename = std::enable_if_t<std::is_base_of<DrawableObject, T>::value>>
T* LoadFromFile(const std::string& path, ShaderProgram* shader)
{
    return nullptr;
    std::ifstream file(path, std::ios_base::binary);
    if(!file)
    {
        std::cout<<"Unable to open model "<<path<<"\n";
        return nullptr;
    }
    auto& space = SpaceManager::Self();
    file.read((char*)&space.metadata, sizeof(space.metadata));
    space.InitFromMetadata();

    std::vector<char> rawData(space.GetSpaceSize());
    std::vector<float> resData;

    file.read(rawData.data(), rawData.size() * sizeof(rawData[0]));

    file.close();

    cl_float3 point;
    for(int i = 0; i < rawData.size(); ++i)
    {
        if(rawData[i] == 0)
        {
            point = space.GetPointCoords(i);
            resData.push_back(point.x);
            resData.push_back(point.y);
            resData.push_back(point.z);

            resData.push_back(1);
            resData.push_back(1);
            resData.push_back(1);
            resData.push_back(0);
        }
    }

    T* obj = new T(shader);
    obj->Create(resData);
    obj->SetPrimitive(DrawMode::Points);
    if(!obj->IsCreated())
    {
        delete obj;
        return nullptr;
    }

    return obj;
}

};

#endif // MODELLOADER_H
