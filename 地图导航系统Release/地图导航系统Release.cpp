// ��ͼ����ϵͳRelease.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <conio.h>

#define INFINITY 99999
#define NUM 50 
#define FALSE 0
#define TURE 1

#include "header.h"

int main()
{
	int x;
	ReadInfo();     //���ļ��ж�ȡ��Ϣ������ͼ
	system("cls"); 
	printf("\n��ӭʹ�õ�ͼ����ϵͳ\n");
	while(1)
	{
		printf("\n");
		printf("1. ������Ϣ��ѯ     \n");
		printf("2. ���·����ѯ     \n");
		printf("3. ��ɾ���к�·��   \n");
		printf("0. �˳�ϵͳ         \n");
		printf("\n��ʾ:ѡ��3��Ҫ����ԱȨ��.\n\n"); 
		printf("\n��ѡ������Ҫ�Ĳ���: ");
		scanf("%d", &x);
		switch(x)
		{
		case 1: system("cls");
				SearchPlace();
				break;
		case 2: system("cls");
				SearchPath();
				break;
		case 3: system("cls");
				password();
				break;
		case 0: printf("\n");
				exit(0);
		default: system("cls");
				 printf("\n������Ϣ����,����������!\n");
				 break;
		}
    }
	
	return 0;
}

