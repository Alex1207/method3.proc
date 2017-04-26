#include "stdafx.h"
#include "container.h"
#include "animal.h"
#include "iostream"
#include <fstream>

using namespace std;
void Init(container &c)
{
	c.kol = 0;
	c.n = 10;
	c.mas = new node*[c.n];
	for (int i = 0; i < c.n; i++)
	{
		c.mas[i] = NULL;
	}
}
void Del(container &c)
{
	for (int i = 0; i<c.n; i++)
	{
		while (c.mas[i] != NULL)
		{
			node* vn = c.mas[i]->next;
			delete c.mas[i];
			c.mas[i] = vn;
		}
	}
}
void In(container &c, ifstream & f1)
{	
	f1 >> c.kol;
	for (int i = 0; i<c.kol; i++)
	{
		animal Animal;
		Animal = InAnimal(f1);
		int sum = 0;
		sum = SumElementsOfString(Animal, c.n);
		if (c.mas[sum] == NULL)
		{
			c.mas[sum] = new node;
			c.mas[sum]->next = NULL;
			c.mas[sum]->Animal = Animal;
		}
		else
		{
			node* vn = new node;
			vn->next = c.mas[sum];
			vn->Animal = Animal;
			c.mas[sum] = vn;
		}
	}	
}
void Out(container c, ofstream & f2)
{
	for (int i = 0; i<c.n; i++)
	{
		cout << "\n" << i << "\n";
		if (c.mas[i] != NULL)	//There is no need to check this condition.
		{
			node* vn = c.mas[i];
			while (vn)
			{
				OutAnimal(vn->Animal, f2);
				vn = vn->next;
			}
		}
	}
}
void Sort(container &c)
{
	for (int k = 0; k<c.n; k++)
	{
		int koli = 0;
		node* prev;
		node* Node = c.mas[k];
		while(Node)
		{
			Node = Node->next;
			koli++;
		}
		for(int i = 0; i < koli - 1; i++) 
		{
			node* prev; //There is no need to do this
			Node = c.mas[k];
			for(int j = i + 1; j < koli; j++) 
			{
				if(Less(Node->Animal, Node->next->Animal))
				{
					node* next = Node->next;
					Node->next = Node->next->next;
					next->next = Node;
					if(Node == c.mas[k])
					{
						c.mas[k] = next;
						prev = next;
					}
					else
					{
						prev->next = next;
						prev = next;
					}
				}
				else 
				{
					prev = Node;
					Node = Node->next;
				}
			}
		}
	}
}
// Alternative: in this function is no need to create a variable koli, it can sort, so far it's possible.
//void Sort(container &c)
//{
//	for (int k = 0; k<c.n; k++)
//	{
//		bool flag = true;
//		node* prev;
//		node* Node = c.mas[k];
//		while(flag)
//		{
//			//node* prev;
//			flag = false;
//			Node = c.mas[k]; 
//			while(Node)
//			{
//				if(Node->next == NULL)
//					break;
//				if(Less(Node->Animal, Node->next->Animal))
//				{
//					node* next = Node->next;
//					Node->next = Node->next->next;
//					next->next = Node;
//					if(Node == c.mas[k])
//					{
//						c.mas[k] = next;
//						prev = next;
//					}
//					else
//					{
//						prev->next = next;
//						prev = next;
//					}
//					flag = true;
//				}
//				else 
//				{
//					prev = Node;
//					Node = Node->next;
//				}
//			}
//		}
//	}
//}

void OutOnlyFish(container c, ofstream & f2)
{
	cout << "\n\n������ �����:\n";
	f2 << "\n\n������ �����:\n";
	for (int i = 0; i<c.n; i++)
	{
		//cout << "\n" << i << "\n";
		if (c.mas[i] != NULL)	//There is no need to check this condition.
		{
			node* vn = c.mas[i];
			while (vn)
			{
				if (vn->Animal.key == FISH)
					OutAnimal(vn->Animal, f2);
				else
				{
					cout << endl;
					f2 << endl;
				}
				vn = vn->next;
			}
		}
	}
}

//This function belongs to container.
//int SumElementsOfString(animal Animal, int n)
//{
//	string str = Animal.name;
//	int sum = 0;
//	for (int i = 0; i < str.length(); i++)
//	{
//		sum = (sum + (unsigned char)str[i])%n;
//	}
//	return sum;
//}