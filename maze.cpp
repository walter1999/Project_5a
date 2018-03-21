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
#include "d_matrix.h"
maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
    fin >> rows; // reads rows from file
    fin >> cols; // reads cols from

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
typedef boost:: graph_traits<Graph>::vertx_iterator vertex_iter;
std::pair<vertex_iter, vertex_iter> vertexPair;
for(vertexPair=vertices(g); vertexPair.first != vertexPair.second; ++vertexPair.first)
  g[*vertexPair.first].visited=false;
}
void setNodeWeights(Graph &g, int w){
// Set all node weights to w.
    typedef boost:: graph_traits<Graph>::edge_iterator edge_iter;
    for(edgePair= edges(g); edgePair.first != edgePair.second; ++edgePair.first){
      g[*edgepair.first].weight=w;
    }
}

void clearMarked(Graph &g){
// Unmark all nodes.
typedef boost:: graph_traits<Graph>::vertx_iterator vertex_iter;
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

      ostr<< g[*edgepair.first].weight;
      if(g[*edgepair.first].marked)
        ostr<< " True";
      else
        ostr<< "False";
      if(g[*edgepair.first].visited;)
      ostr<< "True";
      else
        ostr<< "false";
}
    typedef boost:: graph_traits<Graph>::vertx_iterator vertex_iter;
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
