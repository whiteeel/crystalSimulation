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

	cell[X / 2][0] = 1; //初期状態の代入（核となるゴミを仕込む）

	for (time = 1; time<TIME; time++){                          // 時間を進める
		for (x = 0; x<X; x++)for (y = 0; y<Y; y++)change[x][y] = 0;   // 変数change[x][y]=0を初期化しておく
		//各セルの状態を調べる
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
				}//　セルの変更箇所を確定する

		}

		for (x = 1; x < (X - 1); x++){
			for (y = 1; y < (Y - 1); y++){
				cell[x][y] += change[x][y];
			}// セルの変更箇所を上書き更新します
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

	//　　ファイル"xy"へ結晶化したセルの位置座標を出力する
	for (x = 1; x < (X - 1); x++){
		for (y = 1; y <(Y - 1); y++){
			if (cell[x][y] != 0){
				if (y % 2 != 0)fprintf(xy, "%lf  %lf\n", (double)x, (double)y);   // yが偶数番ならば、(x,y)を出力
				if (y % 2 == 0)fprintf(xy, "%lf  %lf\n", (double)x + 0.5, (double)y);	  // yが奇数番ならば、(x+0.5,y)を出力
			}
		}
	}
} // main
