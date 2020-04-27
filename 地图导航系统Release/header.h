
void OutputMenu();     //根据文件内城市信息输出
void ReadInfo();     //从文件中读取信息并创建图
void SearchPlace();     //查询城市信息
void SearchPath();     //查询最短路径  
void ShortPath(int i);     //Dijkstra算法最短路径
void OutputShortpath(int sight1, int sight2);//输出函数
void AddPlace();     //增加城市并添加与此城市有关的路线 
void DeletePlace();     //删除城市 
void AddPath();     //增加新路线
void DeletePath();     //撤销旧路线
void ManageSystem();     //管理界面
void password();             //管理员登陆
void ChangePassword();     //管理员修改登陆密码

typedef struct ArcNode
{
	int length;     //路径长度,即路径的权值
}ArcNode, *ArcLink;     //边结点的定义

typedef struct VertexNode
{
	int number;     //城市的编号
	char name[100];     //城市的名称
	char info[1000];     //城市的简介
}VertexNode;     //顶点结点的定义

typedef struct Graph
{
	VertexNode vertex[NUM];
	ArcNode arc[NUM][NUM];
	int vexnum;     //图的顶点数
	int arcnum;     //图的边数  
}Graph;                 //图的定义 

Graph G;
int path1[NUM][NUM];
int Dist[NUM];     //存储最短路径的权值
FILE *fp = NULL;

void OutputMenu()     //输出文件中所有景点以便用户直观浏览 
{
	int i;
	ReadInfo();	
	printf("                 城市列表       \n");
	printf("===========================================\n");
	for(i = 1; i <= G.vexnum; i++)
	{	
		printf("   %2d. %s  \n", G.vertex[i].number, G.vertex[i].name);
	}
	printf("===========================================\n");
}

void ReadInfo()     //将存有城市信息的文件读取进程序
{
	int i, j,num;
	for(i = 0; i < NUM; ++i)     //初始化邻接矩阵
		for(j = 0; j < NUM; ++j)
			G.arc[i][j].length = INFINITY;
	fp = fopen("information.txt","r");
	if(fp == NULL)
		printf("\n打开文件 information.txt失败.\n");
	else
	{
		fscanf(fp, "%d\n", &G.vexnum);
		for(j = 0; j < G.vexnum; j++)
		{	fscanf(fp, "%d ", &num);
			i = num;
			G.vertex[i].number = i;
			fscanf(fp, "%s ", G.vertex[i].name); 
			fscanf(fp, "%s\n", G.vertex[i].info);
		}
	}
	fclose(fp);
	fp = fopen("road.txt","r");
	if(fp == NULL)
		printf("\n打开文件 road.txt失败.\n");
	else
	{
		for(i = 1; i <= G.vexnum; i++)
			for(j = 1; j <= G.vexnum; j++)
				fscanf(fp, "%d", &G.arc[i][j].length);
	}
	fclose(fp);
}

void SearchPlace()//查询城市信息  
{
	int i,num;
	char c = 'y';
	while(c == 'y')
	{
		system("cls");
		OutputMenu();
		printf("\n\n请输入您要查找的城市编号：");
		scanf("%d", &num);
		getchar();
		system("cls");
		if(num > 0 && num <= G.vexnum)   //判定信息输入正确 
		{
			for(i = 1; i <= G.vexnum; i++)
				if(num == G.vertex[i].number)
				{
					printf("\n城市编号: %d\n", i);
					printf("\n城市名称: %s\n", G.vertex[i].name);
					printf("\n城市简介: %s\n", G.vertex[i].info);
				}
		}
		else
			printf("\n信息输入有误!\n");
		num = 0;
		printf("\n是否继续查询景点信息(y/n): ");
		c = getchar();
		getchar();
	}
	system("cls");  
}

void SearchPath()     //查询最短路径
{
	int i, j;
	char c = 'y';
	while(c == 'y')
	{
		system("cls");
		OutputMenu();
		printf("\n请选择第一个城市: ");
		scanf("%d", &i);
		printf("\n请选择第二个城市: ");
		scanf("%d", &j);
		getchar();
		if(i > G.vexnum || i <= 0 || j > G.vexnum || j < 0 || i == j)
			printf("\n输入信息错误!\n\n");
		else
		{
			ShortPath(i);     //用Dijkstra算法求出最短路径
			system("cls");
			OutputShortpath(i, j);     //将最短路径上的城市依次输出
		}
		printf("\n是否继续查询最短路径(y/n): ");
		c = getchar();
		getchar();
	}
	system("cls");
}

