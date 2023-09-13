#include <stdlib.h>
#include <stdio.h>

#include <cmatrix/core.h>

void zero2d(Matrix2d *m)
{
    if (m->mat == NULL)
	m->mat = alloc_2d(m->rows, m->cols);

    for (size_t i = 0; i < m->rows; i++)
	for (size_t j = 0; j < m->cols; j++)
	    m->mat[i][j] = 0.0;
}

void zero2f(Matrix2f *m)
{
    if (m->mat == NULL)
	m->mat = alloc_2f(m->rows, m->cols);

    for (size_t i = 0; i < m->rows; i++)
	for (size_t j = 0; j < m->cols; j++)
	    m->mat[i][j] = 0.0;
}

void identity2d(Matrix2d *m)
{
    if (m->rows != m->cols)
	return;

    if (m->mat == NULL)
	m->mat = alloc_2d(m->rows, m->cols);

    for (size_t i = 0; i < m->rows; i++)
	for (size_t j = 0; j < m->cols; j++)
	    if (i == j)
		m->mat[i][j] = 1.0;
	    else
		m->mat[i][j] = 0.0;
}

void identity2f(Matrix2f *m)
{
    if (m->mat == NULL)
	m->mat = alloc_2f(m->rows, m->cols);

    for (size_t i = 0; i < m->rows; i++)
	for (size_t j = 0; j < m->cols; j++)
	    if (i == j)
		m->mat[i][j] = 1.0;
	    else
		m->mat[i][j] = 0.0;
}

void transpose2d(Matrix2d *m)
{
    if (m->rows != m->cols)
	return;

    double **tmp = alloc_2d(m->rows, m->cols);
    for (size_t i = 0; i < m->rows; i++)
	for (size_t j = 0; j < m->cols; j++)
	{
	    tmp[j][i] = m->mat[i][j];
	}

    free2d(m);
    m->mat = NULL;
    m->mat = tmp;
}

void tranpose2f(Matrix2f *m)
{
    if (m->rows != m-> cols)
	return;

    float **tmp = alloc_2f(m->rows, m->cols);
    for (size_t i = 0; i < m->rows; i++)
	for (size_t j = 0; j < m->cols; j++)
	{
	    tmp[j][i] = m->mat[i][j];
	}

    free2f(m);
    m->mat = tmp;
}

Matrix2d createMat2d(size_t rows, size_t cols)
{
    Matrix2d mat;

    mat.mat = alloc_2d(rows, cols);
    mat.rows = rows;
    mat.cols = cols;

    return mat;
}

Matrix2f createMat2f(size_t rows, size_t cols)
{
    Matrix2f mat;

    mat.mat = alloc_2f(rows, cols);
    mat.rows = rows;
    mat.cols = cols;

    return mat;
}


void print_mat2d(Matrix2d *mat)
{
    printf("--------------------\n");
    for (size_t i = 0; i < mat->rows; i++)
    {
	for (size_t j = 0; j < mat->cols; j++)
	    printf("%f ", mat->mat[i][j]);

	printf("\n");
    }
    printf("--------------------\n");
}

void print_mat2f(Matrix2f *mat)
{
    printf("--------------------\n");
    for (size_t i = 0; i < mat->rows; i++)
    {
	for (size_t j = 0; j < mat->cols; j++)
	    printf("%f ", mat->mat[i][j]);

	printf("\n");
    }
    printf("--------------------\n");
}

double** alloc_2d(size_t rows, size_t cols)
{
    double **ptr = (double **) malloc(rows*sizeof(double*));

    for (size_t i = 0; i < rows; i++)
    {
	ptr[i] = (double *) malloc(cols*sizeof(double));
    }

    return ptr;
}

float** alloc_2f(size_t rows, size_t cols)
{
    float **ptr = (float **) malloc(rows*sizeof(float*));

    for (size_t i = 0; i < rows; i++)
    {
	ptr[i] = (float *) malloc(cols*sizeof(float));
    }
}

void free_mat(void **ptr, size_t rows, size_t cols)
{
    for (size_t i = 0; i < rows; i++)
	free(ptr[i]);

    free(ptr);
}

void free2d(Matrix2d *mat)
{
    free_mat((void**) mat->mat, mat->rows, mat->cols);
}

void free2f(Matrix2f *mat)
{
    free_mat((void**) mat->mat, mat->rows, mat->cols);
}
