#ifndef _MESH_H_
#define _MESH_H_

#include "algebra.h"

typedef struct _Triangle {
	int vInds[3]; //vertex indices
} Triangle;

typedef struct _Mesh { 
	int nv;
    int nt;
	
    Vector *vertices;
    Vector *fnorms;
	Vector *vnorms;
    
	Triangle *triangles;
	struct _Mesh *next;
    
    Vector scale;
    Vector rotate;
    Vector translate;
    
    Vector Ka;
    Vector Kd;
    Vector Ks;
    float alpha;
		
	unsigned int vbo, ibo, vao; // OpenGL handles for rendering
} Mesh;

void insertModel(Mesh ** list, int nv, float * vArr, int nt, int * tArr, Vector Ka, Vector Kd, Vector Ks, float alpha, Vector m_trans, Vector m_rotate, Vector m_scale, float scale = 1.0);

#endif
