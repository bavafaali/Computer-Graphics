#define _USE_MATH_DEFINES // To get M_PI defined
#include <math.h>
#include <cmath>
#include <stdio.h>
#include "algebra.h"

Vector CrossProduct(Vector a, Vector b) {
	Vector v = { a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x };
	return v;
}

float DotProduct(Vector a, Vector b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

Vector Subtract(Vector a, Vector b) {
	Vector v = { a.x-b.x, a.y-b.y, a.z-b.z };
	return v;
}    

Vector Add(Vector a, Vector b) {
	Vector v = { a.x+b.x, a.y+b.y, a.z+b.z };
	return v;
}    

float Length(Vector a) {
	return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

Vector Normalize(Vector a) {
	float len = Length(a);
	Vector v = { a.x/len, a.y/len, a.z/len };
	return v;
}

Vector ScalarVecMul(float t, Vector a) {
	Vector b = { t*a.x, t*a.y, t*a.z };
	return b;
}

HomVector MatVecMul(Matrix a, Vector b) {
	HomVector h;
	h.x = b.x*a.e[0] + b.y*a.e[4] + b.z*a.e[8] + a.e[12];
	h.y = b.x*a.e[1] + b.y*a.e[5] + b.z*a.e[9] + a.e[13];
	h.z = b.x*a.e[2] + b.y*a.e[6] + b.z*a.e[10] + a.e[14];
	h.w = b.x*a.e[3] + b.y*a.e[7] + b.z*a.e[11] + a.e[15];
	return h;
}

Vector Homogenize(HomVector h) {
	Vector a;
	if (h.w == 0.0) {
		fprintf(stderr, "Homogenize: w = 0\n");
		a.x = a.y = a.z = 9999999;
		return a;
	}
	a.x = h.x / h.w;
	a.y = h.y / h.w;
	a.z = h.z / h.w;
	return a;
}

Matrix MatMatMul(Matrix a, Matrix b) {
	Matrix c;
	int i, j, k;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			c.e[j*4+i] = 0.0;
			for (k = 0; k < 4; k++)
				c.e[j*4+i] += a.e[k*4+i] * b.e[j*4+k];
		}
	}
	return c;
}

void PrintVector(char const *name, Vector a) {
	printf("%s: %6.5lf %6.5lf %6.5lf\n", name, a.x, a.y, a.z);
}

void PrintHomVector(char const *name, HomVector a) {
	printf("%s: %6.5lf %6.5lf %6.5lf %6.5lf\n", name, a.x, a.y, a.z, a.w);
}

void PrintMatrix(char const *name, Matrix a) { 
	int i,j;

	printf("%s:\n", name);
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			printf("%6.5lf ", a.e[j*4+i]);
		}
		printf("\n");
	}
}

//Given three points on a surface, return the surface normal
Vector SurfaceNormal(Vector a, Vector b, Vector c)
{
    Vector v1 = Subtract(a, b);
    Vector v2 = Subtract(a, c);

    return Normalize(CrossProduct(v1, v2));
}

Matrix Translate(Vector translation)
{
    Matrix translation_mat = {0};

    translation_mat.e[0] = 1;
    translation_mat.e[5] = 1;
    translation_mat.e[10] = 1;
    translation_mat.e[12] = translation.x;
    translation_mat.e[13] = translation.y;
    translation_mat.e[14] = translation.z;
    translation_mat.e[15] = 1;

    //PrintMatrix("translation matrix:", translation_mat);

    return translation_mat;
}

Matrix Scale(Vector s)
{
    Matrix scale_mat = {0};

    scale_mat.e[0] = s.x;
    scale_mat.e[5] = s.y;
    scale_mat.e[10] = s.z;
    scale_mat.e[15] = 1;

    //PrintMatrix("scale matrix:", scale_mat);

    return scale_mat;
}

Matrix Rotate(float rotation_deg, char axis)
{
    float rotation_rad = rotation_deg * (M_PI / 180.0f);
    Matrix Rotate_mat = {0};

    if (axis == 'x'){

        Rotate_mat.e[0] = 1;
        Rotate_mat.e[5] = cos(rotation_rad);
        Rotate_mat.e[6] = sin(rotation_rad);
        Rotate_mat.e[9] = - sin(rotation_rad);
        Rotate_mat.e[10] = cos(rotation_rad);

    } else if (axis == 'y'){

        Rotate_mat.e[0] = cos(rotation_rad);
        Rotate_mat.e[2] = -sin(rotation_rad);
        Rotate_mat.e[5] = 1;
        Rotate_mat.e[8] = sin(rotation_rad);
        Rotate_mat.e[10] = cos(rotation_rad);

    } else if (axis == 'z') {

        Rotate_mat.e[0] = cos(rotation_rad);
        Rotate_mat.e[1] = sin(rotation_rad);
        Rotate_mat.e[4] = -sin(rotation_rad);
        Rotate_mat.e[5] = cos(rotation_rad);
        Rotate_mat.e[10] = 1;

    } else {
        return Rotate_mat;
    }
    
    Rotate_mat.e[15] = 1;

    //PrintMatrix("rotation matrix:", Rotate_mat);

    return Rotate_mat;
}

Matrix MatOrtho(float left, float right, float bottom, float top, float near, float far)
{
    Matrix ortho_proj_mat = {0};

    ortho_proj_mat.e[0] = 2 / (right - left);
    ortho_proj_mat.e[5] = 2 / (top - bottom);
    ortho_proj_mat.e[10] = 2 / (near - far);
    ortho_proj_mat.e[12] = (right + left) /(left - right);
    ortho_proj_mat.e[13] = (top + bottom) / (bottom - top);
    ortho_proj_mat.e[14] = (far + near) / (near - far);
    ortho_proj_mat.e[15] = 1;

    //PrintMatrix("orthogonal projection matrix:", ortho_proj_mat);

    return ortho_proj_mat;
}

Matrix MatPerpective(float fovy, float aspect, float near, float far)
{
    float fovy_rad = fovy * (M_PI / 180.0f);
    Matrix perspective_mat = {0};

    perspective_mat.e[0] = 1 / (aspect * std::tan(fovy_rad / 2));
    perspective_mat.e[5] = 1 / std::tan(fovy_rad/2);
    perspective_mat.e[10] = (far + near) / (near - far);
    perspective_mat.e[11] = -1;
    perspective_mat.e[14] = (2 * far * near) / (near - far);
    

    //PrintMatrix("perspective projection matrix:", perspective_mat);

    return perspective_mat;
}

Matrix ModelTranform(Vector scaling, Vector rotation, Vector translation)
{
    return MatMatMul(Translate(translation),
                     MatMatMul(Rotate(rotation.x, 'x'),
                               MatMatMul(Rotate(rotation.y, 'y'),
                                         MatMatMul(Rotate(rotation.z, 'z'),
                                                   Scale(scaling)))));
}

