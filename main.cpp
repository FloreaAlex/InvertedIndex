//Florea Alexandru - Ionut
//313CA

#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>

#include "hash_table.h"

#define MAX_LOAD_FACTOR 0.7

/**Functia de hash*/
unsigned int hashFunction(char *key)
{
	unsigned int hash = 5381;


	for (unsigned i=0;i<strlen(key);i++)
		hash = ((hash << 5) + hash) + (int)key[i];

	return hash;
}

/**Functie care intersecteaza doua liste inlantuite sortate*/
SortedLinkedList *intersection(SortedLinkedList *SLL1, SortedLinkedList *SLL2)
{
	SortedLinkedList *aux = new SortedLinkedList;
	struct list_elem<char*> *p1, *p2;
	p1 = SLL1->ll.pfirst;
	p2 = SLL2->ll.pfirst;
	while(p1 && p2)
	{
		if(strcmp(p1->info, p2->info) == 0)
		{
			aux->ll.addLast(strdup(p1->info));
			p1 = p1->next;
			p2 = p2->next;
		}
		else if(strcmp(p1->info, p2->info) < 0)
		{
			p1 = p1->next;
		}
		else if(strcmp(p1->info, p2->info) > 0)
		{
			p2 = p2->next;
		}
	}
	return aux;
}

/**Funtie care creaza un nou hashtable si adauga cheile si valorile din vechiul
  *hashtable in cel nou*/
Hashtable *createNewHashtable(Hashtable *H, int HMAX)
{
	Hashtable *newH = new Hashtable(2 * HMAX, hashFunction);
	for(int i = 0; i < HMAX; i++)
	{
		struct list_elem<struct elem_info> *p;
		p = H->H[i].pfirst;
		while(p != NULL)
		{
			newH->putKeyAndList(p->info.key, p->info.sites);
			p = p->next;
		}
	}
	return newH;
}


int main()
{
	int HMAX = 10;
	double loadFactor = 0.0; 
	int nrElem = 0;
	Hashtable *H = new Hashtable(HMAX, hashFunction);
	char line[10000];
	
	/**citesc cate o linie si interpretez cuvintele continute in ea*/
	while(fgets(line, 10000, stdin) != NULL)
	{
		char *p = strtok(line, " \n\t");
		
		if(p == NULL)
			break;
			
		if(strcmp(p, "PUT") == 0)
		{
			char *site = strtok(NULL, " \n\t");
			char *word = strtok(NULL, " \n\t");
			while(word)
			{
				loadFactor = nrElem / HMAX;
				
				/**verifica daca s-a depasit factorul de incarcare, caz in care
				  *creaza altul nou*/
				if(loadFactor <= MAX_LOAD_FACTOR)
				{
					H->put(word, site);
					nrElem ++;
				}
				
				else
				{
					H = createNewHashtable(H, HMAX);
					H->put(word, site);
					HMAX *= 2;
					nrElem ++;
				}
				word = strtok(NULL, " \n\t");
			}
		}
		
		else if(strcmp(p, "GET") == 0)
		{
			bool ok1 = false;
			bool ok2 = false;	
			bool ok3 = false;
			bool ok4 = false;
			
			/**citesc primele doua cuvinte si intersectez siturile aferente lor;
			  *in cazul in care exista un singur cuvant afisez siturile acestuia*/
			char *word1 = strtok(NULL, " \n\t");
			char *word2 = strtok(NULL, " \n\t");
			SortedLinkedList *res = new SortedLinkedList;
			if(word2 == NULL)
			{
				ok1 = true;
				H->get(word1)->print();
			}
			else				
			{	
				/**in cazul in care cuvintele nu se afla in hashtable afisez
				  *SITE_NOT_FOUND*/
				if(H->hasKey(word1) && H->hasKey(word2))
					res = intersection(H->get(word1), H->get(word2));
				else
				{
					ok2 = true;
					printf("SITE_NOT_FOUND\n");
				}
				
				char *word = strtok(NULL, " \n\t");
				while(word)
				{
					if(H->hasKey(word))
					{
						if(!res->ll.isEmpty())
							res = intersection(res, H->get(word));
						/**in cazul in care dupa intersectii multimea siturilor
						  *vida afisez SITE_NOT_FOUND*/
						else
						{
							ok3 = true;
							printf("SITE_NOT_FOUND\n");
							break;
						}
					}
					else
					{
						ok4 = true;
						printf("SITE_NOT_FOUND\n");
						break;
					}
					word = strtok(NULL, " \n\t");
				}
				
			}
			/**daca se reuseste toate intersectiile se afiseaza multimea de
			  *de situri*/
			if(!res->ll.isEmpty() && !ok1 && !ok2 && !ok3 && !ok4)
				res->print();
			else if(!ok1 && !ok2 && !ok3 && !ok4)
				printf("SITE_NOT_FOUND\n"); 
		}
		
		/**se verifica daca situl contine toti termenii si se afiseaza mesajul
		  *corespunzator*/
		else if(strcmp(p, "SITE") == 0)
		{
			bool ok = true;
			char *site = strtok(NULL, " \n\t");
			char *word = strtok(NULL, " \n\t");
			while(word)
			{
				if(!H->hasSite(word, site))
				{
					ok = false;
					break;
				}
				word = strtok(NULL, " \n\t");	
			}
			if(ok)
				printf("WORD_FOUND\n");
			else
				printf("WORD_NOT_FOUND\n");
		}
			
	}
	return 0;
}










