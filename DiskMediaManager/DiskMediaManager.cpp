#include "include.h"

//����Ʈ ��� ����
void Example();

//�޴����
int PrintMenu(Node** List);

void DataAdd(Node** List);					//������ �߰�

void DataEdit(Node** List);					//������ ����
void DataDelete(Node** List);				//������ ����
void DataSearch(Node** List);				//������ �˻�

void DataAllPrint(Node** List);				//������ ���� ���
void DataPrint(Node** List);					//������ Ư������ ���
void DataSorting(Node** List);				//������ ����
int SavingData(Node** List);					//���� ����
int LoadingData(Node** List);				//���� �б�
void DataAllDelete(Node** List);				//����Ʈ�� ��� ��带 �޸𸮿��� ����
void Progressbar();							//����/�ε� ���� ���� ǥ��
int DataValidCheck(Node*** List,int num);	//�ش� �̵� �����ϴ���


int main( void )
{
	Node* List    = NULL;

	int select=-1;

	DataAllDelete(&List);
	LoadingData(&List);

	do
	{
		select=PrintMenu(&List);

		switch(select)
		{
		case 1:
			DataAdd(&List);
			break;
		case 2:
			DataEdit(&List);
			break;
		case 3:
			DataDelete(&List);
			break;
		case 4:
			DataSearch(&List);
			break;
		case 5:
			DataPrint(&List);
			break;
		case 6:
			DataAllPrint(&List);
			break;
		case 7:
			SavingData(&List);
			break;
		case 8:
			DataAllDelete(&List);
			LoadingData(&List);
			break;
		case 9:
			printf(" ���α׷��� �����մϴ�.\n");
			printf("\n");
			break;
		default:
			break;
		}
	}while(select !=9);

	return 0;
}

//������ �߰�
void DataAdd(Node** List)
{
	Node*	NewNode	= NULL;
	Node*	Current= NULL;
	Node*	BeforeCurrent= NULL;

	int i=DLL_GetNodeCount( *List );

	//��� �߰�
	NewNode = DLL_CreateNode( i );
	DLL_AppendNode( List, NewNode );
	Current = DLL_GetNodeAt( *List, i );
	BeforeCurrent = DLL_GetNodeAt( *List, i-1 );

	if(i == 0)
	{
		(*Current).num=0;
	}
	else
	{
		(*Current).num=(*BeforeCurrent).num+1;
	}
	
	printf("���� �̵�� ��ȣ: %d",(*Current).num);
	//scanf("%d",&((*Current).num));			 //ex) [0]-��������,����(1,2)
	printf("\n����:");
	scanf("%s",&((*Current).name));
	printf("\n");
	
}

//������ ����
void DataEdit(Node** List)
{
	int num=0,count=0,result=0;

	count=DLL_GetNodeCount(*List);
	Node*	Current= DLL_GetNodeAt( *List, count-1 );
	
	printf("%d������ �̵� �ֽ��ϴ�.\n\n",Current->num);
	
	while(1)
	{
		printf("������ �̵�� ��ȣ�� �Է�:");
		scanf("%d",&num);

		result = DataValidCheck(&List,num);

		if(result!=-1)
		{
			break;
		}
		else
		{
			printf("\n �ش� �̵�� ��ȣ�� ��ȿ���� �ʽ��ϴ�.\n\n");
		}
	}

	Current = DLL_GetNodeAt( *List, result );
	
	printf("\n����:");
	scanf("%s",&((*Current).name));
	printf("\n");

	Progressbar();
	system("cls");
}

