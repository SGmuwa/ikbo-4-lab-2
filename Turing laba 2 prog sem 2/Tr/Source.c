﻿/*Разработал Сидоренко Михаил (Sidorenko Mikhail), первая версия от 04.2017*/


#pragma once

#ifndef _TURING_MACHINE_H_MUWA_LABA
#define _TURING_MACHINE_H_MUWA_LABA

/* Инструкция, которая компилирует программу без использования технологии CRT (менее безопасно, но кроссплатформенно)*/
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

/* Инструкция, которая отключает Windows.h
Возможны проблемы при работе с руссим языком.*/
#define NO_WINDOWS
/* Инструкция, которая отключает переключение locale и отключает библиотеку locale.h.
Возможны проблемы с русским языком.*/
#define NO_LOCALE

#ifdef _CRT_SECURE_NO_WARNINGS
extern char * gets(char * string);
#endif

/* Библиотека реализует такой абстрактный объект, как бесконечная лента. */
#include "../../Turing/Muwa_expandable_lenta.h"

#ifndef NO_LOCALE
	#ifndef _INC_LOCALE
		#include <locale.h>
	#endif
#endif

#ifndef _INC_STDIO
#include <stdio.h>
#endif /* _INC_STDIO */

#ifndef _INC_STRING
#include <string.h>
#endif /* _INC_STRING */

#ifndef _INC_STDLIB
#include <stdlib.h>
#endif

/* Считывает текст из stdin и помещает в string
string - место сохранения текста из stdin
size - максимальный размер, который может быть помещён в string (не используется при _CRT_SECURE_NO_WARNINGS)*/
char *__cdecl gets_u(char * string, size_t _size)
{
#ifdef _CRT_SECURE_NO_WARNINGS
	return fgets(string, _size, stdin);
#else
	return gets_s(string, _size);
#endif
}

/* Перечисление существующих команд */
enum commands
{
	error,		/* При чтении возникла ошибка */
	comment,	/* * - строка-комментарии */
	movl,		/* Движение влево */
	movr,		/* Движение вправо */
	inc,		/* Добавить в ячейку 1 */
	dec,		/* Убавить из ячейки 1 */
	print,		/* Вывод ячейки */
	get,		/* Считать 1 байт с клавиатуры и записать в текущую ячейку */
	printc,		/* Вывод значения текущей ячейки как символ */
	begin,		/* переход до end, если в ячейке 0 */
	end			/* Переход вврх до begin, если в ячейке 1 */
};

/* Меняет местами две переменных
left - указатель на одну переменную
right - указатель на другую переменную
size - размер, занимаемой переменной (размер типа, например, sizeof(int).) */
void swap(void* left, void* right, size_t size)
{
	register size_t i;
	for (i = 0; i < size; i++)
	{
		((char*)(left))[i] = ((char*)(left))[i] + ((char*)(right))[i];
		((char*)(right))[i] = ((char*)(left))[i] - ((char*)(right))[i]; /* a + b - b */
		((char*)(left))[i] = ((char*)(left))[i] - ((char*)(right))[i]; /* a + b - ((a + b) - b) */
	}
}

#ifndef _INC_STDLIB
/* Отвечает на вопрос, равны ли два блока памяти. */
char IsEqute(const void * A, const void * B, size_t size)
{
	register size_t i = 0u;
	for (; i < size; i++)
	{
		if (((char*)A)[i] != ((char*)B)[i]) return (char)0;
	}
	return (char)1;
}

void Equate(void * A, const void * B, size_t size)
{
#ifdef _CRT_SECURE_NO_WARNINGS
	memcpy(A, B, size);
#else
	register size_t i = 0u;
	for (; i < size; i++)
	{
		((char*)A)[i] = ((char*)B)[i];
	}
#endif
}

/* Находит минимальное из данных.
count - количество данных
size - размер одной единицы данных
result - сюда будет отправляться ответ
[образец] - размер блока, который следует исключить из выборки
[данные], [данные]... - среди них идёт поиск минимального. Исключаются те, которые равны образцу*/
void _SearchMinimumBesides(size_t count, size_t size, void * result,...)
{
	size_t i = 0;
	char * index = (char*)result + size;
	if (count == 0 || size == 0 || result == NULL) return;
	Equate(result, index, size);
	i++, index += size;
	for (; i < count; i++, index += size)
	{

	}
}
#endif

