#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stddef.h>
#include<string.h>
#include<locale.h>
#include<Windows.h>

FILE* intext;
FILE* outtext;
unsigned char* s;
int closein;
int closeout;

int Search_key()
{
	char e;
	int g=0, key,max = 0,maxI;
	size_t i, len;
	int c[256] = { 0 };
	intext = fchoiceen("path", "r");
	if (intext == NULL){
		printf("Файл c зашифрованым текстом не открылся\n");
		return 1;
	}
	while ((e = fgetc(intext)) != EOF){
		g++;
	}
	if (feof(intext) == 0) return 5;
	rewind(intext);
	s = (char*)calloc(sizeof(char), g);
	if (s == NULL){
		printf("Ошибка при выделении памяти\n");
		fclose(intext);
		return 2;
	}
	len = fread(s, sizeof(char), g, intext);
	if (len != g){
		printf("Ошибка при считывании\n");
		free(s);
		return 6;
	}
	for (i = 0; i < len; i++){
		if (s[i] == ' ' || s[i] == '\n') continue;
		else c[s[i]]++;
	}
	for (i = 0; i < 255; i++){
		if (c[i] > max){
			max = c[i];
			maxI = i;
		}
	}
	key = maxI - 'e';
	if (key < 0) key = key * (-1);
	free(s);
	closein = fclose(intext);
	if (closein != 0){
		printf("Файл с зашифрованым текстом не закрылся\n");
		return 3;
	}
	return key;
}
int Decryption(int key)
{
	if (key == 0) return 7;
	int g = 0, r;
	char e;
	size_t i, len;
	intext = fchoiceen("path", "r");
	outtext = fchoiceen("path", "w+t");
	if (intext == NULL){
		printf("Файл c зашифрованым текстом не открылся\n");
		return 1;
	}
	if (outtext == NULL) {
		printf("Файл для записи результата расшифровки не открылся\n");
		return 1;
	}
	while ((e = fgetc(intext)) != EOF){
		g++;
	}
	if (feof(intext) == 0) return 5;
	rewind(intext);
	s = (char*)calloc(sizeof(char), g);
	if (s == NULL){
		printf("Ошибка при выделении памяти\n");
		fclose(intext);
		fclose(outtext);
		return 2;
	}
	len = fread(s, sizeof(char), g, intext);
	if (len != g){
		printf("Ошибка при считывании\n");
		free(s);
		return 6;
	}
	for (i = 0; i < len; i++) {
		if ((s[i] - key) < 'A' && ((s[i] >= 'A' && s[i] <= 'Z')))
			s[i] = (s[i] + 26) - key;
		else if ((s[i] - key) < 'a' && ((s[i] >= 'a' && s[i] <= 'z')))
			s[i] = (s[i] + 26) - key;
		else if (s[i] > 'z' || s[i] < 'A' || (s[i] > 90 && s[i] < 97))
			s[i] = s[i];
		else s[i] = s[i] - key;
	}
	for (i = 0; i < len; i++){
		r = fprintf(outtext, "%c", s[i]);
		if (r < 0){
			printf("Ошибка при записи результата\n");
			fclose(intext);
			fclose(outtext);
			free(s);
			return 4;
		}
	}
	free(s);
	closein = fclose(intext);
	if (closein != 0){
		printf("Файл с зашифрованым текстом не закрылся\n");
		return 3;
	}
	closeout = fclose(outtext);
	if (closeout != 0) {
		printf("Файл с результатом не закрылся\n");
		return 3;
	}
	return 0;
}
int Ecryption(int key)
{
	if (key == 0) return 7;
	int g = 0, r;
	char e;
	size_t i, len;
	intext = fchoiceen("path", "r");
	outtext = fchoiceen("path", "w+t");
	if (intext == NULL){
		printf("Файл c  расшифрованым текстом не открылся\n");
		return 1;
	}
	if (outtext == NULL){
		printf("Файл с зашифрованым текстом не открылся\n");
		return 1;
	}
	while ((e = fgetc(intext)) != EOF){
		g++;
	}
	if (feof(intext) == 0) return 5;
	rewind(intext);
	s = (char*)calloc(sizeof(char), g);
	if (s == NULL){
		printf("Ошибка при выделении памяти\n");
		fclose(intext);
		fclose(outtext);
		return 2;
	}
	len = fread(s, sizeof(char), g, intext);
	if (len != g){
		printf("Ошибка при считывании\n");
		free(s);
		return 6;
	}
	for (i = 0; i < len; i++){
		if ((s[i] + key) > 'z' && (s[i] >= 'a' && s[i] <= 'z'))
			s[i] = (s[i] - 26) + key;
		else if ((s[i] + key) > 'Z' && (s[i] >= 'A' && s[i] <= 'Z'))
			s[i] = (s[i] - 26) + key;
		else if (s[i] > 'z' || s[i] < 'A' || (s[i] > 90 && s[i] < 97))
			s[i] = s[i];
		else s[i] = s[i] + key;
	}
	for (i = 0; i < len; i++){
		r = fprintf(outtext, "%c", s[i]);
		if (r < 0)
		{
			printf("Ошибка при записи результата\n");
			fclose(intext);
			fclose(outtext);
			free(s);
			return 4;
		}
	}
	free(s);
	closein = fclose(intext);
	if (closein != 0){
		printf("Ошибка при закрытии файла\n");
		fclose(intext);
		return 3;
	}
	closeout = fclose(outtext);
	if (closeout != 0){
		printf("Ошибка при закрытии файла\n");
		fclose(outtext);
		return 3;
	}
	return 0;
}
int main()
{
	setlocale(LC_ALL, "Rus");
	int check, e, d;
	int choice;
	check = Search_key();
	if (check >= 0)
	{
		printf("Получено корректное значение ключа\n");
	}
	else
	{
		printf("Ошибка при поиске ключа\n");
		return 0;
	}

	while (check != -1)
	{
		printf("Выберите операцию\n");
		printf("Ключ= %d\n", check);
		printf("Нажмите 1, чтобы расшифровать текст\n");
		printf("Нажмите 2, чтобы зашифровать текст\n");
		printf("Нажмите 0, чтобы закончить работу\n");
		scanf("%d", &choice);
		system("cls");
		if (choice == 1)
		{
			Search_key();
			d = Decryption(&check);
			if (d == 0)
				printf("Расшифровка прошла успешно\n");
			else
			{
				printf("Ошибка при расшифровке\n");
				system("pause");
				return 0;
			}
		}
		else if (choice == 2)
		{
			Search_key();
			e = Ecryption(&check);
			if (e == 0)
				printf("Шифровка прошла успешно\n");
			else
			{
				printf("Ошибка при шифровке\n");
				system("pause");
				return 0;
			}
		}
		else if (choice == 0) return 0;
	}
	system("pause");
	return 0;
}
