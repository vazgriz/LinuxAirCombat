#include "Engine/Texture.h"

#include <string>
#include <stdexcept>

#include <SDL2/SDL.h>
#include <SDL_image.h>

using namespace LACEngine;

Texture LoadFromTGA(const std::string& filename, TextureAlphaType alphaType) {
	SDL_Surface* data = IMG_Load(filename.c_str());

	TextureFormat format = TextureFormat::R;

	switch (data->format->format) {
	case SDL_PIXELFORMAT_RGB888:
		format = TextureFormat::RGB;
		break;
	case SDL_PIXELFORMAT_RGBA32:
		format = TextureFormat::RGBA;
		break;
	case SDL_PIXELFORMAT_INDEX8:
		format = TextureFormat::R;
		break;
	}

	Texture texture(format, data->w, data->h, alphaType);
	char* ptr = texture.CreateLocalData();

	if (texture.GetLocalDataSize() != data->pitch * data->h) {
		throw std::runtime_error("Data size mismatch");
	}

	memcpy(ptr, data->pixels, texture.GetLocalDataSize());

	SDL_FreeSurface(data);
}