//������ ����
void DataDelete(Node** List)
{
	int	i=0, result=0;
	int Count=DLL_GetNodeCount( *List);
	Node* Current = DLL_GetNodeAt( *List, Count-1 );

	printf("%d������ �̵� �ֽ��ϴ�.\n\n",Current->num);

	while(1)
	{
		printf("������ �̵�� ��ȣ�� �Է�:");
		scanf("%d",&i);

		result = DataValidCheck(&List,i);

		if(result!=-1)
		{
			break;
		}
		else
		{
			printf("\n �ش� �̵�� ��ȣ�� ��ȿ���� �ʽ��ϴ�.\n\n");
		}
	}

	Current = DLL_GetNodeAt( *List, result );
	DLL_RemoveNode( List,  Current);
	Progressbar();
	system("cls");
}
//�ش� �̵� ��ȿ���� üũ, invalid:-1, valid:��ȿ�� �� �ش� �̵���� ����Ʈ ��� ��ȣ 
int DataValidCheck(Node*** List,int num)
{
	int i=0,result=0;
	int Count=DLL_GetNodeCount( **List);
	Node*	Current= NULL;


	for(i=0; i<Count; ++i)
	{
		Current = DLL_GetNodeAt( **List, i );

		if(Current->num == num)
			return i;
	}


	return -1;
}
//������ �˻�
void DataSearch(Node** List)
{
	char str[MAX_NAME_LEN]={0};

	Node*	SearchList		= NULL;
	Node*	SearchNewNode	= NULL;
	Node*	SearchCurrent	= NULL;

	Node*	Current = NULL;
	int		SearchCount = 0;
	int		i = 0, k = 0, Count = 0;

	Count = DLL_GetNodeCount( *List );

	

	printf(" �˻�� �Է��� �ּ���:");

	scanf("%s",str);
	
	for(i=0;i<Count;++i)
	{
		Current = DLL_GetNodeAt( *List, i );
		if(strstr(Current->name,str))
		{
			//��� �߰�
			SearchNewNode = DLL_CreateNode( k );
			DLL_AppendNode( &SearchList, SearchNewNode );
			SearchCurrent = DLL_GetNodeAt( SearchList, k );

			memcpy(SearchCurrent->name,Current->name,sizeof(char)*MAX_NAME_LEN);
			SearchCurrent->num=Current->num;
			k++;
		}
	}

	SearchCount = DLL_GetNodeCount( SearchList);


		for(i=0; i<SearchCount; ++i)
		{
			SearchCurrent = DLL_GetNodeAt( SearchList, i );
			printf( "�̵���ȣ: [%d] ����: %s\n",SearchCurrent->num, SearchCurrent->name );

			if(i!=0 && (i+1)%50==0)
			{
				printf("\n �ٴ����������� �Ѿ�ϴ�(���� 'Q'Ű)\n");
				char key=getch();

				if(key=='q'||key=='Q')
				{
					system("cls");
					return;
				}
				else
				{
					system("cls");
				}
			}
		}

	printf("\n ��Ű�� �����ø� �޴��� �Ѿ�ϴ�.\n");
	getch();
	system("cls");


}

//������ ���� ���
void DataAllPrint(Node** List)
{
	int i=0,unit=0;
	int Count = 0;
	char key = 0;

	Node*	NewNode	= NULL;
	Node*	Current= NULL;
	FILE * file = NULL;

	printf(" ���������� ��µ� �̵�� ������ ��?(0: 50��):");
	scanf("%d",&unit);

	system("cls");

	//  ����Ʈ ���
	Count = DLL_GetNodeCount( *List );
	for ( i = 0; i<Count; i++ )
	{
		Current = DLL_GetNodeAt( *List, i );
		//printf( "List[%d] : %d, %d, %s\n", i, Current->Data, Current->num, Current->name );
		printf( "�̵���ȣ: [%d] ����: %s\n",Current->num, Current->name );

		if(unit==0)
		{
			if(i!=0 && (i+1)%50==0)
			{
				printf("\n �ٴ����������� �Ѿ�ϴ�(���� 'Q'Ű)\n");
				key=getch();

				if(key=='q'||key=='Q')
				{
					system("cls");
					return;
				}
				else
				{
					system("cls");
				}
			}
		}
		else
		{
			if(i!=0 && (i+1)%unit==0)
			{
				printf("\n ��Ű�� �����ø� ������������ �Ѿ�ϴ�.\n");
				key=getch();

				if(key=='q'||key=='Q')
				{
					system("cls");
					return;
				}
				else
				{
					system("cls");
				}
			}
		}
		if(i==Count-1)
		{
			printf("\n ��Ű�� �����ø� �޴��� �Ѿ�ϴ�.\n");
			getch();
			system("cls");
		}

	}
	
}


