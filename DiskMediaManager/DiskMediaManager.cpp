#include "include.h"

//리스트 사용 예제
void Example();

//메뉴출력
int PrintMenu(Node** List);

void DataAdd(Node** List);					//데이터 추가

void DataEdit(Node** List);					//데이터 수정
void DataDelete(Node** List);				//데이터 삭제
void DataSearch(Node** List);				//데이터 검색

void DataAllPrint(Node** List);				//데이터 전부 출력
void DataPrint(Node** List);					//데이터 특정범위 출력
void DataSorting(Node** List);				//데이터 정렬
int SavingData(Node** List);					//파일 저장
int LoadingData(Node** List);				//파일 읽기
void DataAllDelete(Node** List);				//리스트의 모든 노드를 메모리에서 제거
void Progressbar();							//저장/로드 등의 상태 표시
int DataValidCheck(Node*** List,int num);	//해당 미디어가 존재하는지


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
			printf(" 프로그램을 종료합니다.\n");
			printf("\n");
			break;
		default:
			break;
		}
	}while(select !=9);

	return 0;
}

//데이터 추가
void DataAdd(Node** List)
{
	Node*	NewNode	= NULL;
	Node*	Current= NULL;
	Node*	BeforeCurrent= NULL;

	int i=DLL_GetNodeCount( *List );

	//노드 추가
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
	
	printf("현재 미디어 번호: %d",(*Current).num);
	//scanf("%d",&((*Current).num));			 //ex) [0]-스프리건,에바(1,2)
	printf("\n내용:");
	scanf("%s",&((*Current).name));
	printf("\n");
	
}

//데이터 수정
void DataEdit(Node** List)
{
	int num=0,count=0,result=0;

	count=DLL_GetNodeCount(*List);
	Node*	Current= DLL_GetNodeAt( *List, count-1 );
	
	printf("%d번까지 미디어가 있습니다.\n\n",Current->num);
	
	while(1)
	{
		printf("수정할 미디어 번호를 입력:");
		scanf("%d",&num);

		result = DataValidCheck(&List,num);

		if(result!=-1)
		{
			break;
		}
		else
		{
			printf("\n 해당 미디어 번호는 유효하지 않습니다.\n\n");
		}
	}

	Current = DLL_GetNodeAt( *List, result );
	
	printf("\n내용:");
	scanf("%s",&((*Current).name));
	printf("\n");

	Progressbar();
	system("cls");
}

