#include "s21_matrix.h"

int s21_mult_number(s21_matrix* A, double number, s21_matrix* result) {
  int flag = OK;
  if (A == NULL || result == NULL || isNotCorrect(*A)) {
    flag = INCORRECT_MATRIX;
  } else {
    if (result->matrix != NULL) {
      s21_remove_matrix(result);
    }

    if (s21_create_matrix(A->rows, A->columns, result) == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
      flag = OK;
    } else {
      flag = INCORRECT_MATRIX;
    }
  }
  return flag;
}