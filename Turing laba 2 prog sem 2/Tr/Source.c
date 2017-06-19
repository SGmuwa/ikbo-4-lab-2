/*���������� ��������� ������ (Sidorenko Mikhail), ������ ������ �� 04.2017*/


#pragma once

#ifndef _TURING_MACHINE_H_MUWA_LABA
#define _TURING_MACHINE_H_MUWA_LABA

/* ����������, ������� ����������� ��������� ��� ������������� ���������� CRT (����� ���������, �� �����������������)*/
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

/* ����������, ������� ��������� Windows.h
�������� �������� ��� ������ � ������ ������.*/
#define NO_WINDOWS
/* ����������, ������� ��������� ������������ locale � ��������� ���������� locale.h.
�������� �������� � ������� ������.*/
#define NO_LOCALE

#ifdef _CRT_SECURE_NO_WARNINGS
extern char * gets(char * string);
#endif

/* ���������� ��������� ����� ����������� ������, ��� ����������� �����. */
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

/* ��������� ����� �� stdin � �������� � string
string - ����� ���������� ������ �� stdin
size - ������������ ������, ������� ����� ���� ������� � string (�� ������������ ��� _CRT_SECURE_NO_WARNINGS)*/
char *__cdecl gets_u(char * string, size_t _size)
{
#ifdef _CRT_SECURE_NO_WARNINGS
	return fgets(string, _size, stdin);
#else
	return gets_s(string, _size);
#endif
}

/* ������������ ������������ ������ */
enum commands
{
	error,		/* ��� ������ �������� ������ */
	comment,	/* * - ������-����������� */
	movl,		/* �������� ����� */
	movr,		/* �������� ������ */
	inc,		/* �������� � ������ 1 */
	dec,		/* ������� �� ������ 1 */
	print,		/* ����� ������ */
	get,		/* ������� 1 ���� � ���������� � �������� � ������� ������ */
	printc,		/* ����� �������� ������� ������ ��� ������ */
	begin,		/* ������� �� end, ���� � ������ 0 */
	end			/* ������� ���� �� begin, ���� � ������ 1 */
};

/* ������ ������� ��� ����������
left - ��������� �� ���� ����������
right - ��������� �� ������ ����������
size - ������, ���������� ���������� (������ ����, ��������, sizeof(int).) */
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
/* �������� �� ������, ����� �� ��� ����� ������. */
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

/* ������� ����������� �� ������.
count - ���������� ������
size - ������ ����� ������� ������
result - ���� ����� ������������ �����
[�������] - ������ �����, ������� ������� ��������� �� �������
[������], [������]... - ����� ��� ��� ����� ������������. ����������� ��, ������� ����� �������*/
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

