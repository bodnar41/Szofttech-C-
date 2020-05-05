/*
 * draw.c
 *
 *   Created by: Bodnár Márk Ármin	
 */
#include "draw.h"
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

double skybox_size = 950;
GLuint displayList1;
double rotateAngle = 0;


void draw_quads(const struct Model* model)
{
    int i, k;
    int vertex_index, texture_index, normal_index;
    double x, y, z, u, v;

	glBegin(GL_QUADS);

    for (i = 0; i < model->n_quads; ++i) {
        for (k = 0; k < 4; ++k) {

            texture_index = model->quads[i].points[k].texture_index;
            u = model->texture_vertices[texture_index].u;
            v = model->texture_vertices[texture_index].v;
            // NOTE: The 1-v is model file specific!
            glTexCoord2f(u, 1-v);

            vertex_index = model->quads[i].points[k].vertex_index;
            x = model->vertices[vertex_index].x;
            y = model->vertices[vertex_index].y;
            z = model->vertices[vertex_index].z;
            glVertex3d(x, y, z);
        }
    }    

    glEnd();
}
void draw_model(const struct Model* model)
{
	draw_triangles(model);
	draw_quads(model);
}

void draw_triangles(const struct Model* model)
{
	int i, k;
	int vertex_index, texture_index, normal_index;
	double x, y, z, normal_x, normal_y, normal_z, u, v;

	glBegin(GL_TRIANGLES);

	for (i = 0; i < model->n_triangles; ++i) {
		for (k = 0; k < 3; ++k) {
			normal_index = model->triangles[i].points[k].normal_index;
			normal_x = model->normals[normal_index].x;
			normal_y = model->normals[normal_index].y;
			normal_z = model->normals[normal_index].z;
			glNormal3d(normal_x, normal_y, normal_z);

			vertex_index = model->triangles[i].points[k].vertex_index;
			x = model->vertices[vertex_index].x;
			y = model->vertices[vertex_index].y;
			z = model->vertices[vertex_index].z;
            switch(k){
            case 0:
                glTexCoord2f(0, 0);
                break;
            case 1:
                glTexCoord2f(0.1*z, 0);
                break;
            case 2:
                glTexCoord2f(0, 0.01);
                break;
            }
			glVertex3d(x, y, z);

		}
	}

	glEnd();
}

void draw_normals(const struct Model* model, double length)
{
	int i;
	double x1, y1, z1, x2, y2, z2;

	glColor3f(0, 0, 1);

	glBegin(GL_LINES);

	for (i = 0; i < model->n_vertices; ++i) {
		x1 = model->vertices[i].x;
		y1 = model->vertices[i].y;
		z1 = model->vertices[i].z;
		x2 = x1 + model->normals[i].x * length;
		y2 = y1 + model->normals[i].y * length;
		z2 = z1 + model->normals[i].z * length;
		glVertex3d(x1, y1, z1);
		glVertex3d(x2, y2, z2);
	}
	glEnd();
}

void draw_ground(int ground) {
	glBindTexture(GL_TEXTURE_2D, ground);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBegin(GL_QUADS);
	int x, z;
	for (x = -skybox_size; x < skybox_size; x += 50) {
		for (z = -skybox_size; z < skybox_size; z += 50) {
			glTexCoord2f(0.0, 0.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x, 0, z);
			glTexCoord2f(1.0, 0.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x + 50, 0, z);
			glTexCoord2f(1.0, 1.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x + 50, 0, z + 50);
			glTexCoord2f(0.0, 1.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x, 0, z + 50);
		}
	}
	glEnd();
}
void draw_skybox_left(Skybox skybox) {
	glBindTexture(GL_TEXTURE_2D, skybox.left);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-skybox_size, 0, -skybox_size);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-skybox_size, skybox_size, -skybox_size);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-skybox_size, skybox_size, skybox_size);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-skybox_size, 0, skybox_size);
	glEnd();
}
void draw_skybox_right(Skybox skybox) {
	glBindTexture(GL_TEXTURE_2D, skybox.right);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(skybox_size, 0, skybox_size);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(skybox_size, skybox_size, skybox_size);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(skybox_size, skybox_size, -skybox_size);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(skybox_size, 0, -skybox_size);
	glEnd();
}
void draw_skybox_front(Skybox skybox) {
	glBindTexture(GL_TEXTURE_2D, skybox.front);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-skybox_size, 0, -skybox_size);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(skybox_size, 0, -skybox_size);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(skybox_size, skybox_size, -skybox_size);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-skybox_size, skybox_size, -skybox_size);
	glEnd();
}
void draw_skybox_back(Skybox skybox) {
	glBindTexture(GL_TEXTURE_2D, skybox.back);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-skybox_size, 0, skybox_size);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-skybox_size, skybox_size, skybox_size);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(skybox_size, skybox_size, skybox_size);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(skybox_size, 0, skybox_size);
	glEnd();
}
void draw_skybox_top(Skybox skybox) {
	glBindTexture(GL_TEXTURE_2D, skybox.top);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(skybox_size, skybox_size, skybox_size);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(skybox_size, skybox_size, -skybox_size);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-skybox_size, skybox_size, -skybox_size);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-skybox_size, skybox_size, skybox_size);


	glEnd();
}
void draw_environment(World world, Rotate* rotate) {
	glEnable(GL_TEXTURE_2D);
   
   GLfloat material_ambient[] = {0.9, 0.9, 0.9, 1};
   GLfloat material_ambient_2[] = {0.1, 0.3, 0.6, 1};
	displayList1 = glGenLists(1);
	glNewList(displayList1, GL_COMPILE);
	
//Bird 	
		glPushMatrix();
		glTranslatef(0, 300, 50);
		glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient_2);
		glBindTexture(GL_TEXTURE_2D, world.bird.texture);
		glRotatef(rotate->valueOfRotationForPendulum, 0, 0, -1);
		glScalef(300.0f, 300.0f, 300.0f);
		draw_model(&world.bird.model);
		glPopMatrix();
		
	glEndList();

