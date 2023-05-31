#include <bits/stdc++.h>
#define SIZE 100105
#define POS_INF 1000000000
#define NEG_INF -999999999
using namespace std;

struct element{
    int node=0, weight=0;

    element(){}

    element(int n, int w){
        node=n;
        weight=w;
    }

    bool operator <(const element &a)const{
        return weight<a.weight;
    }

    bool operator >(const element &a)const{
        return weight>a.weight;
    }
};

priority_queue <element, vector <element>, greater <element> > pq_t;
priority_queue <element, vector <element>, less <element> > pq_s;

int dis[SIZE];
bool vis[SIZE];
int par[SIZE];
vector <int> adj[SIZE];
vector <int> adj_s[SIZE];
vector <int> adj_t[SIZE];


int n, e;

void init_scenario(int source){
    for(int i=1; i<=n; i++){
        dis[i]=NEG_INF;
        vis[i]=false;
    }
    dis[source]=0;
}

void dijkstra_scenario(int source){
    init_scenario(source);
    par[source]=source;
    pq_s.push(element(source, 0));
    int u, v;
    while(!pq_s.empty()){
        u=pq_s.top().node;
        pq_s.pop();
        if(vis[u]) continue;
        vis[u]=true;
        for(int i=0; i<(int)adj[u].size(); i++){
            v=adj[u][i];
            if(dis[v]<dis[u]+adj_s[u][i]){
                dis[v]=dis[u]+adj_s[u][i];
                pq_s.push(element(v, dis[v]));
                par[v]=u;
            }
        }
    }
}

void init_time(int source){
    for(int i=1; i<=n; i++){
        dis[i]=POS_INF;
        vis[i]=false;
    }
    dis[source]=0;
}

void dijkstra_time(int source){
    init_time(source);
    par[source]=source;
    pq_t.push(element(source, 0));
    int u, v;
    while(!pq_t.empty()){
        u=pq_t.top().node;
        pq_t.pop();
        if(vis[u]) continue;
        vis[u]=true;
        for(int i=0; i<(int)adj[u].size(); i++){
            v=adj[u][i];
            if(dis[v]>dis[u]+adj_t[u][i]){
                dis[v]=dis[u]+adj_t[u][i];
                pq_t.push(element(v, dis[v]));
                par[v]=u;
            }
        }
    }
}

void path_print(int src, int dest){
    if(dest==src){
        printf("\n\t>>>The Path is %d ", src);
        return;
    }
    path_print(src, par[dest]);
    printf("%d ", dest);
}

int main(){
    int u, v, s, t, c_s, c_t, choice;
    scanf("%d %d", &n, &e);

    for(int i=0; i<e; i++){
        scanf("%d %d %d %d", &u, &v, &s, &t);

        adj[u].push_back(v);
        //adj[v].push_back(u);

        adj_s[u].push_back(s);
        //adj_s[v].push_back(t);

        adj_t[u].push_back(t);
        //adj_t[v].push_back(t);
    }

    while(true)
    {
        printf("\n\tEnter your source destination and target destination:");
        scanf("%d %d", &c_s, &c_t);

        printf("\n\n\tChoose an Option Number Please.......");
        printf("\n\t1. Best scenario enjoy.");
        printf("\n\t2. Lowest Time Journey.");
        printf("\n\t3. Exit.");

        printf("\n\n\tEnter your choice: ");
        scanf("%d", &choice);

        if(choice==1) {
            dijkstra_scenario(c_s);

            if(dis[c_t] == NEG_INF){
                printf("\n\t>>> No path exists.\n");
            }
            else{
                printf("\n\t>>> You will enjoy total scenario: %d\n", dis[c_t]);
                path_print(c_s, c_t);
                printf("\n");
            }
        }

        else if(choice==2) {
            dijkstra_time(c_s);

            if(dis[c_t] == POS_INF){
                printf("\n\t>>> No path exists.\n");
            }
            else{
                printf("\n\t>>> Your minimum time: %d\n", dis[c_t]);
                path_print(c_s, c_t);
                printf("\n");
            }
        }

        else if(choice==3){
            return 0;
        }

        else {
            printf("\n\tInvalid Input....\n");
        }
    }
    return 0;
}

/* Input

6 8
1 2 4 4
1 3 3 3
1 4 7 7
2 4 2 2
2 5 2 2
3 5 5 5
4 6 3 3
5 6 2 2

*/
