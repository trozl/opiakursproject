#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include<malloc.h>

int *sizemas = 0;

struct db {
	char name[30];
	float mow;
	double koef;
	char forma[30];
	float height;
};

typedef struct db pole;
pole readfromfile(char name[], pole *base, int* sizemas) {
	FILE* fdb;
	fdb = fopen(name, "r");
	for (int i = 0; i < sizemas; i++) {
		printf("Поле структуры %d\n", i + 1);
		fscanf(fdb, "%s", &base[i].name);
		printf("%s\t", &base[i].name);
		fscanf(fdb, "%f", &base[i].mow);
		printf("%.2f\t", base[i].mow);
		fscanf(fdb, "%lf", &base[i].koef);
		printf("%.2lf\t", base[i].koef);
		fscanf(fdb, "%s", &base[i].forma);
		printf("%s\t", base[i].forma);
		fscanf(fdb, "%f", &base[i].height);
		printf("%.2f\t", base[i].height);
		printf("\n");
	}
	return *base;
}
pole newzap(int sizemas, pole *base, char name[]) {
	FILE* fdb;
	int size_n = sizemas;
	size_n++;
	pole* newarr = (pole*)realloc(base, size_n * sizeof(pole));
	base = newarr;
	fdb = fopen(name, "a");
	printf("Введите название антенны\n");
	scanf("%s", &base[size_n].name);
	printf("%d  %s\n", size_n, base[size_n].name);
	fprintf(fdb, "%s\n", base[size_n].name);
	printf("Введите мощность антенны\n");
	scanf("%f", &base[size_n].mow);
	printf("%d  %f\n", size_n, base[size_n].mow);
	fprintf(fdb, "%f\n", base[size_n].mow);
	printf("Введите коэфициент антенны\n");
	scanf("%lf", &base[size_n].koef);
	printf("%d  %lf\n", size_n, base[size_n].koef);
	fprintf(fdb, "%lf\n", base[size_n].koef);
	printf("Введите форму антенны\n");
	scanf("%s", &base[size_n].forma);
	printf("%d  %s\n", size_n, base[size_n].forma);
	fprintf(fdb, "%s\n", base[size_n].forma);
	printf("Введите высоту антенны\n");
	scanf("%f", &base[size_n].height);
	fprintf(fdb, "%f\n", base[size_n].height);
	fprintf(fdb, "\n");
	printf("END OF ADDING\n");
	return *base;
}



int main() {
	setlocale(LC_ALL, 0);
	system("chcp 1251");
	int exitstate = 0, switchstate, tempsize = 0, counter;
	FILE* fdb;
	char name[] = "C:\\Users\\iraki\\Documents\\DB2.txt";
	fdb = fopen(name, "r");
	pole* base;
	while (!feof(fdb))
	{
		if (fgetc(fdb) == '\n')
			tempsize++;
	}
	tempsize = tempsize / 6;
	printf("%d\n", tempsize);
	fclose(fdb);
	base = (pole*)malloc(tempsize * sizeof(pole));
	printf("Выберите пункт меню введя соответсвующую цифру:\n"
		"1.Создание новой записи в базе данных\n"
		"2.Чтение всех записей, НУЖНОДОРАБОТАТЬ!!!!\n"
		"3.Cортировка записей по Q\n"
		"4.Показ записей удовлетворяющим условиям поиска\n"
		"5.WIP\n"
		"6.Выход из программы\n");
	counter = tempsize;
	while (exitstate != 1) {
		sizemas = tempsize;
		printf("Записей :%d\n", sizemas);
		scanf("%d", &switchstate);
		switch (switchstate) {
		case 1:
			newzap(tempsize, base, name);
			fclose(fdb);
			break;
		case 2:
			readfromfile(name, base, tempsize);
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
		case 6:
			free(base);
			exitstate = 1;
			break;
		}
	}
}