/* Поиск диапазона символов. Возвращает указатель на тот символ, который ближе всего к указателю на str
chStart и chEnd это начало и конец поиска:
chStart = 'a'; chEnd = 'z'; Поиск: a .. z
В случае chStart > chEnd функция сама поменяет их местами.
В строке "ziefoka" ответ будет &'z', не смотря на то, что  &'a' будет найден раньше*/
char * _SearchForDiapason(const char * str, char chStart, char chEnd)
{
	char sim, * buffer, * out = NULL; /*До сих пор не понимаю, почему рекомендуется создавать локальные переменные в самом наачале :( */
	if (str == NULL) return NULL;
	if (chStart > chEnd) swap(&chStart, &chEnd, sizeof(char));
	for (sim = chStart; sim <= chEnd; sim++)
	{
		buffer = strchr(str, sim);
		if (buffer != NULL && (buffer < out || out == NULL))
		{
			out = buffer;
		}
	}
	return out;
}

/*Возвращает укзаатель на найденый в тексте str первый символ английского алфавита*/
char * _SearchForAlphabet(const char * str)
{
	char * a, * b, * c;
	if (str == NULL) return NULL;
	a = _SearchForDiapason(str, 'a', 'z');
	b = _SearchForDiapason(str, 'A', 'Z');
	c = _SearchForDiapason(str, '*', '*');
	if (a == NULL)
	{
		if (b == NULL) return c;
		else if (c == NULL) return b;
		else if (c < b) return c;
		else return b;
	}
	else if (b == NULL)
	{
		if (a == NULL) return c;
		else if (c == NULL) return a;
		else if (c < a) return c;
		else return a;
	}
	else if (c == NULL)
	{
		if (a == NULL) return b;
		else if (b == NULL) return a;
		else if (b < a) return b;
		else return a;
	}
	else if (a < b)
	{
		if (a < c) return a;
		else return c;
	}
	else /* b < a */
	{
		if (c < b) return c;
		else return b;
	}
}

/* Переводит на первый в строке символ алфавита. Если не найден, то возвращает указатель на первый символ '\0'. */
void GotoToAlphabet(char ** input)
{
	char * buffer;
	if (input == NULL || *input == NULL) return;
	buffer = _SearchForAlphabet(*input);
	if (buffer == NULL)
	{
		*input += strlen(*input);
	}
	else *input = buffer;
}

/* Данная функция вернёт команду, которая первая в строке *input. Передаётся char** чтобы можно было передвигать char** */
enum commands ReadCommand(char ** input)
{
	char buffer[32] = { '\0' };
	GotoToAlphabet(input);
	sscanf(*input, "%32s", buffer);
	if (buffer[0] != 0) /* Если buffer был заполнен */
	{
		*input += strlen(buffer); /* Добавляем то, что проглатили */
		if(buffer[0] != '*') GotoToAlphabet(input); /* Переходим на следующую команду */
		if (strcmp(buffer, "movl") == 0)
		{
			return movl;
		}
		else if (strcmp(buffer, "movr") == 0)
		{
			return movr;
		}
		else if (strcmp(buffer, "inc") == 0)
		{
			return inc;
		}
		else if (strcmp(buffer, "dec") == 0)
		{
			return dec;
		}
		else if (strcmp(buffer, "print") == 0)
		{
			return print;
		}
		else if (strcmp(buffer, "get") == 0)
		{
			return get;
		}
		else if (strcmp(buffer, "printc") == 0)
		{
			return printc;
		}
		else if (strcmp(buffer, "begin") == 0)
		{
			return begin;
		}
		else if (strcmp(buffer, "end") == 0)
		{
			return end;
		}
		else if (strcmp(buffer, "*") == 0)
		{
			while (**input != '\n' && **input != EOF && **input != '\0') (*input)++;
			return comment;
		}
		else return error;
	}
	else
	{
		(*input)++;
		return error;
	}
}
/* Структура хранит в себе команды и количество комманд */
typedef struct
{
	enum commands * A;	/* Указывает на массив команд */
	size_t c;			/* Количество команд в массиве */
} commands_count;

