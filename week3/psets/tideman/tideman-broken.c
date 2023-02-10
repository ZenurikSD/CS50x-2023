#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs();
void add_pairs_wrap(int ranks[]);
void show_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
int test_paths(int p_loser, int p_index);
void print_winner(void);



int main(int argc, string argv[])
{
    // Check for invalid usage ==================================
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }


    // Populate array of candidates ==================================
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }


    // Clear graph of locked in pairs ==================================
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }


    // Get nº of voters ============================================
    pair_count = 0;
    int voter_count = get_int("Number of voters: ");


    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);
        add_pairs_wrap(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    // lock_pairs();
    // print_winner();
    return 0;
}


// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            // printf("Rank %i: %s ✅\n", rank+1, candidates[i]); //debug
            return true;
        }
    }

    return false;
}


// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // A posição i ganha um ponto para todas as outras abaixo (i+1), (i+2)..
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i+1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }


    //debug - Exibe a matriz de preferências
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i ", preferences[i][j]);
        }
        printf("\n");
    }

    return;
}



// ???
void add_pairs_wrap(int ranks[])
{
    int count = 0;
    int cnddt_a = 0; //pontuação
    int cnddt_b = 0;

    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i+1; j < candidate_count; j++)
        {
            cnddt_a = preferences[ranks[i]][ranks[j]];
            cnddt_b = preferences[ranks[j]][ranks[i]];


            if (i != j)
            {
                if (cnddt_a > cnddt_b)
                {
                    pairs[count].winner = ranks[i];
                    pairs[count].loser  = ranks[j];
                    pair_count++;
                }
                else if (cnddt_b > cnddt_a)
                {
                    pairs[count].winner = ranks[j];
                    pairs[count].loser  = ranks[i];
                    pair_count++;
                }
            }

            count ++;
        }
    }

    show_pairs();
}



// Record pairs of candidates where one is preferred over the other
// ✅ Não sei se o modelo tá errado mas para atualizar as preferências certas, eu preciso inserir o candidato no rank escolhido. Eu preciso do vetor de ranks aqui também.
void add_pairs()
{

    return;
}




// Mostre quais são os pares salvos
void show_pairs(void)
{
    printf("\n");

    for (int i = 0; i < pair_count; i++)
    {
        printf(
            "Par %i: %s %i x %i %s\n", i+1,
            candidates[pairs[i].winner],
            preferences[pairs[i].winner][pairs[i].loser],
            preferences[pairs[i].loser][pairs[i].winner],
            candidates[pairs[i].loser]
            );
    }

    return;
}



// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int winners[pair_count], losers[pair_count], pair_win_margin[pair_count];


    //Constrói o vetor de margens de vitória dos pares.
    for (int i = 0; i < pair_count; i++)
    {
        winners[i] = preferences[pairs[i].winner][pairs[i].loser];
        losers[i]  = preferences[pairs[i].loser][pairs[i].winner];

        pair_win_margin[i] = winners[i] - losers[i];

        printf("Par %i margem: %i\n", i+1, pair_win_margin[i]); //debug
    }

    //Selection sort
    int max = 0;
    pair aux;

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (pair_win_margin[j] > pair_win_margin[i])
            {
                max = j;
            }
        }

        aux = pairs[i];
        pairs[i] = pairs[max];
        pairs[max] = aux;
    }


    printf("\nSorted?");
    show_pairs();

    return;
}


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Testa o caminho de cada par para decidir se trava o par atual
    for (int i = 0; i < pair_count; i++)
    {
        if (test_paths(pairs[i].loser, i) == 2)
        {
            //trave esse par
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}


// Recursivamente percorre os caminhos de cada par para encontrar se um ciclo vai ser criado ou não
int test_paths(int p_loser, int p_index)
{
    int result = 0;

    //caso base
    if (p_loser == pairs[p_index].winner)
    {
        return 1; //cai em ciclo
    }

    int i = 0;

    while (i < pair_count)
    {
        if (p_loser == pairs[i].winner)
        {
            i++;
            break;
        }
        else if (i == pair_count - 1)
        {
            return 2;
        }

        i++;
    }

    result = test_paths(pairs[i].loser, p_index);
    return result;


    // //caso recursivo
    // //Percorre todos os pares e usa o perdedor como ponte entre os caminhos
    // for (int i = 0; i < pair_count; i++)
    // {
    //     if (p_loser == pairs[i].winner)
    //     {
    //         // Continua "recursando" até que atinja um caso base
    //         // Se encontrar um par onde o perdedor atual vence,
    //         // passe o perd. desse par para o próximo nível
    //         test_paths(pairs[i].loser, p_index);
    //     }
    //     else if (i == pair_count - 1)
    //     {
    //         //Se percorrer todos os pares sem encontrar nada
    //         return 2;
    //     }
    // }

    // return;
}


// Print the winner of the election
void print_winner(void)
{
    //esse código não é ideal, eu só quero terminar isso logo.

    int seen_cndt_count[candidate_count];

    for (int i = 0; i < pair_count; i++)
    {
        // Se o par aparecer na matriz locked,
        // incrementa a contagem de candidatos vistos
        if (locked[pairs[i].winner][pairs[i].loser] == true)
        {
            seen_cndt_count[pairs[i].winner] += 2;
            seen_cndt_count[pairs[i].loser] += 1;
        }
    }

    // O candidato que tiver uma quantidade par de pontos é a raiz do gráfico, o vencedor.
    int pontos = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        pontos = seen_cndt_count[i];

        if (pontos > 0 && pontos % 2 == 0)
        {
            // vencedor
            printf("%s\n", candidates[i]);
        }
    }


    return;
}