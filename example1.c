/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;

// pentru simplitate, folosim int uri pt a numi restaurantele/locatiile
// ex: 1 - restaurantul 1 si tot asa

typedef struct g
{
    int v;
    int *vis;
    struct Node **alst;
} GPH;

typedef struct s
{
    int t;
    int scap;
    int *arr;
} STK;

NODE *create_node(int v)
{
    NODE *nn = (NODE *)malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GPH *g, int src, int dest)
{
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;

    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

GPH *create_g(int v)
{
    GPH *g = (GPH *)malloc(sizeof(GPH));
    g->v = v;
    g->alst = (NODE **)malloc(sizeof(NODE *) * v);
    g->vis = (int *)malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++)
    {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }
    return g;
}

STK *create_s(int scap)
{

    STK *s = (STK *)malloc(sizeof(STK));

    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;
    return s;
}

void push(int pshd, STK *s)
{
    if (s->t + 1 < s->scap)
    {
        s->t = s->t + 1;
        s->arr[s->t] = pshd;
    }
}

void DFS(GPH *g, STK *s, int v_nr)
{
    NODE *adj_list = g->alst[v_nr];
    NODE *aux = adj_list;
    g->vis[v_nr] = 1;
    push(v_nr, s);
    while (aux != NULL)
    {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0)
            DFS(g, s, con_ver);
        aux = aux->next;
    }
}

void insert_edges(GPH *g, int edg_nr, int nrv)
{
    int src, dest;
    printf("adauga %d munchii (de la 0 la %d)\n", edg_nr, nrv - 1);
    for (int i = 0; i < edg_nr; i++)
    {
        scanf("%d%d", &src, &dest);
        add_edge(g, src, dest);
    }
}

void wipe(GPH *g, int nrv)
{
    for (int i = 0; i < nrv; i++)
    {
        g->vis[i] = 0;
    }
}

void canbe(GPH *g, int nrv, STK *s1, STK *s2, int ans)
{
    for (int i = 0; i < nrv; i++)
    {
        for (int j = 0; j < nrv; j++)
        {
            s1->t = -1;
            s2->t = -1;
            wipe(g, nrv);
            DFS(g, s1, i);
            wipe(g, nrv);
            DFS(g, s2, j);

            for (int k = 0; k <= s1->t; k++)
            {
                for (int l = 0; l <= s2->t; l++)
                {
                    if (s1->arr[k] == j && s2->arr[l] == i)
                    {
                        printf("Drum direct sau indirect intre %d si %d: DA\n", i, j);
                        ans = 1;
                        goto end;
                    }
                }
            }
        }
    }

end:
    if (!ans)
        printf("Nu exista drum intre nodurile date\n");
}

int main()
{
    int nrv;
    int edg_nr;
    int ans = 0;

    printf("cate noduri are girafa? ");
    scanf("%d", &nrv);

    printf("cate muchii are giraful? ");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);
    STK *s1 = create_s(2 * nrv);
    STK *s2 = create_s(2 * nrv);

    insert_edges(g, edg_nr, nrv);
    canbe(g, nrv, s1, s2, ans);

    return 0;
}
