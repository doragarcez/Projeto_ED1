#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Quantidade_Alunos 60
#define Limite_Disciplinas 10
#define TamanhoRgm 8
#define TamanhoDisciplinas 50
//definindo limite de arrays 
typedef struct {
    char rgm[TamanhoRgm];
    char disciplinas[Limite_Disciplinas][TamanhoDisciplinas];
    int qnt_disciplinas;
} Aluno;
// agrupando informacoes sobre o aluno
void cadastrar_alunos(Aluno alunos[], int *num_alunos) {
    while (*num_alunos < Quantidade_Alunos) {
        Aluno aluno;
        printf("Digite o RGM do aluno: ");
        scanf("%s", aluno.rgm);

        // verificando se o RGM já foi cadastrado
        for (int i = 0; i < *num_alunos; i++) {
            if (strcmp(alunos[i].rgm, aluno.rgm) == 0) {
                printf("RGM já cadastrado.\n");
                return;
            }
        }

        aluno.qnt_disciplinas = 0;

        while (1) {
            if (aluno.qnt_disciplinas >= Limite_Disciplinas) {
                printf("Número máximo de disciplinas atingido.\n");
                break;
            }

            printf("Digite a disciplina: ");
            scanf("%s", aluno.disciplinas[aluno.qnt_disciplinas]);
            aluno.qnt_disciplinas++;

            char MaisDisciplina;
            printf("Mais disciplina? (s/n): ");
            scanf(" %c", &MaisDisciplina);
            if (MaisDisciplina != 's') {
                break;
            }
        }

        alunos[*num_alunos] = aluno;
        (*num_alunos)++;

        char continuar;
        printf("Cadastrar outro aluno? (s/n): ");
        scanf(" %c", &continuar);
        if (continuar != 's') {
            break;
        }
    }
}

void ordenar_alunos(Aluno alunos[], int num_alunos) {
    for (int i = 0; i < num_alunos - 1; i++) {
        for (int j = i + 1; j < num_alunos; j++) {
            if (strcmp(alunos[i].rgm, alunos[j].rgm) > 0) {
                Aluno temp = alunos[i];
                alunos[i] = alunos[j];
                alunos[j] = temp;
            }
        }
    }
}

void exibir_alunos(Aluno alunos[], int num_alunos) {
    printf("\nAlunos cadastrados:\n");
    for (int i = 0; i < num_alunos; i++) {
        printf("RGM: %s, Disciplinas: ", alunos[i].rgm);
        for (int j = 0; j < alunos[i].qnt_disciplinas; j++) {
            printf("%s", alunos[i].disciplinas[j]);
            if (j < alunos[i].qnt_disciplinas - 1) {
                printf(", ");
            }
        }
        printf("\n");
    }
}

int main() {
    Aluno alunos[Quantidade_Alunos];
    int num_alunos = 0;

    cadastrar_alunos(alunos, &num_alunos);
    ordenar_alunos(alunos, num_alunos);
    exibir_alunos(alunos, num_alunos);

    return 0;
}