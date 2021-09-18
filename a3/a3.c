/*
 * Segue a minha resposta para a atividade 3 - enviado no dia 06/09/2021 - às 18:30
 * Em Linux compilar com o comando "gcc -o a3 a3.c -lm", pois se não não compila a biblioteca math
 */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <locale.h>




typedef struct cliente {
    char nome[16];
    char sobrenome[16];
    int anoNascimento;
    float gastosMes;
    float gastosTotais;

} CLIENTE;

typedef struct listaDeClientes {
    int contador;
    int jaAtualizouEsteMes;
    CLIENTE *lista;


} LISTACLIENTES;


//Protótipos
int descobrirQuantidadeDeEntradas();

void imprimirCabecalho();

void imprimirLinhaCliente(CLIENTE cliente);

void imprimirClienteQueMaisCompra(LISTACLIENTES *clientes);

void imprimirClienteEspecifico(LISTACLIENTES *clientes);

int queMesE();

int removerCliente(LISTACLIENTES *clientes);

int atualizarGastosCliente(LISTACLIENTES *clientes);

void zerarGastosMes(LISTACLIENTES *clientes);

int inserirCliente(LISTACLIENTES *clientes);

void atualizarDB(LISTACLIENTES *clientes);

void organizarClientes(LISTACLIENTES *clientes);

void lerDB(LISTACLIENTES *clientes);

void imprimirListaDeClientes(LISTACLIENTES *clientes);

void sistemaInterativo();


/**
 * Descobrindo o mês atual
 * @return int
 */
int queMesE() {
    time_t s;
    struct tm *hora;
    int esteMes;
    s = time(NULL);
    hora = localtime(&s);
    esteMes = hora->tm_mon + 1;
    return esteMes;
}

/**
 * Está função descobre o número de entradas da base de dados e calcula o número de elementos desejados na lista da struct clientes seguindo as instruções do enunciado de subir o tamanho de 10 em 10
 * @return int
 */

int descobrirQuantidadeDeEntradas() {
    FILE *arq;
    int esteMes, contador, tamanhoLista, divisao;

    arq = fopen("clientes.txt", "r");
    if (arq) {
        fscanf(arq, "%d%d", &esteMes, &contador);

    } else {
        printf("Oops, o sistema está com problema favor retornar mais tarde");
        exit(1);
    }
    fclose(arq);
    divisao = (int) ceil(contador / 10);

    tamanhoLista = (divisao * 10) + 10;
    return tamanhoLista;

}

/**
 * Função para imprimir o cabeçalho das listas de veículos
 */
void imprimirCabecalho() {
    printf("\n******************************");
    printf("\nSeu resultado é:");
    printf("\n******************************\n");
}


/**
 * Função para imprimir informação do cliente
 */

void imprimirLinhaCliente(CLIENTE cliente) {
    printf("\n******************************");
    printf("\nNome: %s %s", cliente.nome, cliente.sobrenome);
    printf("\nAno de nascimento: %d", cliente.anoNascimento);
    printf("\nGastos feitos no mês: R$%.2f", cliente.gastosMes);
    printf("\nGastos totais: R$%.2f", cliente.gastosTotais);
    printf("\n******************************\n");
}

/**
 * Listar cliente que mais compra. Como eles já são guardados por ordem decrescente de quem comprou mais no mês, basta ler o primeiro cliente da base.
 */

void imprimirClienteQueMaisCompra(LISTACLIENTES *clientes) {
    imprimirCabecalho();
    imprimirLinhaCliente(clientes->lista[0]);
}

/**
 * Listar um cliente específico
 * @param clientes
 */
void imprimirClienteEspecifico(LISTACLIENTES *clientes) {
    CLIENTE cliente;
    int i;
    int controle = 0;

    printf("\nQual o primeiro nome do cliente que deseja visualizar? Não colocar mais de dois nomes. O segundo não será considerado. ");
    scanf("%s", cliente.nome);
    fflush(stdin);

    printf("\nQual o sobrenome do cliente que deseja visualizar? Não colocar mais de dois nomes. O segundo não será considerado. ");
    scanf("%s", cliente.sobrenome);
    fflush(stdin);

    imprimirCabecalho();
    for (i = 0; i < clientes->contador; i++) {
        if (strcmp(cliente.nome, clientes->lista[i].nome) == 0 &&
            strcmp(cliente.sobrenome, clientes->lista[i].sobrenome) == 0) {
            imprimirLinhaCliente(clientes->lista[i]);
            controle = 1;
            break;

        }
    }
    if (controle == 0) {
        printf("\nInfelizmente esse cliente não existe.");

    }


}


