// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: camara.h
// -- declaraciones de clase para el objeto camara de la práctica 5
//
// Autor: Pedro Domínguez López
//
// #############################################################################

#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

class Camara{
private:
	Tupla3f eye, at;
   	GLfloat old_x = 0, old_y = 0;

   	//Proyeccion
	float left, right, bottom, top, near, far;
	float zoom_factor;
	int tipo;				//Tipo de la camara: ortogonal (0) o perspectiva (1)

public:
	Camara(int tipo, Tupla3f eye, Tupla3f at, GLfloat near, GLfloat far);
	float x,y,z;

	void setObserver();
	void setProyeccion();
	void setVentana(float left, float right, float bottom, float top);

	void girar(float x, float y);
	void zoom(float factor);

	void mod_y(bool incr);
	void mod_x(bool incr);
};

#endif