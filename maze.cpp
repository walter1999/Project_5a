//
//  maze.cpp
//  Project5
//
//  Created by Thomas Campion on 3/14/18.
//  Copyright © 2018 Thomas Campion. All rights reserved.
//

#include "maze.hpp"
#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>
#include "d_except.h"
#include "matrix.h"
#include "heapV.h"



maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
    fin >> rows; // reads rows from file
    fin >> cols; // reads cols from file

    char x; // variable to hodl values

    value.resize(rows,cols); // resize the matrix
    for (int i = 0; i <= rows-1; i++)//  traverse matrix to store bool values
        for (int j = 0; j <= cols-1; j++)
        {
            fin >> x;
            if (x == 'O')// checks to see if spot is empty. Not a wall
                value[i][j] = true;
            else
                value[i][j] = false;// make false if X is detected
        }

}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
    cout << endl;
    // index out of range error
    if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
        throw rangeError("Bad value in maze::print");

    if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
        throw rangeError("Bad value in maze::print");

    for (int i = 0; i <= rows-1; i++)// traverse the graph
    {
        for (int j = 0; j <= cols-1; j++)
        {
            if (i == goalI && j == goalJ)// checks to see if we made it to the end or goal
                cout << "*";
            else
                if (i == currI && j == currJ)// print current location
                    cout << "+";
                else
                    if (value[i][j])// print blank space if there is node
                        cout << " ";
                    else
                        cout << "X";// print x if there is no node
        }
        cout << endl;// print a new line
    }
    cout << endl;// new line
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze, indicating
// whether it is legal to go to cell (i,j).
{
    if (i < 0 || i > rows || j < 0 || j > cols)
        throw rangeError("Bad value in maze::isLegal");

    return value[i][j];// returns the value stored in the matrix
}

void maze::mapMazeToGraph(Graph &g){
// Create a graph g that represents the legal moves in the maze m.
//iterate through the matrix of the maze and checks if its true or false
Graph:: vertex_descriptor Dr;// creates a descriptor for a node
graphM.resize(rows,cols);
for(r = 0; r<rows;r++){
  for(c = 0; c<cols ; c++){
    if(isLegal(r,c)){
      Dr= add_vertex(g);// adds node
      g[Dr].cell = pair<int,int>(r,c);// adds r,c coordinate to the node
      graphM[r][c]=Dr;// adds dr to the matrix



        }

    }

  }

  for(r = 0; r<rows;r++){// traverse matrix
    for(c = 0; c<cols ; c++){
        if(isLegal(r,c)){
          Dr= graphM[r][c];
          //check top
          if(r>0 && isLegal(r-1,c)){// check if there is node on top
            add_edge(Dr,graphM[r-1][c],g);
          }
          //check below
          if(r< rows-1 && value[r+1][c]){//  checks if there is node below
            add_edge(Dr,graphM[r+1][c],g);
          }
          // right
          if(c < cols-1 && value[r][c+1]){// checks if there is a node to the right
            add_edge(Dr, graphM[r][c+1]);
          }
          if(c>0 && value[r][c-1]){// checks if there is a node to the left

            add_edge(Dr,value[r][c-1],g);
          }

        }

    }
  }
// marked evrything as false and zero weight
clearVisited(g);
clearMarked(g);
setNodeWeights(g,0);




}



void maze::printPath(Graph::vertex_descriptor end,
                     stack<Graph::vertex_descriptor> &s,
                     Graph g){

}


void clearVisited(Graph &g){
// Mark all nodes in g as not visited.
typedef boost:: graph_traits<Graph>::vertex_iterator vertex_iter;
std::pair<vertex_iter, vertex_iter> vertexPair;
for(vertexPair=vertices(g); vertexPair.first != vertexPair.second; ++vertexPair.first)
  g[*vertexPair.first].visited=false;
}
void setNodeWeights(Graph &g, int w){
// Set all node weights to w.
    typedef boost:: graph_traits<Graph>::edge_iterator edge_iter;
    std::pair<edge_iter, edge_iter> edgePair;
    for(edgePair= edges(g); edgePair.first != edgePair.second; ++edgePair.first){
      g[*edgepair.first].weight=w;
    }
}

void clearMarked(Graph &g){
// Unmark all nodes.
typedef boost:: graph_traits<Graph>::vertex_iterator vertex_iter;
std::pair<vertex_iter, vertex_iter> vertexPair;
for(vertexPair=vertices(g); vertexPair.first != vertexPair.second; ++vertexPair.first)
  g[*vertexPair.first].marked=false;
}

