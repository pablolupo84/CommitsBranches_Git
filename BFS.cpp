#include "BFS.h"
#include "CommitGraph.h"
#include "Cola.h"
#include "Commit.h"
#include "Lista.h"
#include "CommitBag.h"

using UndavCola::Cola;
using namespace UGitCommitGraph::AdyacencyListIterator;
using UGit::Commit;
using UndavList::List;
using UGitCommitGraph::NodeVertex;

using UBfs::RecorridoAnchura;

struct visitedCommit{
	string hashCode;
	bool visited;
};

struct UBfs::RecorridoAnchura {
	int countVertex;
	const UGitCommitGraph::CommitGraph* graph;
	Function visit;
	UndavList::List* myLista;
};

bool* InitVisited(int countVertex){
	bool* visited=new bool[countVertex];
	for(int i=0;i<countVertex;i++){
		visited[i]=false;
	}
	return visited;
}

void MarkInArray(RecorridoAnchura* recorrido, UGitCommitGraph::NodeVertex* vertex) {
	visitedCommit* item = new visitedCommit;
	item->hashCode=UGitCommitGraph::GetHashCode(vertex);
	item->visited=true;
	UndavList::Add(recorrido->myLista,item);
}

bool MarkedInArrayBool(RecorridoAnchura* recorrido,UGitCommitGraph::NodeVertex* vertex) {
	UndavList::IteratorListitems::Iterator* iterador= UndavList::IteratorListitems::Begin(recorrido->myLista);
	string myHashcode=UGitCommitGraph::GetHashCode(vertex);
	bool isFound=false;
	while(!UndavList::IteratorListitems::IsTheEnd(iterador) && isFound==false){
		visitedCommit* item=(visitedCommit*)UndavList::IteratorListitems::ObtainsItem(iterador);
		if(myHashcode==item->hashCode){
			isFound=true;
		}else{
			UndavList::IteratorListitems::Next(iterador);
		}
	}
	return isFound;
}

void BFS(UGitCommitGraph::CommitGraph * grafo, RecorridoAnchura* recorrido,UGitCommitGraph::NodeVertex* verticeOrigenRecorrido){
	UndavCola::Cola* cola = UndavCola::CrearCola();
	UndavCola::Encolar(cola,verticeOrigenRecorrido);
	MarkInArray(recorrido, verticeOrigenRecorrido);

    while(!UndavCola::EstaVacia(cola)){
    	UGitCommitGraph::NodeVertex* verticeAVisitar = (UGitCommitGraph::NodeVertex*) UndavCola::Desencolar(cola);
    	IteratorCommitGraph* iterador = UGitCommitGraph::AdyacencyListIterator::Begin(grafo,UGitCommitGraph::GetHashCode(verticeAVisitar));
    	recorrido->visit(UGitCommitGraph::GetCommit(verticeAVisitar));
    	while(!UGitCommitGraph::AdyacencyListIterator::End(iterador)) {
    		UGit::Commit * item=UGitCommitGraph::AdyacencyListIterator::Get(iterador);
    		UGitCommitGraph::NodeVertex* verticeAdyacente = UGitCommitGraph::GetVertex(grafo,UGit::GetHashCode(item));
    		if(!MarkedInArrayBool(recorrido, verticeAdyacente)) {
    			UndavCola::Encolar(cola, verticeAdyacente);
    			MarkInArray(recorrido, verticeAdyacente);
            }
            UGitCommitGraph::AdyacencyListIterator::Next(iterador);
        }
        if (iterador != NULL) UGitCommitGraph::AdyacencyListIterator::Destroy(iterador);
    }
    UndavCola::Destruir(cola);
}

RecorridoAnchura* UBfs::Crear(UGitCommitGraph::CommitGraph* graph, Commit* start, Function visitar){
	RecorridoAnchura* bfs = new RecorridoAnchura;
	bfs->visit = visitar;
	bfs->countVertex =  UGitCommitGraph::CountVertex(graph);
	bfs->graph=graph;
	bfs->myLista=UndavList::CreateListEmpty();

	//UGitCommitGraph::print(graph);
	string hashCode = UGit::GetHashCode(start);

	UGitCommitGraph::NodeVertex* verticeComienzo = (UGitCommitGraph::NodeVertex*)UGitCommitGraph::GetVertex(graph,hashCode);
    if (verticeComienzo) {
    	BFS(graph, bfs, verticeComienzo);
	}
    return bfs;
}

void DestruirCommit (void * commit) {
    UGit::DestroyCommit((Commit *) commit);
}

void UBfs::Destruir(RecorridoAnchura* recorrido){
    delete recorrido;
}

