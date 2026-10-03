#include "s21_matrix.h"

int s21_transpose(s21_matrix* A, s21_matrix* result) {
  int flag = OK;
  if (A == NULL || result == NULL || isNotCorrect(*A)) {
    flag = INCORRECT_MATRIX;
  } else {
    if (result->matrix != NULL) {
      s21_remove_matrix(result);
    }

    if (s21_create_matrix(A->columns, A->rows, result) != OK) {
      flag = INCORRECT_MATRIX;
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    }
  }
  return flag;
}