//������ ���� ���
void DataPrint(Node** List)
{
	int i=0,unit=0,startnum=0,endnum=0,result=0;
	int Count = 0;
	char key = 0;

	Node*	NewNode	= NULL;
	Node*	Current= NULL;
	FILE * file = NULL;

	Count = DLL_GetNodeCount( *List );

	while(1)
	{
		printf(" ���� ��ȣ:");
		scanf("%d",&startnum);

		result=DataValidCheck(&List,startnum);

		if(startnum <0)
		{
			system("cls");
			printf(" 0 �̻��� �Է��ϼž� �մϴ�.\n");
		}
		else if(result==-1)
		{
			printf(" �ش��ȣ�� ��ȿ ���� �ʽ��ϴ�.\n");
		}
		else
		{
			startnum=result;
			break;
		}
	}
	
	while(1)
	{
		printf(" �� ��ȣ:");
		scanf("%d",&endnum);

		result=DataValidCheck(&List,endnum);

		if(endnum<startnum)
		{
			system("cls");
			printf(" �� ��ȣ�� ���� ��ȣ ���� ũ�ų� ���ƾ� �մϴ�.\n");
		}
		else if(endnum < 0)
		{
			printf(" �� ��ȣ�� 0 ���� Ŀ�� �մϴ�.\n");
		}
		else if(result==-1)
		{
			printf(" �ش��ȣ�� ��ȿ ���� �ʽ��ϴ�.\n");
		}
		else
		{
			endnum=result;
			break;
		}
	}


	if(endnum-startnum > 50)
	{
		printf(" ���������� ��µ� �̵�� ������ ��?(0: 50��):");
		scanf("%d",&unit);
	}

	system("cls");

	//  ����Ʈ ���
	for ( i = 0; i<Count; i++ )
	{
		if(i<startnum)
			continue;
		
		if(i>endnum)
		{
			printf("\n ��Ű�� �����ø� �޴��� �Ѿ�ϴ�.\n");
			getch();
			system("cls");
			return;
		}

		Current = DLL_GetNodeAt( *List, i );
		//printf( "List[%d] : %d, %d, %s\n", i, Current->Data, Current->num, Current->name );
		printf( "�̵���ȣ: [%d] ����: %s\n",Current->num, Current->name );

		if(unit==0)
		{
			if(i!=0 && (i+1)%50==0&&i!=endnum)
			{
				printf("\n �ٴ����������� �Ѿ�ϴ�(���� 'Q'Ű)\n");
				key=getch();

				if(key=='q'||key=='Q')
				{
					system("cls");
					return;
				}
				else
				{
					system("cls");
				}
			}
		}
		else
		{
			if(i!=0 && (i+1)%unit==0&&i!=endnum)
			{
				printf("\n �ٴ����������� �Ѿ�ϴ�(���� 'Q'Ű)\n");
				key=getch();

				if(key=='q'||key=='Q')
				{
					system("cls");
					return;
				}
				else
				{
					system("cls");
				}
			}
		}
		if(i==Count-1)
		{
			printf("\n ��Ű�� �����ø� �޴��� �Ѿ�ϴ�.\n");
			getch();
			system("cls");
		}

	}

}
//������ ����
void DataSorting(Node** List)
{
}

//������ �����ϱ�
int SavingData(Node** List)
{
	int		i		= 0;
	int		Count  = 0;
	Node*	Current= NULL;

	/* ����� ���� ���� ���� ���� ����*/
	FILE * file = fopen("cd-list.txt","wt");
	if(file==NULL){
		printf("file open error!\n");
		return 1;
	}


	Count = DLL_GetNodeCount( *List );
	for ( i = 0; i<Count; i++ )
	{
		if(i==Count-1)
		{
			Current = DLL_GetNodeAt( *List, i );
			fprintf(file,"[%d]-%s", Current->Data, Current->name );	
		}
		else
		{
			Current = DLL_GetNodeAt( *List, i );
			fprintf(file,"[%d]-%s\n", Current->Data, Current->name );							//ex) [0]-��������,����(1,2)
		}
	}	

	/*������ ����*/
	fclose(file);

	Progressbar();
	system("cls");
	
	return 0;
}

//������ �ε��ϱ�
int LoadingData(Node** List)
{
	int		i		= 0;
	Node*	NewNode	= NULL;
	Node*	Current= NULL;

	/* ����� ���� �б� ���� ���� ����*/
	FILE * file = fopen("cd-list.txt","rt");
	if(file==NULL){
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		//��� �߰�
		NewNode = DLL_CreateNode( i );
		DLL_AppendNode( List, NewNode );
		Current = DLL_GetNodeAt( *List, i );


		char buffer[300]={0};
		fgets(buffer,sizeof(buffer),file);
		sscanf(buffer,"[%d]-%s",&((*Current).num),&((*Current).name));			 //ex) [0]-��������,����(1,2)
		
		i++;

		if(feof(file)!=0)
			break;
	}
	/*������ ����*/
	fclose(file);

	Progressbar();
	system("cls");


	return 0;
}

