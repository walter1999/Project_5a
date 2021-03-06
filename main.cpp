//
//  main.cpp
//  Project5
//
//  Created by Thomas Campion on 3/14/18.
//  Copyright © 2018 Thomas Campion. All rights reserved.
//


#include <iostream>
#include <limits.h>
#include <vector>
#include <list>
#include <fstream>
#include <queue>

#include <boost/graph/adjacency_list.hpp>

#include "maze.hpp"
#include "heapV.h"

using namespace boost;
using namespace std;

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;
typedef Graph::vertex_descriptor Vertex;
typedef Graph::edge_descriptor Edge;
typedef Graph::edge_iterator edge_iterator;
typedef Graph::vertex_iterator vertex_iterator;
typedef Graph::adjacency_iterator adj_iterator;

struct VertexProperties // properties associated with a node
{
    pair<int,int> cell; // maze cell (x,y) value
    Graph::vertex_descriptor pred; // predecessor node
    int weight;// weight
    bool visited;// has it been visited.True= it was, false= it was not
    bool marked;// marked or not. Part of the path or not
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
    int weight;// cost for this edge
    bool visited;// true=it was, false=it was not
    bool marked;// part of the path
};

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

// typedef property<edge_weight_t, int> EdgeProperty;

#define LargeValue 99999999

void clearVisited(Graph &g)
// Mark all nodes in g as not visited.

void setNodeWeights(Graph &g, int w)
// Set all node weights to w.

void clearMarked(Graph &g)

int main()
{
    try
    {
        ifstream fin;

        // Read the maze from the file.
        string fileName = "yourpath/maze1.txt";

        fin.open(fileName.c_str());
        if (!fin)
        {
            cerr << "Cannot open " << fileName << endl;
            exit(1);
        }

        maze m(fin);
        fin.close();

        m.print(m.numRows()-1,m.numCols()-1,0,0);// prints the graph

        Graph g;
        m.mapMazeToGraph(g);// fucntion call

        cout << g << endl;// calls overloaded operator
        
    }
}
