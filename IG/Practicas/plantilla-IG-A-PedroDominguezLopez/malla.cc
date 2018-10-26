//AUTOR: Pedro Domínguez López 3ºA

#include "aux.h"
#include "ply_reader.h"
#include "malla.h"

// *****************************************************************************
//
// Clase ObjMallaIndexada
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void ObjMallaIndexada::draw_ModoInmediato()
{
  // habilitar uso de un array de vértices
  glEnableClientState( GL_VERTEX_ARRAY );

  // indicar el formato y la dirección de memoria del array de vértices
  // (son tuplas de 3 valores float, sin espacio entre ellas)
  glVertexPointer( 3, GL_FLOAT, 0, vertices.data() ) ;

  // visualizar, indicando: tipo de primitiva, número de índices,
  // tipo de los índices, y dirección de la tabla de índices
  glDrawElements( GL_TRIANGLES, triangulos.size()*3, GL_UNSIGNED_INT,
                  triangulos.data() );

  // deshabilitar array de vértices
  glDisableClientState( GL_VERTEX_ARRAY );
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void ObjMallaIndexada::draw_ModoDiferido()
{
    if(vbo_vertices == 0)
         vbo_vertices = CrearVBO(GL_ARRAY_BUFFER,sizeof (int)*3*vertices.size(),vertices.data());
    if(vbo_triangulos == 0)
        vbo_triangulos = CrearVBO(GL_ARRAY_BUFFER,sizeof (int)*3*triangulos.size(),triangulos.data());

    // especificar localización y formato de la tabla de vértices, habilitar tabla

    glBindBuffer( GL_ARRAY_BUFFER, vbo_vertices ); // activar VBO de vértices
    glVertexPointer( 3, GL_FLOAT, 0, 0 );    // especifica formato y offset (=0)
    glBindBuffer( GL_ARRAY_BUFFER, 0 );    // desactivar VBO de vértices.
    glEnableClientState( GL_VERTEX_ARRAY );    // habilitar tabla de vértices

    // visualizar triángulos con glDrawElements (puntero a tabla == 0)

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vbo_triangulos );// activar VBO de triángulos
    glDrawElements( GL_TRIANGLES, 3*triangulos.size(), GL_UNSIGNED_INT, 0 ) ;
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );    // desactivar VBO de triángulos

    // desactivar uso de array de vértices
    glDisableClientState( GL_VERTEX_ARRAY );
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void ObjMallaIndexada::draw(int modo_visu, bool usar_diferido)
{
    if(vertices.empty()) std::cout << "VACIO" << std::endl;

    switch(modo_visu)
    {
        case 0:
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            break;
        case 1:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
        case 2:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
        case 3:
            draw_Ajedrez();
            break;
    }

    if(modo_visu!=3){
        if(usar_diferido) draw_ModoDiferido();
        else draw_ModoInmediato();
    }
}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// dibuja la malla en modo ajedrez
void ObjMallaIndexada::draw_Ajedrez()
{
    //Dividimos el vector de triangulos en 2 vectores
    std::vector<Tupla3i> triangulos_1, triangulos_2 ;

    for(int i = 0; i < triangulos.size(); i++){
        if(i%2 == 0) triangulos_1.push_back(triangulos[i]);
        else triangulos_2.push_back(triangulos[i]);
    }


    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, vertices.data() ) ;

    glColor3f(0,0,0);

    //Llamamos a la funcion para el primer vector
    glDrawElements( GL_TRIANGLES, triangulos_1.size()*3, GL_UNSIGNED_INT,
                    triangulos_1.data() );

    //Seleccionamos otro color
    glColor3f(0.07,0.89,0.89);

    //Llamamos a la funcion para el segundo vector
    glDrawElements( GL_TRIANGLES, triangulos_2.size()*3, GL_UNSIGNED_INT,
                    triangulos_2.data() );

    // deshabilitar array de vértices
    glDisableClientState( GL_VERTEX_ARRAY );

}

// -----------------------------------------------------------------------------
// Recalcula la tabla de normales de vértices (el contenido anterior se pierde)

