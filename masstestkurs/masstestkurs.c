#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include<malloc.h>

 //version 3

struct db {
	char name[30];
	float mow;
	double koef;
	char forma[30];
	float height;
};

typedef struct db pole_t;
void* readfromfile(char name[], pole_t* base, int* sizemas) {
	for (int i = 0; i < *sizemas; i++) {
		printf("\n");
		printf("%s\t", &base[i].name);
		printf("%.2f\t", base[i].mow);
		printf("%.2lf\t", base[i].koef);
		printf("%s\t", base[i].forma);
		printf("%.2f\t", base[i].height);
		printf("\n");
	}
}
pole_t* baseinitialize(char name[], pole_t* base, int* sizemas) {
	FILE* fdb;
	int newsize=0;
	fdb = fopen(name, "r");
	while (!feof(fdb))
	{
		if (fgetc(fdb) == '\n')
			newsize++;
	}
	newsize = newsize / 6;
	fclose(fdb);
	fdb = fopen(name, "r");
	for (int i = 0; i < newsize; i++) {
		fscanf(fdb, "%s", &base[i].name);
		fscanf(fdb, "%f", &base[i].mow);
		fscanf(fdb, "%lf", &base[i].koef);
		fscanf(fdb, "%s", &base[i].forma);
		fscanf(fdb, "%f", &base[i].height);
	}
	fclose(fdb);
	*sizemas = newsize;
return base;
}
pole_t* newzap(int* sizemas, pole_t* base, char name[], pole_t* newarr) {
	FILE* fdb;
	printf("%d\n", sizemas);
	int newsize;
	newsize = *sizemas;
	newarr = base;
	newsize++;
	printf("%d", newsize);
	newarr = (pole_t*)malloc(newsize * sizeof(pole_t));
	 newarr = base;
	 base = newarr;
	if (base == NULL) {
		printf("error");
		base = newarr;
		sizemas = newsize;
		return base;
	}
	fdb = fopen(name, "a");
	printf("Введите название антенны\n");
	scanf("%s", &base[*sizemas].name);
	printf("%s\n", base[*sizemas].name);
	fprintf(fdb, "%s\n", base[*sizemas].name);
	printf("Введите мощность антенны\n");
	scanf("%f", &base[*sizemas].mow);
	printf("%f\n", base[*sizemas].mow);
	fprintf(fdb, "%f\n", base[*sizemas].mow);
	printf("Введите коэфициент антенны\n");
	scanf("%lf", &base[*sizemas].koef);
	printf("%lf\n", base[*sizemas].koef);
	fprintf(fdb, "%lf\n", base[*sizemas].koef);
	printf("Введите форму антенны\n");
	scanf("%s", &base[*sizemas].forma);
	printf("%s\n", base[*sizemas].forma);
	fprintf(fdb, "%s\n", base[*sizemas].forma);
	printf("Введите высоту антенны\n");
	scanf("%f", &base[*sizemas].height);
	fprintf(fdb, "%f\n", base[*sizemas].height);
	printf("%f", base[*sizemas].height);
	fprintf(fdb, "\n");
	*sizemas = newsize;
	//free(newarr);
	return base;
}
int compare(pole_t const* ax, pole_t const* bx) {
	const struct db* a = ax, * b = bx;
	float Q1, Q2, mow1, mow2, height1, height2;
	Q1 = a->mow + 0.5 * a->height;
	Q2 = b->mow + 0.5 * b->height;
	if (Q1 < Q2) return 1;
	if (Q1 > Q2) return -1;
	if (Q1 == Q1) return 0;
}
void printbase(pole_t* base, int* size) {
	printf("Вывод значений базы данных отсортированных по Q\nQ=Мощность+0.5*Высоту\n\n");
	for (int i = 0; i < *size; i++) {
		printf("%s %.2f %.2lf %s %.2f\n", base[i].name, base[i].mow, base[i].koef, base[i].forma, base[i].height);
	}
}
int* namefinder(pole_t* base, int* size, char namesearcher[], int* arrotv) {
	int n = 0;
	for (int i = 0; i < *size; i++) {
		if (strcmp(base[i].name, namesearcher) == 0) {
			arrotv[n++] = i;
		}
	}
	return arrotv;
}

int* heightrangesearch(pole_t* base, int* size, float toph, float baseh, int* arrotv) {
	printf("В диапазоне выост от %.2f до %.2f\n", baseh, toph);
	int n = 0;
	for (int i = 0; i < *size; i++) {
		if (base[i].height > baseh && base[i].height < toph) {
			arrotv[n++] = i;
		}

	}
	return arrotv;
}




