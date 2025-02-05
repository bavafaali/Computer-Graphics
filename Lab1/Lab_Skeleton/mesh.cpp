#include <stdlib.h>
#include "mesh.h"
#include <assert.h>
float rnd() {
	return 2.0f * float(rand()) / float(RAND_MAX) - 1.0f;
}

void insertModel(Mesh ** list, int nv, float * vArr, int nt, int * tArr, Vector m_trans, Vector m_rotate, Vector m_scale, float scale) {
    
	Mesh* mesh = (Mesh*)malloc(sizeof(Mesh));
	mesh->nv = nv;
	mesh->nt = nt;
	mesh->vertices = (Vector*)malloc(nv * sizeof(Vector));
	mesh->vnorms = (Vector*)malloc(nv * sizeof(Vector));
	mesh->triangles = (Triangle*)malloc(nt * sizeof(Triangle));
    mesh->translate = m_trans;
    mesh->rotate = m_rotate;
    mesh->scale = m_scale;
    
	// set mesh vertices
	for (int i = 0; i < nv; i++) {
		mesh->vertices[i].x = vArr[i * 3] * scale;
		mesh->vertices[i].y = vArr[i * 3 + 1] * scale;
		mesh->vertices[i].z = vArr[i * 3 + 2] * scale;
	}

	// set mesh triangles
	for (int i = 0; i < nt; i++) {
		mesh->triangles[i].vInds[0] = tArr[i * 3];
		mesh->triangles[i].vInds[1] = tArr[i * 3 + 1];
		mesh->triangles[i].vInds[2] = tArr[i * 3 + 2];
	}
    
    // vertex normals
    for (int i = 0; i < nt; i++) {
        int idx1 = mesh->triangles[i].vInds[0];
        int idx2 = mesh->triangles[i].vInds[1];
        int idx3 = mesh->triangles[i].vInds[2];
        
        Vector norm = SurfaceNormal(mesh->vertices[idx1],
                                    mesh->vertices[idx2],
                                    mesh->vertices[idx3]);
        
        mesh->vnorms[idx1] = Normalize(Add(mesh->vnorms[idx1], norm));
        mesh->vnorms[idx2] = Normalize(Add(mesh->vnorms[idx2], norm));
        mesh->vnorms[idx3] = Normalize(Add(mesh->vnorms[idx3], norm));
    }
    
	mesh->next = *list;
	*list = mesh;
}
