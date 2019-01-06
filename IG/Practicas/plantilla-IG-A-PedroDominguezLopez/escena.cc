//AUTOR: Pedro Domínguez López 3ºA

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
#include "luz.h"
#include "camara.h"

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    glEnable(GL_CULL_FACE);

    Front_plane = 0.1;
    Back_plane = 2000.0;
    Observer_distance = 2.0;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    //Establece una propiedades al material 
    Material opc_material;

    opc_material.me = { 0, 0, 0, 1.0 };
    opc_material.ma = { 0, 0, 0, 1.0 };
    opc_material.md = { 1, 1, 1, 1.0 };
    opc_material.ms = { 1, 1, 1, 1.0 };
    opc_material.e = 64;

    // crear los objetos de las prácticas: Mallas o Jerárquicos....
    /*cubo = new Cubo();
    tetraedro = new Tetraedro();*/
    obj_ply = new ObjPLY("./plys/beethoven.ply");
    obj_ply->copiar_material(opc_material);

    obj_rev = new ObjRevolucion("./plys/peon.ply",true,true);
    obj_rev->copiar_material(opc_material);

    cilindro = new Cilindro(4,20);
    cilindro->copiar_material(opc_material);

    cono = new Cono(30,20);
    cono->copiar_material(opc_material);

    esfera = new Esfera(30,20);
    esfera->copiar_material(opc_material);

    objetojerarquico = new ObjJerarquico(numero_luz1);
    objetojerarquico->copiar_material(opc_material);

    float brillo = 64.0;

    Tupla4f caf = { 1, 1, 1, 1} ,cdf = { 1, 1, 1, 1},
          csf = { 1, 1, 1, 1}, pos = { 1, 1, 1, 0};

    blanca = new Luz(numero_luz1,pos,caf,cdf,csf);

    caf = { 1, 1, 1, 1};
    cdf = { 1, 0, 1, 1};
    csf = { 1, 0, 1, 1};
    pos = { 5, 0, 10, 1};

    puntual = new Luz(numero_luz2, pos, caf, cdf, csf);

    imagen = new Cuadro();

    num_objetos = 7 ; // se usa al pulsar la tecla 'O' (rotar objeto actual)
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1, 1, 1, 1 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	redimensionar( UI_window_width, UI_window_height );
}

// **************************************************************************
// Funcion que dibuja el objeto activo actual, usando su método 'draw'
// (llamada desde Escena::dibujar)
// ***************************************************************************

void Escena::dibujar_objeto_actual()
{
   using namespace std ;

   // (1) configurar OpenGL para el modo actual (puntos/lineas/sólido)
   //    llamar glPolygonMode, glColor... (y alguna cosas más), según dicho modo
   // .........completar (práctica 1)

   glColor3f(0,0,0);
   glPointSize(3);

   // (2) dibujar el objeto actual usando método 'draw' del objeto asociado al
   // valor entero en 'objeto_actual'

   switch( objeto_actual )
   {
      case 0:
        if ( obj_ply != nullptr ){
          obj_ply->draw(modo,usar_diferido,numero_luz1);
          obj_ply->aplicar_prop();
        }
        break ;
      case 1:
        if ( imagen != nullptr ){
          imagen->cargar_textura("./img.jpeg");
          imagen->draw(modo,usar_diferido,numero_luz1);
        }
        break ;
      case 2:
        if ( esfera != nullptr ){
            esfera->draw(modo,usar_diferido,numero_luz1);
            esfera->aplicar_prop();
        }
        break;
      case 3:
          if ( obj_rev != nullptr ){
              obj_rev->draw(modo,usar_diferido,numero_luz1);
              obj_rev->aplicar_prop();
          }
          break ;
      case 4:
          if ( cilindro != nullptr ){
              cilindro->draw(modo,usar_diferido,numero_luz1);
              cilindro->aplicar_prop();
          }
          break;
      case 5:
          if ( cono != nullptr ){
            cono->draw(modo,usar_diferido,numero_luz1);
            cono->aplicar_prop();
          }
          break;
      case 6:
        if ( objetojerarquico != nullptr ){
            objetojerarquico->draw(modo,usar_diferido);
            objetojerarquico->aplicar_prop();
        }
        break ;
      default:
         cout << "draw_object: el número de objeto actual (" << objeto_actual << ") es incorrecto." << endl ;
         break ;
   }
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
   ejes.draw();
  glEnable(GL_NORMALIZE);
	dibujar_objeto_actual();
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;

    switch( toupper(tecla) )
    {
        case 'M' :
            //Cambiar de modo
            modo = (modo+1) % 4 ;
            cout << "modo actual == " << modo << endl ;
            break ;
        case 'O' :
            // activar siguiente objeto
            objeto_actual = (objeto_actual+1) % num_objetos ;
            cout << "objeto actual == " << objeto_actual << endl ;
            break;
        case 'V' :
            //Cambiar modo draw
            usar_diferido = !usar_diferido;
            break ;
        case 'P' :
            // activar el parámetro siguiente al actual
            objetojerarquico->siguienteParametro();
            break ;
        case 'A' :
            // activa o desactiva las animaciones
            conmutarAnimaciones();
            break ;
        case 'Z' :
            // incrementa el valor del parámetro actual del objeto jerárquico
            if(!anima_activ) objetojerarquico->incrementaParamAct();
            break ;
        case 'X' :
            // decrementa el valor del parámetro actual del objeto jerárquico
            if(!anima_activ) objetojerarquico->decrementaParamAct();
            break ;
        case '>' :
            // incrementar el valor de incremento/decremento usado para las animaciones
            objetojerarquico->acelerar();
            break ;
        case '<' :
            // decrementar el valor de incremento/decremento usado para las animaciones
            objetojerarquico->decelerar();
            break ;
        case 'L' :
            //Si la luz está activa se desactiva, y si está inactiva se activa
            if(glIsEnabled(numero_luz1)){
              std::cout << "LUZ DESACTIVADA" << std::endl;
              blanca->act_desact(numero_luz1,false);
              puntual->act_desact(numero_luz2,false);
            }
            else{
              std::cout << "LUZ ACTIVADA" << std::endl;
              blanca->act_desact(numero_luz1,true);
              puntual->act_desact(numero_luz2,true);
            }
            break ;
        case 'F' :
            glShadeModel(GL_FLAT);
            break;
        case 'S' :
            glShadeModel(GL_SMOOTH);
            break;
        case 'K' :
            //Rotacion de la luz puntual
            puntual->animar();
            break;
        case 'Q' :
            // salir
            return true ;
            break ;
    }
    return false ;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wy = 0.84*Front_plane,
   wx = ratio_xy*wy ;
   glFrustum( -wx, +wx, -wy, +wy, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
    Width = newWidth;
    Height = newHeight;
    change_projection( float(Width)/float(Height) );
    glViewport( 0, 0, Width, Height );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_x, 1.0 ,0.0, 0.0 );
   glRotatef( Observer_angle_y, 0.0, 1.0, 0.0 );
}

//**************************************************************************
// Funcion encargada de activar/desactivar las animaciones
//***************************************************************************

void Escena::conmutarAnimaciones()
{
    anima_activ = !anima_activ;

    if(anima_activ){
        objetojerarquico->inicioAnimaciones();
        glutIdleFunc( funcion_desocupado );
    }
    else glutIdleFunc( nullptr );
}

//**************************************************************************
// Funcion encargada de actualizar el estado de los parámetros del objeto jerárquico
//***************************************************************************

void Escena::mgeDesocupado()
{
    objetojerarquico->actualizarEstado();
    glutPostRedisplay();
}
