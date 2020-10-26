//Дан текст. Слова в тексте разделены пробелами и знаками препинания. Получить n наиболее часто встречающихся слов и число их появлений.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
int colvo_slov(char** text, int str)//функция для подсчёта кол-ва слов
{
	int i, j, n = 0, flag = 0;
	for (i = 0; i < str; i++)
	{
		for (j = 0; text[i][j] != '\0'; j++)
		{
			if (text[i][j] != ' ' && text[i][j] != ',' && text[i][j] != '.' && text[i][j] != '?' && text[i][j] != '"' && text[i][j] != '!' && text[i][j] != '-' && text[i][j] != '\n' && flag == 0)//начало слова
			{
				n += 1;//счётчик слов
				flag = 1;//флаг для определения находимся ли мы внутри слова
			}
			else if ((text[i][j] == ' ' || text[i][j] == ',' || text[i][j] == '.' || text[i][j] == '?' || text[i][j] == '"' || text[i][j] == '!' || text[i][j] == '-' || text[i][j] == '\n') && flag == 1)//находим конец слова
			{
				flag = 0;
			}
		}
	}
	return n;
}
int colvo_raz(char** text, char* buf, int str) //функция для подсчёта сколько раз слово встречается в тексте
{
	int i, n = 0;
	size_t l = strlen(buf);
	for(i = 0; i < str; i++)
	{
	    char* s = text[i];
		char* t = s;
        while ((s = strstr(s, buf)) != NULL) 
		{
			if ((s == t || (s[-1] == ' ' || s[-1] == ',' || s[-1] == '.' || s[-1] == '?' || s[-1] == '"' || s[-1] == '!' || s[-1] == '-' || s[-1] == '\n')) && (s[l] == ' ' || s[l] == ',' || s[l] == '.' || s[l] == '?' || s[l] == '"' || s[l] == '!' || s[l] == '-' || s[l] == '\n'))
				++n;
			s += l;
		}
	}
	return n;
}
int proverka(char** text1, char **text, char* buf, int *a, int n1, int str)//проверяем очередное слово
{
	int l = strlen(buf);
	int flag = 0;
	if (n1 == 1)//записываем первое слово и проверяем сколько раз оно встречается в тексте
	{
		strcpy_s(text1[n1 - 1], 15, buf);
		a[n1 - 1] = colvo_raz(text, buf, str);
	}
	else//сравниваем очередное слово с предыдущими найденными
	{
		for (int i = 0; i < n1; i++)
		{
			if (strcmp(text1[i], buf) == 0)//если слово повторяется тогда уменьшаем количество уникальных слов в тексте на -1 устанавливаем флаг
			{
				flag++;
				n1--;
			}
		}
		if (flag == 0)//если повторений не было найдено то записываем слово и проверяем сколько раз оно встречается в тексте
		{
			strcpy_s(text1[n1 - 1], 15, buf);
			a[n1-1]= colvo_raz(text, buf, str);
		}
	}
	return n1;
}
void sort(char** text1, int* a, int str, int n1)//функция для сортирови массива слов и кол-ва раз которые они встречаются в тексте
{
	for (int i = 0; i < n1/2; i++)
	{
		for (int k = 0; k < n1 - i - 1; k++)
		{
			if (a[k] < a[k + 1])
			{
				a[n1+1] = a[k];
				strcpy_s(text1[n1+1], 15, text1[k]);
				a[k] = a[k + 1];
			    strcpy_s(text1[k], 15, text1[k + 1]);
				a[k + 1] = a[n1+1];
				strcpy_s(text1[k + 1], 15, text1[n1+1]);
			}
		}
	}
}
int main()
{
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	char** text,**text1, *buf;
	int i, j, k, flag=0, ns=0, n, n1=0, n2, str, simv, *a;
	printf("Введите количество строк в тексте\n");
	scanf_s("%d", &str);
	text = (char**)calloc(str,sizeof(char*));//выделяем память для массива строк
	if (NULL == text)
	{
		printf("Не удалось выделить память\n");
		exit(1);
	}
	printf("Введите количество символов в строке\n");
	scanf_s("%d", &simv);
	getchar();
	for (i = 0; i < str; i++)
	{
		text[i] = (char*)calloc(simv,sizeof(char));//выделяем память для каждой строки отдельно
		if (NULL == text[i])
		{
			printf("Не удалось выделить память\n");
			exit(1);
		}
	}
	printf("Введите текст из %d строк не более %d символов\n", str, simv);
	for (i = 0; i < str; i++)//заполняем массив строк
	{
		fgets(text[i],simv,stdin);
	}
	printf("\n");
	n = colvo_slov(text, str);//подсчитываем сколько слов в тексте
	printf("Количество слов в тексте %d", n);
	text1 = (char**)calloc(n, sizeof(char*));//выделяем память для массива слов
	a = (int*)calloc(n, sizeof(int));//выделяем память для количества повторений слова в тексте;
	for (i = 0; i < n; i++)
	{
		text1[i] = (char*)calloc(15, sizeof(char));//выделяем память для каждого слова(по 15 символов)
		if (NULL == text1[i])
		{
			printf("Не удалось выделить память\n");
			exit(1);
		}
	}
	if (NULL == text1)
	{
		printf("Не удалось выделить память\n");
		exit(1);
	}
	for (i = 0; i < str; i++)//находим слова
	{
		for (j=0; text[i][j] != '\0'; j++)
		{
			if (text[i][j] != ' ' && text[i][j] != ',' && text[i][j] != '.' && text[i][j] != '?' && text[i][j] != '"' && text[i][j] != '!' && text[i][j] != '-' && text[i][j] != '\n' && flag == 0)//находим начало слова
			{
				n1 += 1;//счётчик уникальных слов в тексте
				ns = j;//запоминаем начало слова
				flag = 1;
			}
			else if ((text[i][j] == ' ' || text[i][j] == ',' || text[i][j] == '.' || text[i][j] == '?' || text[i][j] == '"' || text[i][j] == '!' || text[i][j] == '-' || text[i][j] == '\n' )&& flag == 1)//находим конец слова
			{
				flag = 0;
				buf = (char*)calloc(15, sizeof(char));//выделяем память под слово
				if(NULL==buf)
				{
					printf("Не удалось выделить память\n");
					exit(1);
				}
				for (k = 0; k < j - ns; k++)//записываем посимвольно слово в буфер
				{
					buf[k]=text[i][ns+k];
				}
				buf[k] = '\0';
				n1 = proverka(text1, text, buf, a, n1, str);
				free(buf);//освобождаем буфер
			}
		}
	}
	printf("\n");
	sort(text1, a, str, n1); //сортируем полученные массивы слов и кол - ва раз которые они встречаются в тексте
	printf("Введите количество слов с максимальным появлением которое вы хотите вывести: ");
	scanf_s("%d", &n2);
	for (i = 0; i < n2; i++)
	{
		printf("%s %d\n", text1[i], a[i]);
	}
	for (i = 0; i < n; i++)//освобождаем выделенную динамически память
	{
		free(text1[i]);
	}
	for (i = 0; i < str; i++)
	{
		free(text[i]);
	}
	free(a);
	free(text1);
	free(text);
	return 0;
}