void ShortPath(int num)    //Dijkstra算法最短路径
{
	int i,j,u,t;
	int n=G.vexnum+1;
	int *final = (int *)malloc(sizeof(int)*(n+1));
	int min;     //记录权值、最终输出路径
	for(i = 0; i < n; i++)   //初始化
	{
		final[i] = 0;     //假设从顶点num到顶点i没有最短路径
		Dist[i] = G.arc[num][i].length;     //将顶点num到其余顶点的最短路径长度初始化为权值
		for(j = 0; j < n; j++)
			path1[i][j] = 0;     //初始化从i到j的路径值
		if(Dist[i] <90000)     //存在路径
		{
			path1[i][num] = 1;
			path1[i][i] = 1;
		}
	}
	Dist[num] = 0;
	final[num]=1;      //标记num已加入final中

	//开始主循环,每一次求得num到某个顶点的最短路径，并将其加入到final集合
	for(i = 1; i <n; i++)     // 其余G.vexnum-1个顶点
	{
		min = INFINITY;
		for(j = 0; j <= n; j++)
			if(!final[j] && Dist[j]<min )     
		{
				u = j;
				min = Dist[j];
		}
			if(min == INFINITY) return; 
			final[u] = 1;     //离num顶点更近的u加入到final集合
		
		for(j = 0; j < n; j++)     //更新当前最短路径极其距离
			if(!final[j] && Dist[u] + G.arc[u][j].length < Dist[j] && G.arc[u][j].length<INFINITY)
			{
				Dist[j] = Dist[u]+G.arc[u][j].length;     //更新路径
				for(t = 0; t < n; t++)
					path1[j][t] = path1[u][t];
				path1[j][j] = 1;
			}
	}
}

void OutputShortpath(int city1,int city2)    // 输出函数
{
	int a, b, c, d, q = 0;
	a = city2;
	if(a != city1)
	{
		printf("\n从 %s 到 %s 的最短路径是:\n\n", G.vertex[city1].name, G.vertex[city2].name);//输出提示信息
		//输出城市1到城市2的最短路径长度，存放在Dist[]数组中
		printf("%s", G.vertex[city1].name);  //输出城市一的名称
		d = city1;      //将城市一的编号赋值给d
		for(c = 0; c < NUM; ++c)
		{
			gate:;        //标号，goto语句跳转的位置
			path1[a][city1] = 0;
			for(b = 0; b < NUM; b++)
			{
				if(G.arc[d][b].length < INFINITY && path1[a][b]) //如果城市一和它的一个临界点之间存在路径且最短路径
				{
					printf("-->%s", G.vertex[b].name);  //输出此节点的名称
					q = q + 1;    //计数变量加一，满8控制输出时的换行
					path1[a][b] = 0;
					d = b;     //将b作为出发点进行下一次循环输出 
					if(q % 14 == 0)
						printf("\n");
					goto gate;
				}
			}
	 	}
		printf("\n\n全程 %d KM \n\n", Dist[a]);
	}
}

void AddPlace()     //增加新的城市,在文件中对之前的文件进行全面覆盖
{
	int x, i, j, length;
	int city;
	char c = 'y', ch = 'y';
	while(c == 'y')
	{
		OutputMenu();
		printf("\n请输入新增城市的编号: ");
		scanf("%d", &x);
		G.vertex[G.vexnum+1].number = x;
		printf("\n请输入新增城市的名称: ");
		scanf("%s", G.vertex[x].name);
		printf("\n请输入新增城市的简介: ");
		scanf("%s", G.vertex[x].info);
		G.vexnum++;
		fp = fopen("information.txt", "wt");
		if(fp == NULL)
			printf("\n打开文件 information.txt失败.\n");
		else
		{
			fprintf(fp, "%d\n", G.vexnum);
			for(i = 1; i <= G.vexnum; i++)
			{
				fprintf(fp, "%d %s %s\n", G.vertex[i].number, G.vertex[i].name, G.vertex[i].info);
			}
			fclose(fp);
			while(ch == 'y')
			{
				printf("\n请输入与新城市相连的城市的编号: ");
				scanf("%d", &city);
				printf("\n请输入路径的长度: ");
				scanf("%d", &length);
				G.arc[x][city].length = G.arc[city][x].length = length;
				fp = fopen("road.txt", "wt");
				for(i = 1; i <= G.vexnum; i++)
				{
					for(j = 1; j < G.vexnum; j++)
					{
						fprintf(fp, "%d ", G.arc[i][j].length);
					}
					fprintf(fp, "%d", G.arc[i][j].length);
					fprintf(fp, "\n");
				}
				fclose(fp);
				printf("\n是否继续添加路线(y/n): ");
				getchar();
				ch = getchar();
				printf("\n是否继续增加城市(y/n): ");
				getchar();
				c = getchar();
			}
		}
	}
	system("cls");
	ReadInfo();
}

