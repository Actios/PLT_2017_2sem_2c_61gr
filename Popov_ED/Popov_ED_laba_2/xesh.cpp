/*
	Popov_ED 2 kurs 61 gruppa. 
	laba2
     ����� ��������� ����. ������������ ����� �������������� �� 2 � ����� �����, 
	 ������������� � ������ �� ����� 2-� ���
 */
 #include<iostream>
 #include<string>
 #include <fstream>
 #include <cstdio>
#include<cstring>
 #define HASHTAB_SIZE 20
 using namespace std;
 
 struct listnode {
     string text;
     int n;
     struct listnode *next;
 };
 struct listnode *hashtab[HASHTAB_SIZE];
 
 unsigned int hashtab_hash(string text)
 {
     int sum=0,hash;
     for(int i=0;i<text.length();i++)
         sum+=(int)text[i]-(int)'0';
     hash=sum%HASHTAB_SIZE;
     return hash;
 }
 
 void hashtab_init(struct listnode **hashtab)
 {
     for (int i = 0; i < HASHTAB_SIZE; i++)
         hashtab[i] = NULL;
 }
 
 void hashtab_add(struct listnode **hashtab, string text)
 {
     struct listnode *node = new listnode;
     int index = hashtab_hash(text);
     // adding to the begin of list
     if (node != NULL) {
         node->text = text;
         node->n=1;
         node->next = hashtab[index];
         hashtab[index] = node;
     }
 }
 
 struct listnode *hashtab_lookup(struct listnode **hashtab, string text)
 {
     int index = hashtab_hash(text);
     struct listnode *node;
     for (node = hashtab[index]; node != NULL; node = node->next) 
     {
         if (node->text == text)
             return node; 
     }
     return NULL;
 }
 
 void find_words(struct listnode **hashtab)
 {
 	listnode **q=hashtab;
 	for (int i=0; i<HASHTAB_SIZE; i++)
 	
	while (q[i])
		{
			if (q[i]->n>=2) cout<<q[i]->text;
			q[i]=q[i]->next;
		}				 
 }
 	
 
 void add_text(struct listnode **hashtab)
 {
 	string str,str1;
 	fstream fin("file.txt");
 	while(!fin.eof())
   {
    getline(fin, str);
    str1+=str+" ";
    
	}
	cout<<"Text in the file:\n"<<str1;
	int i=0;
	cout<<endl;
	str="";
	while (str1[i]!='\0')
	{
		str+=str1[i];
		if (str1[i]==' ') 
		{
			listnode *p=hashtab_lookup(hashtab, str);
     		if (p!=NULL)
     		{
     			p->n+=1;			
 			}
     		else		
				hashtab_add(hashtab, str);
			str.erase (0,i);
			str1.erase (0,i);
			i=0;
			
		}
		i++;
	}
	fin.close();	
 }
 
 int main()
 {
 	hashtab_init(hashtab);
 	cout<<"Commands:"<<endl<<"1.Add text to the hash"<<endl<<"2.Search words whith are more than 2 times"<<endl<<"3.End the program";
 	int command;
 	while(1)
 	{
 		cout<<endl<<"Enter the command: ";
 		cin>>command;
 		switch(command)
 		{
 			case 1:{
     			add_text(hashtab);										
				
 				break;
 				}
			 case 2:{
			 	cout<<"Words are more than 2 times:\n";
			 	find_words(hashtab);
				break;
			 }
			 case 3:{
 				return 0;
 				break;
 			}

 		}
 	}
    return 0;
 }
