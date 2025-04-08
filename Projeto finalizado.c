/*Considere uma sala de 60 alunos (tamanho conhecido). Cada aluno
identificado pelo seu RGM possui sua lista de disciplinas (tamanho
vari�vel para cada aluno). Desenvolver uma aplica��o que:
� realize o cadastro EM ORDEM DO RGM de n alunos e, para cada
aluno, m disciplinas (controlar com pergunta �Mais disciplina?�);
� mostre todos alunos, e respectivas disciplinas, cadastrados;
� procure um aluno pelo RGM e mostre seus dados, caso exista, ou
mensagem de �n�o existe�;
� remova um aluno localizado pelo RGM;
� mostre a lista resultante ap�s a remo��o do aluno.
Obrigat�rio utilizar lista SEQUENCIAL (alunos) e ENCADEADA
(disciplinas);
� Seguir a arquitetura conceitual da figura fornecida;
� Implementar em C ou Java (n�o usar classes ArrayList e LinkedList do
java)
� Aplica��o tipo console (sem interface gr�fica), oferecendo um menu
de op��es (incluir, buscar, mostrar, remover);
� Aten��o para a inser��o ORDENADA de alunos pelo RGM;
� Aloca��o da lista sequencial � est�tica e a encadeada � din�mica;*/

//Bibliotecas usadas no codigo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//defini��o das constantes
#define Quantidade_Alunos 60
#define TamanhoRgm 8
#define TamanhoDisciplinas 50

// Lista encadeada din�mica de Disciplinas
typedef struct Disciplina {
    char nome[TamanhoDisciplinas];
    struct Disciplina* prox;
} Disciplina;

//Struct do Aluno
typedef struct {
    char rgm[TamanhoRgm];
    Disciplina* disciplinas;
} Aluno;

//Fun��o para ordenar alunos por RGM
void ordenacao(Aluno alunos[], int* num_alunos, Aluno novo){
    int i = *num_alunos - 1;
    while (i >= 0 && strcmp(novo.rgm, alunos[i].rgm) < 0){
        alunos[i + 1] = alunos[i];
        i--;
    }
    alunos[i + 1] = novo;
    (*num_alunos)++;
}

//Fun��o para cadastrar os alunos 
void cadastrar_aluno(Aluno alunos[], int* num_alunos){
	//Verfifica se tem espa�o
    if (*num_alunos >= Quantidade_Alunos){           
        printf("Limite de alunos atingido!\n");
        return;
    }

    Aluno novo;
    printf("Digite o RGM do Aluno: ");
    scanf("%s", novo.rgm);

    for (int i = 0; i < *num_alunos; i++){
    	//Verifica se o rgm j� est� cadastrado
        if (strcmp(alunos[i].rgm, novo.rgm) == 0){
            printf("RGM j� cadastrado.\n");
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
            printf("Erro de Aloca��o!\n");
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

//Fun��o para exibir os alunos e suas disciplinas
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

//Fun��o para buscar os alunos e se encontrado mostrar 
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

    printf("Aluno com RGM %s n�o encontrado.\n", rgm_buscado); //Caso n�o encontre
}

//Liberar a m�moria da lista de disciplinas
void liberar_memoria(Disciplina* d){
    while (d) {
        Disciplina* temp = d;
        d = d->prox;
        free(temp);
    }
}

//Fun��o para apagar o aluno pelo rgm
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

    printf("Aluno com RGM %s n�o foi encontrado. \n", rgm_buscado); //Caso n�o encontre
}

//Fun��o para exibir o menu
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
        
        //swith para chamar as fun��es void
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
                printf("Op��o Inv�lida!\n"); //Para o caso do usu�rio escolha algo diferente de 1,2,3,4 e 5
        }
    } while (opcao != 5); 
    
    //Limpa a mem�ria depois que o programa termina 
    for (int i = 0; i < num_alunos; i++){
        liberar_memoria(alunos[i].disciplinas);
    }

    return 0;
}
