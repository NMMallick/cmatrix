#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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
    double **tmp = alloc_2d(m->cols, m->cols);
    for (size_t i = 0; i < m->rows; i++)
	for (size_t j = 0; j < m->cols; j++)
	{
	    tmp[j][i] = m->mat[i][j];
	}

    free2d(m);
    m->mat = tmp;

    size_t dim_tmp = m->cols;
    m->cols = m->rows;
    m->rows = dim_tmp;
}

void transpose2f(Matrix2f *m)
{
    float **tmp = alloc_2f(m->rows, m->cols);
    for (size_t i = 0; i < m->rows; i++)
	for (size_t j = 0; j < m->cols; j++)
	{
	    tmp[j][i] = m->mat[i][j];
	}

    free2f(m);
    m->mat = tmp;

    size_t dim_tmp = m->cols;
    m->cols = m->rows;
    m->rows = dim_tmp;
}

// A*B
Matrix2d multiply2d(Matrix2d *a, Matrix2d *b)
{
    Matrix2d m;
    m.mat = NULL;

    if (a->cols != b->rows)
	return m;

    m = createMat2d(a->rows, b->cols);

    double sum;
    for (size_t i = 0; i < a->rows; i++)
	for (size_t k = 0; k < b->cols; k++)
	{
	    sum = 0.0;
	    for (size_t j = 0; j < a->cols; j++)
	    {
		sum += a->mat[i][j]*b->mat[j][k];
	    }
	    m.mat[i][k] = sum;
	}

    return m;
}

Matrix2f multiply2f(Matrix2f *a, Matrix2f *b)
{
    Matrix2f m;
    m.mat = NULL;

    if (a->cols != b->rows)
	return m;

    m = createMat2f(a->rows, b->cols);

    float sum;
    for (size_t i = 0; i < a->rows; i++)
	for (size_t k = 0; k < b->cols; k++)
	{
	    sum = 0.0;
	    for (size_t j = 0; j < a->cols; j++)
	    {
		sum += a->mat[i][j]*b->mat[j][k];
	    }
	    m.mat[i][k] = sum;
	}

    return m;
}

// A + B
Matrix2d add2d(Matrix2d *a, Matrix2d *b)
{
    Matrix2d res;
    res.mat = NULL;

    if (a->rows != b->rows && a->cols != b->cols)
	return res;

    res = createMat2d(a->rows, a->cols);

    for (size_t i = 0; i < res.rows; i++)
	for (size_t j = 0; j < res.cols; j++)
	    res.mat[i][j] = a->mat[i][j] + b->mat[i][j];

    return res;
}

Matrix2f add2f(Matrix2f *a, Matrix2f *b)
{
    Matrix2f res;
    res.mat = NULL;

    if (a->rows != b->rows && a->cols != b->cols)
	return res;

    res = createMat2f(a->rows, a->cols);

    for (size_t i = 0; i < res.rows; i++)
	for (size_t j = 0; j < res.cols; j++)
	    res.mat[i][j] = a->mat[i][j] + b->mat[i][j];

    return res;
}

Matrix2d sub2d(Matrix2d *a, Matrix2d *b)
{
    Matrix2d res;
    res.mat = NULL;

    if (a->rows != b->rows && a->cols != b->cols)
	return res;

    res = createMat2d(a->rows, a->cols);

    for (size_t i = 0; i < res.rows; i++)
	for (size_t j = 0; j < res.cols; j++)
	    res.mat[i][j] = a->mat[i][j] - b->mat[i][j];

    return res;
}

Matrix2f sub2f(Matrix2f *a, Matrix2f *b)
{
    Matrix2f res;
    res.mat = NULL;

    if (a->rows != b->rows && a->cols != b->cols)
	return res;

    res = createMat2f(a->rows, a->cols);

    for (size_t i = 0; i < res.rows; i++)
	for (size_t j = 0; j < res.cols; j++)
	    res.mat[i][j] = a->mat[i][j] - b->mat[i][j];

    return res;
}

void scale2d(Matrix2d *a, double scale)
{
    for (size_t i = 0; i < a->rows; i++)
	for (size_t j = 0; j < a->cols; j++)
	    a->mat[i][j] *= scale;
}

void scale2f(Matrix2f *a, float scale)
{
    for (size_t i = 0; i < a->rows; i++)
	for (size_t j = 0; j < a->cols; j++)
	    a->mat[i][j] *= scale;
}

