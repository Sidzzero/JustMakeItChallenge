#pragma once
#include <SFML/Graphics.hpp>
#include <map>
class TextureHolder
{
private:
	static TextureHolder * m_instance;
	std::map <std::string, sf::Texture> map;
public:
	TextureHolder();
	static sf::Texture& GetTexture(std::string const& fileName);
};

