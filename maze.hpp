//
//  maze.hpp
//  Project5
//
//  Created by Thomas Campion on 3/14/18.
//  Copyright © 2018 Thomas Campion. All rights reserved.
//

#ifndef maze_hpp
#define maze_hpp

#include <stdio.h>

// Sample solution for project #5

#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>
#include <boost/graph/adjacency_list.hpp>

#include "d_except.h"
#include "matrix.h"
#include "main.cpp"

#define LargeValue 99999999

using namespace std;


class maze
{
public:
    maze(ifstream &fin);
    void print(int,int,int,int);
    bool isLegal(int i, int j);
    void findShortestPathBFS(Graph &g);
    void findPathInList(int const &startNode, int const &endNode, int* &parent);
    void mapMazeToGraph(Graph &g);
    void findPathDFSRecursive(Graph &g,Graph::vertex_descriptor start, Graph::vertex_descriptor goal );
    void findPathDFSStack(Graph &g);
    void printPath(Graph::vertex_descriptor end,
                   stack<Graph::vertex_descriptor> &s,
                   Graph g);
    void relax(Graph &g, Grpah::vertex_descriptor u, Graph::vertex_descriptor v);
    bool dijkstra(Graph &g, Graph::vertex_descriptor s);
    bool bellmanFord(Graph &g, vertex descriptor s);
    int numRows(){return rows;};
    int numCols(){return cols;};

private:
    int rows; // number of rows in the maze
    int cols; // number of columns in the maze12 a

    stack<Graph::vertex_descriptor> DFS;
    stack<Graph::vertex_descriptor> moves;
    stack<Graph:: vertex_descriptor> BFshortestPath;
    queue<Graph::vertex_descriptor> BFS;

    matrix<bool> value;
    matrix<Graph:: vertex_descriptor> graphM;//  matrix for vertex descriptors
};


#endif /* maze_hpp */
