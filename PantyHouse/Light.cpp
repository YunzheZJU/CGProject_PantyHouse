// Light.cpp
// Functions related with lighting are defined here

#include "head.h"

void initLight() {
	glEnable(GL_NORMALIZE);
	// You should comment the next two lines if there is no light in the scene.
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	// Set mirror reflection target to camera instead of infinity
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	// Apply mirror reflection after texturing
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL_EXT, GL_SEPARATE_SPECULAR_COLOR_EXT);
}