//데이터 삭제
void DataDelete(Node** List)
{
	int	i=0, result=0;
	int Count=DLL_GetNodeCount( *List);
	Node* Current = DLL_GetNodeAt( *List, Count-1 );

	printf("%d번까지 미디어가 있습니다.\n\n",Current->num);

	while(1)
	{
		printf("삭제할 미디어 번호를 입력:");
		scanf("%d",&i);

		result = DataValidCheck(&List,i);

		if(result!=-1)
		{
			break;
		}
		else
		{
			printf("\n 해당 미디어 번호는 유효하지 않습니다.\n\n");
		}
	}

	Current = DLL_GetNodeAt( *List, result );
	DLL_RemoveNode( List,  Current);
	Progressbar();
	system("cls");
}
//해당 미디어가 유효한지 체크, invalid:-1, valid:유효할 때 해당 미디어의 리스트 노드 번호 
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
//데이터 검색
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

	

	printf(" 검색어를 입력해 주세요:");

	scanf("%s",str);
	
	for(i=0;i<Count;++i)
	{
		Current = DLL_GetNodeAt( *List, i );
		if(strstr(Current->name,str))
		{
			//노드 추가
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
			printf( "미디어번호: [%d] 내용: %s\n",SearchCurrent->num, SearchCurrent->name );

			if(i!=0 && (i+1)%50==0)
			{
				printf("\n ☆다음페이지로 넘어갑니다(종료 'Q'키)\n");
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

	printf("\n ☆키를 누르시면 메뉴로 넘어갑니다.\n");
	getch();
	system("cls");


}

//데이터 전부 출력
void DataAllPrint(Node** List)
{
	int i=0,unit=0;
	int Count = 0;
	char key = 0;

	Node*	NewNode	= NULL;
	Node*	Current= NULL;
	FILE * file = NULL;

	printf(" 한페이지에 출력될 미디어 데이터 수?(0: 50개):");
	scanf("%d",&unit);

	system("cls");

	//  리스트 출력
	Count = DLL_GetNodeCount( *List );
	for ( i = 0; i<Count; i++ )
	{
		Current = DLL_GetNodeAt( *List, i );
		//printf( "List[%d] : %d, %d, %s\n", i, Current->Data, Current->num, Current->name );
		printf( "미디어번호: [%d] 내용: %s\n",Current->num, Current->name );

		if(unit==0)
		{
			if(i!=0 && (i+1)%50==0)
			{
				printf("\n ☆다음페이지로 넘어갑니다(종료 'Q'키)\n");
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
				printf("\n ☆키를 누르시면 다음페이지로 넘어갑니다.\n");
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
			printf("\n ☆키를 누르시면 메뉴로 넘어갑니다.\n");
			getch();
			system("cls");
		}

	}
	
}


//데이터 범위 출력
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
		printf(" 시작 번호:");
		scanf("%d",&startnum);

		result=DataValidCheck(&List,startnum);

		if(startnum <0)
		{
			system("cls");
			printf(" 0 이상을 입력하셔야 합니다.\n");
		}
		else if(result==-1)
		{
			printf(" 해당번호는 유효 하지 않습니다.\n");
		}
		else
		{
			startnum=result;
			break;
		}
	}
	
	while(1)
	{
		printf(" 끝 번호:");
		scanf("%d",&endnum);

		result=DataValidCheck(&List,endnum);

		if(endnum<startnum)
		{
			system("cls");
			printf(" 끝 번호는 시작 번호 보다 크거나 같아야 합니다.\n");
		}
		else if(endnum < 0)
		{
			printf(" 끝 번호는 0 보다 커야 합니다.\n");
		}
		else if(result==-1)
		{
			printf(" 해당번호는 유효 하지 않습니다.\n");
		}
		else
		{
			endnum=result;
			break;
		}
	}


	if(endnum-startnum > 50)
	{
		printf(" 한페이지에 출력될 미디어 데이터 수?(0: 50개):");
		scanf("%d",&unit);
	}

	system("cls");

	//  리스트 출력
	for ( i = 0; i<Count; i++ )
	{
		if(i<startnum)
			continue;
		
		if(i>endnum)
		{
			printf("\n ☆키를 누르시면 메뉴로 넘어갑니다.\n");
			getch();
			system("cls");
			return;
		}

		Current = DLL_GetNodeAt( *List, i );
		//printf( "List[%d] : %d, %d, %s\n", i, Current->Data, Current->num, Current->name );
		printf( "미디어번호: [%d] 내용: %s\n",Current->num, Current->name );

		if(unit==0)
		{
			if(i!=0 && (i+1)%50==0&&i!=endnum)
			{
				printf("\n ☆다음페이지로 넘어갑니다(종료 'Q'키)\n");
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
				printf("\n ☆다음페이지로 넘어갑니다(종료 'Q'키)\n");
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
			printf("\n ☆키를 누르시면 메뉴로 넘어갑니다.\n");
			getch();
			system("cls");
		}

	}

}
//데이터 정렬
void DataSorting(Node** List)
{
}

//데이터 저장하기
int SavingData(Node** List)
{
	int		i		= 0;
	int		Count  = 0;
	Node*	Current= NULL;

	/* 백업을 위해 쓰기 전용 파일 개방*/
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
			fprintf(file,"[%d]-%s\n", Current->Data, Current->name );							//ex) [0]-스프리건,에바(1,2)
		}
	}	

	/*파일의 종결*/
	fclose(file);

	Progressbar();
	system("cls");
	
	return 0;
}

//데이터 로딩하기
int LoadingData(Node** List)
{
	int		i		= 0;
	Node*	NewNode	= NULL;
	Node*	Current= NULL;

	/* 백업을 위해 읽기 전용 파일 개방*/
	FILE * file = fopen("cd-list.txt","rt");
	if(file==NULL){
		printf("file open error!\n");
		return 1;
	}

	while(1)
	{
		//노드 추가
		NewNode = DLL_CreateNode( i );
		DLL_AppendNode( List, NewNode );
		Current = DLL_GetNodeAt( *List, i );


		char buffer[300]={0};
		fgets(buffer,sizeof(buffer),file);
		sscanf(buffer,"[%d]-%s",&((*Current).num),&((*Current).name));			 //ex) [0]-스프리건,에바(1,2)
		
		i++;

		if(feof(file)!=0)
			break;
	}
	/*파일의 종결*/
	fclose(file);

	Progressbar();
	system("cls");


	return 0;
}

