#include <iostream>
#include <cstdlib>
#include <cstring>
#include <windows.h>
#include <stdio.h>

using namespace std;


struct trie 
{ 
	char *value;
 	char ch; 
 	trie *sibling;    
 	trie *child; 
};

trie *trie_create() 
{
	trie *node = new trie;
	node->ch = '\0'; 
	node->value = NULL; 
	node->sibling = NULL; 
	node->child = NULL;
	return node;        
}

void trie_lookup(trie *root, int val, int &numsg) //������� ���-�� ����, ���������� ������������ ���-�� ��������� � ����� �� �� �����
{
	trie *node, *list;
	for (node = root; node != NULL; node = node->sibling) 
	{
		if (node->value != NULL) 
		{  
			int ivalue = atoi(node->value);
			if (ivalue == val)
				numsg++;
		}    
		if (node->child != NULL) 
			trie_lookup(node->child, val, numsg);	
	}
}
struct trie *trie_insert(trie *root, char *key, char *value) // ������� ��������� �����, � �������� ����� - ���������� ��������� ���� � ����� 
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
	if (node->value != NULL) 
		free(node->value); 
	node->value = strdup(value); 
	return root;
}

void trie_print(trie *root, int level) //����� ������
{
	 trie *node; int i;
	 for (node = root; node != NULL; node = node->sibling) 
	 { 
	 	for (i = 0; i < level; i++)
		 	 cout<< ' ';
		if (node->value != NULL) 
			cout<<'\n'<< node->ch <<' '<< node->value; 
		else 
			cout<< '\n'<< node->ch;     
		if (node->child != NULL) 
			trie_print(node->child, level + 1);
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
 						char sog[10];
 						int kol = consonants(str);
 						sprintf(sog, "%d", kol);
						root = trie_insert(root, str, sog); 
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

