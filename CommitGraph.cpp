#include "Commit.h"
#include "CommitGraph.h"
#include "CommitBag.h"
#include "Lista.h"
#include <iostream>

using namespace UGitCommitGraph;
using UGit::CommitBag;
using UGit::Commit;
using UGit::UCommitBagIterator::CommitBagIterator;
using UGitCommitGraph::AdyacencyListIterator::IteratorCommitGraph;
using UndavList::List;
typedef UndavList::IteratorListitems::Iterator* Iterator;

struct UGitCommitGraph::NodeVertex{
	UGit::Commit* commit;
	UGit::CommitBag* listAdjacency;
	NodeVertex* next;
};

struct UGitCommitGraph::CommitGraph{
	NodeVertex* listVertex;
	int count;
};

struct VertexIterator{
	NodeVertex* nodo;
};

//FUNCIONES DE ITERACION VERTICAL
VertexIterator* BeginVertexIterator(UGitCommitGraph::CommitGraph* graph);
bool IsEndVertexIterator(VertexIterator* iterator);
void NextVertexIterator(VertexIterator* iterator);
NodeVertex* ObtainsItemVertexIterator(VertexIterator* iterator);
void DestroyVertexIterator(VertexIterator* iterator);
bool cointainsNode(CommitGraph* graph,Commit* commit);

UGitCommitGraph::CommitGraph* UGitCommitGraph::Create(){
	UGitCommitGraph::CommitGraph* newGraph = new UGitCommitGraph::CommitGraph;
	newGraph->listVertex=NULL;
	newGraph->count=0;
	return newGraph;
}

NodeVertex* CreateNode(Commit* source, Commit* destination, NodeVertex* next){
	NodeVertex* node = new NodeVertex;
	node->commit = source;
	node->listAdjacency= UGit::CreateBag();
	if(destination!=NULL){
		UGit::Add(node->listAdjacency,destination);
	}
	node->next=next;
	return node;
}

void UGitCommitGraph::Connect(CommitGraph* graph, Commit* source, Commit* destination){
	NodeVertex* newNodo=NULL;

	if(!cointainsNode(graph,source)){
		newNodo=CreateNode(source,NULL,graph->listVertex);
		graph->listVertex=newNodo;
		graph->count++;
	}
	if(destination!=NULL && !cointainsNode(graph,destination) ){
		newNodo=CreateNode(destination,NULL,graph->listVertex);
		graph->listVertex=newNodo;
		graph->count++;
	}
	if (destination!=NULL && !UGitCommitGraph::AreConnected(graph,source,destination)){
		string HashCodeKey = UGit::GetHashCode(source);
		NodeVertex* item = UGitCommitGraph::GetVertex(graph,HashCodeKey);
		UGit::Add(item->listAdjacency,destination);
	}
}

bool cointainsNode(CommitGraph* graph,Commit* commit){
	string hashCode=UGit::GetHashCode(commit);
	NodeVertex* item=UGitCommitGraph::GetVertex(graph,hashCode);

	return (item!=NULL);
}

bool UGitCommitGraph::AreConnected(CommitGraph* graph, Commit* source, Commit* destination){
	bool areConnected=false;
	string HashCodeKey = UGit::GetHashCode(source);
	IteratorCommitGraph *iterador=UGitCommitGraph::AdyacencyListIterator::Begin(graph,HashCodeKey);
	if (iterador!=NULL){
		while(!UGitCommitGraph::AdyacencyListIterator::End(iterador) && areConnected==false){
			if(HashCodeKey==UGit::GetHashCode(UGitCommitGraph::AdyacencyListIterator::Get(iterador))){
				areConnected=true;
			}
			UGitCommitGraph::AdyacencyListIterator::Next(iterador);
		}
		UGitCommitGraph::AdyacencyListIterator::Destroy(iterador);
	}
	return areConnected;
}

void UGitCommitGraph::Destroy(CommitGraph* graph){
	VertexIterator* vertexIterator=BeginVertexIterator(graph);
	while(!IsEndVertexIterator(vertexIterator)){
		UGit::DestroyBag(vertexIterator->nodo->listAdjacency);
		NodeVertex* auxiliar = vertexIterator->nodo;
		vertexIterator->nodo = vertexIterator->nodo->next;
		delete auxiliar;
	}
	delete graph->listVertex;
	delete graph;
	DestroyVertexIterator(vertexIterator);
}

