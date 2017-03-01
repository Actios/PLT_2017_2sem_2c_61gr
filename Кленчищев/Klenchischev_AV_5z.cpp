// ��������� �.�. 2�. 61 ��. 
// 5. ������� � trie-������ ������������� ����� � ����� �� ��������� ���������

#include "stdafx.h"
#include <iostream>
#include <cstring>

using namespace std;

struct trie
{
	char key;
	char *value;
	trie *sibling;
	trie *child;
};

trie *createNode();
trie *insertNode(trie *root, char *key, char *value);
void printTrie(trie *root, int lvl);
void findWords(trie *root, char *word);
void printValues(trie *list);

int main()
{
	setlocale(LC_ALL, "Russian");
	trie *root = NULL;

	int choice = 1;
	while (choice) {
		cout << endl << "�������� ��������: " << endl;
		cout << "0. �����" << endl;
		cout << "1. �������� �����" << endl;
		cout << "2. ������� ������" << endl;
		cout << "3. ����� ����� � ������ �� ���������" << endl;

		cin >> choice;

		switch (choice) {
		case 1: {
			cout << "������� �����: ";
			char word[64];
			cin >> word;
			char value[64];
			strcpy_s(value, word);
			for (int i = 0, l = strlen(word); i < l / 2; i++) {
				char c = word[i];
				word[i] = word[l - i - 1];
				word[l - i - 1] = c;
			}
			root = insertNode(root, word, value);
			break;
		}
		case 2: {
			cout << "������: " << endl;
			printTrie(root, 0);
			break;
		}
		case 3: {
			cout << "������� ���������:";
			char word[64];
			cin >> word;
			findWords(root, word);
			break;
		}
		default: {
			choice = 0;
			break;
		}
		}
	}
	return 0;
}

trie *createNode() {
	trie *node = new trie;
	node->key = NULL;
	node->value = NULL;
	node->sibling = NULL;
	node->child = NULL;

	return node;
}

trie *insertNode(trie *root, char *word, char *value) {
	trie *node = NULL, *parent, *list;
	parent = NULL;
	list = root;

	for (; *word != '\0'; word++) {
		for (node = list; node != NULL; node = node->sibling) {
			if (node->key == *word)
				break;
		}
			
		if (node == NULL) {
			node = createNode();
			node->key = *word;
			node->sibling = list;
			if (parent != NULL)
				parent->child = node;
			else
				root = node;
			list = NULL;
		}
		else
			list = node->child;

		parent = node;
	}

	node->value = _strdup(value);
	return root;
}

void printTrie(trie *root, int lvl) {
	trie *node;
	for (node = root; node != NULL; node = node->sibling) {
		for (int i = 0; i < lvl; i++)
			cout << " ";

		cout << node->key;
		if (node->value != NULL)
			cout << "-" << node->value;
		cout << endl;

		if (node->child != NULL)
			printTrie(node->child, lvl + 1);
	}

	cout << endl;
}

void findWords(trie *root, char *word) {
	trie *node = NULL, *list = root, *parent = NULL;

	for (int i = 0, l = strlen(word); i < l / 2; i++) {
		char c = word[i];
		word[i] = word[l - i - 1];
		word[l - i - 1] = c;
	}

	while (*word != '\0') {
		for (node = list; node != NULL; node = node->sibling)
			if (node->key == *word)
				break;

		if (node == NULL) {
			cout << "��� ���� � ����� ����������" << endl;
			return;
		}
		parent = list;
		list = node->child;
		word++;
	}

	if (parent->value != NULL)
		cout << parent->value << endl;

	printValues(list);
}

void printValues(trie *list) {
	trie *node;
	for (node = list; node != NULL; node = node->sibling) {
		if (node->value != NULL)
			cout << node->value << endl;
		if (node->child != NULL)
			printValues(node->child);
	}
}