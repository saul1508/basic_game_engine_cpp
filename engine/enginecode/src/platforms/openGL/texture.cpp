#include "engine_pch.h"
#include "platforms/openGL/texture.h"

Texture::Texture(const char* filepath, uint32_t slot) {

}

Texture::Texture(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data, uint32_t slot) :
	m_width(width), m_height(height), m_channels(channels)
{

}

void Texture::bindToSlot(uint32_t slot)
{
}

void Texture::edit(uint32_t xOffset, uint32_t yOffset, uint32_t width, uint32_t height, unsigned char* data)
{
}

void Texture::init(uint32_t width, uint32_t height, uint32_t channels, char* data, uint32_t slot)
{
	m_width = width;
	m_height = height;
	m_channels = channels;
}

