#include <cmatrix/core.h>
#include <time.h>

void Test_Transpose()
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
}

void Test_Multiply()
{
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
    print_mat2d(&c);
    printf("rows : %d\ncols: %d\n", c.rows, c.cols);

    free2d(&a);
    free2d(&b);
    free2d(&c);
    // (end) test 2
}

void Test_Inverse()
{
    Matrix2d a = createMat2d(6,6);
    identity2d(&a);

    double arr[6][6] = { {3.0, 1.0, 0.0, 2.0, 1.0, 5.0},
			 {2.0, 4.0, 1.0, 0.0, 3.0, 1.0},
			 {1.0, 0.0, 2.0, 3.0, 1.0, 2.0},
			 {4.0, 2.0, 3.0, 1.0, 5.0, 0.0},
			 {0.0, 1.0, 4.0, 2.0, 3.0, 1.0},
			 {1.0, 3.0, 2.0, 0.0, 4.0, 1.0} };

    for (size_t i = 0; i < a.rows; i++)
	for (size_t j = 0; j < a.cols; j++)
	    a.mat[i][j] = arr[i][j];


    clock_t t;
    t = clock();
    Matrix2d a_inv = inverse2d(&a);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("inverse took %f seconds\n", time_taken);

    if (a_inv.mat == NULL)
    {
	printf("matrix was not invertible\n");
	return;
    }

    Matrix2d res = multiply2d(&a, &a_inv);

    print_mat2d(&a_inv);
    print_mat2d(&res);

    free2d(&res);
    free2d(&a_inv);
    free2d(&a);
}

void Test_Determinant()
{
    Matrix2d a = createMat2d(2,2);
    double ret;

    //2x2 identity matrix det = 1
    identity2d(&a);
    ret = det2d(&a);
    printf("det(A) : %f\n", ret);
    free2d(&a);

    // 3x3 I
    a = createMat2d(3,3);
    identity2d(&a);
    ret = det2d(&a);
    printf("det(A) : %f\n", ret);
    free2d(&a);

    // 6x6 I
    a = createMat2d(6, 6);
    identity2d(&a);
    ret = det2d(&a);
    printf("det(A) : %f\n", ret);
    free2d(&a);

    // elements = incremental index
    a = createMat2d(2,2);
    double inc = 0.0;
    for (size_t i = 0; i < a.rows; i++)
	for (size_t j = 0; j < a.cols; j++)
	    a.mat[i][j] = inc++;
    ret = det2d(&a);
    printf("det(A) : %f\n", ret);
    free2d(&a);

}

int main(int argc, char **argv)
{
    /* Test_Transpose(); */
    /* Test_Multiply(); */
    /* Test_Determinant(); */
    Test_Inverse();

    return 0;
}
