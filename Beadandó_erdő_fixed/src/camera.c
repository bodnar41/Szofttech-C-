/*
 * camera.c
 *
 *   Created by: Bodnár Márk Ármin	
 */
#include "camera.h"
#include <GL/glut.h>
#include <math.h>

#define M_PI 3.14159265358979323846
#define size 950

double degree_to_radian(double degree)
{
	return degree * M_PI / 180.0;
}

void can_move(struct Camera* camera)
{
    if(camera->position.x>size || camera->position.x<-size || camera->position.z<-size || camera->position.z>size)
        camera->position=camera->prev_position;

	if(camera->position.x > -190 && camera->position.x < 190 && camera->position.y > -150 && camera->position.y < 150) {
		if (camera->position.x>-10 && camera->position.x<10) {
			if((camera->position.z < -160 && camera->position.z > -140 && camera->position.y < 125)||(camera->position.z < -140 && camera->position.z > -160 && camera->position.y > -7 && camera->position.y < 125)){
				camera->position=camera->prev_position;
			}
		}
	}
}

void init_camera(struct Camera* camera)
{
	camera->position.x = 0;
	camera->position.y = 150;
	camera->position.z = 0;

	camera->pose.x = 0;
	camera->pose.y = 0;
	camera->pose.z = -180;
}

void set_view_point(const struct Camera* camera)
{
	glRotatef(-(camera->pose.x), 1.0, 0, 0);
	glRotatef(-(camera->pose.z), 0, 1.0, 0);
    
	glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
    
}

void rotate_camera(struct Camera* camera, double horizontal, double vertical)
{
	camera->pose.z += horizontal;
	camera->pose.x += vertical;

	if (camera->pose.z < 0) {
		camera->pose.z += 360.0;
	}

	if (camera->pose.z > 360.0) {
		camera->pose.z -= 360.0;
	}

	if (camera->pose.x < 0) {
		camera->pose.x += 360.0;
	}

	if (camera->pose.x > 360.0) {
		camera->pose.x -= 360.0;
	}
}

void move_camera_forward(struct Camera* camera, double distance)
{
	camera->prev_position = camera->position;
	double angle = degree_to_radian(camera->pose.z);

	camera->position.z -= cos(angle) * distance;
	camera->position.x -= sin(angle) * distance;
    can_move(camera);
}

void move_camera_backward(struct Camera* camera, double distance)
{
	camera->prev_position = camera->position;
	double angle = degree_to_radian(camera->pose.z);

	camera->position.z += cos(angle) * distance;
	camera->position.x += sin(angle) * distance;
    can_move(camera);
}

void step_camera_left(struct Camera* camera, double distance)
{
	camera->prev_position = camera->position;
	double angle = degree_to_radian(camera->pose.z + 90.0);

	camera->position.z -= cos(angle) * distance;
	camera->position.x -= sin(angle) * distance;
    can_move(camera);
}

void step_camera_right(struct Camera* camera, double distance)
{
	camera->prev_position = camera->position;
	double angle = degree_to_radian(camera->pose.z - 90.0);

	camera->position.z -= cos(angle) * distance;
	camera->position.x -= sin(angle) * distance;
    can_move(camera);
}

void move_camera_up(struct Camera* camera, double distance)
{
	camera->prev_position = camera->position;
    if(camera->position.y<size-10)
	camera->position.y += distance;
    can_move(camera);
}

void move_camera_down(struct Camera* camera, double distance)
{
	camera->prev_position = camera->position;
	if(camera->position.y>10)
	camera->position.y -= distance;
    can_move(camera);
}



