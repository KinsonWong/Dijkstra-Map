
void OutputMenu();     //�����ļ��ڳ�����Ϣ���
void ReadInfo();     //���ļ��ж�ȡ��Ϣ������ͼ
void SearchPlace();     //��ѯ������Ϣ
void SearchPath();     //��ѯ���·��  
void ShortPath(int i);     //Dijkstra�㷨���·��
void OutputShortpath(int sight1, int sight2);//�������
void AddPlace();     //���ӳ��в������˳����йص�·�� 
void DeletePlace();     //ɾ������ 
void AddPath();     //������·��
void DeletePath();     //������·��
void ManageSystem();     //�������
void password();             //����Ա��½
void ChangePassword();     //����Ա�޸ĵ�½����

typedef struct ArcNode
{
	int length;     //·������,��·����Ȩֵ
}ArcNode, *ArcLink;     //�߽��Ķ���

typedef struct VertexNode
{
	int number;     //���еı��
	char name[100];     //���е�����
	char info[1000];     //���еļ��
}VertexNode;     //������Ķ���

typedef struct Graph
{
	VertexNode vertex[NUM];
	ArcNode arc[NUM][NUM];
	int vexnum;     //ͼ�Ķ�����
	int arcnum;     //ͼ�ı���  
}Graph;                 //ͼ�Ķ��� 

Graph G;
int path1[NUM][NUM];
int Dist[NUM];     //�洢���·����Ȩֵ
FILE *fp = NULL;

void OutputMenu()     //����ļ������о����Ա��û�ֱ����� 
{
	int i;
	ReadInfo();	
	printf("                 �����б�       \n");
	printf("===========================================\n");
	for(i = 1; i <= G.vexnum; i++)
	{	
		printf("   %2d. %s  \n", G.vertex[i].number, G.vertex[i].name);
	}
	printf("===========================================\n");
}

void ReadInfo()     //�����г�����Ϣ���ļ���ȡ������
{
	int i, j,num;
	for(i = 0; i < NUM; ++i)     //��ʼ���ڽӾ���
		for(j = 0; j < NUM; ++j)
			G.arc[i][j].length = INFINITY;
	fp = fopen("information.txt","r");
	if(fp == NULL)
		printf("\n���ļ� information.txtʧ��.\n");
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
		printf("\n���ļ� road.txtʧ��.\n");
	else
	{
		for(i = 1; i <= G.vexnum; i++)
			for(j = 1; j <= G.vexnum; j++)
				fscanf(fp, "%d", &G.arc[i][j].length);
	}
	fclose(fp);
}

void SearchPlace()//��ѯ������Ϣ  
{
	int i,num;
	char c = 'y';
	while(c == 'y')
	{
		system("cls");
		OutputMenu();
		printf("\n\n��������Ҫ���ҵĳ��б�ţ�");
		scanf("%d", &num);
		getchar();
		system("cls");
		if(num > 0 && num <= G.vexnum)   //�ж���Ϣ������ȷ 
		{
			for(i = 1; i <= G.vexnum; i++)
				if(num == G.vertex[i].number)
				{
					printf("\n���б��: %d\n", i);
					printf("\n��������: %s\n", G.vertex[i].name);
					printf("\n���м��: %s\n", G.vertex[i].info);
				}
		}
		else
			printf("\n��Ϣ��������!\n");
		num = 0;
		printf("\n�Ƿ������ѯ������Ϣ(y/n): ");
		c = getchar();
		getchar();
	}
	system("cls");  
}

void SearchPath()     //��ѯ���·��
{
	int i, j;
	char c = 'y';
	while(c == 'y')
	{
		system("cls");
		OutputMenu();
		printf("\n��ѡ���һ������: ");
		scanf("%d", &i);
		printf("\n��ѡ��ڶ�������: ");
		scanf("%d", &j);
		getchar();
		if(i > G.vexnum || i <= 0 || j > G.vexnum || j < 0 || i == j)
			printf("\n������Ϣ����!\n\n");
		else
		{
			ShortPath(i);     //��Dijkstra�㷨������·��
			system("cls");
			OutputShortpath(i, j);     //�����·���ϵĳ����������
		}
		printf("\n�Ƿ������ѯ���·��(y/n): ");
		c = getchar();
		getchar();
	}
	system("cls");
}

