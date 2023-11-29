#pragma once
#include <SFML/Graphics.hpp>
#include "zoombie.hpp"
using namespace sf;

int createBackground(VertexArray& rVA, IntRect arena);
Zoombie* createHord(int numZoombies, IntRect arena);
