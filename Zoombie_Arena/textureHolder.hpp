#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class TextureHolder{
private:
    std::map<std::string, sf::Texture> m_textures;
    static TextureHolder* m_s_Instance;
public:
    TextureHolder();
    static sf::Texture& getTexture(std::string const& filename);
};