void ShortPath(int num)    //Dijkstra�㷨���·��
{
	int i,j,u,t;
	int n=G.vexnum+1;
	int *final = (int *)malloc(sizeof(int)*(n+1));
	int min;     //��¼Ȩֵ���������·��
	for(i = 0; i < n; i++)   //��ʼ��
	{
		final[i] = 0;     //����Ӷ���num������iû�����·��
		Dist[i] = G.arc[num][i].length;     //������num�����ඥ������·�����ȳ�ʼ��ΪȨֵ
		for(j = 0; j < n; j++)
			path1[i][j] = 0;     //��ʼ����i��j��·��ֵ
		if(Dist[i] <90000)     //����·��
		{
			path1[i][num] = 1;
			path1[i][i] = 1;
		}
	}
	Dist[num] = 0;
	final[num]=1;      //���num�Ѽ���final��

	//��ʼ��ѭ��,ÿһ�����num��ĳ����������·������������뵽final����
	for(i = 1; i <n; i++)     // ����G.vexnum-1������
	{
		min = INFINITY;
		for(j = 0; j <= n; j++)
			if(!final[j] && Dist[j]<min )     
		{
				u = j;
				min = Dist[j];
		}
			if(min == INFINITY) return; 
			final[u] = 1;     //��num���������u���뵽final����
		
		for(j = 0; j < n; j++)     //���µ�ǰ���·���������
			if(!final[j] && Dist[u] + G.arc[u][j].length < Dist[j] && G.arc[u][j].length<INFINITY)
			{
				Dist[j] = Dist[u]+G.arc[u][j].length;     //����·��
				for(t = 0; t < n; t++)
					path1[j][t] = path1[u][t];
				path1[j][j] = 1;
			}
	}
}

void OutputShortpath(int city1,int city2)    // �������
{
	int a, b, c, d, q = 0;
	a = city2;
	if(a != city1)
	{
		printf("\n�� %s �� %s �����·����:\n\n", G.vertex[city1].name, G.vertex[city2].name);//�����ʾ��Ϣ
		//�������1������2�����·�����ȣ������Dist[]������
		printf("%s", G.vertex[city1].name);  //�������һ������
		d = city1;      //������һ�ı�Ÿ�ֵ��d
		for(c = 0; c < NUM; ++c)
		{
			gate:;        //��ţ�goto�����ת��λ��
			path1[a][city1] = 0;
			for(b = 0; b < NUM; b++)
			{
				if(G.arc[d][b].length < INFINITY && path1[a][b]) //�������һ������һ���ٽ��֮�����·�������·��
				{
					printf("-->%s", G.vertex[b].name);  //����˽ڵ������
					q = q + 1;    //����������һ����8�������ʱ�Ļ���
					path1[a][b] = 0;
					d = b;     //��b��Ϊ�����������һ��ѭ����� 
					if(q % 14 == 0)
						printf("\n");
					goto gate;
				}
			}
	 	}
		printf("\n\nȫ�� %d KM \n\n", Dist[a]);
	}
}

void AddPlace()     //�����µĳ���,���ļ��ж�֮ǰ���ļ�����ȫ�渲��
{
	int x, i, j, length;
	int city;
	char c = 'y', ch = 'y';
	while(c == 'y')
	{
		OutputMenu();
		printf("\n�������������еı��: ");
		scanf("%d", &x);
		G.vertex[G.vexnum+1].number = x;
		printf("\n�������������е�����: ");
		scanf("%s", G.vertex[x].name);
		printf("\n�������������еļ��: ");
		scanf("%s", G.vertex[x].info);
		G.vexnum++;
		fp = fopen("information.txt", "wt");
		if(fp == NULL)
			printf("\n���ļ� information.txtʧ��.\n");
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
				printf("\n���������³��������ĳ��еı��: ");
				scanf("%d", &city);
				printf("\n������·���ĳ���: ");
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
				printf("\n�Ƿ�������·��(y/n): ");
				getchar();
				ch = getchar();
				printf("\n�Ƿ�������ӳ���(y/n): ");
				getchar();
				c = getchar();
			}
		}
	}
	system("cls");
	ReadInfo();
}

void DeletePlace()     //ɾ������,���ļ��ж�֮ǰ���ļ�����ȫ�渲��
{
	int x, i, j, k = 0;
	char c = 'y';
	
	while(c == 'y')
	{
		OutputMenu();
		printf("\n������ɾ�����еı��: ");
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
		printf("\n�Ƿ����ɾ������(y/n): ");
		getchar();
		c = getchar();
	}
	system("cls");
	ReadInfo();
}

