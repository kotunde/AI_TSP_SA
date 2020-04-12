#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define MAX_ITER 30
#define T0 100
#define a 0.95
#define N 10

typedef struct state
{
    int ** adj; //adjacency matrix
    int * seq; //sequence of towns
} state;

void simulatedAnnealing(state*);
double temperature(int);
void randomNeighbor(state *);
int f(state *);
int probability(double);
int** allocateMtrx(int);
void shuffle(int *, size_t);
void fillMatrix(int **);
void printMtrx(int ** mtrx,int n);

int main()
{
    srand(time(NULL));
    //generate initial state
    state init;
    //allocation
    init.adj = allocateMtrx(N);
    init.seq = (int*)malloc(N * sizeof(int));
    if (init.seq == NULL)
    {
        printf("Allocation failed");
        return 0;
    }
    //fill with values
    for(int i=0; i<N; ++i)
    {
        init.seq[i] = i;
    }
    //randomize array
    shuffle(init.seq,N);

    //print sequence
    printf("Sequence of towns\n");
    for(int i=0; i<N; ++i)
    {
        printf("%i ",init.seq[i]);
    }
    printf("\n");

    //fill adjacency matrix
    fillMatrix(init.adj);
    //print distances
    printMtrx(init.adj,N);

    //call function
    simulatedAnnealing(&init);

    printf("\nOptimal sequence of towns");
    for(int i=0; i<N; ++i)
    {
        printf("%i ",init.seq[i]);
    }
    printf("\n");

    return 0;
}

void simulatedAnnealing(state * act)
{
    for (int i=0; i<MAX_ITER; ++i)
    {
        double T = temperature(i);
        if (T <= 0.0001)
        {
            return;
        }

        state * next = (state *) malloc(sizeof(state));

        next->adj = (int **) malloc(N * sizeof(int *));
        for(int j = 0; j < N; ++j)
        {
            next->adj[j] = (int *) malloc(N * sizeof(int));
        }

        next->seq = (int *) malloc(N * sizeof(int));

        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < N; ++j)
            {
                next->adj[i][j] = act->adj[i][j];
            }

            next->seq[i] = act->seq[i];
        }



        randomNeighbor(act);



        double DeltaE = f(next) - f(act);
        if (DeltaE < 0)
        {
            act = &next;
        }
        else
        {
            if (probability(exp(-DeltaE/T)))
            {
                act = &next;
            }
        }
    }
}

void randomNeighbor(state* act)
{
    shuffle(act->seq,N);
}

int f(state * stateX)
{
    int distSum = 0;
    for(int i=0; i<N-1; ++i)
    {
        //dist between stateX.seq[i] - stateX.seq[i+1]
        distSum += stateX->adj[stateX->seq[i]][stateX->seq[i+1]];
    }
    return distSum;
}

int probability(double p)
{
    if ((double)(rand()%101)/100 >= p)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

double temperature(int i)
{
    return T0 * pow(a,i);
}

void printMtrx(int ** mtrx,int n)
{
    printf("- - - - - - - - - \n\n");
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            printf("%2d ",mtrx[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int** allocateMtrx(int n)
{
    int **mtrx = (int**)malloc(n * sizeof(int*));
    if (mtrx == NULL)
    {
        printf("Allocation failed");
        return 0;
    }
    for (int i=0; i<n; ++i)
    {
        mtrx[i] = (int*)malloc(n * sizeof(int));
        if (mtrx[i] == NULL)
        {
            printf("Allocation failed");
            return 0;
        }
    }
    return mtrx;
}

void fillMatrix(int** mtrx)
{
    for (int i=0; i<N; ++i)
    {
        for(int j=0; j<N; ++j)
        {
            if(i==j)
            {
                mtrx[i][j] = 0;
            }
            else
            {
                mtrx[i][j] = (rand() % N) +1;
            }
        }
    }
}

void shuffle(int *array, size_t n)
{
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}