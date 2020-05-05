/*
 * camera.h
 *
 *   Created by: Bodnár Márk Ármin	
 */
#ifndef CAMERA_H
#define CAMERA_H

#include "model.h"

#define CAMERA_SPEED 10.0

struct Camera
{
	struct Vertex position;
	struct Vertex pose;
	struct Vertex prev_position;
};


/*
* Converts degree to radian
*/
double degree_to_radian(double degree);
/*
* Checks if the camera can move. If it can't, loads the previous position.
*/
void can_move(struct Camera* camera);

/**
 * Initialize the camera position and direction.
 */
void init_camera(struct Camera* camera);

/**
 * Transform the models into the view point of the camera.
 */
void set_view_point(const struct Camera* camera);

/**
 * Rotate the camera horizontally and vertically.
 */
void rotate_camera(struct Camera* camera, double horizontal, double vertical);

/**
 * Move the camera forward.
 */
void move_camera_forward(struct Camera* camera, double distance);

/**
 * Move the camera backward.
 */
void move_camera_backward(struct Camera* camera, double distance);

/**
 * Step the camera left.
 */
void step_camera_left(struct Camera* camera, double distance);

/**
 * Step the camera right.
 */
void step_camera_right(struct Camera* camera, double distance);

/**
 * Move the camera up.
 */
void move_camera_up(struct Camera* camera, double distance);

/**
 * Move the camera down.
 */
void move_camera_down(struct Camera* camera, double distance);

#endif // CAMERA_H