int main() {
	setlocale(LC_ALL, 0);
	system("chcp 1251");
	int exitstate = 0, switchstate, tempsize = 0;
	float baseh=0, toph=0;
	int* sizemas = (int*) malloc(1000*sizeof(int));
	sizemas = 0;
	FILE* fdb;
	char name[] = "DB2.txt";
	char namesearcher[30];
	fdb = fopen(name, "r");
	pole_t* base;
	pole_t* newarr;
	while (!feof(fdb))
	{
		if (fgetc(fdb) == '\n')
			tempsize++;
	}
	tempsize = tempsize / 6;
	fclose(fdb);
	base = (pole_t*)malloc(tempsize * sizeof(pole_t));
	baseinitialize(name, base, &tempsize);
	printf("\aПрограмма дляработы с базой данных\"Антенна\"\n");
	printf("Выберите пункт меню введя соответсвующую цифру:\n"
		"1.Создание новой записи в базе данных\n"
		"2.Чтение всех записей, НУЖНОДОРАБОТАТЬ!!!!\n"
		"3.Cортировка записей по Q\n"
		"4.Поиск по имени\n"
		"5.Поиск в диапазоне высот\n"
		"6.Выход из"
		"программы\n");
		sizemas = tempsize;
	while (exitstate != 1) {
		int* arrotv = (int*)malloc((tempsize) * sizeof(int));
		printf("\n%d", sizemas);
		tempsize = sizemas;
		scanf("%d", &switchstate);
		switch (switchstate) {
		case 1:
			system("cls");
			newzap(&sizemas, base, name, &newarr);
			printf("%d", tempsize);
			fclose(fdb);
			baseinitialize(name, base, &sizemas);
			printf("\nВыберите пункт меню введя соответсвующую цифру:\n1.Создание новой записи в базе данных\n2.Чтение всех записей, НУЖНОДОРАБОТАТЬ!!!!\n3.Cортировка записей по Q\n4.Поиск по имени\n5.Поиск в диапазоне высот\n6.Выход изпрограммы\n");
			break;
		case 2:
			system("cls");
			baseinitialize(name, base, &sizemas);
			readfromfile(name, base, &tempsize);
			printf("\nВыберите пункт меню введя соответсвующую цифру:\n1.Создание новой записи в базе данных\n2.Чтение всех записей, НУЖНОДОРАБОТАТЬ!!!!\n3.Cортировка записей по Q\n4.Поиск по имени\n5.Поиск в диапазоне высот\n6.Выход изпрограммы\n");
			break;
		case 3:
			system("cls");
			baseinitialize(name, base, &sizemas);
			qsort(base, tempsize, sizeof(pole_t), compare);
			printbase(base, &tempsize);
			printf("\nВыберите пункт меню введя соответсвующую цифру:\n1.Создание новой записи в базе данных\n2.Чтение всех записей, НУЖНОДОРАБОТАТЬ!!!!\n3.Cортировка записей по Q\n4.Поиск по имени\n5.Поиск в диапазоне высот\n6.Выход изпрограммы\n");
			break;
		case 4:
			
			system("cls");
			baseinitialize(name, base, &sizemas);
			printf("Введите имя, по которому нужно произвести поиск\n");
			scanf("%s", &namesearcher);
			printf("По имени %s найденны следующие записи\n", namesearcher);
			arrotv = namefinder(base, &sizemas, namesearcher, arrotv);
			for (int i = 0; i < sizemas; i++) {
				int foundname = 0;
				foundname = *arrotv++;
				if (foundname >= 0 && foundname <= tempsize) {
					printf("%s %.2f %.2lf %s %.2f\n", base[foundname].name, base[foundname].mow, base[foundname].koef, base[foundname].forma, base[foundname].height);
				}
			}
			printf("\nВыберите пункт меню введя соответсвующую цифру:\n1.Создание новой записи в базе данных\n2.Чтение всех записей, НУЖНОДОРАБОТАТЬ!!!!\n3.Cортировка записей по Q\n4.Поиск по имени\n5.Поиск в диапазоне высот\n6.Выход изпрограммы\n");
			break;
		case 5:
			system("cls");
			baseinitialize(name, base, &sizemas);
			printf("Введите нижний порог высоты\n");
			scanf("%f", &baseh);
			printf("Введите верхний порог высоты\n");
			scanf("%f", &toph);
			printf("В диапазоне высот от %f до %f найдены следующие записи\n", baseh, toph);
			arrotv = heightrangesearch(base, &tempsize, toph, baseh, arrotv);
			for (int i = 0; i < sizemas; i++) {
				int foundname = 0;
				foundname = *arrotv++;
				if (foundname >= 0 && foundname <= tempsize) {
					printf("%s %.2f %.2lf %s %.2f\n", base[foundname].name, base[foundname].mow, base[foundname].koef, base[foundname].forma, base[foundname].height);
				}
			}
			printf("\nВыберите пункт меню введя соответсвующую цифру:\n1.Создание новой записи в базе данных\n2.Чтение всех записей, НУЖНОДОРАБОТАТЬ!!!!\n3.Cортировка записей по Q\n4.Поиск по имени\n5.Поиск в диапазоне высот\n6.Выход изпрограммы\n");
			break;
		case 6:
			free(base);
			free(arrotv);
			exitstate = 1;
			return 1;
			break;
		}
	}
}