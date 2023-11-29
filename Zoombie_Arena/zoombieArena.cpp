#include "zoombieArena.h"
#include <random>

int createBackground(VertexArray& rVA, IntRect arena){
    const int TILE_SIZE = 50;
    const int TILE_TYPE = 3;
    const int VERTS_IN_QUAD = 4;

    int worldWidth = arena.width / TILE_SIZE;
    int worldHeight = arena.height / TILE_SIZE;

    rVA.setPrimitiveType(Quads);

    rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);
    int currentVertex = 0;

    for (int w=0; w<worldWidth; w++){
        for (int h=0; h<worldHeight; h++){
            rVA[currentVertex + 0].position = Vector2f(w * TILE_SIZE, h * TILE_SIZE);
            rVA[currentVertex + 1].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);
            rVA[currentVertex + 2].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);
            rVA[currentVertex + 3].position = Vector2f(w * TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);

            if (h == 0 || h == worldHeight -1 || w == 0 || w==worldWidth -1){
                rVA[currentVertex + 0].texCoords = Vector2f(0, + TILE_TYPE * TILE_SIZE);
                rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + TILE_TYPE * TILE_SIZE);
                rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + TILE_TYPE * TILE_SIZE);
                rVA[currentVertex + 2].texCoords = Vector2f(0, TILE_SIZE + TILE_TYPE * TILE_SIZE);
            }
            else
            {
                srand((int) time(0) + h * w -h);
                int mOrG = rand() % TILE_TYPE;
                int verticalOffset = mOrG * TILE_SIZE;

                rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
                rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
                rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
                rVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);
            }
            currentVertex = currentVertex  + VERTS_IN_QUAD;
        }
    }



    return TILE_SIZE;
}

Zoombie* createHord(int numZoombies, IntRect arena){
    Zoombie* zoombies = new Zoombie[numZoombies]; // Array of Zoombies
    int maxY = arena.height - 20;
    int minY = arena.top + 20;

    int maxX = arena.width - 20;
    int minX = arena.left  + 20;

    for (int i=0; i<numZoombies; i++){
        
        srand((int) time(0) * i);
        int side = rand() %4;
        float x, y;

        switch (side)
        {
        case 0:
            x = minX;
            y = (rand() % maxY) + minY;
            break;
        case 1:
            x = maxX;
            y = (rand() % maxY) + minY;
        case 2:
            x = (rand() % maxX) + minX;
            y = minY;
        case 3:
            x = (rand() % maxX) + minX;
            y = maxY;
        default:
            break;
        }
        srand((int) time(0) * i * 2);
        int type = rand() % 3;
        zoombies[i].spawn(x, y, type, i);
    }
    return zoombies;
}