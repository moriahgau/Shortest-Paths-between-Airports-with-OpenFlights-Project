//Psuedocode for BFS Traversal
/*
BFS(graph g_){
    foreach(Vertex v : G.vertices()):
        setLabel(v, UNEXPLORED)
    foreach(Edge e : G.edges()):
        setLabel(e, UNEXPLORED)
    foreach(Vertex v : G.vertices()):
        if getLabel(v) == UNEXPLORED:
        BFS(graph g), v)
}

BFS(graph g_, v){
    Queue q
    setLabel(v, VISITED)
    q.engqueue(v)

    while !q.empty():
        v = q.dequeue()
        foreach (Vertex w : G.adjacent(v)):
            if getLabel(w) == UNEXPLORED:
                setLabel(v, w, DISCOVERY)
                setLabel(w, VISITED)
                q.enqueue(w)
            elseif getLabel(v,w) == UNEXPLORED:
                setLabel(v, w, CROSS)
}







*/