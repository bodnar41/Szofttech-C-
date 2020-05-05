/*
 * draw.h
 *
 *   Created by: Bodnár Márk Ármin	
 */
#ifndef DRAW_H
#define DRAW_H

#include "model.h"

#ifndef GL_EXT_texture_edge_clamp
#define GL_EXT_CLAMP_TO_EDGE                 0x812F
#endif



typedef struct {

	
    double valueOfRotationForPendulum;
	double bird_speed;

}Rotate;

/**
* Draw the model.
*/
void draw_model(const struct Model* model);

/**
* Draw the triangles of the model.
*/
void draw_triangles(const struct Model* model);

/**
* Draws the ground
*/
void draw_ground(int ground);

/*
* Draws the left side of the skybox
*/
void draw_skybox_left(Skybox skybox);

/*
* Draws the right side of the skybox
*/
void draw_skybox_right(Skybox skybox);

/*
* Draws the front side of the skybox
*/
void draw_skybox_front(Skybox skybox);

/*
* Draws the back side of the skybox
*/
void draw_skybox_back(Skybox skybox);

/*
* Draws the top of the skybox
*/
void draw_skybox_top(Skybox skybox);

/*
* Calls the draw_skybox_* and draw_ground methodes, makes the display lists
*/
void draw_environment(World world, Rotate* rotate);

/*
* Adds texture to the skybox
*/
void load_skybox(Skybox* skybox);

/**
* Calls draw_windmills and draw_teapot_for_light
*/
void draw_entities(World world);
#endif // DRAW_H