/**
 * Remover um cliente
 * @return CLIENTE
 */

int removerCliente(LISTACLIENTES *clientes) {
    CLIENTE cliente;
    CLIENTE clienteVazio;
    LISTACLIENTES novaLista;
    novaLista.jaAtualizouEsteMes = clientes->jaAtualizouEsteMes;
    int i;
    int controle = 0;
    int certeza;
    int indiceCliente;

    printf("\nQual o primeiro nome do cliente que deseja remover? Não colocar mais de dois nomes. O segundo não será considerado. ");
    scanf("%s", cliente.nome);
    fflush(stdin);

    printf("\nQual o sobrenome do cliente que deseja remover? Não colocar mais de dois nomes. O segundo não será considerado. ");
    scanf("%s", cliente.sobrenome);
    fflush(stdin);


    for (i = 0; i < clientes->contador; i++) {
        if (strcmp(cliente.nome, clientes->lista[i].nome) == 0 &&
            strcmp(cliente.sobrenome, clientes->lista[i].sobrenome) == 0) {
            controle = 1;
            indiceCliente = i;
            printf("\nTem certeza que quer remover o cliente %s %s? Digite 1 para Sim e 0 para Não ",
                   clientes->lista[indiceCliente].nome, clientes->lista[indiceCliente].sobrenome);
            scanf("%d", &certeza);
            fflush(stdin);
            while (certeza != 0 && certeza != 1) {
                printf("\nVocê digitou um valor inválido. Digite 1 para Sim e 0 para Não ");
                scanf("%d", &certeza);
                fflush(stdin);

            }
            break;
        }
    }
    if (controle == 0) {
        printf("\nInfelizmente esse cliente não existe, para inserir um novo cliente escolha a opção 1 - Inserir Novo Cliente.");

    } else {
        if (certeza == 1) {

            clientes->contador = clientes->contador - 1;
            int j;
            j = indiceCliente;

            int y;


            for (; j < clientes->contador; j++) {
                y = j + 1;
                clientes->lista[j] = clientes->lista[y];
            }
            clientes->lista[clientes->contador] = clienteVazio;
        } else {
            printf("\nVocê decidiu não remover o cliente.");
        }
    }
    if (certeza == 0 || controle == 0) {
        return 0;
    } else {
        return 1;
    }
}

/**
* Atualizar os gastos de um cliente
* @return CLIENTE
*/
int atualizarGastosCliente(LISTACLIENTES *clientes) {
    CLIENTE cliente;
    int i;
    int controle = 0;
    float gastos_temp;
    printf("\nQual o primeiro nome do cliente que deseja atualizar? Não colocar mais de dois nomes. O segundo não será considerado. ");
    scanf("%s", cliente.nome);
    fflush(stdin);

    printf("\nQual o sobrenome do cliente que deseja atualizar? Não colocar mais de dois nomes. O segundo não será considerado. ");
    scanf("%s", cliente.sobrenome);
    fflush(stdin);


    for (i = 0; i < clientes->contador; i++) {
        if (strcmp(cliente.nome, clientes->lista[i].nome) == 0 &&
            strcmp(cliente.sobrenome, clientes->lista[i].sobrenome) == 0) {
            controle = 1;
            printf("\nDe quanto é o gasto novo do cliente %s %s? ", clientes->lista[i].nome,
                   clientes->lista[i].sobrenome);
            scanf("%f", &gastos_temp);
            clientes->lista[i].gastosMes += gastos_temp;
            break;

        }
    }
    if (controle == 0) {
        printf("\nInfelizmente esse cliente não existe, para inserir um novo cliente escolha a opção 1 - Inserir Novo Cliente.");

    }
    return controle;
}

/**
 * Soma os gastos do mês  aos gastos totais e zera os gastos do mês e soma os gastos do mês anterior aos gastos totais
 * @param clientes
 */
void zerarGastosMes(LISTACLIENTES *clientes) {
    int i;

    for (i = 0; i < clientes->contador; i++) {
        clientes->lista[i].gastosTotais += clientes->lista[i].gastosMes;
        clientes->lista[i].gastosMes = 0;
    }
}

/**
 * Inserir um cliente novo
 * @param *clientes
 * @return
 */
