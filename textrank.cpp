#include "vertex.h"
using namespace std;

int no_vertices;
stack<Vertex*> vstack;
vector<string> tags_to_filter;
float d = 0.85;

int main(int argc, char *argv[]){
	//char text[TEXT_LENGTH];
	//fprintf(stdout, "the received text is %s\n", text);
	//fprintf(stdout, "Length of the received text is %d\n", strlen(text));
	init();
	string vertexVal, word;
	int pos, wordNo = 0, exists = 0, loopVar = 0;
	Vertex *vertex;
	
	cin>>no_vertices;
	
	vector<Vertex*> adjList;
	for(loopVar = 0, wordNo = 0; loopVar < no_vertices; loopVar++){
		cin>>word;
		//cout << "Word Number " << loopVar+1 << " : " << word << "\n";
		pos = word.find(TAG_SEPARATOR);
		
		if(filter_tag(word.substr(pos+1))){
			//cerr << "Word No : " << wordNo << "\n";
			/*
			if(exists = (exist_word(adjList, word.substr(0, pos)) + 1)){
				vertex = adjList[exists - 1];
				vertex->score += 1.0;
			}
			else{*/
				vertex = new Vertex(word.substr(0, pos), loopVar, wordNo);
				adjList.push_back(vertex);
			//}
			//cerr << "Word No : " << wordNo << "\n";
			for (int pred = 0; pred	< wordNo; pred++){
				if((loopVar - adjList[pred]->position) <= CO_OCCURENCE_WINDOW){
					adjList[pred]->addNeighbour(wordNo);
					vertex->addNeighbour(pred);
				}
			}
			//if(!exists)
				wordNo++;
		}
	}
	
	no_vertices = wordNo;
	//cerr << adjList.size() << "\t" << no_vertices << "\n";
	//displayAdjList(adjList);
	cout << "\n";
	//cout << "Graph Generated \n";
	//cout << "Applying TextRank \n";
	for (int loopVar = 0; loopVar < NO_ITERATIONS; loopVar++){
		//cerr << "Iteration Number " << loopVar + 1 << "\n";
		depthFirstTraversal(adjList);
	}
	displayAdjList(adjList);
	cout<<"\n\n";
	return 0;
}
