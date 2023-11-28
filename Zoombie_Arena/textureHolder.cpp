#include "textureHolder.hpp"
#include <assert.h>

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder:: TextureHolder(){
    assert(m_s_Instance == nullptr);
    m_s_Instance = this;
}

sf::Texture& TextureHolder::getTexture(std::string const& filename){
    auto& m = m_s_Instance ->m_textures;

    auto keyValuepair = m.find(filename);
    if (keyValuepair != m.end())
    {
        return keyValuepair->second;
    }
    else{
        auto& texture = m[filename];
        texture.loadFromFile(filename);
        return texture;
    }
}