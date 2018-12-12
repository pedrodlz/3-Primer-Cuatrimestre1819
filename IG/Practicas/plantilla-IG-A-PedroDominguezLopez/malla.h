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
#include "CImg.h"

using namespace cimg_library;

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

  struct Material
  {Tupla4f me,  //Emision
    ma,         //Ambiente
    md,         //Difusa
    ms;         //Especular
    int e;      //Brillo
  };

class ObjMallaIndexada
{
   public:

   // función que redibuja el objeto
   // está función llama a 'draw_MI' (modo inmediato)
   // o bien a 'draw_MD' (modo diferido, VBOs)
   void draw(int modo_visu, bool usar_diferido, GLenum numero_luz) ;
   void copiar_material(Material opc_material);
   void aplicar_prop();
   void cargar_textura(std::string imagen);
   void dibujar_cuadro();

   protected:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(GLenum numero_luz);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(GLenum numero_luz);

   // dibuja el objeto en modo ajedrez
   void draw_Ajedrez();

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)
   GLuint CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram );

   GLuint vbo_vertices = 0;
   GLuint vbo_triangulos = 0;

   std::vector<Tupla3f> vertices ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> triangulos ; // una terna de 3 enteros por cada cara o triángulo

   // tabla de normales de vértices y de caras
   std::vector<Tupla3f> nv ;
   std::vector<Tupla3f> nc ;

   //Struct con las propiedades del material 
   Material propiedades;

   std::vector<GLfloat> texCoords;  //Tabla con las coordenadas de la textura
   GLuint textura_id = 0;           //ID de la textura
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
      ObjRevolucion( const std::string & nombre_ply_perfil,const bool tapa_sup, 
        const bool tapa_inf  );
      ObjRevolucion( const std::vector<Tupla3f> & vertices_perfil,const bool tapa_sup, 
        const bool tapa_inf );

    protected:
        void crearMalla( const std::vector<Tupla3f> & perfil_original,
            const int num_instancias_perf,const bool tapa_sup, 
        const bool tapa_inf  ) ;
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

class Cuadro : public ObjMallaIndexada
{
    public:
        Cuadro();
};

#endif
