#include <iostream>
#include <algorithm>
using namespace std;
struct Edge{
	int src;
	int dest;
	int weight;
};
struct Graph{
	int V;
	int E;
	struct Edge *edges;
};
struct Graph *createNewGraph(int V,int E){
	struct Graph *newGraph=(struct Graph *)malloc(sizeof(struct Graph));
	newGraph->V=V;
	newGraph->E=E;
	newGraph->edges=(struct Edge *)malloc(sizeof(Edge)*E);
	return newGraph;
}
struct subset{
	int parent;
	int rank;
};
int Find(struct subset *subsets,int x){
	if(subsets[x].parent!=x){
		subsets[x].parent=Find(subsets,subsets[x].parent);
	}
	return subsets[x].parent;
}
void Union(struct subset *subsets,int x,int y){
	int xparent=Find(subsets,x);
	int yparent=Find(subsets,y);
	if(subsets[xparent].rank>subsets[yparent].rank){
		subsets[yparent].parent=xparent;
	}
	else if(subsets[yparent].rank>subsets[xparent].rank){
		subsets[xparent].parent=yparent;
	}
	else{
		subsets[xparent].parent=yparent;
		subsets[yparent].rank++;
	}
}
int myComparator(const void *a,const void *b){
	struct Edge *x=(struct Edge *)a;
	struct Edge *y=(struct Edge *)b;
	return x->weight>y->weight;
}
void KruskalMST(struct Graph *graph){
	int V=graph->V;
	int E=graph->E;
	struct Edge result[V-1];
	qsort(graph->edges,graph->E,sizeof(graph->edges[0]),myComparator);
	int e=0;
	int i=0;
	struct subset *subsets=(struct subset *)malloc(sizeof(struct subset)*V);
	for(int i=0;i<V;i++){
		subsets[i].parent=i;
		subsets[i].rank=0;
	}
	while(e<V-1){
		struct Edge next_edge=graph->edges[i];
		int x=Find(subsets,next_edge.src);
		int y=Find(subsets,next_edge.dest);
		if(x!=y){
			Union(subsets,x,y);
			result[e]=next_edge;
			e++;
		}
		i++;
	}
	cout<<"The Edges in MST are"<<endl;
	for(int i=0;i<V-1;i++){
		cout<<result[i].src<<" "<<result[i].dest<<" Weight "<<result[i].weight<<endl;
	}
	cout<<"\n";
}
int main(){
	int V=4;
	int E=5;
	struct Graph *graph=createNewGraph(V,E);
	graph->edges[0].src = 0;
    graph->edges[0].dest = 1;
    graph->edges[0].weight = 10;
	graph->edges[1].src = 0;
    graph->edges[1].dest = 2;
    graph->edges[1].weight = 6;
 	graph->edges[2].src = 0;
    graph->edges[2].dest = 3;
    graph->edges[2].weight = 5;
 	graph->edges[3].src = 1;
    graph->edges[3].dest = 3;
    graph->edges[3].weight = 15;
 	graph->edges[4].src = 2;
    graph->edges[4].dest = 3;
    graph->edges[4].weight = 4;
 	KruskalMST(graph);
 	return 0;
}