typedef struct
{
	char * A; /* Array */
	size_t c; /* count */
} char_count;

/* Функция преобразует текст в набор команд. Используется malloc и realloc в каждой итерации.
char_count fData - данные, которые надо преобразовать в enum commands
commands_count * out - адрес, куда должны быть помещены данные. Используется Malloc для out->A
Возвращает: код ошибки.
Ошибки:
-1 - malloc(0) вернул NULL.
-2 - realloc вернул NULL
Успешные ситуации:
0
*/
errno_t ReadsCommands(const char_count fData, commands_count * out)
{
/* enum commands ReadCommand(char ** input) */
	if(fData.A == NULL) return -1;
	char * index = fData.A;
	enum commands buffer;
	size_t i = 0;
	out->c = 0;
	while (index < fData.A + fData.c - 1) if (ReadCommand(&index) != error)
		out->c++; /* Посчитать количество верных комманд */
	out->A = (enum commands*)malloc(out->c*sizeof(enum commands*));
	if (out->A == NULL) return -1; 
	index = fData.A;
	while(index < fData.A + fData.c - 1)
	{
		buffer = ReadCommand(&index);
		if (buffer != error)
		{
			out->A[i++] = buffer;
		}
	}
	return 0;
}

/* Устанавливает значение каждого элемента A равным тому, что содержится в protorype.
A[0] = A[1] = ... = A[count] = *prototype;
A - массив, элементы которого все надо приравнять к *prototype
prototype - указатель на блок память (размера size), содержащий экземпляр, к чему должны приравняться все ячейки массива A
size - sizeof(тип элементов массива A и prototype) (тип *A и тип *prototype должен быть одинаковым)
count - количество элементов в массиве A */
void ArraySetRage(void * A, const void * prototype, size_t size, size_t count)
{
	size_t i, j;
	for(i = 0; i < count; i++)
	{
		for(j = 0; j < size; j++)
		{
			((char*)A)[i*size + j] = ((char*)prototype)[j];
		}
	}
}
/*
#ifndef _INC_FCNTL
#include <fcntl.h>
#endif

#ifndef _fstat
#include <sys/stat.h>
#endif
*/
/* Используется malloc. Считывает все данные с файла
fname - имя файла, который нужно открыть и прочитать
str - указатель на строку, куда надо записывать всё, что было прочитано с файла
str_size - сюда указывется размер файла. Возвращается, когда функция возвращает значения -4, 0, 1, 2, 3
Возвращаемое значение: код ошибки.
Ошибки:
-1 Не удалось открыть дескриптор для чтения
-2 Не удалось открыть файл для бинарного чтения
-3 Не удалось получить статитсику файла, о его размере
-4 Не удалось выделить оперативную память для помещения содержимого файла в оперативную память
Предупреждения:
2 Не только не совпадает количество прочитанной информации, но и размер выделенной памяти оказался 0.
1 Прочитанное количество элементов не совподает с размером файла.
3 Было успешно выделено 0 байт в оперативную память.
Успешные ситуации:
0 Успешно удалось поместить содержимое файла fname в участо памяти, на который теперь указывает *str, а размер содержимого помещён в *str_size.*/
errno_t ReadAllDataFromFile(const char * fname, char ** str, size_t * str_size) 
{

	char * buffer = NULL;

	FILE * file = {0};
#ifdef _CRT_SECURE_NO_WARNINGS
	file = fopen(fname, "rb");
#else
	fopen_s(&file, fname, "rb");
#endif
	if (file != NULL)
	{
		fseek(file, 0L, SEEK_END);
		*str_size = ftell(file) + 1; /* На содержимое файла + признак окончания данных */
		fseek(file, 0L, SEEK_SET);
		buffer = (char*)malloc(*str_size);
		if (buffer == NULL)
		{
			fclose(file);
			return -4; /* Не хватает памяти, но количество памяти удалось прочесть. */
		}
		buffer[0] = '\0';
		ArraySetRage(buffer, buffer, sizeof(char), *str_size); /* Инцилизация массива (присвоит первое значение массива к всем остальным элементам) */
		if (fread(buffer, sizeof(char), *str_size / sizeof(char), file) + 1 != sizeof(char)**str_size)
		{
			fclose(file);
			*str = buffer;
			if (*str_size == 0) return 2; /* Не только не совпадает, но и размер выделенной памяти оказался 0. */
			else return 1; /* warning: прочитанное количество элементов не совподает с размером файла. */
		}
		fclose(file);
		*str = buffer;
		if (*str_size == 0) return 3; /* Было успешно выделено 0 байт в оперативную память. */
		else return 0;
	}
	else
	{
		return -2; /* Не удалось октрыть файл для бинарного чтения */
	}
}