Matrix2d inverse2d(Matrix2d *a)
{
    Matrix2d cof_a;
    cof_a.mat = NULL;

    if (a->rows != a->cols)
	return cof_a;

    double det = det2d(a);

    if (det == 0.0)
	return cof_a;

    cof_a = cofactor2d(a);

    transpose2d(&cof_a);
    scale2d(&cof_a, 1.0/det);

    return cof_a;
}

Matrix2f inverse2f(Matrix2f *a)
{
    Matrix2f cof_a;
    cof_a.mat = NULL;

    if (a->rows != a->cols)
	return cof_a;

    float det = det2f(a);

    if (det == 0.0)
	return cof_a;

    cof_a = cofactor2f(a);

    transpose2f(&cof_a);
    scale2f(&cof_a, 1.0/det);

    return cof_a;
}

Matrix2d cofactor2d(Matrix2d *a)
{
    Matrix2d res;
    res.mat = NULL;

    if (a->rows != a->cols)
	return res;

    double n = a->rows;
    Matrix2d minor;

    res = createMat2d(n, n);

    for (size_t i = 0; i < n; i++)
	for (size_t j = 0; j < n; j++)
	{
	    // Create matrix object to hold the minor matrix
	    minor = createMat2d(n-1, n-1);
	    size_t m_i=0, m_j;

	    for (size_t k = 0; k < n; k++)
	    {
		if (k == i)
		    continue;

		m_j = 0;

		for (size_t l = 0; l < n; l++)
		{
		    if (l == j)
			continue;
		    minor.mat[m_i][m_j++] = a->mat[k][l];
		}
		m_i++;
	    }

	    res.mat[i][j] = pow(-1, (i+j+2))*det2d(&minor);
	    free2d(&minor);
	}

    return res;
}

Matrix2f cofactor2f(Matrix2f *a)
{
    Matrix2f res;
    res.mat = NULL;

    if (a->rows != a->cols)
	return res;

    double n = a->rows;
    Matrix2f minor;

    res = createMat2f(n, n);

    for (size_t i = 0; i < n; i++)
	for (size_t j = 0; j < n; j++)
	{
	    // Create matrix object to hold the minor matrix
	    minor = createMat2f(n-1, n-1);
	    size_t m_i=0, m_j;

	    for (size_t k = 0; k < n; k++)
	    {
		if (k == i)
		    continue;

		m_j = 0;

		for (size_t l = 0; l < n; l++)
		{
		    if (l == j)
			continue;
		    minor.mat[m_i][m_j++] = a->mat[k][l];
		}
		m_i++;
	    }

	    res.mat[i][j] = pow(-1, (i+j+2))*det2f(&minor);
	    free2f(&minor);
	}

    return res;
}

double det2d(Matrix2d *a)
{
    if (a->rows != a->cols)
    {
	exit(1);
    }

    double n = a->rows;

    // Base case
    if (n == 1)
	return a->mat[0][0];

    double det = 0.0;
    for (size_t k = 0; k < n; k++)
    {
	Matrix2d minor = createMat2d(n-1, n-1);

	size_t l=0, m;
	// Create the submatrix
	for (size_t i = 1; i < n; i++)
	{
	    m = 0;
	    for (size_t j = 0; j < n; j++)
	    {
		if (j == k)
		    continue;
		minor.mat[l][m++] = a->mat[i][j];
	    }
	    l++;
	}

	det += a->mat[0][k]*pow(-1, k)*det2d(&minor);
	free2d(&minor);
    }

    return det;
}

float det2f(Matrix2f *a)
{
    // TODO: setup some error ret value
    if (a->rows != a->cols)
	exit(1);

    float n = a->rows;

    // Base case
    if (n == 1)
	return a->mat[0][0];

    float det = 0.0;
    for (size_t k = 0; k < n; k++)
    {
	Matrix2f minor = createMat2f(n-1, n-1);
	size_t l=0, m;

	// Create the submatrix
	for (size_t i = 1; i < n; i++)
	{
	    m = 0;
	    for (size_t j = 0; j < n; j++)
	    {
		if (j == k)
		    continue;
		minor.mat[l][m++] = a->mat[i][j];
	    }
	    l++;
	}

	det += a->mat[0][k]*pow(-1, k)*det2f(&minor);
	free2f(&minor);
    }

    return det;
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

#ifdef DEBUG
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
#endif

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

    return ptr;
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
