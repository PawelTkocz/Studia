#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void swap_elems(int kolejka[], int ver_pos[], int a, int b){
    int temp = kolejka[a];
    kolejka[a] = kolejka[b];
    kolejka[b] = temp;
    temp = ver_pos[kolejka[a]];
    ver_pos[kolejka[a]] = ver_pos[kolejka[b]];
    ver_pos[kolejka[b]] = temp;
}

void przesun_nizej(int kolejka[], int dist[], int ver_pos[], int n, int pos){
    int k = pos;
    int j;
    do{
        j = k;
        if(2*j<n && dist[kolejka[2*j]]<dist[kolejka[k]])
            k = 2*j;
        if(2*j+1<n && dist[kolejka[2*j+1]]<dist[kolejka[k]])
            k = 2*j+1;
        swap_elems(kolejka, ver_pos, j, k);
    }while(j != k);
}

void przesun_wyzej(int kolejka[], int dist[], int ver_pos[], int pos){
    int k = pos;
    int j;
    do{
        j = k;
        if(j>=0 && dist[kolejka[j/2]] > dist[kolejka[k]])
            k = j/2;
        swap_elems(kolejka, ver_pos, j, k);
    }while(j!=k);
}

int pop_min(int kolejka[], int dist[], int ver_pos[], int *n){
    int res = kolejka[0];
    ver_pos[res] = -1;
    *n = *n - 1;
    if(*n==0)
        return res;
    kolejka[0] = kolejka[*n];
    ver_pos[kolejka[0]] = 0;
    przesun_nizej(kolejka, dist, ver_pos, *n, 0);
    return res;
}

int main(){
    int n, m, k;
    scanf("%d %d %d\n", &n, &m, &k);
    int edges[m][2];
    short lengths[m];
    int dest[k];

    int a, b;
    short d;
    for(int i=0; i<m; i++){
        scanf("%d %d %hd\n", &a, &b, &d);
        edges[i][0] = a;
        edges[i][1] = b;
        lengths[i] = d;
    }
    for(int i=0; i<k; i++){
        scanf("%d", &a);
        dest[i] = a;
    }

    int adj_edges[n+2];
    int vertex_edges[2*m];

    for(int i=0; i<n+2; i++)
        adj_edges[i] = 0;
    for(int i=0; i<m; i++){
        adj_edges[edges[i][0]] += 1;
        adj_edges[edges[i][1]] += 1;
    }
    int sum=0;
    for(int i=1; i<n+2; i++){
        int v = adj_edges[i];
        adj_edges[i] = sum;
        sum+=v;
    }
    int vertex_counter[n+1];
    for(int i=0; i<n+1; i++)
        vertex_counter[i] = 0;
    for(int i=0; i<m; i++){
        int v1 = edges[i][0];
        int v2 = edges[i][1];
        vertex_edges[adj_edges[v1]+vertex_counter[v1]] = i;
        vertex_edges[adj_edges[v2]+vertex_counter[v2]] = i;
        vertex_counter[v1] += 1;
        vertex_counter[v2] += 1;
    }

    int kolejka[n];
    int vert_pos[n+1];
    int distances[n+1];
    for(int i=1; i<n+1; i++)
        vert_pos[i] = i-1;
    for(int i=1; i<n+1; i++){
        distances[i] = INT_MAX;
        kolejka[i-1] = i;
    }
    int kolejka_elems = n;
    distances[1] = 0;
    long long temp;
    while(kolejka_elems > 0){
        int v = pop_min(kolejka, distances, vert_pos, &kolejka_elems);
        int dist = distances[v];
        if(dist==INT_MAX)
            break;
        for(int i=adj_edges[v]; i<adj_edges[v+1]; i++){
            int e_number = vertex_edges[i];
            int dest_vertex = edges[e_number][0];
            if (dest_vertex == v)
                dest_vertex = edges[e_number][1];
            if(vert_pos[dest_vertex] != -1){
                temp = (long long)dist + lengths[e_number];
                if(temp < distances[dest_vertex]){
                    distances[dest_vertex] = temp;
                    przesun_wyzej(kolejka, distances, vert_pos, vert_pos[dest_vertex]);
                }
            }
        }
    }

    long long res = 0;
    for(int i=0; i<k; i++){
        if(distances[dest[i]]==INT_MAX){
            printf("NIE\n");
            return 0;
        }
        res += (long long)distances[dest[i]];
    }
    printf("%lld\n", 2*res);
}