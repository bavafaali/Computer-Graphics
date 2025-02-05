#ifndef _MESH_H_
#define _MESH_H_

#include "algebra.h"

typedef struct _Triangle {
	int vInds[3]; //vertex indices
} Triangle;

typedef struct _Mesh { 
	int nv;				
	Vector *vertices;
	Vector *vnorms;
	int nt;				
	Triangle *triangles;
	struct _Mesh *next;
    
    Vector scale;
    Vector rotate;
    Vector translate;
		
	unsigned int vbo, ibo, vao; // OpenGL handles for rendering
} Mesh;

void insertModel(Mesh ** list, int nv, float * vArr, int nt, int * tArr, Vector m_trans, Vector m_rotate, Vector m_scale, float scale = 1.0);

#endif
