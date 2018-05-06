/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "NimLearner.h"
#include <ctime>
#include <iostream>
using namespace std;
void helper(int curPlayer, Graph & g,int tokens,Vertex LastV){
    if(tokens == 0){
        return;
    }
    if(curPlayer == 1){
        curPlayer = 2;
    }else{
        curPlayer = 1;
    }
    if(tokens>1){
        string s1 = "p" + to_string(curPlayer)+"-" + to_string(tokens-1);
        string s2 = "p" + to_string(curPlayer)+"-" + to_string(tokens-2);
        g.insertVertexByLabel(s1);
        g.insertVertexByLabel(s2);
        //set edge


        helper(curPlayer,g,tokens-1,g.getVertexByLabel(s1));
        helper(curPlayer,g,tokens-2,g.getVertexByLabel(s2));
        bool b = g.insertEdge(LastV,g.getVertexByLabel(s1));
        bool a = g.insertEdge(LastV,g.getVertexByLabel(s2));
        //cout<<"set edge from "<<LastV<<" to "<<g.getVertexByLabel(s1)<<" "<<b<<endl;
        //cout<<"set edge from "<<LastV<<" to "<<g.getVertexByLabel(s2)<<" "<<a<<endl;
    }else if(tokens == 1){
        string s1 = "p" + to_string(curPlayer)+"-" + to_string(tokens-1);
        g.insertVertexByLabel(s1);
        //set edge
        helper(curPlayer,g,tokens-1,g.getVertexByLabel(s1));
        g.insertEdge(LastV,g.getVertexByLabel(s1));
        //cout<<"set edge from "<<LastV<<" to "<<g.getVertexByLabel(s1)<<endl;

    }
}

/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
    /* Your code goes here! */
    //g_.initSnapshot("states");
    string v  = "p1-" + to_string(startingTokens);
  //  cout<<startingVertex_<<endl;
    g_.insertVertexByLabel(v);
    startingVertex_ = g_.getVertexByLabel(v);
    helper(1,g_,startingTokens,startingVertex_);
    for (unsigned i = startingTokens; i > 1; i--){
        //insert edge from player 1 to player 2
		g_.insertEdge(g_.getVertexByLabel("p1-" + to_string(i)), g_.getVertexByLabel("p2-" + to_string(i-1)));
		g_.insertEdge(g_.getVertexByLabel("p1-" + to_string(i)), g_.getVertexByLabel("p2-" + to_string(i-2)));

        //set edge weight from player 1 to player 2
        g_.setEdgeWeight(g_.getVertexByLabel("p1-" + to_string(i)), g_.getVertexByLabel("p2-" + to_string(i-1)), 0);
        g_.setEdgeWeight(g_.getVertexByLabel("p1-" + to_string(i)), g_.getVertexByLabel("p2-" + to_string(i-2)), 0);

        //insert edge from player 2 to player 1
		g_.insertEdge(g_.getVertexByLabel("p2-" + to_string(i)), g_.getVertexByLabel("p1-" + to_string(i-1)));
		g_.insertEdge(g_.getVertexByLabel("p2-" + to_string(i)), g_.getVertexByLabel("p1-" + to_string(i-2)));

        //set edge weight from player 2 to player 1
		g_.setEdgeWeight(g_.getVertexByLabel("p2-" + to_string(i)), g_.getVertexByLabel("p1-" + to_string(i-1)), 0);
		g_.setEdgeWeight(g_.getVertexByLabel("p2-" + to_string(i)), g_.getVertexByLabel("p1-" + to_string(i-2)), 0);
	}
	if (startingTokens >= 1){
        //last few edges
		g_.insertEdge(g_.getVertexByLabel("p1-" + to_string(1)), g_.getVertexByLabel("p2-" + to_string(0)));
		g_.insertEdge(g_.getVertexByLabel("p2-" + to_string(1)), g_.getVertexByLabel("p1-" + to_string(0)));
		g_.setEdgeWeight(g_.getVertexByLabel("p1-" + to_string(1)), g_.getVertexByLabel("p2-" + to_string(0)), 0);
		g_.setEdgeWeight(g_.getVertexByLabel("p2-" + to_string(1)), g_.getVertexByLabel("p1-" + to_string(0)), 0);
	}
    //cout<<g_.getEdge(g_.getVertexByLabel("p2-2"), g_.getVertexByLabel("p1-0")).source<<"   "<<g_.getEdge(g_.getVertexByLabel("p2-2"), g_.getVertexByLabel("p1-0")).dest<<endl;

    //g_.snapshot();
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
 vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
 /* Your code goes here! */
 Vertex temp = startingVertex_;
 vector<Vertex> adjVertex = g_.getAdjacent(temp);
 int a = rand() % (adjVertex.size());
 Vertex next = adjVertex[a];
 path.push_back(g_.getEdge(temp,next));
 temp = next;
 //cout<<"1";
 adjVertex = g_.getAdjacent(temp);
 while(!adjVertex.empty()){

    int a = rand() % (adjVertex.size());
    Vertex next = adjVertex[a];

    path.push_back(g_.getEdge(temp,next));
    if(next.substr(2,2)=="-0"){
        return path;
    }
    temp = next;
    //cout<<temp<<endl;;
    adjVertex = g_.getAdjacent(temp);

 }
  return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const  vector<Edge> & path) {
 /* Your code goes here! */
    string temp = g_.getVertexLabel(path.back().dest);
    temp = temp.substr(1,1);
    if(temp == "1"){
        int rewarded = -1;
        for(auto it = path.begin();it!=path.end();it++){

            int weight   = g_.getEdgeWeight((*it).source,(*it).dest);
            weight += rewarded;
            g_.setEdgeWeight((*it).source,(*it).dest,weight);
            rewarded = -rewarded;
        }
    }else if(temp == "2"){
        int rewarded = 1;

        for(auto it = path.begin();it!=path.end();it++){
            int weight   = g_.getEdgeWeight((*it).source,(*it).dest);
            weight += rewarded;
            g_.setEdgeWeight((*it).source,(*it).dest,weight);
            rewarded = -rewarded;
        }
    }
}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
