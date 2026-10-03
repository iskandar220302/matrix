#include "s21_matrix.h"

int s21_determinant(s21_matrix* A, double* result) {
  int flag = OK;

  if (A == NULL || result == NULL || isNotCorrect(*A)) {
    flag = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    flag = CALCULATION_ERROR;
  } else if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    *result = 0;

    for (int j = 0; j < A->columns; j++) {
      s21_matrix minor;

      if (s21_create_matrix(A->rows - 1, A->columns - 1, &minor) != OK) {
        flag = INCORRECT_MATRIX;
      } else {
        s21_get_minor(A, &minor, 0, j);

        double det_minor = 0;
        s21_determinant(&minor, &det_minor);

        int sign = (j % 2 == 0) ? 1 : -1;

        *result += sign * A->matrix[0][j] * det_minor;

        s21_remove_matrix(&minor);
      }
    }
  }

  return flag;
}