//�޴� ���
int PrintMenu(Node** List)
{
	int select=-1;

	printf(" ����������������������������������������\n");
	printf(" �������ü ������ ���� / �˻� ���α׷���\n");
	printf(" ����������������������������������������\n");
	printf(" ��������DiskMediaManager Ver 1.0��������\n");
	printf(" ����������������������������������������\n");
	printf(" ��1. �߰���2. ���� ��3. ���� ��4. �˻���\n");
	printf(" ����������������������������������������\n");
	printf(" ��5. ���� ���     ��6. ���� ���     ��\n");
	printf(" ����������������������������������������\n");
	printf(" ��7. ���� ����	    ��8. ���� �б�     ��\n");
	printf(" ����������������������������������������\n");
	printf(" ��9. ���α׷� ����                    ��\n");
	printf(" ����������������������������������������\n");
	printf(" ������ ��%6d���� ��ü�� ��ϵ�     ��\n",DLL_GetNodeCount( *List ));
	printf(" ����������������������������������������\n");
	printf("  ��ȣ�� �����ϼ���:[ ]\b\b");

	fflush(stdin);			// �Է¹��۸� Ŭ�����Ѵ�.
	scanf("%d",&select);
	system("cls");			// clear the screen.
	
	return select;
}
// ����Ʈ�� ��� ��带 �޸𸮿��� ����
void DataAllDelete(Node** List)
{
	int   i       = 0;
	int   Count   = 0;
	Node* Current = NULL;

	

	Count = DLL_GetNodeCount(*List);

	for ( i = 0; i<Count; i++ )
	{
		Current = DLL_GetNodeAt( *List, 0 );

		if ( Current != NULL ) 
		{
			DLL_RemoveNode( List, Current );
			DLL_DestroyNode( Current );
		}
	}
}



void Progressbar()
{
	printf(" ����������� ~ 0%\r"); _sleep(100);
	printf(" ����������� ~ 10%\r");_sleep(100);
	printf(" ����������� ~ 20%\r");_sleep(100);
	printf(" ����������� ~ 30%\r");_sleep(100);
	printf(" ����������� ~ 40%\r");_sleep(100);
	printf(" ����������� ~ 50%\r");_sleep(100);
	printf(" ����������� ~ 60%\r");_sleep(100);
	printf(" ����������� ~ 70%\r");_sleep(100);
	printf(" ����������� ~ 80%\r");_sleep(100);
	printf(" ����������� ~ 90%\r");_sleep(100);
	printf(" ����������� ~ 100%\r");_sleep(100);
	printf(" ����������� ~ COMPLETE!\r\a");_sleep(50);
	printf(" ����������� ~ COMPLETE!\r");_sleep(50);
	printf(" ����������� ~ COMPLETE!\r\a");_sleep(50);
	printf(" ����������� ~ COMPLETE!\r");_sleep(50);
	printf(" ����������� ~ COMPLETE!\r\a");_sleep(50);
	printf(" ����������� ~ COMPLETE!\r");_sleep(50);
	printf(" ����������� ~ COMPLETE!\r\a");_sleep(50);
	printf(" ����������� ~ COMPLETE!\r");_sleep(50);
	printf(" ����������� ~ COMPLETE!\r\a");_sleep(50);
	printf(" ����������� ~ COMPLETE!\r");_sleep(50);
	return;
}

void Example()
{
	int   i       = 0;
	int   Count   = 0;
	Node* List    = NULL;
	Node* NewNode = NULL;
	Node* Current = NULL;

	/*  ��� 5�� �߰� */
	for ( i = 0; i<5; i++ )
	{
		NewNode = DLL_CreateNode( i );
		DLL_AppendNode( &List, NewNode );
	}

	/*  ����Ʈ ��� */
	Count = DLL_GetNodeCount( List );
	for ( i = 0; i<Count; i++ )
	{
		Current = DLL_GetNodeAt( List, i );
		printf( "List[%d] : %d\n", i, Current->Data );
	}

	/*  ����Ʈ�� ����° ĭ �ڿ� ��� ���� */
	printf( "\nInserting 3000 After [2]...\n\n" );

	Current = DLL_GetNodeAt( List, 2 );
	NewNode = DLL_CreateNode( 3000 );
	DLL_InsertAfter( Current, NewNode );

	/*  ����Ʈ ��� */
	Count = DLL_GetNodeCount( List );
	for ( i = 0; i<Count; i++ )
	{
		Current = DLL_GetNodeAt( List, i );
		printf( "List[%d] : %d\n", i, Current->Data );
	}
}