void DeletePlace()     //删除城市,在文件中对之前的文件进行全面覆盖
{
	int x, i, j, k = 0;
	char c = 'y';
	
	while(c == 'y')
	{
		OutputMenu();
		printf("\n请输入删除城市的编号: ");
		scanf("%d", &x);
		for(i = x; i <= G.vexnum; i++)
		{
			strcpy(G.vertex[i].name, G.vertex[i+1].name);
			strcpy(G.vertex[i].info, G.vertex[i+1].info);
			if(G.vertex[i].number == 0)
				break;
		}
		G.vexnum--;
		for(i = 1; i <= G.vexnum; i++)
		{
			for(j = x; j <= G.vexnum; j++)
			{
				G.arc[i][j].length = G.arc[i][j+1].length;
				G.arc[j][i].length = G.arc[j+1][i].length;
			}
		}
		fp = fopen("information.txt", "wt");
		fprintf(fp, "%d\n", G.vexnum);
		for(i = 1; i <= G.vexnum; i++)
		{
			fprintf(fp, "%d %s %s\n", G.vertex[i].number, G.vertex[i].name, G.vertex[i].info);
		}
		fclose(fp);
		fp = fopen("road.txt", "wt");
		for(i = 1; i <= G.vexnum; i++)
		{
			for(j = 1; j < G.vexnum; j++)
			{
				fprintf(fp, "%d ", G.arc[i][j].length);
			}
			fprintf(fp, "%d", G.arc[i][j].length);
				fprintf(fp, "\n");
		}
		fclose(fp);
		printf("\n是否继续删除城市(y/n): ");
		getchar();
		c = getchar();
	}
	system("cls");
	ReadInfo();
}

void AddPath()     //增加新路线
{
	int i, j;
	int num1, num2;
	int start, end, length;
	char c = 'y';
	while(c == 'y')
	{
		OutputMenu();
		printf("\n请输入增加路线的第一个城市编号: ");
		scanf("%d", &num1);
		if(num1 > 0 && num1 <= G.vexnum)   //判定信息输入正确
		{
			for(i = 1; i <= G.vexnum; i++)
				if(num1 == G.vertex[i].number)
					start = num1;     //找到编号与输入相同的城市,将编号赋予start
		}
		printf("\n请输入增加路线的第二个城市编号: ");
		scanf("%d", &num2);
		if(num2 > 0 && num2 <= G.vexnum)   //判定信息输入正确
		{
			for(i = 1; i <= G.vexnum; i++)
				if(num2 == G.vertex[i].number)
					end = num2;     //找到编号与输入相同的城市,将编号赋予end
		}
		if(num1 > G.vexnum || num1 <= 0 || num2 > G.vexnum || num2 < 0 || num1 == num2)
			printf("\n输入信息错误!\n\n");
		else
		{
			printf("\n请输入两个城市之间的距离(KM): ");
			scanf("%d", &length);
			G.arc[start][end].length = G.arc[end][start].length = length;
			fp = fopen("road.txt", "wt");
			for(i = 1; i <= G.vexnum; i++)
			{
				for(j = 1; j < G.vexnum; j++)
				{
					fprintf(fp, "%d ", G.arc[i][j].length);
				}
				fprintf(fp, "%d", G.arc[i][j].length);
				fprintf(fp, "\n");
			}
			fclose(fp);
		}
		printf("\n是否继续增加路线(y/n): ");
		getchar();
		c = getchar();
	}
	system("cls");
	ReadInfo();
}

