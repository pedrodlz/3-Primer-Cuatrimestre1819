// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: ObjMallaIndexada.h
// -- declaraciones de clase ObjMallaIndexada (mallas indexadas) y derivados
//
//AUTOR: Pedro Domínguez López 3ºA
//
// #############################################################################

#ifndef OBJETOS_H_INCLUDED
#define OBJETOS_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class ObjMallaIndexada
{
   public:

   // función que redibuja el objeto
   // está función llama a 'draw_MI' (modo inmediato)
   // o bien a 'draw_MD' (modo diferido, VBOs)
   void draw(int modo_visu, bool usar_diferido) ;

   protected:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato();

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido();

   // dibuja el objeto en modo ajedrez
   void draw_Ajedrez();

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)
   GLuint CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram );

   GLuint vbo_vertices = 0;
   GLuint vbo_triangulos = 0;

   std::vector<Tupla3f> vertices ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> triangulos ; // una terna de 3 enteros por cada cara o triángulo

   // completar: tabla de colores, tabla de normales de vértices
} ;

// *****************************************************************************
//
// clases derivadas de ObjMallaIndexada (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad
// (tiene 9 vertices y 6 caras)

class Cubo : public ObjMallaIndexada
{
   public:
   Cubo() ;

} ;

// *****************************************************************************
// Tetraedro con centro en el origen
// (tiene 4 vertices y 4 caras)

class Tetraedro : public ObjMallaIndexada
{
   public:
   Tetraedro() ;

} ;

// *****************************************************************************
// objeto leído de un archivo PLY

class ObjPLY : public ObjMallaIndexada
{
   public:
      ObjPLY( const std::string & nombre_archivo );

} ;

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

class ObjRevolucion : public ObjMallaIndexada
{
    public:
      ObjRevolucion(){};
      //tapa_tipo-> 0:dos tapas, 1:tapa superior,2:tapa inferior,3:ninguna
      ObjRevolucion( const std::string & nombre_ply_perfil,const int tapa_tipo );
      ObjRevolucion( const std::vector<Tupla3f> & vertices_perfil,const int tapa_tipo );

    protected:
        void crearMalla( const std::vector<Tupla3f> & perfil_original,
            const int num_instancias_perf,const int tapa_tipo ) ;
    private:
        Tupla3f revolucionaPerfil( Tupla3f vertice_rotar,double alfa);
} ;

class Cilindro : public ObjRevolucion
{
    public:
        Cilindro( const int num_vert_perfil, const int num_instancias_perf );
} ;

class Cono : public ObjRevolucion
{
    public:
        Cono( const int num_vert_perfil, const int num_instancias_perf );
} ;

class Esfera : public ObjRevolucion
{
    public:
        Esfera( const int num_vert_perfil, const int num_instancias_perf );
} ;

#endif
