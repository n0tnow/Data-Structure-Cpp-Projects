#include <iostream>
#include <string>

#define SIZE 5

using namespace std;


class Node
{
	public:
		int key;
		string value;
		Node *next;
		Node()
		{
			key = 0;
			value = "";
			next = NULL;
		}
	
};

class HashTable
{
	public:
		Node *dizi [SIZE];
		
		HashTable()
		{
			for(int i; i<SIZE; i++)
			{
				dizi[i] = new Node();		
			}
			cout<<"Tablo yapisi hazirlandi."<<endl;
			
		}
		
		int indexUret(int key)
		{
			return key %SIZE;
		}
		
		void ekle()
		{
			cout<<"Ekleme Islemi..."<<endl;
			
			Node *eleman = new Node();
			cout<<"Key: ";cin>>eleman ->key;
			cout<<"Value: ";cin>>eleman ->value;
			
			int index = indexUret(eleman->key);
			Node *temp = dizi[index];
			
			while(temp->next != NULL)
			temp = temp->next;
			
			temp->next = eleman ;
			cout<<"Eleman Eklendi.."<<endl;
			
		}
		
		void yazdir()
		{
			cout<<"Yazdirma Islemi..."<<endl;
			
			for(int i; i < SIZE ; i++)
			{
				Node *temp = dizi[i];
				cout<<"\nDizi ["<<i<<"] -> ";
				while(temp->next != NULL)
				{
					temp = temp->next;
					cout<<temp->key<<" : "<<temp->value<<" -> ";
				}
			}
		}
};

int main()
{
	HashTable ht;
	
	ht.ekle();
	ht.ekle();
	ht.ekle();
	
	ht.yazdir();
}