#include "Font.h"

nc::Font::~Font()
{
	//
}

bool nc::Font::Load(const std::string& name, void* data)
{
	int dataInt = *(int*)data;
	font = TTF_OpenFont( name.c_str(), dataInt);
	if (font == nullptr)
	{
		std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
		return false;
	}
	return true;
}

SDL_Surface* nc::Font::CreateSurface(const std::string& text, const nc::Color& color)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (surface == nullptr)
	{
		std::cout << "TTF_RenderText_Solid Error: " << SDL_GetError() << std::endl;
	}
	return surface;
}
