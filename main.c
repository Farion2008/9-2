//��� �����. ����� � ������ ��������� ��������� � ������� ����������. �������� n �������� ����� ������������� ���� � ����� �� ���������.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
int colvo_slov(char** text, int str)//������� ��� �������� ���-�� ����
{
	int i, j, n = 0, flag = 0;
	for (i = 0; i < str; i++)
	{
		for (j = 0; text[i][j] != '\0'; j++)
		{
			if (text[i][j] != ' ' && text[i][j] != ',' && text[i][j] != '.' && text[i][j] != '?' && text[i][j] != '"' && text[i][j] != '!' && text[i][j] != '-' && text[i][j] != '\n' && flag == 0)//������ �����
			{
				n += 1;//������� ����
				flag = 1;//���� ��� ����������� ��������� �� �� ������ �����
			}
			else if ((text[i][j] == ' ' || text[i][j] == ',' || text[i][j] == '.' || text[i][j] == '?' || text[i][j] == '"' || text[i][j] == '!' || text[i][j] == '-' || text[i][j] == '\n') && flag == 1)//������� ����� �����
			{
				flag = 0;
			}
		}
	}
	return n;
}
int colvo_raz(char** text, char* buf, int str) //������� ��� �������� ������� ��� ����� ����������� � ������
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
int proverka(char** text1, char **text, char* buf, int *a, int n1, int str)//��������� ��������� �����
{
	int l = strlen(buf);
	int flag = 0;
	if (n1 == 1)//���������� ������ ����� � ��������� ������� ��� ��� ����������� � ������
	{
		strcpy_s(text1[n1 - 1], 15, buf);
		a[n1 - 1] = colvo_raz(text, buf, str);
	}
	else//���������� ��������� ����� � ����������� ����������
	{
		for (int i = 0; i < n1; i++)
		{
			if (strcmp(text1[i], buf) == 0)//���� ����� ����������� ����� ��������� ���������� ���������� ���� � ������ �� -1 ������������� ����
			{
				flag++;
				n1--;
			}
		}
		if (flag == 0)//���� ���������� �� ���� ������� �� ���������� ����� � ��������� ������� ��� ��� ����������� � ������
		{
			strcpy_s(text1[n1 - 1], 15, buf);
			a[n1-1]= colvo_raz(text, buf, str);
		}
	}
	return n1;
}
void sort(char** text1, int* a, int str, int n1)//������� ��� ��������� ������� ���� � ���-�� ��� ������� ��� ����������� � ������
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
	SetConsoleCP(1251);// ��������� ������� �������� win-cp 1251 � ����� �����
	SetConsoleOutputCP(1251); // ��������� ������� �������� win-cp 1251 � ����� ������
	char** text,**text1, *buf;
	int i, j, k, flag=0, ns=0, n, n1=0, n2, str, simv, *a;
	printf("������� ���������� ����� � ������\n");
	scanf_s("%d", &str);
	text = (char**)calloc(str,sizeof(char*));//�������� ������ ��� ������� �����
	if (NULL == text)
	{
		printf("�� ������� �������� ������\n");
		exit(1);
	}
	printf("������� ���������� �������� � ������\n");
	scanf_s("%d", &simv);
	getchar();
	for (i = 0; i < str; i++)
	{
		text[i] = (char*)calloc(simv,sizeof(char));//�������� ������ ��� ������ ������ ��������
		if (NULL == text[i])
		{
			printf("�� ������� �������� ������\n");
			exit(1);
		}
	}
	printf("������� ����� �� %d ����� �� ����� %d ��������\n", str, simv);
	for (i = 0; i < str; i++)//��������� ������ �����
	{
		fgets(text[i],simv,stdin);
	}
	printf("\n");
	n = colvo_slov(text, str);//������������ ������� ���� � ������
	printf("���������� ���� � ������ %d", n);
	text1 = (char**)calloc(n, sizeof(char*));//�������� ������ ��� ������� ����
	a = (int*)calloc(n, sizeof(int));//�������� ������ ��� ���������� ���������� ����� � ������;
	for (i = 0; i < n; i++)
	{
		text1[i] = (char*)calloc(15, sizeof(char));//�������� ������ ��� ������� �����(�� 15 ��������)
		if (NULL == text1[i])
		{
			printf("�� ������� �������� ������\n");
			exit(1);
		}
	}
	if (NULL == text1)
	{
		printf("�� ������� �������� ������\n");
		exit(1);
	}
	for (i = 0; i < str; i++)//������� �����
	{
		for (j=0; text[i][j] != '\0'; j++)
		{
			if (text[i][j] != ' ' && text[i][j] != ',' && text[i][j] != '.' && text[i][j] != '?' && text[i][j] != '"' && text[i][j] != '!' && text[i][j] != '-' && text[i][j] != '\n' && flag == 0)//������� ������ �����
			{
				n1 += 1;//������� ���������� ���� � ������
				ns = j;//���������� ������ �����
				flag = 1;
			}
			else if ((text[i][j] == ' ' || text[i][j] == ',' || text[i][j] == '.' || text[i][j] == '?' || text[i][j] == '"' || text[i][j] == '!' || text[i][j] == '-' || text[i][j] == '\n' )&& flag == 1)//������� ����� �����
			{
				flag = 0;
				buf = (char*)calloc(15, sizeof(char));//�������� ������ ��� �����
				if(NULL==buf)
				{
					printf("�� ������� �������� ������\n");
					exit(1);
				}
				for (k = 0; k < j - ns; k++)//���������� ����������� ����� � �����
				{
					buf[k]=text[i][ns+k];
				}
				buf[k] = '\0';
				n1 = proverka(text1, text, buf, a, n1, str);
				free(buf);//����������� �����
			}
		}
	}
	printf("\n");
	sort(text1, a, str, n1); //��������� ���������� ������� ���� � ��� - �� ��� ������� ��� ����������� � ������
	printf("������� ���������� ���� � ������������ ���������� ������� �� ������ �������: ");
	scanf_s("%d", &n2);
	for (i = 0; i < n2; i++)
	{
		printf("%s %d\n", text1[i], a[i]);
	}
	for (i = 0; i < n; i++)//����������� ���������� ����������� ������
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