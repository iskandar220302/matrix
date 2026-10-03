#include "s21_matrix.h"

int isNotCorrect(s21_matrix A) {
  int res = 0;
  if (A.rows <= 0 || A.columns <= 0 || A.matrix == NULL) res = 1;
  return res;
}

void s21_get_minor(s21_matrix* A, s21_matrix* minor, int row, int col) {
  int mi = 0;

  for (int i = 0; i < A->rows; i++) {
    if (i == row) continue;

    int mj = 0;

    for (int j = 0; j < A->columns; j++) {
      if (j == col) continue;

      minor->matrix[mi][mj] = A->matrix[i][j];
      mj++;
    }

    mi++;
  }
}