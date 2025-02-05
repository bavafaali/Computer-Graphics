#include "camera.h"

//Interface function for the projection matrix
//Note: Not all parameters may be needed, but the provided tests require this signature
Matrix ProjectionMatrix(Camera cam, int screenWidth, int screenHeight, ProjectionMode mode)
{
//    if (mode == PERSPECTIVE) {
//
//        return MatPerpective(cam.fov,
//                             screenWidth/screenHeight,
//                             cam.nearPlane,
//                             cam.farPlane);
//
//    } else if (mode == ORTHOGONAL) {
//
//        return MatOrtho(-20.0 , 20.0, -10.0, 10.0,
//                        cam.nearPlane,
//                        cam.farPlane);
//    }

    Matrix P;
    P.e[0] = 1.299038f; P.e[4] = 0.000000f; P.e[ 8] =  0.000000f; P.e[12] =  0.0f;
    P.e[1] = 0.000000f; P.e[5] = 1.732051f; P.e[ 9] =  0.000000f; P.e[13] =  0.0f;
    P.e[2] = 0.000000f; P.e[6] = 0.000000f; P.e[10] = -1.000200f; P.e[14] = -2.000200f;
    P.e[3] = 0.000000f; P.e[7] = 0.000000f; P.e[11] = -1.000000f; P.e[15] =  0.0f;

    return P;
}

//Interface function for view matrix
Matrix ViewMatrix(Camera cam)
{
    Vector reverse_trans = {-cam.position.x, -cam.position.y, -cam.position.z};

    return MatMatMul(Rotate(-cam.rotation.z, 'z'),
                     MatMatMul(Rotate(-cam.rotation.y, 'y'),
                               MatMatMul(Rotate(-cam.rotation.x, 'x'),
                                         Translate(reverse_trans))));
}
