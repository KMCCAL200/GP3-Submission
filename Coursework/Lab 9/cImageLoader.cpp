/*
==================================================================================
cImageLoader.cpp
==================================================================================
*/

#include "cImageLoader.h"

cImageLoader::cImageLoader()				// Constructor
{
	m_dib = NULL;
	m_ImageData = NULL;
	m_ImageWidth = 0;
	m_ImageHeight = 0;
}

cImageLoader::cImageLoader(const char* filename)
{
	m_dib = LoadTexture(filename);
}

cImageLoader::~cImageLoader()        // destructor
{
	//unloadTexture(m_dib);
}

FIBITMAP* cImageLoader::LoadTexture(const char* filename)
{
	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	//if still unkown, return failure
	if (fif == FIF_UNKNOWN)
		return NULL;

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	//if the image failed to load, return failure
	if (!dib)
		return NULL;

	setImageData(dib);
	setImageWidth(dib);
	setImageHeight(dib);

	bits = getImageData();
	width = getImageWidth();
	height = getImageHeight();
	
	//if this somehow one of these failed (they shouldn't), return failure
	if ((bits == 0) || (width == 0) || (height == 0))
		return NULL;

	//return success
	m_dib = dib;
	return dib;
}

BYTE* cImageLoader::getImageData()
{
	//retrieve the image data
	return m_ImageData;
}

void cImageLoader::setImageData(FIBITMAP* texture)
{
	m_ImageData = FreeImage_GetBits(texture);
}

unsigned int cImageLoader::getImageWidth()
{
	//get the image width
	return m_ImageWidth;
}

void cImageLoader::setImageWidth(FIBITMAP* texture)
{
	m_ImageWidth = FreeImage_GetWidth(texture); //get the image width

}

unsigned int cImageLoader::getImageHeight()
{
	return m_ImageHeight;
}

void cImageLoader::setImageHeight(FIBITMAP* texture)
{
	m_ImageHeight = FreeImage_GetHeight(texture);
}

//free the memory for a texture
void cImageLoader::unloadTexture(FIBITMAP *textureToUnload)
{
	//Free FreeImage's copy of the data
	FreeImage_Unload(textureToUnload);
}

