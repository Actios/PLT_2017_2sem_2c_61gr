#include <iostream>
#include <cstdlib>
#include <cstring>
#include <windows.h>
#include <stdio.h>

using namespace std;


struct trie 
{ 
	int value;
 	char ch; 
 	trie *sibling;    
 	trie *child; 
};

trie *trie_create() 
{
	trie *node = new trie;
	node->ch = '\0'; 
	node->value = 0; 
	node->sibling = NULL; 
	node->child = NULL;
	return node;        
}

void trie_lookup(trie *root, int val, int numsg) //������� ���-�� ����, ���������� ������������ ���-�� ��������� � ����� �� �� �����
{
	trie *node, *list;
	for (node = root; node != NULL; node = node->sibling) 
	{
		if (node->value != 0) 
		{  
			if (node->value == val)
				numsg++;
		}    
		if (node->child != NULL) 
			trie_lookup(node->child, val, numsg);	
	}
}
struct trie *trie_insert(trie *root, char *key, int value) // ������� ��������� �����, � �������� ����� - ���������� ��������� ���� � ����� 
{ 
	trie *node, *parent, *list;
	parent = NULL; 
	list = root; 
	for (; *key != '\0'; key++) 
	{ 
		for (node = list; node != NULL; node = node->sibling) 
		{
			 if (node->ch == *key) 
			 	break; 
		}
		if (node == NULL) 
		{ 
			node = trie_create();
			node->ch = *key; 
			node->sibling = list; 
			if (parent != NULL) 
				parent->child = node; 
			else 
				root = node; 
			list = NULL; 
		} 
		else 
		{ 
			list = node->child; 
		} 
		parent = node;
	}  
	node->value = value;
	return root;
}

void trie_print(trie *root, int level) //����� ������
 {
 	trie *node;
 	int i;
 	for (node = root; node!=NULL;node = node->sibling)
 	{
 		for (i = 0;i < level;i++)
 			printf(" ");
 	
 		if (node->value != 0)
			printf("%c (%d) \n" ,node->ch,  node->value);
 		else
 			printf("%c \n",node->ch);
 	
 		if (node->child != NULL)
 			trie_print(node->child, level+1);
 	}
}
int consonants(char *str) // ������� ���������� ��������� ��������� ����� 
{
	int sg=0;
    char sog[]="������������������������������������������";
 
    for(int i=0; i < strlen(str); i++)
            for(int j=0; j < strlen(sog); j++)
                    if(str[i] ==sog[j])
                            sg++;
    
 	return sg;
}

int main() 
{ 
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);	
	
	trie *root = NULL;
	
	int otv1, otv2;
	do
	{	
			cout << " �������� ��������:" << endl << "1. �������� ����� �����" << endl << "2. ������� ������"<< endl
			<< "3. ���������� ���-�� ����, ������� �������� ������������ ���-�� ���������"<< endl << "0. �����"<< endl <<"=";
			cin >> otv1;
			switch (otv1)
			{
				case 0: 
					break;
				case 1:  
					{
						cout<< "������� �����:" << endl;
						char str[100];
 						cin >> str;
 						int kol = consonants(str);
						root = trie_insert(root, str, kol); 
						break;
					}
				case 2: 
					{
						trie_print(root, 0);
						cout<< endl;
						break;
					}
				case 3:
					{
						int ksg, numsg=0;
						cout << "������� ���-�� ���������:";
						cin >> ksg;
						trie_lookup(root, ksg, numsg);
						cout << "����� ����:" << numsg << endl;
						break;
					}
					
				default:
					{
						cout << endl << "������" << endl; 
						break;
					}
			}
		
	}
	while(otv1 != 0);
	
	system("pause");
	return 0;
}