int inserirCliente(LISTACLIENTES *clientes) {
    CLIENTE cliente;
    int i;
    int controle = 0;

    printf("\nFavor inserir os dados do cliente pedidos abaixo: ");
    printf("\nQual o primeiro nome do cliente? Colocar somente um nome, qualquer valor depois de um  espaço será  desconsiderado. ");
    scanf("%s", cliente.nome);
    fflush(stdin);
    while (strlen(cliente.nome) > 15) {
        printf("\nO nome é longo demais, favor inserir no máximo 15 caracteres: ");
        scanf("%s", cliente.nome);
        fflush(stdin);
    }
    printf("\nQual o primeiro sobrenome do cliente? Colocar somente um nome, qualquer valor depois de um  espaço será  desconsiderado. ");
    scanf("%s", cliente.sobrenome);
    fflush(stdin);
    while (strlen(cliente.sobrenome) > 15) {
        printf("\nO sobrenome é longo demais, favor inserir no máximo 15 caracteres: ");
        scanf("%s", cliente.nome);
        fflush(stdin);
    }


    for (i = 0; i < clientes->contador; i++) {
        if (strcmp(cliente.nome, clientes->lista[i].nome) == 0 &&
            strcmp(cliente.sobrenome, clientes->lista[i].sobrenome) == 0) {
            controle = 1;
            printf("\nEste cliente já existe, se deseja atualizar seus gastos favor usar a opção 3 - Atualizar gastos de cliente? ");
            return 0;

        }
    }


    if (controle == 0) {
        printf("\nQual o ano de nascimento do cliente? ");
        scanf("%d", &cliente.anoNascimento);
        fflush(stdin);
        while (cliente.anoNascimento < 1900) {

            printf("\nVocê inseriu um ano inválido, favor usar o formato AAAA, ex. 2021: ");
            scanf("%d", &cliente.anoNascimento);
            fflush(stdin);
        }
        printf("\nDe quanto é o gasto novo do cliente? ");
        scanf("%f", &cliente.gastosMes);
        cliente.gastosTotais = 0;

        clientes->lista[clientes->contador] = cliente;
        clientes->contador += 1;

    }

    return 1;
}

/**
 * Gravar a lista de clientes completa no arquivo de texto
 * @param clienteNovo
 */

void atualizarDB(LISTACLIENTES *clientes) {
    FILE *arq;
    int i;
    arq = fopen("clientes.txt", "w");


    if (arq) {
        fprintf(arq, "%d\t%d\n", clientes->jaAtualizouEsteMes, clientes->contador);
        for (i = 0; i < clientes->contador; i++) {
            fprintf(arq, "%s\t%s\t%d\t%.2f\t%.2f\n", clientes->lista[i].nome, clientes->lista[i].sobrenome,
                    clientes->lista[i].anoNascimento,
                    clientes->lista[i].gastosMes, clientes->lista[i].gastosTotais);

        }
        printf("\nA base de dados foi atualizada com sucesso.");

    } else {

        printf("\nOops, ocorreu um erro no sistema, favor tentar novamente mais tarde.");
    }

    fclose(arq);

}

/**
 * Organizar a lista de clientes por ordem decrescente de quem comprou mais no mês
 * @param clientes
 * @return
 */

void organizarClientes(LISTACLIENTES *clientes) {
    //Organizar DB por ordem decrescente de quem gastou mais:
    int a;
    int b;
    CLIENTE cliente_temp;


    for (a = 0; a < clientes->contador; a++) {

        for (b = 0; b < clientes->contador; b++) {

            if (clientes->lista[b].gastosMes < clientes->lista[a].gastosMes) {
                cliente_temp = clientes->lista[a];
                clientes->lista[a] = clientes->lista[b];
                clientes->lista[b] = cliente_temp;
            }
        }
    }


}

/**
 * Lê a base de dados e retorna a lista de cliente.
 * @param clientes
 */
void lerDB(LISTACLIENTES *clientes) {
    FILE *arq;

    CLIENTE cliente;
    int contador = 0;

    arq = fopen("clientes.txt", "r");
    if (arq) {
        fscanf(arq, "%d%d", &clientes->jaAtualizouEsteMes, &clientes->contador);
        while (!feof(arq)) {

            fscanf(arq, "%s%s%d%f%f", cliente.nome, cliente.sobrenome, &cliente.anoNascimento, &cliente.gastosMes,
                   &cliente.gastosTotais);

            clientes->lista[contador] = cliente;
            contador++;
        }
    } else {
        printf("\nOops, ocorreu um erro no sistema, favor tentar novamente mais tarde.");

    }

    fclose(arq);


}

/**
 * Imprime a lista completa de clientes
 * @param clientes
 */
