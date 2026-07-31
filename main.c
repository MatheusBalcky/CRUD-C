#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inputs_outputs.h"
#include <unistd.h>
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

typedef struct {
    int matricula;
    char nome[100];
    char curso[50];
} Aluno;

typedef struct {
    int option_number;
    int matricula;
} MenuData;

MenuData menu();

int handle_crud(MenuData data);

int handle_create();

int handle_read(int aluno_matricula);

int handle_update(int aluno_matricula);

int handle_delete(int aluno_matricula);

Aluno *struct_database(int *out_lines);

FILE *open_file(const char *fileName, const char *modo);


//*---------------------------FUNÇÃO MAIN---------------------------------//


int main (void){
    MenuData crud_option;
    int switcher = 1;

    while(switcher){
        crud_option = menu();

        handle_crud(crud_option);
        switcher = crud_option.option_number;
    }

    // struct_database();

    return 0;
}



//*----------------------FUNÇÕES----------------------------//



MenuData menu(){
    MenuData data;
    
    printf("\n================MENU DE ALUNOS================\n");
    printf("\nOlá o que você deseja, selecione uma opção abaixo.\n\n");
    printf("(1) Adicionar um aluno\n");
    printf("(2) Consultar um aluno\n");
    printf("(3) Atualizar um aluno\n");
    printf("(4) Deletar um aluno\n");
    printf("(0) Sair\n");
    printf("=================================\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &data.option_number);

    if(data.option_number == 2 || data.option_number == 3 || data.option_number == 4){
        data.matricula = inputInt("Digite o numero de matricula: ");
    }


    return data;
}
 
int handle_crud(MenuData data){
    switch (data.option_number) {

    case 1:
        handle_create();
        break;

    case 2:
        handle_read(data.matricula);
        break;
    
    case 3:
        handle_update(data.matricula);
        break;

    case 0:
        printf(RED "Programa encerrado!\n" RESET);
        break;
    default:
        printf("Opção inválida \n");
        break;
    }

    return 0;
}

int handle_create(){
    FILE *file = fopen("arq.txt", "a");
    if(file == NULL){
        printf("Error ao abrir arquivo \n.");
        return 0;
    } 

    printf("\n==============ADICIONANDO ALUNO===================\n");
    int matricula = inputInt("Digite o número de matrícula: ");

    char aluno[10];
    inputString("Digite o primeiro nome do aluno: ", aluno);

    char curso[10];
    inputString("Digite o nome do curso: ", curso);

    fprintf(file, "\n%d;%s;%s", matricula, aluno, curso);

    printf("\nAdicionando Aluno...\n");
    sleep(2);
    printf("Aluno adicionado, voltando para o menu.\n");
    sleep(2);
    printf("\n");

    fclose(file);

    return 1;
}

int handle_read(int aluno_matricula){
    FILE *file = open_file("arq.txt", "r");
    
    char line[100];
    short student_founded = 0; //controlar o estado de aluno encontrado e ñ encontrado

    //loop de busca do aluno line by line e campos
    while (fgets(line, sizeof(line), file) != NULL) {
        char *campos[3];// armazenara os ponteiros, que apontam para os campos.

        campos[0] = strtok(line, ";");
        campos[1] = strtok(NULL, ";");
        campos[2] = strtok(NULL, ";");
        int current_matricula = atoi(campos[0]);

        if(current_matricula == aluno_matricula){
            student_founded = 1;    
            printf("Aluno encontrado...\n\n");
            printf("%-20s %-30s %-15s\n", "Matricula", "Nome", "Curso");
            printf("%-20s %-30s %-15s\n", campos[0], campos[1], campos[2]);

            printf("Pressione enter para continuar!");
            while(getchar() != '\n'); //limpar o buffer
            getchar();

            break;
        }
         
    }

    if(student_founded == 0) printf(RED "Aluno da matrícula: %d, não encontrado.\n" RESET, aluno_matricula);
    

    fclose(file);
    printf(GREEN "Arquivo lido com sucesso.\n" RESET);
    sleep(2);

    return 1;
}

int handle_update(int aluno_matricula){
    FILE *file = open_file("arq.txt", "r+");

    char line[100];
    int student_founded = 0;

    while(fgets(line, sizeof(line), file) != NULL){
        char *campos[3];

        campos[0] = strtok(line, ";");
        campos[1] = strtok(NULL, ";");
        campos[2] = strtok(NULL, ";");
        int current_matricula = atoi(campos[0]);
        if(current_matricula == aluno_matricula){
            student_founded = 1;
            printf("Aluno encontrado...\n\n");
            printf("%-20s %-30s %-15s\n", "Matricula", "Nome", "Curso");
            printf("%-20s %-30s %-15s\n", campos[0], campos[1], campos[2]);

            printf("Qual campo você deseja alterar?\n");
            int number_input = inputInt("Digite 1(Matricula), 2(Nome), 3(Curso): ");



            break;
        }

    }

    return 0;
}

int handle_delete(int aluno_matricula){
    FILE *file = open_file("arq.txt", "r+");


}

Aluno *struct_database(int *out_lines) {
    FILE *file = open_file("arq.txt", "r");
    char line[256];
    int lines = 0;

    fgets(line, sizeof(line), file);
    while (fgets(line, sizeof(line), file) != NULL) lines++;
    fclose(file);

    //CRIAR O VETOR DOS ALUNOS
    FILE *file2 = open_file("arq.txt", "r");
    Aluno *alunos = malloc(lines * sizeof(Aluno)); // sobrevive após o return
    if (alunos == NULL) {
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

        i++;
    }

    fclose(file2);

    *out_lines = lines; // devolve a quantidade pro chamador
    return alunos;
}



// Aluno struct_database(){
//     FILE *file = open_file("arq.txt", "r");

//     char line[256];
//     int lines = 0;

//     fgets(line, sizeof(line), file);

//     while(fgets(line, sizeof(line), file) != NULL) lines++; // contas quantas linhas tem o arq.txt p/ criar vetor
//     fclose(file);

//     //CRIAR O VETOR DOS ALUNOS
//     FILE *file2 = open_file("arq.txt", "r");
//     Aluno alunos[lines];
//     line[0] = '\0';
//     int i = 0;

//     fgets(line, sizeof(line), file2); //pular cabeçalho
//     while(fgets(line, sizeof(line), file2) != NULL){

//         char *campo;

//         campo = strtok(line, ";"); //1 campo
//         alunos[i].matricula = atoi(campo);
//         campo = strtok(NULL, ";"); //2 campo
//         strcpy(alunos[i].nome, campo);

//         campo = strtok(NULL, ";"); //3 campo
//         strcpy(alunos[i].curso, campo);

//         i++;
//     }

//     fclose(file2);
//     return alunos;
// }







FILE *open_file(const char *file_name, const char *modo){
    FILE *file = fopen(file_name, modo);

    if(file == NULL){
        printf("Erro ao abrir arquivo");
        return NULL;
    }

    return file;
}