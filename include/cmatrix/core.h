#ifndef CORE_H_
#define CORE_H_

#include <stddef.h>

/**
 * @brief Matrix implementation
 */
typedef struct Matrix2d
{
    double **mat;
    size_t rows,
	cols;
} Matrix2d;

typedef struct Matrix2f
{
    float **mat;
    size_t rows,
	cols;
} Matrix2f;

/**
 * @brief allocate memory for a [rows*cols] 2 dimenionsal matrix
 *
 * @param rows The number of rows to be allocated for the matrix
 * @param cols The number of columns to be allocated for the matrix
 *
 * @return copy of a Matrix2[df] with allocated memory
 */
Matrix2d createMat2d(size_t rows, size_t cols);
Matrix2f createMat2f(size_t rows, size_t cols);

/**
 * @brief zero the elements of the matrix
 *
 * @param m The matrix whose elements will be zero'd
 */
void zero2d(Matrix2d *m);
void zero2f(Matrix2f *m);

/**
 * @brief set the paramter matrix as identity
 *
 * @param m The matrix whose elements will match the identity matrix
 */
void identity2d(Matrix2d *m);
void identity2f(Matrix2f *m);

/**
 * @brief tranpose the parameter matrix
 */
void transpose2d(Matrix2d *m);
void transpose2f(Matrix2f *m);

/**
 * @brief multiply the two parametered matrices in respective order
 */
Matrix2d multiply2d(Matrix2d *a, Matrix2d *b);
Matrix2f multiply2f(Matrix2f *a, Matrix2f *b);

/**
 * @brief scalar multiply a matrix
 */
void scale2d(Matrix2d *a, double scale);
void scale2f(Matrix2f *a, float scale);

/**
 * @brief add two matrices together
 */
Matrix2d add2d(Matrix2d *a, Matrix2d *b);
Matrix2f add2f(Matrix2f *a, Matrix2f *b);

/**
 * @brief subtract two matrices
 */
Matrix2d sub2d(Matrix2d *a, Matrix2d *b);
Matrix2f sub2f(Matrix2f *a, Matrix2f *b);

/**
 * @brief take the inverse of a matrix using t (1/|det(a)|)*adj(a)
 */
Matrix2d inverse2d(Matrix2d *a);
Matrix2f inverse2f(Matrix2f *a);

/**
 * @brief take the determinant of a matrix
 */
double det2d(Matrix2d *a);
float det2f(Matrix2f *a);

/**
 * @brief find the cofactor of a matrix a
 */
Matrix2d cofactor2d(Matrix2d *a);
Matrix2f cofactor2f(Matrix2f *a);

/**
 * @brief print out the element of a matrix
 */
void print_mat2d(Matrix2d *mat);
void print_mat2f(Matrix2f *mat);

// DO NOT TOUCH
double** alloc_2d(size_t rows, size_t cols);
float** alloc_2f(size_t rows, size_t cols);

void free_mat(void **ptr, size_t rows, size_t cols);

void free2d(Matrix2d *mat);
void free2f(Matrix2f *mat);

#endif