void DeletePath()     //删除路线
{
	int i, j;
	int num1, num2;
	int start, end;
	char c = 'y';
	while(c == 'y')
	{
		OutputMenu();
		printf("\n请输入删除路线的第一个城市编号: ");
		scanf("%d", &num1);
		if(num1 > 0 && num1 <= G.vexnum)   //判定信息输入正确
		{
			for(i = 1; i <= G.vexnum; i++)
				if(num1 == G.vertex[i].number)
					start = num1;     //找到编号与输入相同的城市,将编号赋予start
		}
		printf("\n请输入删除路线的第二个城市编号: ");
		scanf("%d", &num2);
		if(num2 > 0 && num2 <= G.vexnum)   //判定信息输入正确
		{
			for(i = 1; i <= G.vexnum; i++)
				if(num2 == G.vertex[i].number)
					end = num2;     //找到编号与输入相同的城市,将编号赋予end
		}
		if(num1 > G.vexnum || num1 <= 0 || num2 > G.vexnum || num2 < 0 || num1 == num2)
			printf("\n输入信息错误!\n\n");
		else
		{
			G.arc[start][end].length = G.arc[end][start].length = INFINITY;
			fp = fopen("road.txt", "wt");
			for(i = 1; i <= G.vexnum; i++)
			{
				for(j = 1; j < G.vexnum; j++)
				{
					fprintf(fp, "%d ", G.arc[i][j].length);
				}
				fprintf(fp, "%d", G.arc[i][j].length);
				fprintf(fp, "\n");
			}
			fclose(fp);
		}
		printf("\n是否继续删除路线(y/n): ");
		getchar();
		c = getchar();
	}
	system("cls");
	ReadInfo();
}

void ChangePassword()     //修改登陆密码
{
	int password1, password2, newpass;
	char c = 'y'; 
	fp = fopen("password.txt", "wt");
	if(fp == NULL)
		printf("\n打开文件 password.txt失败.\n");
	else
	{
		while(c == 'y')
		{
			printf("\n请输入新密码: ");
			scanf("%d", &password1);
			printf("\n请再次输入新密码: ");
			scanf("%d", &password2);
			if(password1 == password2)
			{
				newpass = password1;
				fprintf(fp, "%d", newpass);
				printf("\n修改密码成功.\n");
				break;
			}
			else
			{
				printf("\n两次密码输入不相同,修改密码失败.\n");
				printf("\n是否继续修改密码(y/n): ");
	 			getchar();
				c = getchar();
			}
		}
		fclose(fp);
		printf("\n按任意键返回管理菜单\n");
		getchar();
		system("cls"); 
		ManageSystem();
	}
}

void ManageSystem()     //管理界面
{
	int x;
	printf("\n欢迎使用地图导航管理系统\n");
	printf("\n");
	printf("1. 增加城市       \n");
	printf("2. 删除城市      \n");
	printf("3. 增加路线       \n");
	printf("4. 撤销路线       \n");
	printf("5. 修改登陆密码     \n");
	printf("0. 退出管理系统     \n");
	printf("\n请选择您需要的操作: ");
	scanf("%d", &x);
	switch(x)
	{
	case 1: system("cls");
			AddPlace();
			break;
	case 2: system("cls");
			DeletePlace();
			break;
	case 3: system("cls");
			AddPath();
			break;
	case 4: system("cls");
			DeletePath();
			break;
	case 5: ChangePassword();
			system("cls");
			break;
	case 0: printf("\n");
			system("cls");
			break;
	default: system("cls");
			 printf("\n输入信息错误,请重新输入!\n");
			 break;
	}
}

void password()    //管理员身份认证
{
	int t;
	int password, pass;
	fp = fopen("password.txt","r");
	if(fp == NULL)
		printf("\n打开文件 password.txt失败.\n");
	else
	{
		fscanf(fp, "%d", &pass);
		printf("\n请输入密码: ");
		scanf("%d", &password);
		for(t = 1; t < 3; t++)
		{
			if(password == pass)
			{
				system("cls");
				ManageSystem();
				break;
			}
			else
			{
				printf("\n密码错误，请再次输入: ");
				scanf("%d", &password);
			}
		}
	}
	fclose(fp);
	if(password != pass)
	{
		printf("\n对不起,您无法登陆管理系统.\n\n请按任意键返回主界面...\n");
		getchar();
		getchar();
		system("cls");
	}
}