#include "s21_matrix.h"

int s21_inverse_matrix(s21_matrix* A, s21_matrix* result) {
  int flag = OK;

  if (A == NULL || result == NULL || isNotCorrect(*A)) {
    flag = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    flag = CALCULATION_ERROR;
  } else {
    double det = 0;

    if (s21_determinant(A, &det) != OK) {
      flag = INCORRECT_MATRIX;
    } else if (fabs(det) < 1e-6) {
      flag = CALCULATION_ERROR;
    } else {
      s21_matrix complements = {0};
      s21_matrix transposed = {0};

      if (s21_calc_complements(A, &complements) != OK) {
        flag = INCORRECT_MATRIX;
      } else if (s21_transpose(&complements, &transposed) != OK) {
        s21_remove_matrix(&complements);
        flag = INCORRECT_MATRIX;
      } else {
        s21_remove_matrix(result);

        if (s21_create_matrix(A->rows, A->columns, result) != OK) {
          flag = INCORRECT_MATRIX;
        } else {
          double inv_det = 1.0 / det;

          for (int i = 0; i < result->rows; i++) {
            for (int j = 0; j < result->columns; j++) {
              result->matrix[i][j] = transposed.matrix[i][j] * inv_det;
            }
          }
        }

        s21_remove_matrix(&complements);
        s21_remove_matrix(&transposed);
      }
    }
  }

  return flag;
}