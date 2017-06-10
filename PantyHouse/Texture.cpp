// Texture.cpp
// Texturing objects

#include "head.h"

void initTexture() {
	// Genarate signatures for textures
	glGenTextures(4, scene.texture);
	// TODO:Generate textures from source images

	// Uncomment if you want to enable multitexturing
	//glActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
	//glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");
	//glClientActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glClientActiveTextureARB");
}