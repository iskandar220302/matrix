#include "s21_matrix.h"

int s21_calc_complements(s21_matrix* A, s21_matrix* result) {
  int flag = OK;

  if (A == NULL || result == NULL || isNotCorrect(*A)) {
    flag = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    flag = CALCULATION_ERROR;
  } else {
    if (result->matrix != NULL) {
      s21_remove_matrix(result);
    }

    if (s21_create_matrix(A->rows, A->columns, result) != OK) {
      flag = INCORRECT_MATRIX;
    } else {
      if (A->rows == 1) {
        result->matrix[0][0] = 1;
      } else {
        for (int i = 0; i < A->rows && flag == OK; i++) {
          for (int j = 0; j < A->columns && flag == OK; j++) {
            s21_matrix minor = {0};

            if (s21_create_matrix(A->rows - 1, A->columns - 1, &minor) != OK) {
              flag = INCORRECT_MATRIX;
            } else {
              s21_get_minor(A, &minor, i, j);

              double det = 0;
              s21_determinant(&minor, &det);

              int sign = ((i + j) % 2 == 0) ? 1 : -1;

              result->matrix[i][j] = sign * det;

              s21_remove_matrix(&minor);
            }
          }
        }
      }
    }
  }

  return flag;
}