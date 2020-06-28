#pragma once
#include "Chunk.h"
#include "helpfile.h"
#include <map>
#include "GameObject.h"
constexpr auto mapSize = 3;
class World : public GameObject
{
    const int width=2;
    const int height=2;
public:
    Chunk* chunkMap[mapSize][mapSize];

    inline Chunk* GetChunk(glm::vec2 position)
    {
        if(position.x >=0 && position.y >= 0 && position.x < mapSize && position.y < mapSize)
            return chunkMap[(int)position.x][(int)position.y];
        return nullptr;
    }
    inline void Update(const double& deltaTime)
    {
        for (int x = 0; x < mapSize; x++)
        {
            for (int z = 0; z < mapSize; z++)
            {
                chunkMap[x][z]->Update(deltaTime);
                chunkMap[x][z]->Render();
            }
        }
    }
    inline void Generate()
    {
        for (int x = 0; x < mapSize; x++)
        {
            for (int z = 0; z < mapSize; z++)
            {
                chunkMap[x][z] = new Chunk({ x, 0, z });
            }
        }
        for (int x = 0; x < mapSize; x++)
        {
            for (int z = 0; z < mapSize; z++)
            {
                chunkMap[x][z]->GenerateMesh();
            }
        }
    }
};

