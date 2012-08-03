#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stack>
#include <vector>
using namespace std;

#define TAG_SEPARATOR "_"
#define CO_OCCURENCE_WINDOW 3
#define NO_ITERATIONS 30

class Neighbour{
	public:
	int vertexId;
	float weight;
	Neighbour *nextNeighbour;
	
	Neighbour(int vertexNo){
		vertexId = vertexNo;
		weight = 1.0;
		nextNeighbour = NULL;
	}
};

class Vertex{
	public:
	string value;
	int position;
	int gposition;
	float score;
	Neighbour *neighbour;
	
	Vertex(string vertexVal, int pos, int gpos){
		value = vertexVal;
		position = pos;
		gposition = gpos;
		score = 1.0;
		neighbour = NULL;
	}
	void addNeighbour(int);
	void showNeighbours();
	int count_neighbours();
};

void init();
void displayAdjList(vector<Vertex*>);
void depthFirstTraversal(vector<Vertex*>);
bool filter_tag(string);
int exist_word(vector<Vertex*> adjList, string word);

