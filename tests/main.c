#include <cmatrix/core.h>

int main(int argc, char **argv)
{
    Matrix2d mat = createMat2d(1,2);

    zero2d(&mat);
    print_mat2d(&mat);

    identity2d(&mat);
    print_mat2d(&mat);

    double count = 0.0;
    for(size_t i = 0; i < mat.rows; i++)
    	for(size_t j = 0; j < mat.cols; j++)
    	    mat.mat[i][j] = count++;

    print_mat2d(&mat);
    transpose2d(&mat);
    print_mat2d(&mat);

    free2d(&mat);
    return 0;
}
