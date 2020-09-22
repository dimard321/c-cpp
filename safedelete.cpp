#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <Bcrypt.h>
#include <list>
#include <string>
using namespace std;
typedef unsigned char byte;
const byte tab[27][3]
{
{ 0x55, 0x55, 0x55 },
{ 0xAA, 0xAA, 0xAA },
{ 0x92, 0x49, 0x24 },
{ 0x49, 0x24, 0x92 },
{ 0x24, 0x92, 0x49 },
{ 0x00, 0x00, 0x00 },
{ 0x11, 0x11, 0x11 },
{ 0x22, 0x22, 0x22 },
{ 0x33, 0x33, 0x33 },
{ 0x44, 0x44, 0x55 },
{ 0x55, 0x55, 0x66 },
{ 0x66, 0x66, 0x66 },
{ 0x77, 0x77, 0x77 },
{ 0x88, 0x88, 0x88 },
{ 0x99, 0x99, 0x99 },
{ 0xAA, 0xAA, 0xAA },
{ 0xBB, 0xBB, 0xBB },
{ 0xCC, 0xCC, 0xCC },
{ 0xDD, 0xDD, 0xDD },
{ 0xEE, 0xEE, 0xEE },
{ 0xFF, 0xFF, 0xFF },
{ 0x92, 0x49, 0x24 },
{ 0x49, 0x24, 0x92 },
{ 0x24, 0x92, 0x49 },
{ 0x6D, 0xB6, 0xDB },
{ 0xB6, 0xDB, 0x6D },
{ 0xDB, 0x6D, 0xB6 },
};
int GetSize(string path){
	FILE* file;
	file = fopen(path.c_str(), "r+b");
	if (file == NULL){
		cout << "Файл не открылся" << endl;
		return 1;
	}
	int Fsize = 0;
	if (fseek(file, 0, SEEK_END) != 0){
		return 7;
	}
	Fsize = ftell(file);
	if (Fsize == -1L){
		cout << "Ошибка при получении размера файла(ftell)" << endl;
		return 13;
	}
	if (fclose(file) == EOF){
		cout << "Ошибка при закрытии файла" << endl;
		return 9;
	}
	return Fsize;
}
int reWrite1(string path, const byte* value, int Fsize){
	if (Fsize < 0){
		cout << "Ошибка функции GetSize" << endl;
		return 5;
	}
	FILE* file = fopen(path.c_str(), "wb+");
	if (file == NULL){
		cout << "Ощибка при открытии файла" << endl;
		return 1;
	}
	for (int i = 0; i < Fsize; i++){
		if (fwrite((char*)&value[i % 3],
			sizeof(value[i % 3]), 1, file) < 1)
		{
			cout << "Ошибка при записи в файл" <<endl;
			return 8;
		}
	}
	if (fclose(file) == EOF){
		cout << "Ошибка при закрытии файла" << endl;
		return 9;
	}
	return 0;
}
int reWrite2(string path, int Fsize){
	byte* rndBytes = NULL;
	if (Fsize < 0){
		cout << "Ошибка функции GETSIZE" << endl;
		return 5;
	}
	FILE* file = fopen(path.c_str(), "wb+");
	if (file == NULL){
		cout << "Ошибка при открытии файла" << endl;
		return 1;
	}
	try{
		rndBytes = new byte[Fsize];
	}
	catch (bad_alloc ex){
		return 3;
	}
	if (fseek(file, 0, 0) != 0){
		return 7;
	}
	HCRYPTPROV hCryptCtx = NULL;
	if (CryptAcquireContext(&hCryptCtx, NULL,MS_DEF_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT) == 0) return 19;
	if (CryptGenRandom(hCryptCtx, Fsize, rndBytes)== 0) return 20;
	if (CryptReleaseContext(hCryptCtx, 0) == 0) return 21;
	for (int i = 0; i < Fsize; i++){
		if (fwrite(rndBytes, sizeof(rndBytes[0]), 1,file) < 1){
			cout << "Ошибка при записи в файл" <<endl;
			return 8;
		}
	}
	memset(rndBytes, 0xCC, Fsize);
	delete[] rndBytes;
	if (fclose(file) == EOF){
		cout << "Ошибка при закрытии файла" << endl;
		return 9;
	}
	return 0;
}
int REWRITE(string path, const byte tab[27][3], int Fsize){
	for (int i = 0; i < 4; i++){
		if (reWrite2(path, Fsize) != 0){
			cout << "Ошибка функции reWrite2" << endl;
			return 10;
		}
	}
	for (int i = 0; i < 27; i++){
		if (reWrite1(path, tab[i], Fsize) != 0){
			cout << "Ошибка функции reWrite1" << endl;
			return 11;
		}
	}
	for (int i = 0; i < 4; i++){
		if (reWrite2(path, Fsize) != 0){
			cout << "Ошибка функции reWrite2" << endl;
			return 10;
		}
	}
	return 0;
}
int REWRITEMYBYTES(string path, int Fsize, char byte_value){
	if (Fsize < 0){
		cout << "Ошибка функции GetSize" << endl;
		return 5;
	}
	FILE* file = fopen(path.c_str(), "wb+");
	if (file == NULL){
		cout << "Ошибка при открытии файла" << endl;
		return 1;
	}
	for (int j = 0; j < Fsize; j++){
		if (fwrite(&byte_value,	sizeof(byte_value), 1, file) < 1){
			cout << "Ошибка при записи в файл" << endl;
			return 8;
		}
	}
	if (fclose(file) == EOF){
		cout << "Ошибка при закрытии файла" << endl;
		return 9;
	}
	return 0;
}
int GetAllFiles(WIN32_FIND_DATA* FindFile, string path, list<string>* data){
	HANDLE h;
	h = FindFirstFile((path + "\\*").c_str(),FindFile);
	do
	{
		if (lstrcmpi(FindFile->cFileName, ".")== 0 || lstrcmpi(FindFile->cFileName, "..") == 0)
			continue;
		if (!(FindFile -> dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			data->push_front(path + "\\" + FindFile->cFileName);
		}
		else if (FindFile -> dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			data->push_front(path + "\\" + FindFile->cFileName);
			GetAllFiles(FindFile, (path + "\\" + FindFile->cFileName), data);
		}
	} while (FindNextFile(h, FindFile));
	if (FindClose(h) == 0)
	{
		cout << "Ошибка функции FindClose" <<endl;
		return 12;
	}
	return 0;
}
int DeleteFolder(WIN32_FIND_DATA* FindFile, string path, list<string>* data, string choice)
{
	int count;
	list<string>::iterator iter;
	if (choice == "1"){
		for (iter = data->begin(); iter != data -> end(); iter++){
			DWORD Attributte = GetFileAttributes((*iter).c_str());
			if (Attributte & FILE_ATTRIBUTE_DIRECTORY){
				if(!RemoveDirectory((*iter).c_str())){
					cout << "Ошибка функции RemoveDirectory" << endl;
					return 17;
				}
			}
			else{
				int size = GetSize((*iter).c_str());
				if (REWRITE((*iter).c_str(),tab, size) != 0){
					cout << "Ошибка функции REWRITE" << endl;
					return 6;
				}
				if (DeleteFile((*iter).c_str()) == 0){
					cout << "Ошибка функции DeleteFile" << endl;
					return 16;
				}
			}
		}
	}
	else if (choice == "2"){
		cout << "Введите количество итераций" <<endl;
		cin >> count;
		byte * byte_value;
		try{
			byte_value = new byte[count];
		}
		catch (bad_alloc ex){
			cout << "Ошибка выделения памяти" << endl;
			return 3;
		}
		cout << "Введите байты с клавиатуры" << endl;
		for (int i = 0; i < count; i++){
			scanf("%d", &byte_value[i]);
		}
		for (iter = data->begin(); iter != data -> end(); iter++){
			DWORD Attributte = GetFileAttributes((*iter).c_str());
			if (Attributte & FILE_ATTRIBUTE_DIRECTORY){
				if(!RemoveDirectory((*iter).c_str())){
					cout << "Ошибка функции RemoveDirectory" << endl;
					return 17;
				}
			}
			else{
				int size = GetSize((*iter).c_str());
				for (int i = 0; i < count; i++){
					if(REWRITEMYBYTES((*iter).c_str(), size, byte_value[i]) !=0){
						cout << "Ошибка функции REWRITEMYBYTES" << endl;
						system("pause");
						return 14;
					}
				}
				if (DeleteFile((*iter).c_str()) ==0){
					cout << "Ошибка функции DeleteFile" << endl;
					return 16;
				}
			}
		}
	}
	return 0;
}
int main()
{
	setlocale(LC_ALL, "RUS");
	WIN32_FIND_DATA FindFile;
	string start, choice2, confirm;
	string choice1;
	list <string> data;
	list<string>::iterator iter;
	cout << "Безопасное удаление" << endl;
	cout << "Введите START для начала работы программы \\ Введите EXIT для закрытия" << endl;
	getline(cin, start);
	string path;
	if (start == "START")
	{
		cout << "Нажмите 1, чтобы удалить информацию алгоритмом Гутмана \\ Нажмите 2, чтобы удалить информацию вручную"<<endl;
		getline(cin, choice1);
		if ((choice1 != "1") && (choice1 != "2")){
			cout << "Введено некорректное значение" << endl;
			system("pause");
			return 4;
		}
		cout << "Введите FILE для удаления фалйа \\ Введите FOLDER для удаления папки" << endl;
		getline(cin, choice2);
		if (choice2 == "FOLDER"){
			cout << "Введите путь к папке" << endl;
			getline(cin, path);
			HANDLE h;
			h = FindFirstFile((path).c_str(),&FindFile);
			if (h == INVALID_HANDLE_VALUE){
				cout << "Введен некорректный путь"<< endl;
				system("pause");
				return 2;
			}
			cout << endl;
			cout << "Список файлов,которые будут удалены:" << endl;
			if (GetAllFiles(&FindFile, path, &data)!= 0){
				cout << "Ошибка функции GETALLFILES" << endl;
				system("pause");
				return 15;
			}
			for (iter = data.begin(); iter !=data.end(); iter++){
				cout << *iter << endl;
			}
			cout << "Удалить файлы в папке YES \\ NO"<<endl;
			getline(cin, confirm);
			if (confirm == "YES"){
				if (DeleteFolder(&FindFile, path,
					&data, choice1) != 0){
					cout << "Ошибка функцииDeleteFolder" << endl;
					system("pause");
					return 18;
				}
				cout << "Файлы успешно удалены" << endl;
			}
			else if (confirm == "NO"){
				system("pause");
				return 0;
			}
			else{
				cout << "Введено некорректноезначение" << endl;
				system("pause");
				return 4;
			}
		}
		else if (choice2 == "FILE"){
			cout << "Введите путь к файлу" << endl; 
			getline(cin, path);
			HANDLE h;
			h = FindFirstFile((path).c_str(),&FindFile);
			if (h == INVALID_HANDLE_VALUE){
				cout << "Введен некорректный путь"<< endl;
				system("pause");
				return 2;
			}
			cout << "Удалить данный файл YES or NO"<< endl;
			cin >> confirm;
			if (confirm == "YES"){
				int size = GetSize(path);
				if (size < 0){
					cout << "Ошибка функции GetSize"<< endl;
					system("pause");
					return 5;
				}
				if (choice1 == "1"){
					if (REWRITE(path, tab, size) !=0){
						cout << "Ошибка функции REWRITE" << endl;
						system("pause");
						return 6;
					}
				}
				else if (choice1 == "2"){
					int count;
					cout << "Введите количество итераций" << endl;
					cin >> count;
					if (count <= 0){
						cout << "Введено некорректное значениеcount" << endl;
						return 4;
					}
					byte* byte_value;
					try{
						byte_value = new
							byte[count];
					}
					catch (bad_alloc ex){
						cout << "Ошибка выделения памяти" << endl;
						return 3;
					}
					cout << "Введите байты с клавиатуры" << endl;
					for (int i = 0; i < count; i++){
						scanf("%d",&byte_value[i]);
					}
					for (int i = 0; i < count; i++){
						if (REWRITEMYBYTES(path,size, byte_value[i]) != 0){
							cout << "Ошибка функции REWRITEMYBYTES" << endl;
							system("pause");
							return 14;
						}
					}
				}
				if (DeleteFile(path.c_str()) != 0){
					cout << "Файл успешно удален" <<endl;
					system("pause");
					return 0;
				}
				else{
					cout << "Ошибка при удалении файла" << endl;
					system("pause");
					return 16;
				}
			}
			else if (confirm == "NO"){
				system("pause");
				return 0;
			}
			else{
				cout << "Введено некорректное значение" << endl;
				system("pause");
				return 4;
			}
		}
	}
	else if (start == "EXIT"){
		system("pause");
		return 0;
	}
	else{
		cout << "Введено некорректное значение" << endl;
		system("pause");
		return 4; 
	}
	system("pause");
	return 0;
}