void ObjMallaIndexada::calcular_normales()
{
   // completar .....(práctica 2)
}

GLuint ObjMallaIndexada::CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram )
{
    GLuint id_vbo ;                 // resultado: identificador de VBO
    glGenBuffers( 1, & id_vbo );    // crear nuevo VBO, obtener identificador (nunca 0)
    glBindBuffer( tipo_vbo, id_vbo ); // activar el VBO usando su identificador

    // esta instrucción hace la transferencia de datos desde RAM hacia GPU
    glBufferData( tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW );

    glBindBuffer( tipo_vbo, 0 );    // desactivación del VBO (activar 0)
    return id_vbo ;                 // devolver el identificador resultado
}


// *****************************************************************************
//
// Clase Cubo (práctica 1)
//
// *****************************************************************************

Cubo::Cubo()
{

    float tamanio = 0.5;

   // inicializar la tabla de vértices
   vertices =  {  { -tamanio, -tamanio, -tamanio }, // 0
                  { -tamanio, -tamanio, +tamanio }, // 1
                  { -tamanio, +tamanio, -tamanio }, // 2
                  { -tamanio, +tamanio, +tamanio }, // 3
                  { +tamanio, -tamanio, -tamanio }, // 4
                  { +tamanio, -tamanio, +tamanio }, // 5
                  { +tamanio, +tamanio, -tamanio }, // 6
                  { +tamanio, +tamanio, +tamanio }  // 7
               };

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   triangulos = { { 0, 2, 4 }, { 4, 2, 6 },
                  { 1, 5, 3 }, { 3, 5, 7 },
                  { 1, 3, 0 }, { 0, 3, 2 },
                  { 5, 4, 7 }, { 7, 4, 6 },
                  { 1, 0, 5 }, { 5, 0, 4 },
                  { 3, 7, 2 }, { 2, 7, 6 }
                } ;
}

// *****************************************************************************
//
// Clase Tetraedro (práctica 1)
//
// *****************************************************************************

