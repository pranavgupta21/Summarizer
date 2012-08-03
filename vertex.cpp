#include "vertex.h"
using namespace std;

extern int no_vertices;
extern stack<Vertex*> vstack;
extern vector<string> tags_to_filter;
extern float d;

void init(){
	tags_to_filter.push_back("JJ");
	tags_to_filter.push_back("JJR");
	tags_to_filter.push_back("JJS");
	tags_to_filter.push_back("NN");
	tags_to_filter.push_back("NNS");
	tags_to_filter.push_back("NNP");
	tags_to_filter.push_back("NNPS");
}

void displayAdjList(vector<Vertex*> adjList){
	for(int vertexNo = 0; vertexNo < adjList.size(); vertexNo++){
		printf("%3d\t%3d\t%10s\t%f | ", vertexNo, adjList[vertexNo]->position, adjList[vertexNo]->value.c_str(), adjList[vertexNo]->score);
		adjList[vertexNo]->showNeighbours();
		cout << "\n";
	}
}

void depthFirstTraversal(vector<Vertex*> adjList){
	//cerr << "depthFirstTraversal() : no_vertices = " << no_vertices << "\n";
	int *visited = (int*)calloc(no_vertices, sizeof(int)), addCount = 0;
	//cerr << "depthFirstTraversal() : break 1\n";
	float neighbour_sum = 0;
	vstack.push(adjList[0]);
	visited[0] = 1;
	//cerr << "depthFirstTraversal() : break 2\n";
	while(!vstack.empty()){
		Vertex *topVertex = vstack.top();
		//cout<< "Stack Size : " << vstack.size() - 1 << "\n";
		//cout<< "Top : " << topVertex->gposition << "\n";
		//cout<<"Neighbours : ";
		//topVertex->showNeighbours();
		Neighbour *neighbr = topVertex->neighbour;
		//cerr << "depthFirstTraversal() : break 3\n";
		addCount = 0;
		neighbour_sum = 0;
		//cout<<"Neighbours added : ";
		while(neighbr != NULL){
			neighbour_sum += adjList[neighbr->vertexId]->score * (neighbr->weight/adjList[neighbr->vertexId]->count_neighbours());		// used w(ij) whereas w(ji) has to be used
			//cerr << "depthFirstTraversal() : neighbour vertex Id = " << neighbr->vertexId << "\n";
			if(!visited[neighbr->vertexId]){
				//cerr << "depthFirstTraversal() : not visited neighbour vertex Id = " << neighbr->vertexId << "\n";
				vstack.push(adjList[neighbr->vertexId]);
				addCount++;
				visited[neighbr->vertexId] = 1;
				//cout<<neighbr->vertexId<<"\t";
			}
			neighbr = neighbr->nextNeighbour;
		}
		
		topVertex->score = (1.0 - d) + d * neighbour_sum;
		//cerr << "depthFirstTraversal() : break 4\n";
		if(!addCount){
			//cout<<"No Neighbour Added\n";
			//cout<<topVertex->value<<endl;
			vstack.pop();
		}
		//cout<<"\nAdd Count : "<<addCount<<"\n";
	}
	delete[] visited;
	//cerr << "depthFirstTraversal() : break 5\n";
}

void Vertex::addNeighbour(int vertexNo){
	Neighbour *neighbr = new Neighbour(vertexNo);
	neighbr->nextNeighbour = neighbour;
	neighbour = neighbr;
}

void Vertex::showNeighbours(){
	Neighbour *neighbr = neighbour;
	if(neighbr == NULL){
		cout<<"No neighbours / outgoing edges\n";
		return;
	}
	while(neighbr != NULL){
		cout<<neighbr->vertexId<<"\t";
		neighbr = neighbr->nextNeighbour;
	}
	cout<<"\n";
}

int Vertex::count_neighbours(){
	int no_neighbours = 0;
	Neighbour *neighbr = neighbour;
	while(neighbr != NULL){
		no_neighbours++;
		neighbr = neighbr->nextNeighbour;
	}
	return no_neighbours;
}

bool filter_tag(string tag_name){
	for(vector<string>::iterator tag_it = tags_to_filter.begin(); tag_it != tags_to_filter.end(); tag_it++){
		if (tag_name == *tag_it)
			return true;
	}
	return false;	
}

int exist_word(vector<Vertex*> adjList, string word){
	//cout << word << "\n";
	for(int word_no = 0; word_no < adjList.size(); word_no++){
		if (word == adjList[word_no]->value)
			return word_no;
	}
	return -1;
}
