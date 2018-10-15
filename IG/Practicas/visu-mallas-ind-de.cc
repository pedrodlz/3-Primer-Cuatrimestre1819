// suponiendo que las tablas son tablas de la librería estandard, declaradas así:

std::vector<Tupla3f> vertices ; // coords de vértices (3 valores 'float' por vértice)
std::vector<Tupla3i> triangulos ; // indices de vertices de triángulos (3 valores 'int' por cada cara (triángulo)

// entonces podemos visualizar en modo inmediato usando 'glDrawElements', así:

glEnableClientState( GL_VERTEX_ARRAY );
glVertexPointer( 3, GL_FLOAT, 0, vertices.data() ) ;
glDrawElements( GL_TRIANGLES, triangulos.size()*3, GL_UNSIGNED_INT, triangulos.data() );
glDisableClientState( GL_VERTEX_ARRAY );
