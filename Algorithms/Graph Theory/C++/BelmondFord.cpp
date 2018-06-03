#include <cstdio>
#include <climits>
#include <vector>
#include <list>
#include <utility>
 
using namespace std;
 
void PrintNegativeCycle(vector< pair<int, int> > shortestDistances, int vertex, int startVertex)
{
    if (vertex == startVertex) {
        printf("%d ", vertex);
    } else if (shortestDistances[vertex].second == 0) {
        PrintNegativeCycle(shortestDistances, startVertex, startVertex);
        printf("%d ", vertex);
    } else {
        PrintNegativeCycle(shortestDistances, shortestDistances[vertex].second, startVertex);
        printf("%d ", vertex);
    }
}
 
int bellmanFord(vector< list< pair<int, int> > > adjacencyList, int vertices, int startVertex, vector< pair<int, int> > & shortestDistances)
{
    list< pair<int, int> >::iterator traverse;
    int i, j, k;
     
    
    for (i = 0; i <= vertices; ++i) {
        shortestDistances[i].first = INT_MAX;
        shortestDistances[i].second = -1;
    }
     
    shortestDistances[startVertex].first = 0;
    shortestDistances[startVertex].second = 0;

    for (i = 1; i <= vertices - 1; ++i) {    
        for (j = 1; j <= vertices; ++j) {    
            traverse = adjacencyList[j].begin();
             
            while (traverse != adjacencyList[j].end()) {
                if (shortestDistances[j].first == INT_MAX) {
                    ++traverse;
                    continue;
                }
                 
               
                if ((*traverse).second + shortestDistances[j].first < 
                                        shortestDistances[(*traverse).first].first) {
                    
                    shortestDistances[(*traverse).first].first = (*traverse).second
                                        + shortestDistances[j].first;
                    shortestDistances[(*traverse).first].second = j;
                }
                 
                ++traverse;
            }
        }
    }
     
    
    for (j = 1; j <= vertices; ++j) {
        traverse = adjacencyList[j].begin();
         
        while (traverse != adjacencyList[j].end()) {
    
            if ((*traverse).second + shortestDistances[j].first < 
                                        shortestDistances[(*traverse).first].first) {
    
                return j;
            }
             
            ++traverse;
        }
    }
     
    return -1;
}
 
int main()
{
    int vertices, edges, v1, v2, weight;
     
    printf("Enter the Number of Vertices -\n");
    scanf("%d", &vertices);
     
    printf("Enter the Number of Edges -\n");
    scanf("%d", &edges);
     
   
    vector< list< pair<int, int> > > adjacencyList(vertices + 1);
     
    printf("Enter the Edges V1 -> V2, of weight W\n");
     
    for (int i = 1; i <= edges; ++i) {
        scanf("%d%d%d", &v1, &v2, &weight);
        adjacencyList[v1].push_back(make_pair(v2, weight));
    }
     
    printf("\nThe Adjacency List-\n");

    for (int i = 1; i < adjacencyList.size(); ++i) {
        printf("adjacencyList[%d] ", i);
         
        list< pair<int, int> >::iterator itr = adjacencyList[i].begin();
         
        while (itr != adjacencyList[i].end()) {
            printf(" -> %d(%d)", (*itr).first, (*itr).second);
            ++itr;
        }
        printf("\n");
    }
         
    vector< pair<int, int> > shortestDistances(vertices + 1);
    int startVertex;
     
    printf("\nEnter a Start Vertex -\n");
    scanf("%d", &startVertex);
     
    int returnValue = bellmanFord(adjacencyList, vertices, startVertex, shortestDistances);
     
    if (returnValue == -1) {
        printf("No Negative Cycles exist in the Graph -\n");
    } else {
        printf("Negative Cycles exists in the Graph -\n");
        PrintNegativeCycle(shortestDistances, shortestDistances[returnValue].second, returnValue);
         
        return 0;
    }
     
    printf("\n\nVertex    Shortest Distance to Vertex %d     Parent Vertex-\n", startVertex);
    for (int i = 1; i <= vertices; ++i) {
        printf("%d \t  %d \t\t\t\t    %d\n", i, shortestDistances[i].first, shortestDistances[i].second);
    }
     
    return 0;
}