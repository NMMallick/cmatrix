#include <stdlib.h>
#include <stdio.h>

#include <cmatrix/core.h>

static size_t __NUM_ALLOC_M2d__ = 0;
static size_t __NUM_ALLOC_M2f__ = 0;

static Matrix2d *m2dPtr;
static Matrix2f *m2fPtr;

/* typedef struct m2dCollector */
/* { */
/*     Matrix2d *mPtr; */
/*     size_t size; */
/* } m2dCollector; */

/* typedef struct m2fCollector */
/* { */
/*     Matrix2f *mPtr; */
/*     size_t size; */
/* } m2fCollector; */

/* static m2fCollector __m2fcol__ = {.mPtr = NULL, .numAlocMats=0}; */
/* static m2dCollecter __m2dcol__ = {.mPtr = NULL, .numAlocMats=0}; */

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

void tranpose2f(Matrix2f *m)
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
    res->mat = NULL;

    if (a->rows != b->rows && a->cols != b->cols)
	return res;

    res = createMat2f(a->rows, a->cols);

    for (size_t i = 0; i < res->rows; i++)
	for (size_t j = 0; j < res->cols; j++)
	    res.mat[i][j] = a->mat[i][j] + b->mat[i][j];

    return res;
}

Matrix2f add2d(Matrix2f *a, Matrix2f *b)
{
    Matrix2f res;
    res->mat = NULL;

    if (a->rows != b->rows && a->cols != b->cols)
	return res;

    res = createMat2f(a->rows, a->cols);

    for (size_t i = 0; i < res->rows; i++)
	for (size_t j = 0; j < res->cols; j++)
	    res.mat[i][j] = a->mat[i][j] + b->mat[i][j];

    return res;
}

Matrix2d sub2d(Matrix2d *a, Matrix2d *b)
{
    Matrix2d res;
    res->mat = NULL;

    if (a->rows != b->rows && a->cols != b->cols)
	return res;

    res = createMat2f(a->rows, a->cols);

    for (size_t i = 0; i < res->rows; i++)
	for (size_t j = 0; j < res->cols; j++)
	    res.mat[i][j] = a->mat[i][j] - b->mat[i][j];

    return res;
}

Matrix2f sub2f(Matrix2f *a, Matrix2f *b)
{
    Matrix2f res;
    res->mat = NULL;

    if (a->rows != b->rows && a->cols != b->cols)
	return res;

    res = createMat2f(a->rows, a->cols);

    for (size_t i = 0; i < res->rows; i++)
	for (size_t j = 0; j < res->cols; j++)
	    res.mat[i][j] = a->mat[i][j] - b->mat[i][j];

    return res;
}

Matrix2d inverse2d(Matrix2d *a)
{
    Matrix2d res;
    res.mat = NULL;

    if (a->rows != a->cols)
	return res;

    Matrix2d aug = createMatrix2d(a->rows, 2*a->cols);

    // Create an augmented matrix [mat | I] where I is the identity matrix
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a_cols; j++) {
            aug.mat[i][j] = a->mat[i][j];
            aug.mat[i][j + a->rows] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Perform row operations to get the identity matrix on the left side
    for (int i = 0; i < a->rows; i++) {
        if (aug.mat[i][i] == 0.0) {
            return res; // Matrix is singular, cannot be inverted
        }

        // Scale the current row to have 1 on the diagonal
        double scale = augmented[i][i];
        for (int j = 0; j < 2*a->rows; j++) {
            aug.mat[i][j] /= scale;
        }

        // Subtract multiples of the current row from other rows to get 0s below and above the diagonal
        for (int j = 0; j < a->rows; j++) {
            if (i != j) {
                double factor = aug.mat[j][i];
                for (int k = 0; k < 2*a->rows; k++) {
                    aug.mat[j][k] -= factor * aug.mat[i][k];
                }
            }
        }
    }

    // Copy the right half of the augmented matrix (the inverse) into the result
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->rows; j++) {
            res.mat[i][j] = aug.mat[i][j + N];
        }
    }
}

Matrix2f inverse2f(Matrix2f *a)
{
    Matrix2f res;
    res.mat = NULL;

    return res;
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
