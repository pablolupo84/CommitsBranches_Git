#ifndef COMMITGRAPH_H_
#define COMMITGRAPH_H_

#include "Commit.h"
using UGit::Commit;

namespace UGitCommitGraph{
	struct CommitGraph;
	struct NodeVertex;

	// Precondicion: Ninguna
	// Postcondicion: Crear un grafo vacio
	CommitGraph* Create();

	// Precondicion: @graph, @source y @destination son instancias validas
	// Postcondicion: Si @source y @destination ya estan conectados no realiza ningun accion.
	// Si @source y @destintion no estan conectados realiza una conexion directa (no conmutativa) con origen en @source y destino en @destination
	void Connect(CommitGraph* graph, Commit* source, Commit* destination);

	// Precondicion: @graph, @source y @destination son instancias validas
	// Postcondicion: Devuelve true si @source es adyacente a @destination
	bool AreConnected(CommitGraph* graph, Commit* source, Commit* destination);

	// Precondicion: @graph es instancia valida.
	// Postcondicion: Devuelve la cantidad de vertices del grafo.
	int CountVertex(const CommitGraph* graph);

	void print(CommitGraph* graph);
	//void* GetVertex(CommitGraph* graph, string commitHashCode);
	NodeVertex* GetVertex(CommitGraph* graph, string commitHashCode);

	string GetHashCode(NodeVertex* vertex);

	Commit* GetCommit(NodeVertex* vertex);

	namespace AdyacencyListIterator{
		struct IteratorCommitGraph;
		IteratorCommitGraph* Begin(CommitGraph* graph, string commitHashCode);
		bool End(const IteratorCommitGraph* iterator);
		Commit* Get(IteratorCommitGraph* iterator);
		void Next(IteratorCommitGraph* iterator);
		void Destroy(IteratorCommitGraph* iterador);
	}

	void Destroy(CommitGraph* graph);
}

#endif
