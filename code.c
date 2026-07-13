#include <stdio.h>
#include <stdbool.h>

#define N 6 // 0:Mumbai, 1:Delhi, 2:Bengaluru, 3:Hyd, 4:Chennai, 5:Kolkata
#define INF 9999

int W[N][N] = {
    {0, 1400, 1000, 700, INF, INF},
    {1400, 0, INF, INF, INF, 1500},
    {1000, INF, 0, 600, 350, INF},
    {700, INF, 600, 0, 600, INF},
    {INF, INF, 350, 600, 0, 1650},
    {INF, 1500, INF, INF, 1650, 0}
};

char *cities[] = {"Mumbai", "Delhi", "Bengaluru", "Hyderabad", "Chennai", "Kolkata"};

int findParent(int i, int parent[])
{// using kruskal MST
  while (parent[i] != i)
    i = parent[i];
  return i;
}

void printHeader(const char *name, const char *description)
{
  printf("\n====================================\n");
  printf(" LAYER: %s\n", name);
  printf("====================================\n");
  printf(" CONCEPT: %s\n", description);
  printf("------------------------------------\n");
  printf(" RESULTS:\n");
}

void BFS(int s)
{
  int i, v, u, f = 0, r = 0, q[N];
  printHeader("BFS (Connectivity)", "Checks broad network layout visibility.");
  bool visit[N] = {false};
  visit[s] = true;
  q[r++] = s;
  printf("  Path: ");
  while (f < r)
  {
    u = q[f++];
    printf("%s", cities[u]);
    for (v = 0; v < N; v++){
      if((W[u][v] != INF) && (visit[v] != true)){
        visit[v] = true;
        q[r++] = v;
      }
    }
    if (f < r){
      printf(" -> ");
    }
  }
  printf("\n====================================\n");
}

void DFSUtil(int u, bool visit[], int *first)
{
  int v;
  visit[u] = true;
  if (*first == 0)
    printf(" -> ");
  *first = 0;
  printf("%s", cities[u]);
  for (v = 0; v < N; v++){
    if((W[u][v] != INF) && (visit[v] != true)){
      DFSUtil(v, visit, first);
    }
  }
}

void DFS(int s)
{
  int first = 1;
  printHeader("DFS (Deep Scan)", "Explores route corridors to boundaries first.");
  bool visit[N] = {false};
  printf("  Path: ");
  DFSUtil(s, visit, &first);
  printf("\n====================================\n");
}

void dijkstra()
{
  int i, s, d, c, v, min, u, count, curr, dist[N], parent[N], p[N];
  printf("\n            ------ Cities selection ------\n");
  printf("Mumbai(0), Delhi(1), Bengaluru(2), Hyderabad(3), Chennai(4), Kolkata(5) \n |*| Enter only the number assigned to the city, not the city name itself.\n");
  printf("Enter source city :");
  scanf("%d", &s);
  printf("Enter destination city :");
  scanf("%d", &d);
  printHeader("Dijkstra (Navigation)", "Calculates point-to-point route via lowest km.");
  bool visit[N] = {false};
  for (i = 0; i < N; i++){
    dist[i] = INF;
    parent[i] = -1;
  }
  dist[s] = 0;
  for(c = 0; c < N - 1; c++)
  {
    min = INF, u = -1;
    for (v = 0; v < N; v++)
      if((visit[v] != true) && (dist[v] < min)){
        min = dist[v];
        u = v;
      }
    if (u == -1)
      break;
    visit[u] = true;
    for (v = 0; v < N; v++){
      if ((visit[v] != true) && (W[u][v] != INF) && (dist[u] + W[u][v] < dist[v])){
        dist[v] = dist[u] + W[u][v];
        parent[v] = u;
      }
    }
  }
  printf("  Total Length: %d km\n", dist[d]);
  printf("  Route Plan : ");
  count = 0, curr = d;
  while (curr != -1)
  {
    p[count++] = curr;
    curr = parent[curr];
  }
  for (int i = count - 1; i >= 0; i--){
    printf("%s", cities[p[i]]);
    if(i != 0){
      printf(" -> ");
    }
  }
  printf("\n====================================\n");
}

void bellmanFord()
{
  int s, i, k, u, v, dist[N];
  printf("\n------City selection------\n");
  printf("Mumbai(0), Delhi(1), Bengaluru(2), Hyderabad(3), Chennai(4), Kolkata(5) \n |*| Enter only the number assigned to the city, not the city name itself.\n");
  printf("Enter which city to measure all cities distance: ");
  scanf("%d", &s);
  printHeader("Bellman-Ford (Vectors)", "Computes global target lists from one origin node.");
  for(int i = 0; i < N; i++)
    dist[i] = INF;
  dist[s] = 0;
  for (k = 0; k < N - 1; k++){
    for (u = 0; u < N; u++){
      for (v = 0; v < N; v++){
        if((W[u][v] != INF) && (dist[u] + W[u][v] < dist[v])){
          dist[v] = dist[u] + W[u][v];
        }
      }
    }
  }
  printf("  Vectors Outward from %s:\n", cities[s]);
  for (i = 0; i < N; i++)
    printf("  * %-5.4s : %d km\n", cities[i], dist[i]);
  printf("====================================\n");
}