void AddPath()     //������·��
{
	int i, j;
	int num1, num2;
	int start, end, length;
	char c = 'y';
	while(c == 'y')
	{
		OutputMenu();
		printf("\n����������·�ߵĵ�һ�����б��: ");
		scanf("%d", &num1);
		if(num1 > 0 && num1 <= G.vexnum)   //�ж���Ϣ������ȷ
		{
			for(i = 1; i <= G.vexnum; i++)
				if(num1 == G.vertex[i].number)
					start = num1;     //�ҵ������������ͬ�ĳ���,����Ÿ���start
		}
		printf("\n����������·�ߵĵڶ������б��: ");
		scanf("%d", &num2);
		if(num2 > 0 && num2 <= G.vexnum)   //�ж���Ϣ������ȷ
		{
			for(i = 1; i <= G.vexnum; i++)
				if(num2 == G.vertex[i].number)
					end = num2;     //�ҵ������������ͬ�ĳ���,����Ÿ���end
		}
		if(num1 > G.vexnum || num1 <= 0 || num2 > G.vexnum || num2 < 0 || num1 == num2)
			printf("\n������Ϣ����!\n\n");
		else
		{
			printf("\n��������������֮��ľ���(KM): ");
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
		printf("\n�Ƿ��������·��(y/n): ");
		getchar();
		c = getchar();
	}
	system("cls");
	ReadInfo();
}

void DeletePath()     //ɾ��·��
{
	int i, j;
	int num1, num2;
	int start, end;
	char c = 'y';
	while(c == 'y')
	{
		OutputMenu();
		printf("\n������ɾ��·�ߵĵ�һ�����б��: ");
		scanf("%d", &num1);
		if(num1 > 0 && num1 <= G.vexnum)   //�ж���Ϣ������ȷ
		{
			for(i = 1; i <= G.vexnum; i++)
				if(num1 == G.vertex[i].number)
					start = num1;     //�ҵ������������ͬ�ĳ���,����Ÿ���start
		}
		printf("\n������ɾ��·�ߵĵڶ������б��: ");
		scanf("%d", &num2);
		if(num2 > 0 && num2 <= G.vexnum)   //�ж���Ϣ������ȷ
		{
			for(i = 1; i <= G.vexnum; i++)
				if(num2 == G.vertex[i].number)
					end = num2;     //�ҵ������������ͬ�ĳ���,����Ÿ���end
		}
		if(num1 > G.vexnum || num1 <= 0 || num2 > G.vexnum || num2 < 0 || num1 == num2)
			printf("\n������Ϣ����!\n\n");
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
		printf("\n�Ƿ����ɾ��·��(y/n): ");
		getchar();
		c = getchar();
	}
	system("cls");
	ReadInfo();
}

void ChangePassword()     //�޸ĵ�½����
{
	int password1, password2, newpass;
	char c = 'y'; 
	fp = fopen("password.txt", "wt");
	if(fp == NULL)
		printf("\n���ļ� password.txtʧ��.\n");
	else
	{
		while(c == 'y')
		{
			printf("\n������������: ");
			scanf("%d", &password1);
			printf("\n���ٴ�����������: ");
			scanf("%d", &password2);
			if(password1 == password2)
			{
				newpass = password1;
				fprintf(fp, "%d", newpass);
				printf("\n�޸�����ɹ�.\n");
				break;
			}
			else
			{
				printf("\n�����������벻��ͬ,�޸�����ʧ��.\n");
				printf("\n�Ƿ�����޸�����(y/n): ");
	 			getchar();
				c = getchar();
			}
		}
		fclose(fp);
		printf("\n����������ع���˵�\n");
		getchar();
		system("cls"); 
		ManageSystem();
	}
}

void ManageSystem()     //�������
{
	int x;
	printf("\n��ӭʹ�õ�ͼ��������ϵͳ\n");
	printf("\n");
	printf("1. ���ӳ���       \n");
	printf("2. ɾ������      \n");
	printf("3. ����·��       \n");
	printf("4. ����·��       \n");
	printf("5. �޸ĵ�½����     \n");
	printf("0. �˳�����ϵͳ     \n");
	printf("\n��ѡ������Ҫ�Ĳ���: ");
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
			 printf("\n������Ϣ����,����������!\n");
			 break;
	}
}

void password()    //����Ա�����֤
{
	int t;
	int password, pass;
	fp = fopen("password.txt","r");
	if(fp == NULL)
		printf("\n���ļ� password.txtʧ��.\n");
	else
	{
		fscanf(fp, "%d", &pass);
		printf("\n����������: ");
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
				printf("\n����������ٴ�����: ");
				scanf("%d", &password);
			}
		}
	}
	fclose(fp);
	if(password != pass)
	{
		printf("\n�Բ���,���޷���½����ϵͳ.\n\n�밴���������������...\n");
		getchar();
		getchar();
		system("cls");
	}
}