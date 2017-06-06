/* Разработал: Сидоренко Михаил (Sidorenko Mikhail), 15.03.2017 */


#ifndef _MUWA_EXPANDABLE_LENTA
#define _MUWA_EXPANDABLE_LENTA

/* Включите этот параметр, если код не должен содержать XML документацию и комментарии //. */
//#define C89

/* Secure Development Lifecycle */
#ifndef SDL
#ifdef C89
#define SDL 0
#endif /* C89 */

/* Поставьте SDL 0, если Ваш компилятор не поддерживает данную технологию. */
#define SDL 1

#endif // !SDL

#ifndef _INC_STRING
#include <string.h>
#endif // _INC_STRING

#ifndef _INC_STDLIB
#include <stdlib.h>
#endif // _INC_STDLIB

#ifndef C89
/// <summary>
/// Структура, которая представляет собой указатель на начальный байт, конечный доступный и на текущий.
/// </summary>
struct Lenta
#else
struct Lenta
#endif
{
	unsigned char * elements;	/* Начальный байт массива.				*/
	unsigned char * position;	/* Текущий байт массива.				*/
	unsigned char * top;		/* Последний доступный байт массива.	*/
};

char * ExpandableLenta_GetText(struct Lenta input, char empty)
{
	char * output = (char*)malloc(sizeof(char)*(input.top - input.elements + 1 + 1));
	int i = 0;
	for (; i < input.top - input.elements + 1; i++)
	{
		if (input.elements[i] != '\0')
		{
			output[i] = input.elements[i];
		}
		else
		{
			output[i] = empty; /* Знак лямбды */
		}
	}
	output[input.top - input.elements + 1] = 0;
	return output;
}

/* Функция создаёт начальную ленту из 5 ячеек. Текущим выбирается третий из них. */
struct Lenta ExpandableLenta_Create(void)
{
	int i = 0;
	struct Lenta output = { (unsigned char *)malloc(sizeof(unsigned char) * 5), NULL, NULL };
	if (output.elements == NULL) return output;
	for (; i < 5; i++)
	{
		output.elements[i] = 0;
	}
	output.position = output.elements + 2;
	output.top = output.elements + 4;
	return output;
}

/* Функция создаёт ленту с указаным словом
 text: Слово, которое должно быть помещено	*/
struct Lenta ExpandableLenta_CreateText(char * text)
{
	size_t count = strlen(text);
	size_t i = 0;
	struct Lenta output = { (unsigned char *)malloc(sizeof(unsigned char) * (5 + count)), NULL, NULL };
	output.position = output.elements + 2;
	output.top = output.elements + 4 + count;

	output.elements[5 + count - 1] = 0;
	output.elements[5 + count - 2] = 0;
	output.elements[5 + count - 3] = 0;
	output.elements[0] = 0;
	output.elements[1] = 0;

	for (i = 2; i < 2 + count; i++)
	{
		output.elements[i] = text[i - 2];
	}
	return output;
}

