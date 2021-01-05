#ifndef LISTA_H_
#define LISTA_H_

namespace UndavList{
	struct List;

	List* CreateListEmpty();
	List* Create(void* elements[], int countItems);
	List* Create(const List* elements);

	void Add(List* list, void* item);
	void AddToBegin(List* list, void* item);
	void AddToEnd(List* list, void* item);

	void* RemoveFirst(List* lista);
	void* RemoveLast(List* lista);
	void RemoveItem(List* list, void *item);

	bool IsEmpty(const List* lista);
	int Count(const List* lista);

	void Destroy(List* list);
	//Primitivas para procesamiento secuencial
	namespace IteratorListitems{
		struct Iterator;
		Iterator* Begin(List* list);
		bool IsTheEnd(Iterator* iterator);
		void Next(Iterator* iterator);
		void* ObtainsItem(Iterator* iterator);
		void Destroy(Iterator* iterator);
	}
}

#endif