//Duckling
		glPushMatrix();
			glTranslatef(-600, 0, -30);
			glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
			
			glBindTexture(GL_TEXTURE_2D, world.duckling.texture);
			glScalef(1.4f, 1.4f, 1.4f);			
			draw_model(&world.duckling.model);	
	
		glPopMatrix();
		
//Mallard		
		glPushMatrix();
			glTranslatef(-600, 0, -100);
			glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
			
			glBindTexture(GL_TEXTURE_2D, world.mallard.texture);
			glScalef(0.8f, 0.8f, 0.8f);			
			draw_model(&world.mallard.model);	
	
		glPopMatrix();
		
//Deer		
		glPushMatrix();
			glTranslatef(0, 0, 100);
			glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
			
			glBindTexture(GL_TEXTURE_2D, world.deer.texture);
			glScalef(2.0f, 2.0f, 2.0f);			
			draw_model(&world.deer.model);	
	
		glPopMatrix();
		
//Fox		
		glPushMatrix();
			glTranslatef(200, 0, -100);
			glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
			
			glBindTexture(GL_TEXTURE_2D, world.fox.texture);
			glScalef(0.6f, 0.6f, 0.6f);			
			draw_model(&world.fox.model);	
	
		glPopMatrix();
		
//Trees
	/*	glPushMatrix();
			glTranslatef(700, 0, 20);
			glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
			
			glBindTexture(GL_TEXTURE_2D, world.tree1.texture);
			glScalef(30.0f, 30.0f, 30.0f);			
			draw_model(&world.tree1.model);	
	
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(-700, 0, -20);
			glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
			
			glBindTexture(GL_TEXTURE_2D, world.tree2.texture);
			glScalef(30.0f, 30.0f, 30.0f);			
			draw_model(&world.tree2.model);	
	
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(-300, 0, -400);
			glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
			
			glBindTexture(GL_TEXTURE_2D, world.tree3.texture);
			glScalef(30.0f, 30.0f, 30.0f);		
			draw_model(&world.tree3.model);	
	
		glPopMatrix();
			glPushMatrix();
			glTranslatef(300, 0, 400);
			glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
			
			glBindTexture(GL_TEXTURE_2D, world.tree4.texture);
			glScalef(30.0f, 30.0f, 30.0f);		
			draw_model(&world.tree4.model);	
	
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(-100, 0, 200);
			glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
			
			glBindTexture(GL_TEXTURE_2D, world.tree5.texture);
			glScalef(30.0f, 30.0f, 30.0f);		
			draw_model(&world.tree5.model);	
	
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(100, 0, -800);
			glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
			
			glBindTexture(GL_TEXTURE_2D, world.tree6.texture);
			glScalef(30.0f, 30.0f, 30.0f);		
			draw_model(&world.tree6.model);	
	
		glPopMatrix();
 */
	GLfloat zeros[] = { 0, 0, 0 };
	GLfloat ones[] = { 1, 1, 1 };
	
	
	glMaterialfv(GL_FRONT, GL_DIFFUSE, zeros);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ones);
	draw_ground(world.ground);



	draw_skybox_left(world.skybox);
	draw_skybox_right(world.skybox);
	draw_skybox_front(world.skybox);
	draw_skybox_back(world.skybox);
	draw_skybox_top(world.skybox);

	glDisable(GL_TEXTURE_2D);

}
void load_skybox(Skybox* skybox) {
	skybox->front = load_texture("textures//erdo.jpg");
	skybox->left = load_texture("textures//erdo.jpg");
	skybox->right = load_texture("textures//erdo.jpg");
	skybox->back = load_texture("textures//erdo.jpg");
	skybox->top = load_texture("textures//egbolt.jpg");
}

void draw_grandbird(World world) 
{

			glPushMatrix();
			
				glCallList(displayList1);
			
			glPopMatrix();
}



void draw_entities(World world) {
	glEnable(GL_TEXTURE_2D);
	draw_grandbird(world);

	
	glDisable(GL_TEXTURE_2D);
}