/* field - поле со списоком команд. Требуется для being и end
com - указатель на команду из field, которую следует обработать
update - лента, на которую помещена вся память
Возвращаемое значение:
-1 Комманда com вне границах массива field.A .. field.A + field.c - 1
0 Всё сработало нормально
1 Не понятно, что делать с данной командой
2 Ошибка чтения из stdin.
*/
errno_t Step(const commands_count field, enum commands ** com, struct Lenta * update)
{
	auto unsigned short int buffer = 0;
	if(*com < field.A || *com > field.A + field.c - 1) return -1;
	ExpandableLenta_MemoryAdjustment(update);
	switch (**com)
	{
	case movl:
		update->position--;
		(*com)++;
		return 0;
	case movr:
		update->position++;
		(*com)++;
		return 0;
	case inc:
		update->position[0]++;
		(*com)++;
		return 0;
	case dec:
		update->position[0]--;
		(*com)++;
		return 0;
	case printc:
		printf("%c\n", update->position[0]);
		(*com)++;
		return 0;
	case print:
		printf("%hu\n", (unsigned short int)update->position[0]);
		(*com)++;
		return 0;
	case get:
#ifdef _CRT_SECURE_NO_WARNINGS
		printf("byte: ");
		(*com)++;
		if (scanf("%hu", &buffer) != 1) return 2;
#else
		printf_s("byte: ");
		if (scanf_s("%hu", &buffer) != 1) return 2;
#endif
		update->position[0] = (char)buffer;
		return 0;
	case begin:
		if (update->position[0] == 0)
		{
			/* переход в end + 1 */
			int find = 1;
			while(find != 0)
			{
				(*com)++;
				if(/* *com < field.A || */*com > field.A + field.c - 1) return -1;
				if(**com == begin) find++;
				else if(**com == end) find--;
			}
			(*com)++;
			return 0;
		}
		else
		{
			(*com)++;
			return 0;
		}
	case end:
		if (update->position[0] != 0)
		{
			/* переход обратно на родственную begin + 1. */
			int find = -1;
			while(find != 0)
			{
				(*com)--;
				if(*com < field.A/* || *com > fild.A + field.c - 1*/) return -1;
				if(**com == begin) find++;
				else if(**com == end) find--;
			}
			(*com)++;
			return 0;
		}
		else
		{
			(*com)++;
			return 0;
		}
	default:
		(*com)++;
		return 1;
	}
}

#ifndef NO_WINDOWS
	#ifndef _INC_WINDOWS
		#include <Windows.h>
	#endif
#endif


