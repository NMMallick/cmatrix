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

Matrix2d createMat2d(size_t rows, size_t cols);
Matrix2f createMat2f(size_t rows, size_t cols);

void zero2d(Matrix2d  *m);
void zero2f(Matrix2f *m);

void identity2d(Matrix2d *m);
void identity2f(Matrix2f *m);

void print_mat2d(Matrix2d *mat);
void print_mat2f(Matrix2f *mat);

// DO NOT TOUCH
double** alloc_2d(size_t rows, size_t cols);
float** alloc_2f(size_t rows, size_t cols);

void free_mat(void **ptr, size_t rows, size_t cols);

void free2d(Matrix2d *mat);
void free2f(Matrix2f *mat);

#endif
