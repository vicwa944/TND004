/*********************************************
* file:	~\tnd004\lab\lab4a\digraph.cpp       *
* remark: mplementation of directed graphs   *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "digraph.h"
#include "queue.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Digraph::Digraph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    dist  = new int [n + 1];
    path  = new int [n + 1];
    done  = new bool[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Digraph::~Digraph()
{
    delete[] array;
    delete[] dist;
    delete[] path;
    delete[] done;
}

// -- MEMBER FUNCTIONS

// insert directed edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Digraph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
}

// remove directed edge (u, v)
void Digraph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
}

// unweighted single source shortest paths
void Digraph::uwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    Queue<int> Q;

    for (int i = 1; i <= size; ++i){

        dist[i] = INFINITY;
        path[i] = 0;
    }

    dist[s] = 0;

    Q.enqueue(s);

    while(!Q.isEmpty()){

        int v = Q.getFront();
        Q.dequeue();

        Node* n = array[v].getFirst();
        while(n) {
           int u =  n->vertex;
            n->weight;
             if(dist[u] == INFINITY){

                dist[u] = dist[v]+1;
                path[u] = v;
                Q.enqueue(u);
            }
            n = array[v].getNext();
        }
    }
}

// positive weighted single source shortest pats
void Digraph::pwsssp(int s)
{
    if (s < 1 || s > size)
    {
        cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
        return;
    }

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

// print graph
void Digraph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                  " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}

// print shortest path tree for s
void Digraph::printTree() const
{
    cout << "----------------------" << endl;
    cout << "vertex    dist    path" << endl;
    cout << "----------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " :" << setw(8) << dist[v] << setw(8) << path[v] << endl;
    }

    cout << "----------------------" << endl;
}

void Digraph::printHelp(int i) const{


    if(i == 0)
        return;

    printHelp(path[i]);
    cout << i;

}

// print shortest path from s to t
void Digraph::printPath(int t) const
{
    if (t < 1 || t > size)
    {
         cout << "\nERROR: expected target t in range 1.." << size << " !" << endl;
         return;
    }



        printHelp(t);
        cout << "(" <<dist[t] << ")" <<endl;



}