void prim()
{
  int i, c, v, u, min, cost, parent[N], key[N];
  bool mst[N] = {false};
  printHeader("Prim MST (Central Grid)", "Grows structural grid outwards from a base hub.");
  cost = 0;
  for (i = 0; i < N; i++)
    key[i] = INF;
  key[0] = 0;
  parent[0] = -1;
  for (c = 0; c < N - 1; c++)
  {
    min = INF, u = -1;
    for (v = 0; v < N; v++){
      if((mst[v] != true) && (key[v] < min)){
        min = key[v];
        u = v;
      }
    }
    mst[u] = true;
    for (v = 0; v < N; v++){
      if ((W[u][v] != INF) && (mst[v] != true) && (W[u][v] < key[v])){
        parent[v] = u;
        key[v] = W[u][v];
      }
    }
  }
  printf("  Structural Trunk Recommendations:\n");
  for (int i = 1; i < N; i++)
  {
    printf("  *  %-4.4s <-> %-4.4s : %d km\n", cities[parent[i]], cities[i], W[i][parent[i]]);
    cost += W[i][parent[i]];
  }
  printf("\n  Total Grid Matrix Footprint: %d km\n", cost);
  printf("====================================\n");
}

void kruskal()
{
  int i, j, min, u, v, cost, edges, parent[N];
  printHeader("Kruskal MST (Logistics)", "Links isolated map nodes by standard cheapest gaps.");
  cost = 0, edges = 0;
  for (i = 0; i < N; i++)
    parent[i] = i;
  printf("  Construction Steps:\n");
  while (edges < N - 1)
  {
    min = INF, u = -1, v = -1;
    for(i = 0; i < N; i++){
      for(j = 0; j < N; j++){
        if(findParent(i, parent) != findParent(j, parent) && W[i][j] < min)
        {
          min = W[i][j];
          u = i;
          v = j;
        }
      }
    }
    if (u != -1)
    {
      parent[findParent(u, parent)] = findParent(v, parent);
      edges++;
      printf("  * %-4.4s <-> %-4.4s : %d km\n", cities[u], cities[v], min);
      cost += min;
    }
  }
  printf("\n  Total Grid Matrix Footprint: %d km\n", cost);
  printf("====================================\n");
}

void floydWarshall()
{
  int i, j, k, d[N][N];
  printHeader("Floyd-Warshall (Matrix)", "Generates a complete lookup database for all city pairs.");
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      d[i][j] = W[i][j];
    }
  }
  for(k = 0; k < N; k++){
    for(i = 0; i < N; i++){
      for(j = 0; j < N; j++){
        if (d[i][k] + d[k][j] < d[i][j]){
          d[i][j] = d[i][k] + d[k][j];
        }
      }
    }
  }

  printf("         MUM  DEL  BLR  HYD  CHE  KOL\n");
  printf("  -----------------------------------\n");
  for (i = 0; i < N; i++)
  {
    printf("  %-4.4s | ", cities[i]);
    for (j = 0; j < N; j++)
    {
      if (d[i][j] == INF)// if no connection any two cities
        printf("%-5s", "INF");
      else
        printf("%-5d", d[i][j]);
    }
    printf("\n");
  }
  printf("====================================\n");
}

int main()
{
  int choice;
  while (1)
  {
    printf("\n==== BHARAT NAVIGATION PLATFORM ====\n");
    printf("1. Map Connectivity (BFS)\n2. Deep Network Scan (DFS)\n3. Point-to-Point Path (Dijkstra)\n");
    printf("4. Distance Vectors (Bellman-Ford)\n5. Central Grid Design (Prim)\n");
    printf("6. Cluster Connections (Kruskal)\n7. Matrix Lookup Table (Floyd-Warshall)\n8. Exit\n");
    printf("Select Module (1-8): ");
    if(scanf("%d", &choice) != 1){
      printf("Not a valid choice!");
      break;
    }
    if(choice == 8)
      break;
    switch(choice)
    {
    case 1:
      BFS(0);
      break;
    case 2:
      DFS(0);
      break;
    case 3:
      dijkstra();
      break;
    case 4:
      bellmanFord();
      break;
    case 5:
      prim();
      break;
    case 6:
      kruskal();
      break;
    case 7:
      floydWarshall();
      break;
    default:
      printf("Invalid choice.\n");
    }
  }
  return 0;
}