void UserInterface(int argc, char * argv[])
{
/* errno_t ReadsCommands(const char_count fData, commands_count * out) */
	char fname[_MAX_PATH] = {'\0'};
	char_count fData = {NULL, 0};
	char * ToClear = NULL; /* То, что будет помещено в эту переменную, будет очищено. Использукется для вывода ленты*/
	errno_t er = 0; /* ошибки работы */
	commands_count fCommands = {NULL, 0};
	struct Lenta lt = {NULL, NULL, NULL};
	enum commands * iCom = NULL; /* Указатель (индекс) на текущую команду */
	#ifndef NO_LOCALE
		setlocale(LC_ALL, "rus");
	#endif
	if (argc == 2)
	{
#ifdef _CRT_SECURE_NO_WARNINGS
		if (memcpy(fname, argv[1], strlen(argv[1])) == fname)
#else
		if (memcpy_s(fname, _MAX_PATH, argv[1], strlen(argv[1])) == 0)
#endif
		{
			goto filename_ready;
		}
	}
reset:
	/* Получение данных из файла */
	
	printf("Filename: ");
	do
	{
		if(er != 0) printf("error code: %d\n. Please, again.", (int)er);
		gets_u(fname, _MAX_PATH);
	filename_ready:
		#ifndef NO_WINDOWS
			OemToCharA(fname, fname);
		#endif
		er = ReadAllDataFromFile(fname, &(fData.A), &(fData.c));
	} while(er < 0); /* Считываем все данные с файла */
	if(er > 0) printf("filesize = 0 or read error\nWarning code: %d\n", (int)er);

	er = 0;
	/* Преобразование данных файла в комманды */
	er = ReadsCommands(fData, &fCommands);
	if(er < 0)
	{
		printf("char->commands: Error code: %d\nProgram reset...", (int)er);
		er = 0;
		free(fData.A);
		if(fCommands.A != NULL) free(fCommands.A);
		fData.c = 0; fCommands.c = 0;
		fname[0] = '\0';
		goto reset;
	}
	free(fData.A); fData.A = NULL; fData.c = 0;
	
	/* Прохождение шагов */
	lt = ExpandableLenta_Create();
	if(lt.position == NULL)
	{
		printf("ExpandableLenta_Create() return NULL (malloc)\nError code: %d\nProgram reset...", (int)er);
		er = 0;
		free(fData.A);
		if(fCommands.A != NULL) free(fCommands.A);
		fData.c = 0; fCommands.c = 0;
		fname[0] = '\0';
		goto reset;
	}
/*errno_t Step(const commands_count field, enum commands * com, struct Lenta * update) */
	iCom = fCommands.A;
	
	while(Step(fCommands, &iCom, &lt) >= 0);
	ToClear = ExpandableLenta_GetText(lt, '_');
#ifdef _CRT_SECURE_NO_WARNINGS
	printf("\nLenta:\n%s", ToClear);
#else
	printf_s("\nLenta:\n%s", ToClear, strlen(ToClear));
#endif
	free(fCommands.A); fCommands.A = NULL; fCommands.c = 0;
	free(lt.elements); lt.elements = lt.position = lt.top = NULL;
	free(ToClear);
	return;
}

#endif _TURING_MACHINE_H_MUWA_LABA


void main(int argc, char * argv[])
{
	char flag[2] = { 0 };
	while (1)
	{
		UserInterface(argc, argv);
		gets_u(&flag, 2u);
		if (*flag == 'q' || *flag == 'Q') return;
	}
}















/*enum commands * ReadsCommands(FILE * file, int * count)
{
	char * buffer[1024];
	int i = 0;
	for (; i < 1024; i++)
	{
		buffer[i] = (char*)malloc(sizeof(char)*256);
		buffer[i][0] = 0;
	}
	i = 0;
	//Чтение (построчно) данных из файла в бесконечном цикле
	while (fscanf(file, "%s", buffer[i])) i++;
	*count = i;
	enum commands * output = (enum commands *)malloc(sizeof(enum commands) * *count);
	for (; i >= 0; i--)
	{
		if (strcmp(buffer[i], "movl") == 0)
		{
			output[i] = movl;
		}
		else if (strcmp(buffer[i], "movr") == 0)
		{
			output[i] = movr;
		}
		else if (strcmp(buffer[i], "inc") == 0)
		{
			output[i] = inc;
		}
		else if (strcmp(buffer[i], "dec") == 0)
		{
			output[i] = dec;
		}
		else if (strcmp(buffer[i], "print") == 0)
		{
			output[i] = print;
		}
		else if (strcmp(buffer[i], "get") == 0)
		{
			output[i] = get;
		}
		else if (strcmp(buffer[i], "printc") == 0)
		{
			output[i] = printc;
		}
		else if (strcmp(buffer[i], "begin") == 0)
		{
			output[i] = begin;
		}
		else if (strcmp(buffer[i], "end") == 0)
		{
			output[i] = end;
		}
		else output[i] = error;
	}
	return output;
}*/