ostream &operator<<(ostream &ostr, const Graph &g){
// Output operator for the Graph class. Prints out all nodes and their
// properties, and all edges and their properties.
typedef boost:: graph_traits<Graph>::edge_iterator edge_iter;
std:: pair<edge_iter, edge_iter> edgePair;
// Traverse all the edges and cout their properties
for(edgePair= edges(g); edgePair.first != edgePair.second; ++edgePair.first){

      ostr<< g[*edgePair.first].weight;
      if(g[*edgePair.first].marked)
        ostr<< " True";
      else
        ostr<< "False";
      if(g[*edgePair.first].visited;)
      ostr<< "True";
      else
        ostr<< "false";
}
    typedef boost:: graph_traits<Graph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vertexPair;
    //Traverse every node and cout their properties
    for(vertexPair=vertices(g); vertexPair.first != vertexPair.second; ++vertexPair.first){
      ostr<< g[*vertexPair.first].weight;
      if(g[*vertexPair.first].visited){
        ostr<< " true";
      }
      else {
        ostr<<" false";
      }
      if(g[*vertexPair.first].visited){
      ostr<< "true";
    }
      else{
      ostr<< "false"
    }


    }
  return ostr;


}

void maze::findPathDFSStack(Graph &g){// passes down the graph by reference and finds a path using DFS
    Graph:: vertex_descriptor Dr;
    Graph:: vertex_descriptor first;
    first= graphM[0][0];

    if (!g[first].visited){// checks if the first node has been visited
      DFS.push(first);// pushes it into the stack
      while(!DFS.empty()){// checks if the stack is empty
        Dr= DFS.pop();
        if(!g[Dr].visited){
          //visit(DR)
          g[Dr].visted= true;
          std::pair<adjacency_iterator, adjacency_iterator> neighbors =
          boost::adjacent_vertices(vertex(Dr,g), g);
          for(neighbors.first != neighbors.second; ++neighbors.first)// loop that checks the neighbors around vertex Dr
          {
            if(!g[*neighbors.first].visited){
              DFS.push(*neighbors.first);
              g[*neighbors.first].predecessor=Dr;// sets the predecessor to the parent node
            }
          }

        }



      }
    }
  }
void maze::findShortestPathBFS(Graph &g){
  clearVisited(g);
  Graph:: vertex_descriptor Dr;
  Graph:: vertex_descriptor first;
  Graph:: vertex_descriptor last;
  Graph:: vertex_descriptor previous;
  first= graphM[0][0];

  if (!g[first].visited){// checks to see if first vertex has been visited
    BFS.enqueue(first);// adds it to the que
    while(!DFS.empty()){// while the q is not empty
      Dr= DFS.dequeue();
      if(!g[Dr].visited){
        //visit(DR)
        g[Dr].visted= true;
      //  g[Dr].predecessor=
        std::pair<adjacency_iterator, adjacency_iterator> neighbors =
        boost::adjacent_vertices(vertex(Dr,g), g);
        for(neighbors.first != neighbors.second; ++neighbors.first)// loop that checks the neighbors
        {
          if(!g[*neighbors.first].visited){
            DFS.enqueue(*neighbors.first);
            g[*neighbors.first].predecessor=Dr;
          }
        }

      }
      /*last= graphM[rows-1][columns-1];
      BFshortestPath.push(last);
      previous=g[last].predecessor
      BFshortestPath.push(previous);
      while(g[previous].predecessor != NIL){// loop that goes from the end to the beginning using the predecessor
        previous= g[previous].predecessor;
        BFshortestPath.push(previous);


      }*/
    }
  }









}
void maze::findPathDFSRecursive(Graph &g,Graph::vertex_descriptor start, Graph::vertex_descriptor goal){







}








void maze::findPath(int const &startNode, int const &endNode, int* &parent){
      if( startNode == endNode || endNode == -1){
          printf("%d\n", startNode);
      }
      else{
          findPath(startNode, parent[endNode], parent);
          printf("%d\n", endNode);
      }
  }

