// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: camara.h
// -- declaraciones de clase para el objeto camara de la práctica 4
//
// Autor: Pedro Domínguez López
//
// #############################################################################

#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

class Camara{
private:
	Tupla3f eye, at, up;	//Componentes de la luz

	int tipo;				//Tipo de la camara: ortogonal o perspectiva
	float left, rigth, near, far;

	rotarXExaminar(float angle);
	rotarYExaminar(float angle);
	rotarZExaminar(float angle);
	rotarXFirstPerson(float angle);
	rotarYFirstPerson(float angle);
	rotarZFirstPerson(float angle);
	mover(float x, float y, float z);
	zoom(float factor);

	setObserver(){ gluLookAt()};
	setProyeccion();

public:

};

#endif