// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: camara.cc
// -- implementación del objeto camara de la práctica 5
//
// Autor: Pedro Domínguez López
//
// #############################################################################

#include "camara.h"

Camara::Camara (int tipo_c, Tupla3f eye, Tupla3f at, GLfloat near, GLfloat far)
{
	tipo = tipo_c;
   	this->eye = eye;
   	this->at = at;
   	this->near = near;
   	this->far = far;

   	x = eye(0);
   	y = eye(1);
   	z = eye(2);
   	zoom_factor = 1;
}

void Camara::setVentana(float left, float right, float bottom, float top)
{
	this->left = left;
	this->right = right;
	this->bottom = bottom;
	this->top = top;
}


void Camara::mod_y(bool incr)
{
	if(incr) y++;
	else y--;
}
void Camara::mod_x(bool incr)
{
	if(incr) x++;
	else x--;
}

void Camara::zoom(float factor)
{
	zoom_factor *= factor;
	setProyeccion();
}

void Camara::girar(float x, float y)
{
	this->x = y + old_y;
   	this->y = x + old_x;

    glRotatef(this->x,1,0,0);
	glRotatef(this->y,0,1,0);

   	old_x = x;
   	old_y = y;

   	glutPostRedisplay();
}

void Camara::setProyeccion()
{
	glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

	if(tipo == 0){
		glOrtho(left*zoom_factor, right*zoom_factor, bottom*zoom_factor, top*zoom_factor, near, far);
	}
	else if(tipo == 1){
		glFrustum(left*zoom_factor, right*zoom_factor, bottom*zoom_factor, top*zoom_factor, near, far);
	}

	glutPostRedisplay();
}

void Camara::setObserver()
{
	glTranslatef(0,0,-z);
    glRotatef(x,1,0,0);
	glRotatef(y,0,1,0);
	//gluLookAt(eye(0),eye(1),eye(2),at(0),at(1),at(2),0,1,0);
}