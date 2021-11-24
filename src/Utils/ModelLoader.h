#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <string>
#include <iostream>
#include <fstream>

#include "GameFramework/DrawableObject.h"
#include "Space/SpaceManager.h"
#include "Color.h"


namespace ModelLoader
{

template<typename T, typename = std::enable_if_t<std::is_base_of<DrawableObject, T>::value>>
T* LoadRawFromFile(const std::string& path,
                   ShaderProgram* shader,
                   const Color& color = Color::fromUint(255, 255, 255, 255))
{
    std::ifstream file(path, std::ios_base::binary);
    if(!file)
    {
        std::cout<<"Unable to open model "<<path<<"\n";
        return nullptr;
    }
    ModelMetadata metadata;
    file.read((char*)&metadata, sizeof(ModelMetadata));
    SpaceManager& space = SpaceManager::Self();
    space.SetMetadata(metadata);
    space.InitFromMetadata();
    space.ActivateBuffer(SpaceManager::BufferType::ZoneBuffer);

    file.read(space.GetZoneBuffer(), space.GetBufferSize() * sizeof(char));
    file.close();

    std::vector<float> resData;
    resData.reserve(shader->GetLayout().GetWidth() * metadata.zeroCount);

    Vector3f point;
    for(int i = 0; i < space.GetBufferSize(); ++i)
    {
        if(space.GetZone(i) == 0)
        {
            // Position
            point = space.GetPointCoords(i);
            resData.push_back(point.x);
            resData.push_back(point.y);
            resData.push_back(point.z);

            // Color
            resData.push_back(color.red);
            resData.push_back(color.green);
            resData.push_back(color.blue);
            resData.push_back(color.alpha);

            // VoxelSize
            resData.push_back(metadata.pointSize.x);
        }
    }
    space.Clear();

    T* obj = new T(shader);
    obj->Create(resData);
    if(!obj->IsCreated())
    {
        delete obj;
        return nullptr;
    }
    obj->SetPrimitive(DrawMode::Points);

    return obj;
}

};

#endif // MODELLOADER_H
