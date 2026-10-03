#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, s21_matrix* result) {
  if (result == NULL) {
    return INCORRECT_MATRIX;
  }

  result->matrix = NULL;
  result->rows = 0;
  result->columns = 0;

  if (rows <= 0 || columns <= 0) {
    return INCORRECT_MATRIX;
  }

  if (rows > MAX_MATRIX_SIZE || columns > MAX_MATRIX_SIZE) {
    return INCORRECT_MATRIX;
  }

  size_t r = (size_t)rows;
  size_t c = (size_t)columns;

  result->matrix = (double**)calloc(r, sizeof(double*));
  if (!result->matrix) {
    return INCORRECT_MATRIX;
  }

  for (size_t i = 0; i < r; i++) {
    result->matrix[i] = (double*)calloc(c, sizeof(double));

    if (!result->matrix[i]) {
      for (size_t j = 0; j < i; j++) {
        free(result->matrix[j]);
      }
      free(result->matrix);

      result->matrix = NULL;
      return INCORRECT_MATRIX;
    }
  }

  result->rows = rows;
  result->columns = columns;

  return OK;
}