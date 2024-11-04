
//Symbolic variables

//Number of nodes:
#define N 4


//Declaration of function prototypes and any other declarations
void TSP(int matrix[N][N]);
int first_minimum(int matrix[N][N], int i);
int second_minimum(int matrix[N][N], int i);
void TSP_Recursion(int matrix[N][N], int current_bound, int current_weight, int level, int current_route[]);
void copy_To_Final(int current_route[]);


//In our case we need to use "extern", because we have global variables or functions that need to be accessed
//across multiple files in the program without duplicating their definitions. In simple terms, "extern" is
//used to declare a variable or function, that is defined in another file. It essentially tells the compiler:
//"This variable or function exist, but its definition is elsewhere."
extern int final_route[N + 1];  //Definition can be found in "branch_and_bound.c" file
extern int visited[N];          //Definition can be found in "branch_and_bound.c" file
extern int final_result;        //Definition can be found in "branch_and_bound.c" file
