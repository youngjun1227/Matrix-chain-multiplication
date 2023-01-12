#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE_NAME "test_set_1.txt"
#define OUTPUT_FILE_NAME "test_set_1_sol.txt"

struct save_point {
	int number;
	int row, col;
	int** arr;
};

struct save_point* sp;

int** colrow;
int** final_test;
int** matrix;


int MCM(int a, int b) {

	if (a == b) {
		return 0;
	}

	int min = 2147000000;
	int result = 0;

	for (int i = a; i < b; i++) {
		result = MCM(a, i) + MCM(i + 1, b) + colrow[a-1][0]*colrow[i-1][1]*colrow[b-1][1];
		if (result < min) {
			min = result;
		}
	}
	return min;
}

int** matrix_mul(int** a_matrix, int** b_matrix, int p) {
	// 계산과정 중 필요한 결과 행렬 동적할당
	
	final_test = (int**)malloc(sizeof(int*) * colrow[0][0]);
	for (int i = 0; i < colrow[0][0]; i++) {
		final_test[i] = (int*)malloc(sizeof(int) * colrow[p+1][1]);
	}
	// 계산과정
	for (int i = 0; i < colrow[0][0]; i++) {
		for (int j = 0; j < colrow[p + 1][1]; j++) {
			final_test[i][j] = 0;
			for (int k = 0; k < colrow[p][1]; k++) {
				final_test[i][j] += a_matrix[i][k] * b_matrix[k][j];
			}
		}
	}
	return final_test;
}


int main() {
	
	FILE* infp;
	FILE* outfp;

	srand((unsigned int)time(NULL));
	int a = 0, b = 0; // 입력받는 행과 열
	int line = 0;
	int read = 0;
	int k = 0;
	

	infp = fopen(INPUT_FILE_NAME, "r");
	outfp = fopen(OUTPUT_FILE_NAME, "w");

	while (fscanf(infp, "%d %d\n", &a, &b) == 2) {
		line++;
	}
	colrow = (int**)malloc(sizeof(int*) * line);
	for (int i = 0; i < line; i++) {
		colrow[i] = (int*)malloc(sizeof(int) * 2);
	}
	
	fclose(infp);
	infp = fopen(INPUT_FILE_NAME, "r");
	while (k < line) {
		read = fscanf(infp, "%d %d\n", &a, &b);
		colrow[k][0] = a;
		colrow[k][1] = b;
		k++;
	};

	sp = (struct save_point*)malloc(sizeof(struct save_point) * line);
	
	int t = 0;
	/* matrix 크기 동적할당 받기 */
	while (t < line) {
		// matrix 동적할당
		matrix = (int**)malloc(sizeof(int*) * colrow[t][0]);
		for (int i = 0; i < colrow[t][0]; i++) {
			matrix[i] = (int*)malloc(sizeof(int) * colrow[t][1]);
		}
		// 난수(1 ~ 5)까지 수를 무작위로 넣음
		for (int i = 0; i < colrow[t][0]; i++) {
			for (int j = 0; j < colrow[t][1]; j++) {
				matrix[i][j] = rand() % 20 + 1;
			}
		}
		sp[t].arr = matrix;
		t++;
	}
	// 행렬계산 결과값 출력하기
	int** mat_1 = sp[0].arr;
	int** mat_2 = sp[1].arr;
	int** mat;
	mat = mat_1;
	int h = 1;
	int p = 0;
	while (h < line) {
		mat = matrix_mul(mat, mat_2, p);
		mat_2 = sp[h + 1].arr;
		h++;
		p++;
	}
	//outfp에 프린트하는 과정
	fprintf(outfp, "%d\n", MCM(1, line));
	// output matrix를 출력
	fprintf(outfp, "Output Matrix\n");
	for (int i = 0; i < colrow[0][0]; i++) {
		for (int j = 0; j < colrow[line-1][1]; j++) {
			fprintf(outfp, "%d ", mat[i][j]);
		}
		fprintf(outfp,"\n");
	}
	fprintf(outfp, "\n");
	// input matrix를 출력
	int u = 0;
	while (u < line) {
		fprintf(outfp, "Input Matrix %d\n", u+1);
		for (int i = 0; i < colrow[u][0]; i++) {
			for (int j = 0; j < colrow[u][1]; j++) {
				fprintf(outfp, "%3d ", sp[u].arr[i][j]);
			}
			fprintf(outfp, "\n");
		}
		fprintf(outfp, "\n");
		u++;
	}

	for (int i = 0; i < colrow[0][0]; i++) {
		free(final_test[i]);
	}
	free(final_test);

	for(int i = 0; i < colrow[t - 1][0]; i++) {
		free(matrix[i]);
	}
	free(matrix);
	free(sp);
	for (int i = 0; i < line; i++) {
		free(colrow[i]);
	}
	free(colrow);
}