#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <stack>
#include <unistd.h>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// Matriz de char representnado o labirinto
char **maze; // Voce também pode representar o labirinto como um vetor de vetores de char (vector<vector<char>>)

// Numero de linhas e colunas do labirinto
int num_rows;
int num_cols;

// Representação de uma posição
struct pos_t
{
	int i;
	int j;
};

// Estrutura de dados contendo as próximas
// posicões a serem exploradas no labirinto
std::stack<pos_t> valid_positions;
/* Inserir elemento:

	 pos_t pos;
	 pos.i = 1;
	 pos.j = 3;
	 valid_positions.push(pos)
 */
// Retornar o numero de elementos:
//    valid_positions.size();
//
// Retornar o elemento no topo:
//  valid_positions.top();
//
// Remover o primeiro elemento do vetor:
//    valid_positions.pop();

// Função que le o labirinto de um arquivo texto, carrega em
// memória e retorna a posição inicial
pos_t load_maze(const char *file_name)
{
	pos_t initial_pos;
	char aux;
	// Abre o arquivo para leitura (fopen)


	FILE *file = fopen(file_name, "r"); // Abre o arquivo para leitura					   // outFile é o arquivo onde a saída será escrita
	if (!file)
	{
		cout << "Arquivo maze.txt nao pode ser aberto" << endl;
		 abort();
		
	}
	fscanf(file,"%d %d", &num_rows, &num_cols);
	cout << num_rows << num_cols ;//printando o numero de linhas e colunas
	
	
	

	// Le o numero de linhas e colunas (fscanf)
	// e salva em num_rows e num_cols

	// Aloca a matriz maze (malloc)
	maze = (char **)malloc(num_rows * sizeof(char *));
	for (int i = 0; i < num_rows; ++i){
		// Aloca cada linha da matriz
		maze[i] = (char *)malloc(num_cols * sizeof(char));
	}
	 
		for (int i = 0; i < num_rows; ++i)
		{
			for (int j = 0; j < num_cols; ++j)
			{
				if ((aux = fgetc(file)) != EOF){//percorre o arquivo pegando caracter por caracter 
					maze[i][j] = aux;//aloca os caracteres na matrix
					if(maze[i][j] == 'e'){//se encontrar a entrada aloca sua posição inicial
						initial_pos.i = i;
						initial_pos.j = j;
					}
				}
			}
			aux = fgetc(file); 
		}
	return initial_pos;
	fclose(file);
}

// Função que imprime o labirinto
void print_maze()
{
	for (int i = 0; i < num_rows; ++i)
	{
		for (int j = 0; j < num_cols; ++j)
		{
			printf("%c", maze[i][j]);//printando cada posição da matrix de caracter
		}
		//printf("\n");
	}
}

// Função responsável pela navegação.
// Recebe como entrada a posição initial e retorna um booleando indicando se a saída foi encontrada
bool walk(pos_t pos)
{


	if(maze[pos.i][pos.j] == 's')//caso encontremos a saída 
		{
			print_maze();
			maze[pos.i][pos.j] = '.ADJ_SETOFFSET';
			usleep(50000);
			return true;
		}

	pos_t new_pos;
	
	maze[pos.i][pos.j] = '.';
	usleep(50000);
	system("clear");
	print_maze();
	
	 
		
		if(pos.i+1 < num_rows && maze[pos.i+1][pos.j] == 's'){

			system("clear");
			print_maze();
			maze[pos.i][pos.j] = '.';
			system("clear");
			print_maze();
			return true;

		}
		/*
		 	Caso alguma das posiçÕes validas para percorrer
	 	*/

		if(pos.i-1 >= 0 && pos.i-1 < num_rows && (maze[pos.i-1][pos.j] == 'x')){
			new_pos.i = pos.i-1;
			new_pos.j = pos.j;
			valid_positions.push(new_pos);
		}

		
	 	if(pos.j+1 >= 0 && pos.j+1 < num_cols && (maze[pos.i][pos.j+1] == 'x')){
			new_pos.i = pos.i;
			new_pos.j = pos.j+1;
			valid_positions.push(new_pos);
		}

		if(pos.j-1 >= 0 && pos.j-1 < num_cols && (maze[pos.i][pos.j-1] == 'x')){
			new_pos.i = pos.i;
			new_pos.j = pos.j-1;
			valid_positions.push(new_pos);
		}

		if(pos.i+1 >= 0 && pos.i+1 < num_rows && (maze[pos.i+1][pos.j] == 'x')){
			new_pos.i = pos.i+1;
			new_pos.j = pos.j;
			valid_positions.push(new_pos);
		}

		if(pos.j+1 >= 0 && pos.j+1 < num_cols && (maze[pos.i][pos.j+1] == 's')){
			new_pos.i = pos.i;
			new_pos.j = pos.j+1;
			valid_positions.push(new_pos);
		}

		
		if(pos.i-1 >= 0 && pos.i-1 < num_rows && (maze[pos.i-1][pos.j] == 's')){
			new_pos.i = pos.i-1;
			new_pos.j = pos.j;
			valid_positions.push(new_pos);
		}

		if(pos.j-1 >= 0 && pos.j-1 < num_cols && (maze[pos.i][pos.j-1] == 's')){
			new_pos.i = pos.i;
			new_pos.j = pos.j-1;
			valid_positions.push(new_pos);
		}

		if(pos.i+1 >= 0 && pos.i+1 < num_rows && (maze[pos.i+1][pos.j] == 's')){
			new_pos.i = pos.i+1;
			new_pos.j = pos.j;
			valid_positions.push(new_pos);
		}


		//Analisa se a pilha não esta vazia 
		//Pega o primeiro valor de  valid_positions, retira e chama a funçao walk

		if (!valid_positions.empty()) {
			pos_t next_position = valid_positions.top();
			valid_positions.pop();
			walk(next_position);
			while (!valid_positions.empty()){
				valid_positions.pop();
			}
			
		}
	return false;
	
}

int main(int argc, char *argv[])
{
	pos_t initial_pos = load_maze("/workspaces/maze_runner/data/maze.txt");
	bool exit_found = walk(initial_pos);
	for(int i = 0; i < num_rows; i++){//limpamos a memoria fazendo um delete na matrix de caracteres
		delete(maze[i]);
	}
	delete(maze);
	return 0;
}
