#include "TextureHolder.h"
#include <assert.h>
TextureHolder* TextureHolder::m_instance = nullptr;
TextureHolder::TextureHolder()
{
	assert(m_instance == nullptr);
	m_instance = this;
}

sf::Texture& TextureHolder::GetTexture(std::string const& fileName)
{
	auto temp_Map = m_instance->map;
	auto temp_KVP = temp_Map.find(fileName);
	if (temp_KVP!=temp_Map.end())
	{
		return temp_KVP->second;
	}
	else
	{
		auto& tmp_texture = temp_Map[fileName];
		tmp_texture.loadFromFile(fileName);
		return tmp_texture;
	}
}