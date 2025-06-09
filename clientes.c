#include <stdio.h>   // Biblioteca padrão para entrada e saída
#include <stdlib.h>  // Biblioteca padrão para funções utilitárias (não usada diretamente aqui)
#include <string.h>  // Biblioteca para manipulação de strings

// Define o número máximo de clientes que podem ser manipulados
#define MAX_CLIENTES 100

// Define o tamanho máximo permitido para o nome do cliente
#define TAM_NOME 50

// Estrutura que representa um cliente
typedef struct {
    int id;                     // Identificador do cliente
    char nome[TAM_NOME];       // Nome do cliente
    char email[100];           // Email do cliente
} Cliente;

// Função para salvar um cliente no arquivo "clientes.txt"
void salvarCliente(Cliente c) {
    // Abre o arquivo em modo de adição (append), para não sobrescrever os dados existentes
    FILE *fp = fopen("clientes.txt", "a");
    if (fp == NULL) {
        // Verifica se houve erro ao abrir o arquivo
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    // Escreve os dados do cliente no formato: id,nome,email
    fprintf(fp, "%d,%s,%s\n", c.id, c.nome, c.email);

    // Fecha o arquivo após salvar
    fclose(fp);
}

// Função para listar todos os clientes armazenados no arquivo
void listarClientes() {
    // Abre o arquivo em modo de leitura
    FILE *fp = fopen("clientes.txt", "r");
    if (fp == NULL) {
        // Se o arquivo não existir ou não puder ser lido, informa ao usuário
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    char linha[200];  // Buffer para armazenar cada linha lida do arquivo

    // Exibe título
    printf("\nLista de clientes:\n");

    // Lê linha por linha do arquivo e imprime na tela
    while (fgets(linha, sizeof(linha), fp)) {
        printf("%s", linha);
    }

    // Fecha o arquivo após leitura
    fclose(fp);
}

// Função principal do programa
int main() {
    int opcao;          // Variável para armazenar a opção do menu escolhida pelo usuário
    Cliente cliente;    // Variável do tipo Cliente para armazenar os dados inseridos

    // Laço principal do menu
    do {
        // Exibe o menu de opções
        printf("\n=== MENU ===\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Listar clientes\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        
        // Lê a opção escolhida pelo usuário
        scanf("%d", &opcao);
        getchar(); // Limpa o caractere de nova linha deixado no buffer pelo scanf

        // Escolhe a ação de acordo com a opção selecionada
        switch (opcao) {
            case 1:
                // Cadastrando um novo cliente

                // Solicita e lê o ID do cliente
                printf("ID: ");
                scanf("%d", &cliente.id);
                getchar(); // Limpa buffer após leitura do número

                // Solicita e lê o nome do cliente
                printf("Nome: ");
                fgets(cliente.nome, TAM_NOME, stdin);
                // Remove o caractere de nova linha (\n) do final, se houver
                cliente.nome[strcspn(cliente.nome, "\n")] = '\0';

                // Solicita e lê o email do cliente
                printf("Email: ");
                fgets(cliente.email, 100, stdin);
                // Remove o caractere de nova linha (\n) do final, se houver
                cliente.email[strcspn(cliente.email, "\n")] = '\0';

                // Salva os dados do cliente no arquivo
                salvarCliente(cliente);
                printf("Cliente salvo com sucesso!\n");
                break;

            case 2:
                // Lista os clientes cadastrados
                listarClientes();
                break;

            case 0:
                // Encerra o programa
                printf("Saindo...\n");
                break;

            default:
                // Caso a opção não seja reconhecida
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0); // Repete enquanto o usuário não escolher "0"

    return 0; // Finaliza o programa
}
