#include "s21_matrix.h"

int s21_mult_matrix(s21_matrix* A, s21_matrix* B, s21_matrix* result) {
  int flag = OK;
  if (A == NULL || B == NULL || result == NULL || isNotCorrect(*A) ||
      isNotCorrect(*B)) {
    flag = INCORRECT_MATRIX;
  } else {
    if (result->matrix != NULL) {
      s21_remove_matrix(result);
    }

    if (A->columns != B->rows) {
      flag = CALCULATION_ERROR;
    } else if (s21_create_matrix(A->rows, B->columns, result) == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          for (int k = 0; k < A->columns; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
      flag = OK;
    } else {
      flag = INCORRECT_MATRIX;
    }
  }
  return flag;
}