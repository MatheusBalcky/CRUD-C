#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inputs_outputs.h"
#include <unistd.h>
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

typedef struct {
    int matricula;
    char nome[100];
    char curso[50];
} Aluno;

int menu();
int handle_crud(int menu_option);
int handle_create();
int handle_read();
int handle_update();
int handle_delete();
Aluno *struct_database(int *out_lines);
FILE *open_file(const char *fileName, const char *modo);


//*---------------------------FUNÇÃO MAIN---------------------------------//
int main (void){
    int crud_option;
    int switcher = 1;

    while(switcher){
        crud_option = menu();

        handle_crud(crud_option);
        switcher = crud_option;
    }

    return 0;
}




//*----------------------FUNÇÕES----------------------------//

int menu(){
    int menu_option = 0;
    
    printf("\n================MENU DE ALUNOS================\n");
    printf("\nOlá o que você deseja, selecione uma opção abaixo.\n\n");
    printf("(1) Adicionar um aluno\n");
    printf("(2) Consultar um aluno\n");
    printf("(3) Atualizar um aluno\n");
    printf("(4) Deletar um aluno\n");
    printf("(0) Sair\n");
    printf("=================================\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &menu_option);

    return menu_option;
}
 
int handle_crud(int menu_option){

    switch (menu_option) {

    case 1:
        handle_create();
        break;

    case 2:
        handle_read();
        break;
    
    case 3:
        handle_update();
        break;

    case 4:
        handle_delete();
        break;

    case 0:
        printf(RED "\nPrograma encerrado!\n\n" RESET);
        break;

    default:
        printf("Opção inválida \n");
        break;
    }

    return 0;
}

int handle_create(){
    FILE *file = open_file("arq.txt", "a");

    printf("\n==============ADICIONANDO ALUNO===================\n");

    int matricula = inputInt("Digite o número de matrícula: ");

    char aluno[10];
    inputString("Digite o primeiro nome do aluno: ", aluno);

    char curso[10];
    inputString("Digite o nome do curso: ", curso);

    
    fprintf(file, "\n%d;%s;%s", matricula, aluno, curso);

    printf(GREEN "\nAluno adicionado. Pressione enter para continuar!\n" RESET);
    while(getchar() != '\n'); //limpar o buffer
    getchar();

    fclose(file);

    return 1;
}

int handle_read(){
    printf("\n==============CONSULTANDO ALUNO===================\n");

    int aluno_matricula = inputInt("Digite o numero de matricula: ");

    int alunos_lines;
    Aluno *alunos = struct_database(&alunos_lines); // MONTAR MATRIZ DOS DADOS.

    for(int i = 0; i < alunos_lines; i++){
        if(alunos[i].matricula == aluno_matricula){
            printf(GREEN "Aluno encontrado...\n\n" RESET);

            printf("%-10s %-20s %-15s\n", "Matrícula", "Nome", "Curso");
            printf("%-10d%-20s %-15s\n", alunos[i].matricula, alunos[i].nome, alunos[i].curso);

            printf("Pressione enter para continuar!\n");
            while(getchar() != '\n'); //limpar o buffer
            getchar();

            free(alunos);
            return 1; 
        }
    }

    printf(RED "Aluno da matrícula: %d, não encontrado.\n" RESET, aluno_matricula);
    printf("Pressione enter para continuar!\n");
    while(getchar() != '\n'); //limpar o buffer
    getchar();
    return 0;
}

int handle_update(){
    printf("\n==============ATUALIZANDO ALUNO===================\n");

    int aluno_matricula = inputInt("Digite o numero de matricula: ");

    int lines = 0;
    Aluno *alunos = struct_database(&lines);
    int aluno_index = -1;

    for(int i = 0; i < lines; i++){
        if(alunos[i].matricula == aluno_matricula){
            printf(GREEN "Aluno p/ atualizar encontrado...\n\n" RESET);

            printf("%-10s %-20s %-15s\n", "Matrícula", "Nome", "Curso");
            printf("%-10d%-20s %-15s\n", alunos[i].matricula, alunos[i].nome, alunos[i].curso);

            aluno_index = i; //& WSALVA A POSIÇÃO DO ALUNO NA MATRIX PARA ALTERAÇÃO
            break;
        }
    }

    if(aluno_index == -1){
        printf(RED "Aluno não encontrado." RESET);
        return 0;
    }

    int update_num = inputInt("Qual campo do aluno voce deseja alterar.\nDigite o numero, (0) Matricula, (1) Nome, (2) Curso: ");

    switch (update_num){
    case 0:
        int new_matricula = inputInt("Digite o novo número de matricula: ");
        alunos[aluno_index].matricula = new_matricula;
        break;
    case 1:
        char new_name[10];
        inputString("Digite o novo nome: ", new_name);
        strcpy(alunos[aluno_index].nome, new_name);
        break;
    case 2:
        char new_curso[10];
        inputString("Digite o novo curso: ", new_curso);
        strcpy(alunos[aluno_index].curso, new_curso);
        break;
    default:
        printf("Campo inválido.");
        break;
    }

    //& REESCREVE O ARQUIVO.TXT COM AS NOVAS ALTERAÇÕES

    FILE *file = open_file("arq.txt", "w");

    fprintf(file, "matricula;nome;curso\n");

    for(int i = 0; i < lines; i++){
        fprintf(file, "%d;%s;%s", alunos[i].matricula, alunos[i].nome, alunos[i].curso);
        if(i + 1 == lines) break;
        fprintf(file, "\n");
    }

    fclose(file);

    return 0;
}

int handle_delete(){
    int aluno_matricula = inputInt("Qual a matricula do aluno p/ ser deletado: ");

    int alunos_lines = 0;
    Aluno *alunos = struct_database(&alunos_lines);

    int aluno_indice = -1;
    for(int i = 0; i < alunos_lines; i++){
        if(alunos[i].matricula == aluno_matricula){
            aluno_indice = i;

            printf(GREEN "Aluno encontrado...\n\n" RESET);

            printf("%-10s %-20s %-15s\n", "Matrícula", "Nome", "Curso");
            printf("%-10d%-20s %-15s\n", alunos[i].matricula, alunos[i].nome, alunos[i].curso);

            printf("Pressione enter para continuar e deletar o aluno!\n");
            while(getchar() != '\n'); //limpar o buffer
            getchar();
        }
    }

    if(aluno_indice == -1){
        printf(RED "Aluno não encontrado." RESET);
        return 0;
    }

    //& REMOVER ALUNO COM DESLOCAMENTO DOS ELEMENTOS;
    alunos_lines--; //alunos_lines-- vai garantir q o for n ultrapasse o final do vetor.
    for(int i = aluno_indice; i < alunos_lines; i++){
        alunos[i] = alunos[i + 1]; 
    }

    //& REESCREVE O ARQUIVO.TXT COM AS NOVAS ALTERAÇÕES
    FILE *file = open_file("arq.txt", "w");

    fprintf(file, "matricula;nome;curso\n");

    for(int i = 0; i < alunos_lines; i++){
        fprintf(file, "%d;%s;%s", alunos[i].matricula, alunos[i].nome, alunos[i].curso);
        if(i + 1 == alunos_lines) break;
        fprintf(file, "\n");
    }

    fclose(file);
    free(alunos);
    printf(RED "Aluno deletado" RESET);
    return 0;
}

Aluno *struct_database(int *out_lines) {
    FILE *file = open_file("arq.txt", "r");
    char line[256];
    int lines = 0;

    fgets(line, sizeof(line), file); //& DESCARTA CABEÇALHO

    while (fgets(line, sizeof(line), file) != NULL) lines++;
    fclose(file);

    //CRIAR O VETOR DOS ALUNOS
    FILE *file2 = open_file("arq.txt", "r");
    Aluno *alunos = malloc(lines * sizeof(Aluno)); // sobrevive após o return
    if (alunos == NULL) {
        printf(RED "Erro ao alocar memória para estruturar matriz" RESET);
        fclose(file2);
        return NULL;
    }

    fgets(line, sizeof(line), file2); // pular cabeçalho

    int i = 0;
    while (fgets(line, sizeof(line), file2) != NULL) {
        char *campo;

        campo = strtok(line, ";");
        alunos[i].matricula = atoi(campo);

        campo = strtok(NULL, ";");
        strcpy(alunos[i].nome, campo);

        campo = strtok(NULL, ";");
        strcpy(alunos[i].curso, campo);
        alunos[i].curso[strcspn(alunos[i].curso, "\n")] = '\0';

        i++;
    }

    fclose(file2);

    *out_lines = lines; // devolve a quantidade pro chamador
    return alunos;
}

FILE *open_file(const char *file_name, const char *modo){
    FILE *file = fopen(file_name, modo);

    if(file == NULL){
        printf("Erro ao abrir arquivo");
        return NULL;
    }

    return file;
}