//메뉴 출력
int PrintMenu(Node** List)
{
	int select=-1;

	printf(" ┏━━━━━━━━━━━━━━━━━━┓\n");
	printf(" ┃저장매체 데이터 관리 / 검색 프로그램┃\n");
	printf(" ┣━━━━━━━━━━━━━━━━━━┫\n");
	printf(" ┠───DiskMediaManager Ver 1.0───┨\n");
	printf(" ┣━━━━━━━━━━━━━━━━━━┫\n");
	printf(" ┃1. 추가│2. 수정 │3. 삭제 │4. 검색┃\n");
	printf(" ┠──────────────────┨\n");
	printf(" ┃5. 범위 출력     │6. 전부 출력     ┃\n");
	printf(" ┠──────────────────┨\n");
	printf(" ┃7. 파일 저장	    │8. 파일 읽기     ┃\n");
	printf(" ┠──────────────────┨\n");
	printf(" ┃9. 프로그램 종료                    ┃\n");
	printf(" ┣━━━━━━━━━━━━━━━━━━┫\n");
	printf(" ┃현재 총%6d개의 매체가 등록됨     ┃\n",DLL_GetNodeCount( *List ));
	printf(" ┗━━━━━━━━━━━━━━━━━━┛\n");
	printf("  번호를 선택하세요:[ ]\b\b");

	fflush(stdin);			// 입력버퍼를 클리어한다.
	scanf("%d",&select);
	system("cls");			// clear the screen.
	
	return select;
}
// 리스트의 모든 노드를 메모리에서 제거
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
	printf(" □□□□□□□□□□ ~ 0%\r"); _sleep(100);
	printf(" ■□□□□□□□□□ ~ 10%\r");_sleep(100);
	printf(" ■■□□□□□□□□ ~ 20%\r");_sleep(100);
	printf(" ■■■□□□□□□□ ~ 30%\r");_sleep(100);
	printf(" ■■■■□□□□□□ ~ 40%\r");_sleep(100);
	printf(" ■■■■■□□□□□ ~ 50%\r");_sleep(100);
	printf(" ■■■■■■□□□□ ~ 60%\r");_sleep(100);
	printf(" ■■■■■■■□□□ ~ 70%\r");_sleep(100);
	printf(" ■■■■■■■■□□ ~ 80%\r");_sleep(100);
	printf(" ■■■■■■■■■□ ~ 90%\r");_sleep(100);
	printf(" ■■■■■■■■■■ ~ 100%\r");_sleep(100);
	printf(" □□□□□□□□□□ ~ COMPLETE!\r\a");_sleep(50);
	printf(" ■■■■■■■■■■ ~ COMPLETE!\r");_sleep(50);
	printf(" □□□□□□□□□□ ~ COMPLETE!\r\a");_sleep(50);
	printf(" ■■■■■■■■■■ ~ COMPLETE!\r");_sleep(50);
	printf(" □□□□□□□□□□ ~ COMPLETE!\r\a");_sleep(50);
	printf(" ■■■■■■■■■■ ~ COMPLETE!\r");_sleep(50);
	printf(" □□□□□□□□□□ ~ COMPLETE!\r\a");_sleep(50);
	printf(" ■■■■■■■■■■ ~ COMPLETE!\r");_sleep(50);
	printf(" □□□□□□□□□□ ~ COMPLETE!\r\a");_sleep(50);
	printf(" ■■■■■■■■■■ ~ COMPLETE!\r");_sleep(50);
	return;
}

void Example()
{
	int   i       = 0;
	int   Count   = 0;
	Node* List    = NULL;
	Node* NewNode = NULL;
	Node* Current = NULL;

	/*  노드 5개 추가 */
	for ( i = 0; i<5; i++ )
	{
		NewNode = DLL_CreateNode( i );
		DLL_AppendNode( &List, NewNode );
	}

	/*  리스트 출력 */
	Count = DLL_GetNodeCount( List );
	for ( i = 0; i<Count; i++ )
	{
		Current = DLL_GetNodeAt( List, i );
		printf( "List[%d] : %d\n", i, Current->Data );
	}

	/*  리스트의 세번째 칸 뒤에 노드 삽입 */
	printf( "\nInserting 3000 After [2]...\n\n" );

	Current = DLL_GetNodeAt( List, 2 );
	NewNode = DLL_CreateNode( 3000 );
	DLL_InsertAfter( Current, NewNode );

	/*  리스트 출력 */
	Count = DLL_GetNodeCount( List );
	for ( i = 0; i<Count; i++ )
	{
		Current = DLL_GetNodeAt( List, i );
		printf( "List[%d] : %d\n", i, Current->Data );
	}
}