/* ����� ��������� ��������. ���������� ��������� �� ��� ������, ������� ����� ����� � ��������� �� str
chStart � chEnd ��� ������ � ����� ������:
chStart = 'a'; chEnd = 'z'; �����: a .. z
� ������ chStart > chEnd ������� ���� �������� �� �������.
� ������ "ziefoka" ����� ����� &'z', �� ������ �� ��, ���  &'a' ����� ������ ������*/
char * _SearchForDiapason(const char * str, char chStart, char chEnd)
{
	char sim, * buffer, * out = NULL; /*�� ��� ��� �� �������, ������ ������������� ��������� ��������� ���������� � ����� ������� :( */
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

/*���������� ��������� �� �������� � ������ str ������ ������ ����������� ��������*/
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

/* ��������� �� ������ � ������ ������ ��������. ���� �� ������, �� ���������� ��������� �� ������ ������ '\0'. */
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

/* ������ ������� ����� �������, ������� ������ � ������ *input. ��������� char** ����� ����� ���� ����������� char** */
enum commands ReadCommand(char ** input)
{
	char buffer[32] = { '\0' };
	GotoToAlphabet(input);
	sscanf(*input, "%32s", buffer);
	if (buffer[0] != 0) /* ���� buffer ��� �������� */
	{
		*input += strlen(buffer); /* ��������� ��, ��� ���������� */
		if(buffer[0] != '*') GotoToAlphabet(input); /* ��������� �� ��������� ������� */
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
/* ��������� ������ � ���� ������� � ���������� ������� */
typedef struct
{
	enum commands * A;	/* ��������� �� ������ ������ */
	size_t c;			/* ���������� ������ � ������� */
} commands_count;

typedef struct
{
	char * A; /* Array */
	size_t c; /* count */
} char_count;

/* ������� ����������� ����� � ����� ������. ������������ malloc � realloc � ������ ��������.
char_count fData - ������, ������� ���� ������������� � enum commands
commands_count * out - �����, ���� ������ ���� �������� ������. ������������ Malloc ��� out->A
����������: ��� ������.
������:
-1 - malloc(0) ������ NULL.
-2 - realloc ������ NULL
�������� ��������:
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
		out->c++; /* ��������� ���������� ������ ������� */
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

/* ������������� �������� ������� �������� A ������ ����, ��� ���������� � protorype.
A[0] = A[1] = ... = A[count] = *prototype;
A - ������, �������� �������� ��� ���� ���������� � *prototype
prototype - ��������� �� ���� ������ (������� size), ���������� ���������, � ���� ������ ������������ ��� ������ ������� A
size - sizeof(��� ��������� ������� A � prototype) (��� *A � ��� *prototype ������ ���� ����������)
count - ���������� ��������� � ������� A */
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
/* ������������ malloc. ��������� ��� ������ � �����
fname - ��� �����, ������� ����� ������� � ���������
str - ��������� �� ������, ���� ���� ���������� ��, ��� ���� ��������� � �����
str_size - ���� ���������� ������ �����. ������������, ����� ������� ���������� �������� -4, 0, 1, 2, 3
������������ ��������: ��� ������.
������:
-1 �� ������� ������� ���������� ��� ������
-2 �� ������� ������� ���� ��� ��������� ������
-3 �� ������� �������� ���������� �����, � ��� �������
-4 �� ������� �������� ����������� ������ ��� ��������� ����������� ����� � ����������� ������
��������������:
2 �� ������ �� ��������� ���������� ����������� ����������, �� � ������ ���������� ������ �������� 0.
1 ����������� ���������� ��������� �� ��������� � �������� �����.
3 ���� ������� �������� 0 ���� � ����������� ������.
�������� ��������:
0 ������� ������� ��������� ���������� ����� fname � ������ ������, �� ������� ������ ��������� *str, � ������ ����������� ������� � *str_size.*/
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
		*str_size = ftell(file) + 1; /* �� ���������� ����� + ������� ��������� ������ */
		fseek(file, 0L, SEEK_SET);
		buffer = (char*)malloc(*str_size);
		if (buffer == NULL)
		{
			fclose(file);
			return -4; /* �� ������� ������, �� ���������� ������ ������� ��������. */
		}
		buffer[0] = '\0';
		ArraySetRage(buffer, buffer, sizeof(char), *str_size); /* ����������� ������� (�������� ������ �������� ������� � ���� ��������� ���������) */
		if (fread(buffer, sizeof(char), *str_size / sizeof(char), file) + 1 != sizeof(char)**str_size)
		{
			fclose(file);
			*str = buffer;
			if (*str_size == 0) return 2; /* �� ������ �� ���������, �� � ������ ���������� ������ �������� 0. */
			else return 1; /* warning: ����������� ���������� ��������� �� ��������� � �������� �����. */
		}
		fclose(file);
		*str = buffer;
		if (*str_size == 0) return 3; /* ���� ������� �������� 0 ���� � ����������� ������. */
		else return 0;
	}
	else
	{
		return -2; /* �� ������� ������� ���� ��� ��������� ������ */
	}
}

/* field - ���� �� �������� ������. ��������� ��� being � end
com - ��������� �� ������� �� field, ������� ������� ����������
update - �����, �� ������� �������� ��� ������
������������ ��������:
-1 �������� com ��� �������� ������� field.A .. field.A + field.c - 1
0 �� ��������� ���������
1 �� �������, ��� ������ � ������ ��������
2 ������ ������ �� stdin.
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
			/* ������� � end + 1 */
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
			/* ������� ������� �� ����������� begin + 1. */
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
	char * ToClear = NULL; /* ��, ��� ����� �������� � ��� ����������, ����� �������. ������������� ��� ������ �����*/
	errno_t er = 0; /* ������ ������ */
	commands_count fCommands = {NULL, 0};
	struct Lenta lt = {NULL, NULL, NULL};
	enum commands * iCom = NULL; /* ��������� (������) �� ������� ������� */
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
	/* ��������� ������ �� ����� */
	
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
	} while(er < 0); /* ��������� ��� ������ � ����� */
	if(er > 0) printf("filesize = 0 or read error\nWarning code: %d\n", (int)er);

	er = 0;
	/* �������������� ������ ����� � �������� */
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
	
	/* ����������� ����� */
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
	//������ (���������) ������ �� ����� � ����������� �����
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
