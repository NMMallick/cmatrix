#include <cmatrix/core.h>

int main(int argc, char **argv)
{
    Matrix2d mat = createMat2d(3,3);

    zero2d(&mat);
    print_mat2d(&mat);

    identity2d(&mat);
    print_mat2d(&mat);

    mat.mat[0][1] = 2.0;
    mat.mat[1][0] = 2.0;
    print_mat2d(&mat);

    free2d(&mat);
    return 0;
}
