#include <iostream>
#include "Lista.h"

using std::cout;
using std::endl;
using UndavList::List;

struct Nodo{
	void* item;
	Nodo* next;
};

struct UndavList::List{
	Nodo* first;
	Nodo* last;
	int countElements;
};

Nodo* CreateNodo(void* Item, Nodo* next);

List* UndavList::CreateListEmpty(){
	List* list = new List;
	list->first = list->last = NULL;
	list->countElements = 0;
	return list;
}

List* UndavList::Create(const List* elements){
	List* list=CreateListEmpty();
	Nodo *iterator=elements->first;
	while(iterator!=NULL){
		AddToEnd(list, iterator->item);
		list->countElements++;
		iterator=iterator->next;
	}
	return list;
}

List* UndavList::Create(void* elements[], int countItems){
	List* list=CreateListEmpty();
	for(int i=0;i<countItems;i++){
		list->countElements++;
		AddToEnd(list,elements[i]);
	}
	return list;
}

void UndavList::Add(List* list, void* item){
	AddToEnd(list, item);
}

void UndavList::AddToBegin(List* list, void* item){
	list->first = CreateNodo(item, list->first);
	list->countElements++;
}

void UndavList::AddToEnd(List* list, void* item){
	Nodo* newLastNode = CreateNodo(item, NULL);
	if(IsEmpty(list)){
		list->first = newLastNode;
	}else{
		list->last->next = newLastNode;
	}
	list->last = newLastNode;
	list->countElements++;
}

bool UndavList::IsEmpty(const List* list){
	return list->first == NULL;
}

void* UndavList::RemoveFirst(List* list){
	void* item = NULL;
	if(!IsEmpty(list)){
		item = list->first->item;
		Nodo* auxiliar = list->first;
		list->first = auxiliar->next;
		delete auxiliar;
		list->countElements--;
		if(list->countElements==0){
			list->last = NULL;
		}
	}
	return item;
}

void* UndavList::RemoveLast(List* list){
	void* item = NULL;
	if(!IsEmpty(list)){
		item = list->last->item;
		if(Count(list) == 1){
			RemoveFirst(list);
		}else{
			Nodo* iterador = list->first;
			Nodo* anteUltimo = list->first;
			while(anteUltimo->next != list->last){
				anteUltimo = iterador = iterador->next;
			}
			Nodo* ultimoAEliminar = anteUltimo->next;
			anteUltimo->next = NULL;
			list->last = anteUltimo;
			delete ultimoAEliminar;
		}
		list->countElements--;
	}
	return item;
}

void UndavList::RemoveItem(List* list, void *item){
	bool continuar=true;
	Nodo* nodoActual=list->first;
	Nodo* nodoAnterior=NULL;
	while(nodoActual!=NULL && continuar){
		if(nodoActual->item==item){
			if ( nodoActual ==list->first ){
				RemoveFirst(list);
            }
            else if(nodoActual==list->last){
            	RemoveLast(list);
            }else{
            	nodoAnterior->next = nodoActual->next;
            	delete nodoActual;
            }
			list->countElements--;
			continuar=false;
        }else{
        	nodoAnterior = nodoActual;
        	nodoActual = nodoActual->next;
        }
    }
}

int UndavList::Count(const List* list){
	return list->countElements;
}

Nodo* CreateNodo(void* Item, Nodo* siguiente){
	Nodo* nodo = new Nodo;
	nodo->item = Item;
	nodo->next = siguiente;
	return nodo;
}

struct UndavList::IteratorListitems::Iterator{
	Nodo* nodoActual;
};

UndavList::IteratorListitems::Iterator* UndavList::IteratorListitems::Begin(List* list){
	Iterator* iterator = new Iterator;
	iterator->nodoActual= list->first;
	return iterator;
}

bool UndavList::IteratorListitems::IsTheEnd(Iterator* iterator){
	return iterator->nodoActual == NULL;
}

void UndavList::IteratorListitems::Next(Iterator* iterator){
	if(!IsTheEnd(iterator)){
		iterator->nodoActual = iterator->nodoActual->next;
	}
}

void* UndavList::IteratorListitems::ObtainsItem(Iterator* iterator){
	void* item = NULL;
	if(!IsTheEnd((iterator))){
		item = iterator->nodoActual->item;
	}
	return item;
}

void UndavList::IteratorListitems::Destroy(Iterator* iterator){
	if(iterator!=NULL){
		delete iterator;
	}
}

void UndavList::Destroy(List* list){
	Nodo* iterator = list->first;
	while(iterator!=NULL){
		Nodo* auxiliar = iterator;
		iterator = iterator->next;
		delete auxiliar;
	}
	delete(list);
}