Tetraedro::Tetraedro()
{
    float tamanio = 0.5;

    // inicializar la tabla de vértices
    vertices =  {  { 0, -tamanio, -tamanio }, // 0
                   { -tamanio, -tamanio, +tamanio }, // 1
                   { +tamanio, -tamanio, +tamanio }, // 2
                   { 0, +tamanio, 0 }, // 3
                };

    // inicializar la tabla de caras o triángulos:
    // (es importante en cada cara ordenar los vértices en sentido contrario
    //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

    triangulos = { { 0, 2, 3 },
                   { 2, 1, 3 },
                   { 1, 0, 3 },
                   { 0, 1, 2 }};
}

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, vertices, triangulos );

}


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion( const std::string & nombre_ply_perfil,
    const int tapa_tipo )
{
    int num_instancias = 20;

    std::vector<Tupla3f> vertices_tmp;
    ply::read_vertices(nombre_ply_perfil,vertices_tmp);
    crearMalla(vertices_tmp,num_instancias,tapa_tipo);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un vector de vertices

ObjRevolucion::ObjRevolucion( const std::vector<Tupla3f> & vertices_perfil,
    const int tapa_tipo )
{
    int num_instancias = 20;

    crearMalla(vertices_perfil,num_instancias,tapa_tipo);
}

// *****************************************************************************
// aplica la rotacion a un vertice pasado como argumento

Tupla3f ObjRevolucion::revolucionaPerfil(Tupla3f vertice_rotar, double alfa)
{
    Tupla3f vertice_res;

    vertice_res(0) = ((vertice_rotar(0) * cos(alfa)) + (vertice_rotar(2)*sin(alfa)));
    vertice_res(1) = vertice_rotar(1);
    vertice_res(2) = ((vertice_rotar(0)*(-sin(alfa))) + (vertice_rotar(2)*cos(alfa)));

    return vertice_res;
}

// *****************************************************************************
// añade los nuevos vertices tras la rotacion y añade las caras y las tapas si
// las tiene

void ObjRevolucion::crearMalla(const std::vector<Tupla3f> & perfil_original,
    const int num_instancias_perf, const int tapa_tipo )
{
    const double PI = 3.1415926545;
    int num_vert_perfil = perfil_original.size(), a, b,c;
    double alfa = 0;

    //Añade los vertices tras la rotacion
    for(int i = 0; i < num_instancias_perf; i++){
        for(int j = 0; j < num_vert_perfil; j++){
            double alfa_r = (2*PI*i)/num_instancias_perf;
            vertices.push_back(revolucionaPerfil(perfil_original[j],alfa_r));
        }
    }

    //Añade las caras
    for(int i = 0; i < num_instancias_perf; i ++){
        for(int j = 0; j < num_vert_perfil - 1; j++){
            a = (num_vert_perfil*i) + j;
            b = (num_vert_perfil*((i+1)%num_instancias_perf)) + j;
            triangulos.push_back({a,b,b+1});
            triangulos.push_back({a,b+1,a+1});
        }
    }

    //Primero comprueba que se quiera al menos una tapa
    if(tapa_tipo < 3 && tapa_tipo >= 0){

        if (tapa_tipo == 0){//Añade vertices con y == 0
            vertices.push_back({0,perfil_original[0](1),0});
            vertices.push_back({0,perfil_original[num_vert_perfil-1](1),0});
        }
        else if(tapa_tipo == 1){//Solo añade el vertice superior con y == 0
            vertices.push_back(perfil_original[0]);
            vertices.push_back({0,perfil_original[num_vert_perfil-1](1),0});
        }
        else if(tapa_tipo == 2){//Solo añade el vertice inferior con y == 0
            vertices.push_back({0,perfil_original[0](1),0});
            vertices.push_back(perfil_original[num_vert_perfil-1]);
        }

        //Tapa inferior
        if(tapa_tipo != 1){

            a = num_instancias_perf*num_vert_perfil;

            for(int i = 0; i < num_instancias_perf; i++){
                b = num_vert_perfil*i;
                c = (num_vert_perfil*((i+1)%num_instancias_perf));
                triangulos.push_back({a,b,c});
            }
        }

        //Tapa superior
        if(tapa_tipo != 2){
            a = (num_instancias_perf*num_vert_perfil) + 1;

            for(int i = 0; i < num_instancias_perf; i++){
                b = (num_vert_perfil*(i+1)) - 1;
                c = (num_vert_perfil*(((i+1)%num_instancias_perf)+1)) - 1;
                triangulos.push_back({a,b,c});
            }
        }
    }
}

// *****************************************************************************
//
// Clase Cilindro (práctica 2)
//
// *****************************************************************************

Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf ){

    std::vector<Tupla3f> perfil;
    float radio = 0.5;
    float altura = 1;

    for(int i = 0; i < num_vert_perfil; i++){
        float y = altura * ((float)i/(num_vert_perfil - 1));
        perfil.push_back({radio,y,0});
    }

    crearMalla(perfil,num_instancias_perf,0);
}

// *****************************************************************************
//
// Clase Cono (práctica 2)
//
// *****************************************************************************

Cono::Cono(const int num_vert_perfil, const int num_instancias_perf ){

    std::vector<Tupla3f> perfil;
    float radio = 0.5;
    float altura = 1;

    for(int i = 0; i < num_vert_perfil; i++){
        float x = (1 - (float) i / (num_vert_perfil - 1)) * radio;
        float y = (-altura/radio)* x + altura;
        perfil.push_back({x,y,0});
    }

    crearMalla(perfil,num_instancias_perf,0);
}

// *****************************************************************************
//
// Clase Esfera (práctica 2)
//
// *****************************************************************************

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf ){

    std::vector<Tupla3f> perfil;
    float radio = 0.5;

    for (int i = 0; i < num_vert_perfil; i++) {
        float y = radio * (-1 + (float) 2 * i / (num_vert_perfil - 1));
        perfil.push_back({sqrt(radio * radio - y * y), y, 0.0});
    }

    crearMalla(perfil,num_instancias_perf,3);
}
