#include <SDL.h>
#include <SDL_image.h>

#include "RenderWindow.h"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cout << "MERDE WINDOW ERROR: " << SDL_GetError() << std::endl;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);
	if (texture == NULL)
	{
		std::cout << "MERDE TEXTURE : " << IMG_GetError() << std::endl;

	}
	return texture;
}


void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity)
{
	SDL_Rect src;
	src.x = static_cast<int>(p_entity.getCurrentFrame().x);
	src.y = static_cast<int>(p_entity.getCurrentFrame().y);
	src.w = static_cast<int>(p_entity.getCurrentFrame().w);
	src.h = static_cast<int>(p_entity.getCurrentFrame().h);

	SDL_Rect dst;
	dst.x = p_entity.getX(); // change x.y to change location of spawn 
	dst.y = p_entity.getY();
	dst.w = p_entity.getCurrentFrame().w; //can be zoomed in by using *number
	dst.h = p_entity.getCurrentFrame().h;


	SDL_RenderCopy(renderer, p_entity.getTexture(), &src, &dst);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

SDL_Renderer* RenderWindow::getRenderer() const
{
	return renderer;
}
