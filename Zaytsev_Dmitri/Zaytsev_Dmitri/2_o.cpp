#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

struct inf
 {
  string phone_number;
  string fio;
  string address;
 };
 
struct cell
 {
  int hash;
  inf data;
  cell *next;
 };

cell *table = new cell[99];
  
int f_hash(string phone_number)
 {
  int sum = 0;
  for(int i = 0 ; i < phone_number.length(); ++i)
   {
    sum = sum + (int)(phone_number[i]) - (int)('0');
   }	
  return(sum);
 }
 
void search(int hash,string phone_number)
 {
  cell *now = new cell;
  *now = table[hash];
  while( (now->data.phone_number != phone_number) && (now->hash != 0) )
   {
    now = now->next;
   }
  if(now->hash == 0)
   {
    cout<<endl<<"����� �� ������"<<endl;
   }
  else
   {
    cout<<endl<<"����� ������."<<endl;
    cout<<"---------------------------------------------------------------"<<endl;
	cout<<"����� ��������: "<<now->data.phone_number<<endl;
    cout<<"���: "<<now->data.fio<<endl;
    cout<<"�����: "<<now->data.address<<endl;
	cout<<"---------------------------------------------------------------"<<endl;
   }
 }

int main()
{
 setlocale(LC_ALL, "Russian");
  for(int i = 0 ; i<99 ; ++i)
   {
    table[i].hash = 0;
    table[i].next = new cell;
    table[i].next->hash = 0;
	table[i].next->next = NULL;
   }
  bool trig;
  string temp;
  int hash_now;
  cell *now;
  while(1)
   {
    cout<<"������ ����� ������? 1/0"<<endl;
    cin>>trig;
    if(trig == 0)
	 {
	  break;
	 }
	else
	 {
	  now=new cell;
	  cout<<"������� ����� ��������"<<endl;
	  cin.ignore();
	  getline(cin , temp);
	  hash_now = f_hash(temp);
	  now->next = table[hash_now].next;
	  table[hash_now].next = now;
	  table[hash_now].hash = hash_now;
	  now->hash = hash_now;
	  now->data.phone_number = temp;
	  cout<<"������� ���"<<endl;
	  cin.ignore(0);
	  getline(cin , now->data.fio);
	  cout<<"������� �����"<<endl;
	  cin.ignore(0);
	  getline(cin , now->data.address);
	 }
   }
  string s_num;
  int s_hash;
  while(1)
   {cout<<endl<<"������ �������� �� �����? 1/0"<<endl;
    cin>>trig;
    if(trig == 0)
     {break;}
    else
     {cout<<"������� ������� �����"<<endl;
	  cin.ignore();
	  getline(cin , s_num);
      s_hash = f_hash(s_num);
      search(s_hash , s_num);}}
  return 0;
 }
