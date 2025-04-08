/*Considere uma sala de 60 alunos (tamanho conhecido). Cada aluno
identificado pelo seu RGM possui sua lista de disciplinas (tamanho
variável para cada aluno). Desenvolver uma aplicação que:
• realize o cadastro EM ORDEM DO RGM de n alunos e, para cada
aluno, m disciplinas (controlar com pergunta “Mais disciplina?”);
• mostre todos alunos, e respectivas disciplinas, cadastrados;
• procure um aluno pelo RGM e mostre seus dados, caso exista, ou
mensagem de “não existe”;
• remova um aluno localizado pelo RGM;
• mostre a lista resultante após a remoção do aluno.
Obrigatório utilizar lista SEQUENCIAL (alunos) e ENCADEADA
(disciplinas);
• Seguir a arquitetura conceitual da figura fornecida;
• Implementar em C ou Java (não usar classes ArrayList e LinkedList do
java)
• Aplicação tipo console (sem interface gráfica), oferecendo um menu
de opções (incluir, buscar, mostrar, remover);
• Atenção para a inserção ORDENADA de alunos pelo RGM;
• Alocação da lista sequencial é estática e a encadeada é dinâmica;*/

//Bibliotecas usadas no codigo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//definição das constantes
#define Quantidade_Alunos 60
#define TamanhoRgm 8
#define TamanhoDisciplinas 50

// Lista encadeada dinâmica de Disciplinas
typedef struct Disciplina {
    char nome[TamanhoDisciplinas];
    struct Disciplina* prox;
} Disciplina;

//Struct do Aluno
typedef struct {
    char rgm[TamanhoRgm];
    Disciplina* disciplinas;
} Aluno;

//Função para ordenar alunos por RGM
void ordenacao(Aluno alunos[], int* num_alunos, Aluno novo){
    int i = *num_alunos - 1;
    while (i >= 0 && strcmp(novo.rgm, alunos[i].rgm) < 0){
        alunos[i + 1] = alunos[i];
        i--;
    }
    alunos[i + 1] = novo;
    (*num_alunos)++;
}

//Função para cadastrar os alunos 
void cadastrar_aluno(Aluno alunos[], int* num_alunos){
	//Verfifica se tem espaço
    if (*num_alunos >= Quantidade_Alunos){           
        printf("Limite de alunos atingido!\n");
        return;
    }

    Aluno novo;
    printf("Digite o RGM do Aluno: ");
    scanf("%s", novo.rgm);

    for (int i = 0; i < *num_alunos; i++){
    	//Verifica se o rgm já está cadastrado
        if (strcmp(alunos[i].rgm, novo.rgm) == 0){
            printf("RGM já cadastrado.\n");
            return;
        }
    }

    novo.disciplinas = NULL;

    char nome_disciplina[TamanhoDisciplinas];
    char mais;
    
    //loop para adicionar as disciplinas 
    do{
        printf("Digite o nome da disciplina: ");
        scanf(" %[^\n]", nome_disciplina);

        Disciplina* nova = (Disciplina*)malloc(sizeof(Disciplina));
        if (!nova){
            printf("Erro de Alocação!\n");
            exit(1);
        }
        strcpy(nova->nome, nome_disciplina);
        nova->prox = novo.disciplinas;
        novo.disciplinas = nova;

        printf("Mais disciplina? (s/n):"); //Pergunta se quer adicionar mais disciplinas
        scanf(" %c", &mais);
    } while (mais == 's' || mais == 'S');

    ordenacao(alunos, num_alunos, novo);
    printf("Aluno cadastrado com sucesso!\n");
}

//Função para exibir os alunos e suas disciplinas
void exibir_alunos(Aluno alunos[], int num_alunos) {
    if (num_alunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    for (int i = 0; i < num_alunos; i++) {
        printf("RGM: %s\n", alunos[i].rgm);
        printf("Disciplinas:\n");
        Disciplina* atual = alunos[i].disciplinas;
        while (atual) {
            printf("  - %s\n", atual->nome);
            atual = atual->prox;
        }
        printf("\n");
    }
}

//Função para buscar os alunos e se encontrado mostrar 
void buscar_aluno(Aluno alunos[], int num_alunos) {
    char rgm_buscado[TamanhoRgm];
    printf("Digite o RGM do aluno que deseja buscar: ");
    scanf("%s", rgm_buscado);

    for (int i = 0; i < num_alunos; i++) {
        if (strcmp(alunos[i].rgm, rgm_buscado) == 0) {
            printf("Aluno encontrado:\n");
            printf("RGM: %s, Disciplinas: ", alunos[i].rgm);
            Disciplina* atual = alunos[i].disciplinas;
            while (atual){
                printf("  - %s\n", atual->nome);
                atual = atual->prox;
            }
            return;
        }
    }

    printf("Aluno com RGM %s não encontrado.\n", rgm_buscado); //Caso não encontre
}

//Liberar a mémoria da lista de disciplinas
void liberar_memoria(Disciplina* d){
    while (d) {
        Disciplina* temp = d;
        d = d->prox;
        free(temp);
    }
}

//Função para apagar o aluno pelo rgm
void excluir_aluno(Aluno alunos[], int* num_alunos){
    char rgm_buscado[TamanhoRgm];
    printf("Digite o RGM do aluno que deseja excluir: ");
    scanf("%s", rgm_buscado);

    for (int i = 0; i < *num_alunos; i++){
        if (strcmp(alunos[i].rgm, rgm_buscado) == 0){
            liberar_memoria(alunos[i].disciplinas);
            for(int j = i; j < *num_alunos - 1; j++){
                alunos[j] = alunos[j + 1];
            }
            (*num_alunos)--;
            printf("Aluno removido com sucesso.\n");
            return;
        }
    }

    printf("Aluno com RGM %s não foi encontrado. \n", rgm_buscado); //Caso não encontre
}

//Função para exibir o menu
void exibir_menu() {
    printf("x --------- M E N U --------- x\n");
    printf("| [1] Cadastrar Alunos        |\n");
    printf("| [2] Mostrar Alunos          |\n");
    printf("| [3] Procurar Aluno por RGM  |\n");
    printf("| [4] Remover Aluno           |\n");
    printf("| [5] Sair do Console         |\n");
    printf("x --------------------------- x\n");
    printf(">");
}

int main() {
    setlocale(0, "portuguese"); 
    
    Aluno alunos[Quantidade_Alunos];
    int num_alunos = 0;
    int opcao;
    
    //Parte que faz o menu funcionar 
    do{
        exibir_menu();
        scanf("%d", &opcao);
        
        //swith para chamar as funções void
        switch (opcao){
            case 1:
                cadastrar_aluno(alunos, &num_alunos);
                break;
            case 2:
                exibir_alunos(alunos, num_alunos);
                break;
            case 3: 
                buscar_aluno(alunos, num_alunos);
                break;
            case 4:
                excluir_aluno(alunos, &num_alunos);
                break;
            case 5:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção Inválida!\n"); //Para o caso do usuário escolha algo diferente de 1,2,3,4 e 5
        }
    } while (opcao != 5); 
    
    //Limpa a memória depois que o programa termina 
    for (int i = 0; i < num_alunos; i++){
        liberar_memoria(alunos[i].disciplinas);
    }

    return 0;
}
