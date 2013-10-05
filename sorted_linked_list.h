//Florea Alexandru - Ionut
//313CA

#pragma once

#include <iostream>
#include <cstring>

#include "linked_list.h"

using namespace std;

class SortedLinkedList /**lista inlantuita sortata*/
{
		
    public:
    	LinkedList<char*> ll;
    	
    	SortedLinkedList() {}
    
    	/**adauga o noua valoare in lista, insa pentru a mentine lista sortata
    	  *trebuie sa caute locul unde trebuie adaugata valoarea*/
        void addElement(char* x) 
        {
            struct list_elem<char*> *p, *paux;

            p = ll.pfirst;
            while (p != NULL && strcmp(p->info, x) <= 0)
            {
            	if(strcmp(p->info, x) == 0)
            		return;
                p = p->next;
            }

            if (p == NULL)
                ll.addLast(strdup(x));
                
            else if(p == ll.pfirst)
            	 ll.addFirst(strdup(x));
            	 
            else 
            {
                paux = new struct list_elem<char*>;
                paux->info = strdup(x);
                paux->next = p;
                paux->prev = p->prev;
	        		 p->prev->next = paux;
                p->prev = paux;
            }
        }
        
        /**verifica daca se afla o valoare in lista*/
        bool hasValue(char *x)
        {
        	struct list_elem<char*> *p =ll.pfirst;
        	while(p != NULL)
        	{
        		if(strcmp(x, p->info) == 0)
        			return true;
        		p = p->next;
        	}
        	return false;
        }
        
		/**afiseaza continutul listei*/
        void print()
        {
        	struct list_elem<char*> *p = ll.pfirst;
        	while(p != NULL)
        	{
        		cout << p->info << " ";
        		p = p->next;
        	}
        	cout << endl;
        }
};












