// Utils.cpp
// Utility functions for changing global variables are defined here
// Write functions as less as possible in this file!

#include "head.h"

// TODO:You can move these two function to Draw.cpp or System.cpp
void callList() {
	glCallList(scene.List);
}

void updateList() {
	scene.List = genTableList();
}