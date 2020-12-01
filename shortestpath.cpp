//#include the .h file
using namespace std;
#define INF 99999

int V, src, cost[15000][15000]; // total of 14110 airports 
int dist[15000];
bool visited[15000] = {0};  // default each to be false
int parent[15000];

void init(){
    for(int i = 0; i < V;i ++){
        parent[i] = i;
        dist[i] = INF;
    }
    dist[src] = 0; // src node is the starting airport id, inconsistency with dist[i] here
}

int getNearest(){
    int minvalue = INF;
    int minnode = 0;
    for(int i = 0; i < V; i++){
        if ((visited[i]== false) && (dist[i] < minvalue)){
            minvalue = dist[i];
            minnode = i;
        }
    }
    return minnode;
}
void dijkstra(){
    for(int i = 0; i < V; i++){
        int nearest = getNearest();
        visited[nearest] = true;
        for(int adjnode = 0; adjnode < V; adjnode++){
            if(cost[nearest][adjnode] != INF && dist[adjnode] > dist[nearest]+cost[nearest][adjnode]){
                dist[adjnode] = dist[nearest]+cost[nearest][adjnode];
                parent[adjnode] = nearest;
            }
        }
    }
}
// For testing
// void display(){
// }

// int main(void){  // part of the main function
//     cin>>V; // read in # of airports
//     for(int i = 0; i < V; i++){
//         for(int j = 0; j < V; j++){
//             cin >> cost[i][j]
//         }
//     }
//     cin >> src;
//     init();
//     aijkstra();
//     display();
// }

// implement cost matrix by using latitude and longitude from openflights, BFS traversal? 