#define   _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define X 300
#define Y 300
int main(){
	FILE* xy = fopen("xy", "w");

	FILE* fp2; /////


	int time, TIME = 100;
	int cell[X][Y] = { 0 }, change[X][Y] = { 0 };
	int x, y;
	int goukei;

	char filename[60];


	FILE* fp = fopen("hukuda", "w");
	fprintf(fp, "set xrange[0:%d]\n", X);
	fprintf(fp, "set yrange[0:%d]\n", Y);
	for (time = 1; time < TIME; time++){
		fprintf(fp, "plot'%d'\n", time);
		fprintf(fp, "pause 0.1\n");
	}

	cell[X / 2][0] = 1; //������Ԃ̑���i�j�ƂȂ�S�~���d���ށj

	for (time = 1; time<TIME; time++){                          // ���Ԃ�i�߂�
		for (x = 0; x<X; x++)for (y = 0; y<Y; y++)change[x][y] = 0;   // �ϐ�change[x][y]=0�����������Ă���
		//�e�Z���̏�Ԃ𒲂ׂ�
		for (x = 1; x<(X - 1); x++)for (y = 1; y<(Y - 1); y++){
			if (cell[x][y] == 0){
				if (x % 2 == 0){
					goukei = cell[x][y + 1] + cell[x][y - 1] + cell[x - 1][y] + cell[x - 1][y - 1] + cell[x + 1][y] + cell[x + 1][y - 1];
				}
				if (x % 2 != 0){
					goukei = cell[x][y + 1] + cell[x][y - 1] + cell[x - 1][y] + cell[x - 1][y + 1] + cell[x + 1][y] + cell[x + 1][y + 1];
				}
				if (goukei >=1){
					change[x][y] = 1;
				}//�@�Z���̕ύX�ӏ����m�肷��

		}

		for (x = 1; x < (X - 1); x++){
			for (y = 1; y < (Y - 1); y++){
				cell[x][y] += change[x][y];
			}// �Z���̕ύX�ӏ����㏑���X�V���܂�
		}


		sprintf(filename, "%d%", time);

		fp2 = fopen(filename, "w");
		for (x = 1; x < (X - 1); x++){
			for (y = 1; y < (Y - 1); y++){
				if (cell[x][y] != 0){
					if (y % 2 != 0)fprintf(fp2, "%lf  %lf\n", (double)x, (double)y);
					if (y % 2 == 0)fprintf(fp2, "%lf  %lf\n", (double)x + 0.5, (double)y);
				}
			}
		}
		fclose(fp2);
	} //time

	//�@�@�t�@�C��"xy"�֌����������Z���̈ʒu���W���o�͂���
	for (x = 1; x < (X - 1); x++){
		for (y = 1; y <(Y - 1); y++){
			if (cell[x][y] != 0){
				if (y % 2 != 0)fprintf(xy, "%lf  %lf\n", (double)x, (double)y);   // y�������ԂȂ�΁A(x,y)���o��
				if (y % 2 == 0)fprintf(xy, "%lf  %lf\n", (double)x + 0.5, (double)y);	  // y����ԂȂ�΁A(x+0.5,y)���o��
			}
		}
	}
} // main
