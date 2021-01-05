#ifndef BFS_H_
#define BFS_H_

#include "CommitGraph.h"
#include "Commit.h"

namespace UBfs{
    struct RecorridoAnchura;
    typedef void (*Function)(Commit * vertice);
    RecorridoAnchura* Crear(UGitCommitGraph::CommitGraph* graph, Commit * comienzo, Function visitar);
    bool EsAlcanzable(RecorridoAnchura* recorrido, int destino);
    int ObtenerDistanciaCamino(RecorridoAnchura* recorrido, int destino);
    void Destruir(RecorridoAnchura* recorrido);
}

#endif /* BFS_H_ */
