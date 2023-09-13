#include <cmatrix/core.h>

int main(int argc, char **argv)
{
    // (begin) test 1
    Matrix2d mat = createMat2d(5,5);

    zero2d(&mat);
    identity2d(&mat);

    double count = 0.0;
    for(size_t i = 0; i < mat.rows; i++)
    	for(size_t j = 0; j < mat.cols; j++)
    	    mat.mat[i][j] = count++;

    transpose2d(&mat);
    free2d(&mat);
    // (end) test 1

    // (begin) test 2
    Matrix2d a = createMat2d(24,4);
    Matrix2d b = createMat2d(4,1);

    identity2d(&a);
    identity2d(&b);

    double counter = 0.0;
    for (size_t i = 0; i < a.rows; i++)
	for (size_t j = 0; j < a.cols; j++)
	    a.mat[i][j] = counter++;

    for (size_t i = 0; i < b.rows; i++)
	for (size_t j = 0; j < b.cols; j++)
	    b.mat[i][j] = counter++;

    printf("a\n");
    print_mat2d(&a);

    printf("b\n");
    print_mat2d(&b);

    Matrix2d c = multiply2d(&a, &b);

    if (c.mat == NULL)
    {
	printf("err\n");
	exit(0);
    }

    printf("c matrix\n");
//    transpose2d(&c);
    print_mat2d(&c);
    printf("rows : %d\ncols: %d\n", c.rows, c.cols);

    free2d(&a);
    free2d(&b);
    free2d(&c);
    // (end) test 2
    return 0;
}