int UGitCommitGraph::CountVertex(const CommitGraph* graph){
	return graph->count;
}

Commit* UGitCommitGraph::GetCommit(NodeVertex* vertex){
	return vertex->commit;
}

string UGitCommitGraph::GetHashCode(NodeVertex* vertex){
	return UGit::GetHashCode(vertex->commit);
}

struct UGitCommitGraph::AdyacencyListIterator::IteratorCommitGraph{
	CommitBagIterator* iterator;
};

IteratorCommitGraph* UGitCommitGraph::AdyacencyListIterator::Begin(CommitGraph* graph, string commitHashCode){
	IteratorCommitGraph* iterator=NULL;
	NodeVertex* item=(NodeVertex*)GetVertex(graph,commitHashCode);
	if(item!=NULL){
		iterator=new IteratorCommitGraph;
		iterator->iterator=UGit::UCommitBagIterator::Begin(item->listAdjacency);
	}
	return iterator;
}

bool UGitCommitGraph::AdyacencyListIterator::End(const IteratorCommitGraph* iterator){
	return UGit::UCommitBagIterator::IsEnd(iterator->iterator);
}

UGit::Commit* UGitCommitGraph::AdyacencyListIterator::Get(IteratorCommitGraph* iterator){
	return UGit::UCommitBagIterator::GetCommit(iterator->iterator);
}

void UGitCommitGraph::AdyacencyListIterator::Next(IteratorCommitGraph* iterator){
	UGit::UCommitBagIterator::Next(iterator->iterator);
}

void UGitCommitGraph::AdyacencyListIterator::Destroy(IteratorCommitGraph* iterador){
	UGit::UCommitBagIterator::DestroyIterator(iterador->iterator);
}

VertexIterator* BeginVertexIterator(UGitCommitGraph::CommitGraph* graph){
	VertexIterator* iterator = new VertexIterator;
	iterator->nodo=graph->listVertex;
	return iterator;
}

bool IsEndVertexIterator(VertexIterator* iterator){
	return iterator->nodo== NULL;
}

void NextVertexIterator(VertexIterator* iterator){
	if(!IsEndVertexIterator(iterator)){
		iterator->nodo = iterator->nodo->next;
	}
}

NodeVertex* ObtainsItemVertexIterator(VertexIterator* iterator){
	return iterator->nodo;
}

void DestroyVertexIterator(VertexIterator* iterator){
	delete iterator;
}

NodeVertex* UGitCommitGraph::GetVertex(CommitGraph* graph, string commitHashCode){
	VertexIterator* vertexIterator=BeginVertexIterator(graph);
	bool isFound=false;
	NodeVertex* item=NULL;
	NodeVertex* itemResultado=NULL;
	while(!IsEndVertexIterator(vertexIterator) && isFound==false){
		item=ObtainsItemVertexIterator(vertexIterator);
		if(UGit::GetHashCode(item->commit)==commitHashCode){
			itemResultado=item;
			isFound=true;
		}else{
			NextVertexIterator(vertexIterator);
		}
	}
	DestroyVertexIterator(vertexIterator);
	return itemResultado;
}


void UGitCommitGraph::print(CommitGraph* graph){
	VertexIterator* vertexIterator=BeginVertexIterator(graph);
	std::cout<<"Test de Grafo Completo para BFS"<<std::endl;
	std::cout<<"Total Vertex :"<< UGitCommitGraph::CountVertex(graph)<<std::endl;
	while(!IsEndVertexIterator(vertexIterator)){
		NodeVertex* item=ObtainsItemVertexIterator(vertexIterator);
		std::cout<<"V: "<<UGit::GetMessage(item->commit)<<std::endl;
		UGit::UCommitBagIterator::CommitBagIterator* iterador= UGit::UCommitBagIterator::Begin(item->listAdjacency);
		while(!UGit::UCommitBagIterator::IsEnd(iterador)){
			Commit* item=UGit::UCommitBagIterator::GetCommit(iterador);
			std::cout<<"A: "<<UGit::GetMessage(item)<<std::endl;
			UGit::UCommitBagIterator::Next(iterador);
		}
		NextVertexIterator(vertexIterator);
	}
	DestroyVertexIterator(vertexIterator);
}