#ifndef C89
/// <summary>
/// Проверка линии в машине Тьюринга, хватает ли места. Если не хватает, то идёт выделение новой памяти для ленты в машине Тьюринга. При неудаче возвращается отрицательный код ошибки.
/// </summary>
/// <param name="input">Состояние ленты Тьюринга</param>
/// <return>Возвращает код, симвализирующий отчёт работы.
/// 0	Выделение памяти не потребовалось
/// 1	Память успешно выделена в сторону начала памяти
/// 2	Память успешно выделена в сторону убывания памяти
/// 3	Память успешно выделена в обе стороны
/// -1	Локальная ошибка определения требований к выделению памяти. Состояние машины Тьюринга не изменено
/// -2	Ошибка при выделении памяти в количестве sizeof(unsigned char)*(input->top - input->elements + 1 + 2) байт.  Состояние машины Тьюринга не изменено
/// -3	Ошибка при выделении памяти в обе стороны в количестве sizeof(unsigned char)*(input->top - input->elements + 1 + 4) байт.  Состояние машины Тьюринга не изменено.
/// -4	memcpy_s: Определено, что не хватает памяти в сторону убывания памяти, но возникла ошибка при копировании данных из старого сегмента памяти в новый. При этой ошибке новая память помечается свободной автоматически, изменения не принимаются в силу. Компиляция программы с технологией SDL.
/// -5	memcpy: Определено, что не хватает памяти в сторону убывания памяти, но возникла ошибка при копировании данных из старого сегмента памяти в новый. При этой ошибке новая память помечается свободной автоматически, изменения не принимаются в силу.
/// -6	memcpy_s: Определено, что не хватает памяти в сторону возрастания памяти, но возникла ошибка при копировании данных из старого сегмента памяти в новый. При этой ошибке новая память помечается свободной автоматически, изменения не принимаются в силу. Компиляция программы с технологией SDL.
/// -7	memcpy: Определено, что не хватает памяти в сторону возрастания памяти, но возникла ошибка при копировании данных из старого сегмента памяти в новый. При этой ошибке новая память помечается свободной автоматически, изменения не принимаются в силу.
/// -8	memcpy_s: Определено, что не хватает памяти в обе стороны, но возникла ошибка при копировании данных из старого сегмента памяти в новый. При этой ошибке новая память помечается свободной автоматически, изменения не принимаются в силу. Компиляция программы с технологией SDL.
/// -9	memcpy: Определено, что не хватает памяти в обе стороны, но возникла ошибка при копировании данных из старого сегмента памяти в новый. При этой ошибке новая память помечается свободной автоматически, изменения не принимаются в силу.
/// </return>
int ExpandableLenta_MemoryAdjustment(struct Lenta * input);
#else
/* Проверка линии в машине Тьюринга, хватает ли места. Если не хватает, то идёт выделение новой памяти для ленты в машине Тьюринга. При неудаче возвращается отрицательный код ошибки. */
int ExpandableLenta_MemoryAdjustment(struct Lenta * input);
#endif
int ExpandableLenta_MemoryAdjustment(struct Lenta * input)
{
	int flag = 0;
	unsigned char * buffer;
	if (input->position + 2 >= input->top)
	{
		flag += 1;
	}
	flag <<= 1;
	if (input->position - 2 <= input->elements)
	{
		flag += 1;
	}
	switch (flag)
	{
		case 0: /* Везде всё хватает */
		{
			return 0;
		}
		case 1: /* Снизу не хватает */
		{
			buffer = (unsigned char*)malloc(sizeof(unsigned char)*(input->top - input->elements + 1 + 2));
			if (buffer == NULL)
			{
				return -2;
			}
#if SDL == 1
			if (memcpy_s(buffer + 2, input->top - input->elements, input->elements, input->top - input->elements) != 0)
			{
				free(buffer);
				return -4;
			}
#else
			if (memcpy(buffer + 2, input->elements, input->top - input->elements) == NULL)
			{
				free(buffer);
				return -5;
			}
#endif
			free(input->elements);													/* Помечаем, что старый информация из старого массива данных не нужна	*/
			input->position = input->position - input->elements + buffer + 2;		/* Устанавливаем новую позицию											*/
			input->top = buffer + (input->top - input->elements) + 2;				/* Устанавливаем указатель на последний доступный элемент				*/
			input->elements = buffer;												/* Указываем, где наш новый участок памяти								*/
																					/* Очищаем новые секторы:												*/
			ExpandableLenta_GetText(*input, 'L');
			buffer[0] = 0;
			buffer[1] = 0;
			input->top[0] = 0;
			ExpandableLenta_GetText(*input, 'L');
			return 1;
		}
		case 2: /* Сверху не хватает */
		{
			buffer = (unsigned char*)malloc(sizeof(unsigned char)*(input->top - input->elements + 1 + 2));
			if (buffer == NULL)
			{
				return -2;
			}
#if SDL == 1
			if (memcpy_s(buffer, input->top - input->elements + 2, input->elements, input->top - input->elements) != 0)
			{
				free(buffer);
				return -6;
			}
#else
			if (memcpy(buffer, input->elements, input->top - input->elements) == NULL)
			{
				free(buffer);
				return -7;
			}
#endif
			free(input->elements);													/* Помечаем, что старый информация из старого массива данных не нужна	*/
			input->position = input->position - input->elements + buffer;			/* Устанавливаем новую позицию											*/
			input->top = buffer + (input->top - input->elements) + 2;				/* Устанавливаем указатель на последний доступный элемент				*/
			input->elements = buffer;												/* Указываем, где наш новый участок памяти								*/
																					/* Очищаем новые секторы:												*/

			input->top[0] = 0;
			input->top[-1] = 0;
			input->top[-2] = 0;
			return 2;
		}
		case 3: /* Не хватает с двух сторон */
		{
			buffer = (unsigned char*)malloc(sizeof(unsigned char)*(input->top - input->elements + 1 + 4));
			if (buffer == NULL)
			{
				return -3;
			}
#if SDL == 1
			if (memcpy_s(buffer + 2, input->top - input->elements + 2, input->elements, input->top - input->elements) != 0)
			{
				free(buffer);
				return -8;
			}
#else
			if (memcpy(buffer + 2, input->elements, input->top - input->elements) == NULL)
			{
				free(buffer);
				return -9;
			}
#endif
			free(input->elements);													/* Помечаем, что старый информация из старого массива данных не нужна	*/
			input->position = input->position - input->elements + buffer + 2;		/* Устанавливаем новую позицию											*/
			input->top = buffer + (input->top - input->elements) + 4;				/* Устанавливаем указатель на последний доступный элемент				*/
			input->elements = buffer;												/* Указываем, где наш новый участок памяти								*/
																					/* Очищаем новые секторы:												*/
			buffer[0] = 0;
			buffer[1] = 0;
			input->top[0] = 0;
			input->top[-1] = 0;
			input->top[-2] = 0;
			return 3;
		}
		default: /* взлом системы? */
			return -1;
	}
}

#endif /* _MUWA_EXPANDABLE_LENTA */