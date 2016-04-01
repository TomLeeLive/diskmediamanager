//DoublyLinkedList
#ifndef DOUBLY_LINKEDLIST_H
#define DOUBLY_LINKEDLIST_H

#define MAX_NAME_LEN	250

typedef int ElementType;

typedef struct tagNode
{
	int		num;						//��ȣ
	char	name[MAX_NAME_LEN];		//�̸�

	ElementType Data;
	struct tagNode* PrevNode;
	struct tagNode* NextNode;
} Node;

/* �Լ� ���� ���� */
Node* DLL_CreateNode( ElementType NewData );
void  DLL_DestroyNode( Node* Node);
void  DLL_AppendNode( Node** Head, Node* NewNode );
void  DLL_InsertAfter( Node* Current, Node* NewNode );
void  DLL_RemoveNode( Node** Head, Node* Remove );
Node* DLL_GetNodeAt( Node* Head, int Location );
int   DLL_GetNodeCount( Node* Head );

#endif DOUBLY_LINKEDLIST_H