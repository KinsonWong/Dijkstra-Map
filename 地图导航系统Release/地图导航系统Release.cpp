// 地图导航系统Release.cpp : 定义控制台应用程序的入口点。
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
	ReadInfo();     //从文件中读取信息并创建图
	system("cls"); 
	printf("\n欢迎使用地图导航系统\n");
	while(1)
	{
		printf("\n");
		printf("1. 城市信息查询     \n");
		printf("2. 最短路径查询     \n");
		printf("3. 增删城市和路线   \n");
		printf("0. 退出系统         \n");
		printf("\n提示:选项3需要管理员权限.\n\n"); 
		printf("\n请选择您需要的操作: ");
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
				 printf("\n输入信息错误,请重新输入!\n");
				 break;
		}
    }
	
	return 0;
}

