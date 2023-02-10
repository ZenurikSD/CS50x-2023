#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];
// int preferences[3][3] = {{0, 7, 3}, {2, 0, 5}, {6, 4, 0}};

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
int path_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void show_pref_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
int test_paths(int curr_loser, int base_index);
void show_locked();
void print_winner(void);


// =========================================================[MAIN]======
int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
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

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

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

        printf("\n");
    }

    //Pqp automatiza isso logo ===========================================================
    // candidates[0] = "ana";
    // candidates[1] = "bruno";
    // candidates[2] = "carlos";
    // candidate_count = 3;
    // pair_count = 0;


    add_pairs();
    // show_pref_pairs(); //apaga
    sort_pairs();
    // show_pref_pairs(); //apaga
    lock_pairs();
    // show_locked(); //apaga
    print_winner();
    return 0;
}


// =========================================================[FUNÇÕES]======
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
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }

    return;
}


// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // percorro a grade de preferências da mesma forma de cima
    // Observo a disputa entre X e Y,
    //   Se X vs Y é maior que Y vs X, ou vice versa, salva o par.

    int points_x = 0;
    int points_y = 0;

    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            points_x = preferences[i][j];
            points_y = preferences[j][i];

            if (points_x > points_y)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;

                pair_count ++;
            }
            else if (points_y > points_x)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;

                pair_count ++;
            }
        }
    }

    return;
}


// Mostre a matriz de preferências e quais são os pares salvos
void show_pref_pairs(void)
{
    //Exibe a matriz de preferências
    printf("[preferences]: \n");
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i ", preferences[i][j]);
        }
        printf("\n");
    }

    printf("\n");


    // Exibe os pares
    for (int i = 0; i < pair_count; i++)
    {
        printf(
            "Par %i: %s %i x %i %s | diff: %i\n", i + 1,
            candidates[pairs[i].winner],
            preferences[pairs[i].winner][pairs[i].loser],
            preferences[pairs[i].loser][pairs[i].winner],
            candidates[pairs[i].loser],
            preferences[pairs[i].winner][pairs[i].loser] -
            preferences[pairs[i].loser][pairs[i].winner]
        );
    }

    return;
}



// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //Percorra todos os pares e crie um vetor que armazena a margem de vitória
    int wins[pair_count];

    for (int i = 0; i < pair_count; i++)
    {
        wins[i] = preferences[pairs[i].winner][pairs[i].loser] -
                  preferences[pairs[i].loser][pairs[i].winner];
    }


    // Meu algoritmo de bubble sort
    int unsorted_count = pair_count;
    pair par_aux;
    int aux;

    while (unsorted_count > 1)
    {
        for (int i = 0; i < unsorted_count - 1; i++)
        {
            if (wins[i] < wins[i + 1])
            {
                par_aux = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = par_aux;

                //inverte também as margens de vitória, necessário para as comparações
                aux = wins[i];
                wins[i] = wins[i + 1];
                wins[i + 1] = aux;
            }
        }
        unsorted_count --;
    }

    // printf("\n🔄 Ordenou?\n");

    return;
}


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    /* Percorra todos os pares e envie o índice atual para uma função recursiva
     * para determinar se trava o par ou não.
     */
    for (int i = 0; i < pair_count; i++)
    {
        test_paths(pairs[i].loser, i);
    }

    return;
}


//Percorre recursivamente o caminho do par enviado de lock_pairs()
/* curr_loser: índice do perdedor, faz a conexão entre uma linha e a próxima no gráfico, cria o caminho.
 * base_index: O índice do par sendo testado lá no lock_pairs;
*/
int test_paths(int path_loser, int base_index)
{
    //Caso base
    int result = 0;

    if (path_loser == pairs[base_index].winner)
    {
        return 1; //o caminho alcança um loop
    }


    for (int i = 0; i < pair_count; i++)
    {
        //Se o perdedor atual aparece vencendo em um dos pares travados com true
        if (locked[path_loser][pairs[i].loser] == true)
        {
            return test_paths(pairs[i].loser, base_index);
        }
        else if (i == pair_count - 1)
        {
            locked[pairs[base_index].winner][pairs[base_index].loser] = true;
        }
    }

    return result;
}


//Exibe a matriz de pares travados
void show_locked()
{
    printf("[Locked pairs]: \n");
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (locked[i][j] == true)
            {
                printf("✅ ");
            }
            else if (locked[i][j] == false)
            {
                printf("❌ ");
            }
        }
        printf("\n");
    }
}



// Print the winner of the election
void print_winner(void)
{
    int source = 0;

    //Percorre todas as linhas da matriz locked e conta quantas vezes um candidato tem seu par travado.
    // Minha lógica é: Se ele não perde, não tem uma seta apontando pra ele no
    // gráfico, portanto, essa é a raiz.
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (i != j)
            {
                if (locked[i][j] == true)
                {
                    source++;
                }
            }
        }

        if (source == pair_count - 1)
        {
            //vencedor
            printf("%s\n", candidates[pairs[i].winner]);
            break;
        }
    }


    return;
}