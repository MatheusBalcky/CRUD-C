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
    int option_number;
    int matricula;
} MenuData;

MenuData menu();

int handle_crud(MenuData data);

int handle_create();

int handle_read (int option);


//*---------------------------FUNÇÃO MAIN---------------------------------//


int main (void){
    MenuData crud_option;
    int switcher = 1;

    while(switcher){
        crud_option = menu();

        handle_crud(crud_option);
        switcher = crud_option.option_number;
    }


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
    FILE *file = fopen("arq.txt", "r");


    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0; //false
    }
    
    char line[100];
    short student_founded = 0; //controlar o estado de aluno encontrado e ñ encontrado

    while (fgets(line, sizeof(line), file) != NULL) {
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