#include <iostream>
#include <list>
#include <stack>
using namespace std;
class Graph{
private:
	int V;
	list<int> *adjList;
	void topologicalSortHelper(int vertex,bool Visited[],stack<int> &Stack);
public:
	Graph(int V);
	void addEdge(int src,int dest);
	void topologicalSort();
};
Graph::Graph(int V){
	this->V=V;
	adjList=new list<int>[V];
}
void Graph::addEdge(int src,int dest){
	adjList[src].push_back(dest);
}
void Graph::topologicalSort(){
	stack<int> Stack;
	bool *Visited=new bool[V];
	for(int i=0;i<V;i++){
		Visited[i]=false;
	}
	for(int i=0;i<V;i++){
		if(Visited[i]==false){
			topologicalSortHelper(i,Visited,Stack);
		}
	}
	while(!Stack.empty()){
		cout<<Stack.top()<<" ";
		Stack.pop();
	}
}
void Graph::topologicalSortHelper(int vertex,bool Visited[],stack<int> &Stack){
	Visited[vertex]=true;
	list<int>::iterator i;
	for(i=adjList[vertex].begin();i!=adjList[vertex].end();i++){
		if(Visited[*i]==false){
			topologicalSortHelper(*i,Visited,Stack);
		}
	}
	Stack.push(vertex);
}
int main(){
	Graph g(6);
	g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
 	cout << "Following is a Topological Sort of the given graph \n";
    g.topologicalSort();
	return 0;
}