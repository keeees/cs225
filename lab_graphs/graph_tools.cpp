/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"
using namespace std;
/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    //TODO: YOUR CODE HERE
    int result;
    vector<Vertex> ver = graph.getVertices();
    for (int i = 0; i < ver.size(); i++){
        graph.setVertexLabel(ver[i], "UNEXPLORED");
    }
    vector <Edge> edges = graph.getEdges();
	for(size_t i = 0; i < edges.size(); i++){
        Vertex so = edges[i].source;
		    Vertex de = edges[i].dest;
		    graph.setEdgeLabel(so, de, "UNEXPLORED");
	  }
    queue <Vertex> q;
    graph.setVertexLabel(ver[0], "VISITED");
    q.push(ver[0]);

    result = graph.getEdgeWeight(ver[0],graph.getAdjacent(ver[0])[0]);
    Vertex v1 = ver[0];
    Vertex v2 = graph.getAdjacent(ver[0])[0];
    while(!q.empty()){
      Vertex v = q.front();
      q.pop();
      vector <Vertex> adjacent = graph.getAdjacent(v);
      for(size_t i = 0; i < adjacent.size(); i++){
        if(graph.getVertexLabel(adjacent[i]) == "UNEXPLORED"){
          graph.setEdgeLabel(v,adjacent[i], "DISCOVERY");
          graph.setVertexLabel(adjacent[i], "VISITED");
          q.push(adjacent[i]);
          int temp = graph.getEdgeWeight(v,adjacent[i]);
          if(temp < result){
              v1 = v;
              v2 = adjacent[i];
              result = temp;
          }

        }else if(graph.getEdgeLabel(v,adjacent[i]) == "UNEXPLORED"){
          graph.setEdgeLabel(v, adjacent[i], "CROSS");
          int temp = graph.getEdgeWeight(v,adjacent[i]);
          if(temp < result){
              v1 = v;
              v2 = adjacent[i];
              result = temp;
          }
        }
      }
    }

     graph.setEdgeLabel(v1, v2, "MIN");
    return result;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    //TODO: YOUR CODE HERE
    unordered_map <Vertex, Vertex> m;
    vector<Vertex> ver = graph.getVertices();
    for (int i = 0; i < ver.size(); i++){
        graph.setVertexLabel(ver[i], "UNEXPLORED");
    }
    vector <Edge> edges = graph.getEdges();
    for(size_t i = 0; i < edges.size(); i++){
        Vertex so = edges[i].source;
        Vertex de = edges[i].dest;
        graph.setEdgeLabel(so, de, "UNEXPLORED");
    }
    queue <Vertex> q;
    graph.setVertexLabel(start, "VISITED");
    q.push(start);
    while(!q.empty()){
      Vertex v = q.front();
      q.pop();
      vector <Vertex> adjacent = graph.getAdjacent(v);
      for(size_t i = 0; i < adjacent.size(); i++){
        if(graph.getVertexLabel(adjacent[i]) == "UNEXPLORED"){
          graph.setEdgeLabel(v,adjacent[i], "DISCOVERY");
          graph.setVertexLabel(adjacent[i], "VISITED");
          q.push(adjacent[i]);
          pair <Vertex, Vertex> temp (adjacent[i],v);
          m.insert(temp);
        }else if(graph.getEdgeLabel(v,adjacent[i]) == "UNEXPLORED"){
          graph.setEdgeLabel(v, adjacent[i], "CROSS");
        }
      }
    }

    int distance = 0;
	while(end != start)
	{
		graph.setEdgeLabel(end, m[end], "MINPATH");
		end = m[end];
		distance ++;
	}
	return distance;

}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the dsets.h and dsets.cpp .
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    //TODO: YOUR CODE HERE
    vector <Edge> edges = graph.getEdges();
    sort(edges.begin(), edges.end());
    DisjointSets dset;
    unordered_map <Vertex,int> m;
    vector<Vertex> ver = graph.getVertices();
    int i = 0;
    for(auto it = ver.begin();it!= ver.end();it++){
      m.insert(pair<Vertex,int>(*it,i));
      i++;
    }
    dset.addelements(ver.size());
    for(int i = 0;i<edges.size();i++){
      Vertex v1 = edges[i].source;
      Vertex v2 = edges[i].dest;
      if(dset.find(m[v1]) != dset.find(m[v2])){
        dset.setunion(m[v1],m[v2]);
        graph.setEdgeLabel(v1,v2,"MST");
      }
    }
}
