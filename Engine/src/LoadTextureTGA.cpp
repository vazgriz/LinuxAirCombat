#include "Engine/Texture.h"

#include <string>
#include <stdexcept>

#include <SDL2/SDL.h>
#include <SDL_image.h>

using namespace LACEngine;

std::shared_ptr<Texture> LACEngine::TryLoadFromTGA(const std::string& filename, TextureAlphaType alphaType) {
	SDL_Surface* data = IMG_Load(filename.c_str());

	if (data == nullptr) {
		return nullptr;
	}

	TextureFormat format = TextureFormat::None;

	switch (data->format->format) {
	case SDL_PIXELFORMAT_RGB24:
		format = TextureFormat::RGB;
		break;
	case SDL_PIXELFORMAT_RGBA32:
		format = TextureFormat::RGBA;
		break;
	case SDL_PIXELFORMAT_INDEX8:
		format = TextureFormat::R;
		break;
	case SDL_PIXELFORMAT_BGR24:
		format = TextureFormat::BGR;
		break;
	}

	if (format == TextureFormat::None) {
		std::string name = SDL_GetPixelFormatName(data->format->format);
		throw std::runtime_error("Invalid data format");
	}

	std::shared_ptr<Texture> texture = std::make_shared<Texture>(format, data->w, data->h, alphaType);
	char* ptr = texture->CreateLocalData();

	if (texture->GetLocalDataSize() != data->pitch * data->h) {
		throw std::runtime_error("Data size mismatch");
	}

	memcpy(ptr, data->pixels, texture->GetLocalDataSize());

	SDL_FreeSurface(data);

	return texture;
}