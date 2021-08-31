#include "Renderer.h"
#include "Math/MathUtils.h"
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>


namespace nc
{
	void Renderer::Startup()
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		}
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
		TTF_Init();
	}

	void Renderer::Shutdown()
	{
		IMG_Quit();
		TTF_Quit();
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}

	void Renderer::Update(float dt)
	{

	}

	void Renderer::Create(const std::string& name, int width, int height)
	{
		SDL_Point screen{ 800, 600 };
		SDL_Window* window = SDL_CreateWindow("GAT150", 100, 100, screen.x, screen.y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (window == nullptr)
		{
			std::cout << "SDL_CreateWindowError:" << SDL_GetError() << std::endl;
			SDL_Quit();
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	}

	void Renderer::BegineFrame()
	{
		SDL_RenderClear(renderer);
	}

	void Renderer::Endframe()
	{
		SDL_RenderPresent(renderer);
	}

	void Renderer::Draw(std::shared_ptr<nc::Texture> texture, const Vector2& position, float angle, const Vector2& scale)
	{
		Vector2 size = texture->GetSize();
		size = size * scale;

		Vector2 newPosition = position - (size * 0.5f);

		SDL_Rect rect;
		rect.x = static_cast<int>(newPosition.x);
		rect.y = static_cast<int>(newPosition.y);
		rect.w = static_cast<int>(size.x);
		rect.h = static_cast<int>(size.y);

		SDL_RenderCopyEx(renderer, texture->texture, nullptr, &rect, nc::RadToDeg(angle), nullptr, SDL_FLIP_HORIZONTAL);
	}

	void Renderer::Draw(std::shared_ptr<nc::Texture> texture, const Transform& transform)
	{
		Vector2 size = texture->GetSize();
		size = size * transform.scale;
		
		Vector2 newPosition = transform.position - (size * 0.5f);

		SDL_Rect dest;
		dest.x = static_cast<int>(newPosition.x);
		dest.y = static_cast<int>(newPosition.y);
		dest.w = static_cast<int>(size.x);
		dest.h = static_cast<int>(size.y);

		SDL_RenderCopyEx(renderer, texture->texture, nullptr, &dest, nc::RadToDeg(transform.rotation), nullptr, SDL_FLIP_NONE);
	}

	void Renderer::Draw(std::shared_ptr<nc::Texture> texture, SDL_Rect& source, const Transform& transform)
	{
		Vector2 size = Vector2{ source.w, source.h };
		size *= transform.scale;

		Vector2 newPosition = transform.position - (size * 0.5f);

		SDL_Rect dest;
		dest.x = static_cast<int>(newPosition.x);
		dest.y = static_cast<int>(newPosition.y);
		dest.w = static_cast<int>(size.x);
		dest.h = static_cast<int>(size.y);

		SDL_RenderCopyEx(renderer, texture->texture, &source, &dest, nc::RadToDeg(transform.rotation), nullptr, SDL_FLIP_NONE);
	}
}