void imprimirListaDeClientes(LISTACLIENTES *clientes) {
    imprimirCabecalho();
    int i;
    for (i = 0; i < clientes->contador; i++) {
        imprimirLinhaCliente(clientes->lista[i]);
    }
}

/**
 * O coração do sistema. Faz as inicializações iniciais necessárias além de perguntar para o usuário o que quer fazer e decidir qual ação tomar dependendo da opção
 */

void sistemaInterativo() {
    LISTACLIENTES clientes;
    int bytes;
    int novoBytes;
    int entradas;
    int esteMes;
    int opcao;
    int certeza;

    esteMes = queMesE();

    entradas = descobrirQuantidadeDeEntradas();
    bytes = sizeof(CLIENTE);
    clientes.lista = (CLIENTE *) calloc(entradas, bytes);
    if (clientes.lista) {
        lerDB(&clientes);
        //Verificar se o Mês virou e zerar Gastos
        if (clientes.jaAtualizouEsteMes != esteMes) {
            printf("\nComo o mês virou, os gastos mensais foram adicionados aos gastos totais e os gastos mensais foram zerados");
            clientes.jaAtualizouEsteMes = esteMes;
            zerarGastosMes(&clientes);
            atualizarDB(&clientes);

        }
        do {
            printf("\n******************************");
            printf("\nPor favor digite a opção desejada: \n1 - Inserir novo cliente\n2 - Remover cliente\n3 - Atualizar gastos de cliente\n4 - Zerar montantes gastos\n5 - Listar cliente que mais compra\n6 - Listar todos os clientes do que mais compra para o que menos \n7 - Exibir gastos do mês de um cliente específico\n8 - Sair do sistema\n");
            scanf("%d", &opcao);
            printf("\n******************************");
            switch (opcao) {
                case 1:

                    if (inserirCliente(&clientes) == 1) {
                        organizarClientes(&clientes);
                        atualizarDB(&clientes);
                        if ((clientes.contador % 10) == 0) {
                            entradas = descobrirQuantidadeDeEntradas();
                            novoBytes = bytes * entradas;
                            clientes.lista = (CLIENTE *) realloc(clientes.lista, novoBytes);
                        }
                    }

                    break;
                case 2:
                    if (removerCliente(&clientes) == 1) {
                        atualizarDB(&clientes);
                        if ((clientes.contador % 10) == 0) {
                            entradas = descobrirQuantidadeDeEntradas();
                            novoBytes = bytes * entradas;
                            clientes.lista = (CLIENTE *) realloc(clientes.lista, novoBytes);
                        }
                    }


                    break;
                case 3:
                    if (atualizarGastosCliente(&clientes) == 1) {
                        organizarClientes(&clientes);
                        atualizarDB(&clientes);
                    }
                    break;
                case 4:
                    //Sempre que o programa roda, ele verifica se o mês virou para zerar os gastos mensais. Aqui, forneço além disso a possibilidade de zerar na mão mesmo que o mês não virou

                    printf("\nAo virar o mês o sistema automaticamente atualiza os gastos totais e zera os gastos mensais. Prosseguindo você irá fazer essa atualização novamente, tem certeza que deseja zerar os gastos mensais e atualizar os gastos totais? Digite 1 para Sim e 0 para Não ");
                    scanf("%d", &certeza);
                    fflush(stdin);
                    while (certeza != 0 && certeza != 1) {
                        printf("\nOpção inválida. Digite 1 para Sim e 0 para Não ");
                        scanf("%d", &certeza);
                        fflush(stdin);
                    }
                    if (certeza == 1) {
                        zerarGastosMes(&clientes);
                        atualizarDB(&clientes);
                        printf("\nProcesso realizado.");
                    } else {
                        printf("\nVocê escolheu não atualizar a base.");

                    }

                    break;
                case 5:
                    imprimirClienteQueMaisCompra(&clientes);
                    break;
                case 6:
                    imprimirListaDeClientes(&clientes);
                    break;
                case 7:
                    imprimirClienteEspecifico(&clientes);
                    break;
                case 8:
                    printf("\nFoi um prazer tê-lo conosco.\n");
                    break;
                default:
                    printf("\nOpção inválida, favor digitar uma das opções fornecidas\n");
                    break;
            }


        } while (opcao != 8);
        printf("\nAté a próxima.\n");

    } else {
        printf("\nSeu computador não tem memória suficiente para rodar este programa.\n");
    }

    free(clientes.lista);


}

void main() {


    sistemaInterativo();


}
