//Florea Alexandru - Ionut
//313CA

#pragma once

#include <iostream>
#include <cstring>

#include "linked_list.h"
#include "sorted_linked_list.h"

using namespace std;

struct elem_info 
{
    char *key;
    SortedLinkedList *sites; 
};

class Hashtable 
{
	private:
		int HMAX;
      unsigned int (*hash) (char*);
      
	public:
		LinkedList<struct elem_info> *H;
      			
   	Hashtable(int hmax, unsigned int (*h) (char*)) 
     	{
        	HMAX = hmax;
         hash = h;
         H = new LinkedList<struct elem_info>[HMAX];
		}

		/**Metoda care adauga in hashtable cheia si valoarea aferenta ei*/
		void put(char *key, char *value) 
		{
		   struct list_elem<struct elem_info> *p;
		   struct elem_info info;

		   unsigned int hkey = hash(key) % HMAX;
		   p = H[hkey].pfirst;

			while (p != NULL) 
			{
		     	if (strcmp(p->info.key, key) == 0)
		      	break;
		      p = p->next;
		   }

		   if (p != NULL)
	     		p->info.sites->addElement(strdup(value));         
		    
		   else 
			{
		     	info.key = strdup(key);
		     	info.sites = new SortedLinkedList;
		      info.sites->addElement(strdup(value));
		      H[hkey].addLast(info);
		   }
      }
      
      /**Metoda care adauga in hashtable cheia si lista de valori aferente ei*/
      void putKeyAndList(char *key, SortedLinkedList *list)
      {
			unsigned int hkey = hash(key) % HMAX;
		   struct elem_info info;
		   	
		   info.key = strdup(key);
		   info.sites = list;
		   H[hkey].addLast(info);
      }
      
      /**Metoda care intoarce lista de situri aferenta cheii key*/
		SortedLinkedList *get(char* key) 
		{
        	struct list_elem<struct elem_info> *p;

         unsigned int hkey = hash(key) % HMAX;
         p = H[hkey].pfirst;
           	
         while (p != NULL) 
         {
          	if (strcmp(p->info.key, key) == 0) 
					break;
        		p = p->next;
         }

        	if (p != NULL)
            return p->info.sites;
         else 
			{
          	cout << "Error 101 - The key does not exist\n";
            return NULL;
         }
     	}

		/**Metoda care verifica daca o cheie se afla in hashtable*/
		bool hasKey(char* key) 
		{
      	struct list_elem<struct elem_info> *p;

         unsigned int hkey = hash(key) % HMAX;
         p = H[hkey].pfirst;

         while (p != NULL) 
			{
 	        if (strcmp(p->info.key, key) == 0)
 	      	  break;
           p = p->next;
         }

         if (p != NULL)
         	return true;
         else
            return false;
      }
      
      /**Metoda care verifica daca un site se afla in lista de situri a cheii*/
      bool hasSite(char *key, char *site)
      {
      	struct list_elem<struct elem_info> *p;
      	struct list_elem<char*> *pinfo;
         unsigned int hkey = hash(key) % HMAX;
         p = H[hkey].pfirst;
         
         while(p != NULL)
         {
         	if(strcmp(key, p->info.key) == 0)
         		break;
         	p = p->next;
         }
         
         if(p != NULL)
         	pinfo = p->info.sites->ll.pfirst;
         else
         	return false;
         	
        	while(pinfo != NULL)
         {
         	if(strcmp(site, pinfo->info) == 0)
         		break;
         	pinfo = pinfo->next;
         }
         
         if (pinfo != NULL)
         	return true;
         else
            return false;
      }
      	     
};





			