void maze::findShortestPathBFS(Graph &g){


      int *dist = new int[V];
      int *parent = new int[V];

      for(int v = 0; v < V; ++v){
          dist[v] = INF;
          parent[v] = -1;
      }

      dist[s] = 0;
      queue<int> Q;
      Q.push( s );


      while( !Q.empty() ){
          int u = Q.front();
          Q.pop();

          cout << u << " ";

          list<int>::iterator it;
          for(it = adjList[u].begin(); it != adjList[u].end(); ++it){
              if( dist[*it] == INF ){
                  Q.push(*it);
                  dist[*it] = dist[u] + 1;
                  parent[*it] = u;
              }
          }
      }


      // Print all the reachable nodes with distance from current nodes.
      printf("\n");
      for(int v = 0; v < V; ++v){
          if(dist[v] != INF){
              printf("%d -> %d: %d\n", s, v, dist[v]);
          }else{
              printf("%d -> %d: No Path\n", s, v);
          }
      }


      // Print the parent array.
      for(int v = 0; v < V; ++v){
          printf("parent of %d: %d\n", v, parent[v]);
      }


      // Try to find the shortest path from current node to another.
      // This can be modified based on need. Return the vector or
      // array from here to main in order to call function from there.
      int node;
      printf("Find shortest path from node %d to another:\n", s);
      cin >> node;
      if( dist[node] != INF )
          findPath(s, node, parent);
      else
          printf("No paths available");


}
void maze::relax(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v){
  std::pair<Graph::edge_descriptor, bool> retrievedEdge = boost::edge(u, v, g);
  if(g[v].weight > g[u].weight + g[retrieveEdge.first].weight ){
    g[v].weight=g[u].weight + g[retrieveEdge.first].weight;
    g[v].predecessor= u;
  }
}
void maze::initializeGraph(Graph &g, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end, ifstream &fin){
   EdgeProperties e;

   int n, i, j;
   int startId, endId;
   fin >> n;
   fin >> startId >> endId;
   Graph::vertex_descriptor v;

   // Add nodes.
   for (int i = 0; i < n; i++)
   {
      v = add_vertex(g);
      if (i == startId)
	 start = v;
      if (i == endId)
	 end = v;
   }

   while (fin.peek() != '.')
   {
      fin >> i >> j >> e.weight;
      Graph::add_edge(i,j,e,g);
   }
}
bool maze::dijkstra(Graph &g, Graph::vertex_descriptor s){
    std::pair<vertex_iter, vertex_iter> vertexPair;// intial condition to set up all the nodes distnace to infinity
    for(vertexPair=vertices(g); vertexPair.first != vertexPair.second; ++vertexPair.first){
        g[*vertexPair.first].weight=9999999;
        g[*vertexPair.first].predecessor= NIL;
        
    }
    g[s].weight= 0;// sets weight of the source to zero
    heapV<Graph::vertex_descriptor, Graph> h;
    std::pair<vertex_iter, vertex_iter> vertexPair;
    
    std::pair<adjacency_iterator, adjacency_iterato> neighbors;
    
    for(vertexPair=vertices(g); vertexPair.first != vertexPair.second; ++vertexPair.first){// go through all the nodes and insert them in the heap
        h.minHeapInsert(*vertexPair.first,g);
        
    }
    while(!h.empty()){
        Graph::vertex_descriptor u= h.extractMinheapMinimum(g);// extract min value
        s.push_back(u);
        
        neighbors= boost::adjacent_vertices(vertex(u,g),g);
        for(; neighbors.first != neighbors.second; neighbors++.firts){// iterate over the the neighbors 
            relax(g,u,*neighbors.first);
            h.minHeapDecreaseKey(h.getIndex(*neighbors.first),g);
            
            
        }
    }
}
bool maze::bellmanFord(Graph &g, Graph::vertex_descriptor s){
// initilaize distances to infinity except for the source 

std::pair<vertex_iter, vertex_iter> vertexPair;
for(vertexPair=vertices(g); vertexPair.first != vertexPair.second; ++vertexPair.first){
    g[*vertexPair.first].weight=9999999;
    g[*vertexPair.first].predecessor= NIL;
  
}
g[s].weight= 0;// sets weight of the source to zero
    
    

// loop from 1 to int get vertice-1
typedef boost:: graph_traits<Graph>::edge_iterator edge_iter;
    std::pair<edge_iter, edge_iter> edgePair;
for(int i=1, i<boost::num_vertices(g); i++ ){

  for(edgePair= edges(g); edgePair.first != edgePair.second; ++edgePair.first){
     // get source and destination relax source and destination
      
      
      relax(g,source(*edgePair.first,g), target(*edgePair.first,g));
}
}
std::pair<edge_iter, edge_iter> Edge;
    Graph::vertex_descriptor v;
    Graph::vertex_descriptor u;
    for(Edge= edges(g); Edge.first != Edge.second; ++Edge.first){// check for negative cycles
        
        u=source(*Edge.first,g);
        v=target(*Edge.first,g);
        if( g[v].weight > g[u].weight + g[*Edge].weight){// negative cycle dectected
            
            return false;
            
        }
    }
    return true;
}

void maze::DPrint(Graph &g){
    // print graphs 
    Graph::vertex_descriptor temp;
    
    int weight;
    int pred;
    
    for(int i=0, i<boost::num_vertices(g); i++ ){
        temp = s[i];
        
        pred = temp.predecessor;
        weight = temp.weight;
        
        std::cout<<"Predecessor: "<<pred<<"   Weight: "<<weight<<std::endl;
        
    }
    
}


void maze::BFPrint(Graph &g){
    //prints graphs
    int weight;
    int pred;
    
    for(vertexPair=vertices(g); vertexPair.first != vertexPair.second; ++vertexPair.first){
        weight = g[*vertexPair.first].weight;
        pred = g[*vertexPair.first].predecessor;
        
        std::cout<<"Predecessor: "<<pred<<"   Weight: "<<weight<<std::endl;
        
    }

}
