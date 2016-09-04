/*********************************************
* file:	~\tnd004\lab\lab4b\graph.h           *
* remark:implementation of undirected graphs *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Graph::Graph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Graph::~Graph()
{
    delete[] array;
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
    array[v].insert(u, w);
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
    array[v].remove(u);
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const
{
    int s = 1;
    for(int i = 1; i <= size; ++i)
    {

        dist[i] = INFINITY;
        path[i] = 0;
        done[i] = false;
    }

    dist[s] = 0;
    done[s] = true;

    int v = s;

    while (true)
    {

        Node* n = array[v].getFirst();

        while(n)
        {
            int u =  n->vertex;
            int w = n->weight;
            if(!done[u] && dist[u]>dist[v]+w)
            {

                dist[u] = dist[v] + w;
                path[u] = v;
            }
            n = array[v].getNext();
        }

        int smallest = INFINITY;
        int shortest = 0;
        for(int j = 1; j <= size; ++j)
        {
            if (dist[j] < smallest && done[j] != true)
            {
                smallest = dist[j];
                shortest = j;
            }

        }
        if( smallest == INFINITY) break;

        v = shortest;//find smallest distance
        done[v] = true;
    }
}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{
    new Node n = array.getFirst();
    int e = 1;
    Heap H;
    DSets D(n);

    H.Heap(e);
    int counter = 0;
    while(counter < n-1){

        n = H.deleteMin();
        if(D.find(u) != D.find(v)){

            D.join(D.find(u) , D.find(v));
            counter++;
        }


    }
}

// print graph
void Graph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                                            " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}
