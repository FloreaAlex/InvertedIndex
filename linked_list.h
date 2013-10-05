//Florea Alexandru - Ionut
//313CA

#ifndef __LL_H_
#define __LL_H_

#include <stdio.h>
#include <string.h>

template<typename T> struct list_elem {
    T info;
    struct list_elem<T> *next, *prev;
};

template <typename T> class LinkedList 
{
	public:

		  struct list_elem<T> *pfirst, *plast;
		  
		/**constructor*/
        LinkedList()
        {
            pfirst = plast = NULL;
        }

		/**adauga un nod la inceputul listei*/	
        void addFirst(T x) 
        {
            struct list_elem<T> *paux;

            paux = new struct list_elem<T>;
            memcpy(&(paux->info), &x, sizeof(T));
            paux->prev = NULL;
            paux->next = pfirst;

            if (pfirst != NULL) pfirst->prev = paux;
            pfirst = paux;

            if (plast == NULL) plast = pfirst;
        }

		/**adauga un nod la sfarsitul listei*/
        void addLast(T x) 
        {
            struct list_elem<T> *paux;

            paux = new struct list_elem<T>;
            memcpy(&(paux->info), &x, sizeof(T));
            paux->prev = plast;
            paux->next = NULL;

            if (plast != NULL) 
            	plast->next = paux;
            	
            plast = paux;
            
            if (pfirst == NULL) 
            	pfirst = plast;
        }

		/**sterge nodul de la pointerul primit ca parametru*/
        void removeNode(struct list_elem<T> *p) 
        {
            if (p != NULL) 
            {
                if (p->prev != NULL)
                    p->prev->next = p->next;
                    
                if (p->next != NULL)
                    p->next->prev = p->prev;

                if (p->prev == NULL) // p == pfirst
                    pfirst = p->next;

                if (p->next == NULL) // p == plast
                    plast = p->prev;

                delete p;
            }
        }
        
        /**verifica daca lista este goala*/
        bool isEmpty() {
            return (pfirst == NULL);
        }
};
#endif
