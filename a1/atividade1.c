#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//Declarando meus structs
typedef struct Veiculo {
    char marca[20];
    char modelo[20];
    int ano;
    char placa[9];
} VEICULO;

typedef struct listaVeiculos {
    int contador;
    VEICULO lista[100];
} LISTAVEICULOS;

//Declarando os protótipos de função
int queAnoE();
VEICULO  dadosVeiculo();
LISTAVEICULOS organizarDB(LISTAVEICULOS carros, VEICULO carroNovo);
void gravarDadosVeiculoDBEmOrdem(LISTAVEICULOS carros);
void gravarDadosVeiculoDB(VEICULO carro);
void escolhaInserirDados();
void imprimirCabecalho();
void imprimirListaDeCarros(LISTAVEICULOS carros);
void filtrarPorAno(LISTAVEICULOS carros) ;
void filtrarPorAnoMinimo(LISTAVEICULOS carros);
void filtrarPorMarca(LISTAVEICULOS carros);
void filtrarPorModelo(LISTAVEICULOS carros);
LISTAVEICULOS lerDBVeiculos();
void sistemaInterativo();


/**
 * Descobrindo o ano atual
 * @return int o ano atual
 */
int queAnoE() {
    time_t s;
    struct tm *hora;
    int esteAno;
    s = time(NULL);
    hora = localtime(&s);
    esteAno = hora->tm_year + 1900;
    return esteAno;
}

/**
 * Função para pedir do usuário os dados do veículo
 * @return
 */
VEICULO dadosVeiculo() {
    VEICULO carro;
    int esteAno = queAnoE() + 1;//Carros muitas vezes tem modelo do ano seguinte

    printf("Favor inserir os dados do veículo.\n");
    printf("Marca do veículo: ");
    scanf("%s", carro.marca);
    carro.marca[strlen(carro.marca)] = '\0';

    printf("Modelo do veículo: ");
    fflush(stdin);
    scanf("%s", carro.modelo);
    carro.modelo[strlen(carro.modelo)] = '\0';


    printf("Ano do veículo no formato AAAA: ");
    fflush(stdin);

    scanf("%d", &carro.ano);
    while (carro.ano < 1900 || carro.ano > esteAno) {
        fflush(stdin);
        printf("Você inseriu um ano inválido, favor usar o formato AAAA, ex. 2021: ");
        scanf("%d", &carro.ano);
    }


    printf("A placa do veículo no formato XXX-2222: ");
    fflush(stdin);

    scanf("%s", carro.placa);


    while (strlen(carro.placa) != 8) {
        fflush(stdin);
        printf("Você inseriu um formato inválido, favor inserir a placa do veículo no formato XXX-2222: ");
        scanf("%s", carro.placa);
    }

    fflush(stdin);


    return carro;
}

/**
 * Função que vai organizar os dados a serem gravados na base de dados por ano do veículo
 * @param carros
 * @param carroNovo
 * @return
 */

LISTAVEICULOS organizarDB(LISTAVEICULOS carros, VEICULO carroNovo) {


    carros.lista[carros.contador] = carroNovo;

    carros.contador = carros.contador + 1;

    VEICULO carro_temp;
    int i;
    int j;

    for (i = 0; i < carros.contador; i++) {

        for(j=0; j < carros.contador; j++){

            if(carros.lista[j].ano > carros.lista[i].ano){
                carro_temp = carros.lista[i];
                carros.lista[i] = carros.lista[j];
                carros.lista[j] = carro_temp;
            }
        }
    }



    return carros;
}

/**
 * Gravar os dados no arquivo veículos já organizados
 * @param carro
 */

void gravarDadosVeiculoDBEmOrdem(LISTAVEICULOS carros) {
    FILE *arq;
    int i;
    arq = fopen("veiculos.txt", "w");


    if (arq) {
        for (i = 0; i < carros.contador; i++) {
            fprintf(arq, "\n%s\t%s\t%d\t%s", carros.lista[i].marca, carros.lista[i].modelo, carros.lista[i].ano,
                    carros.lista[i].placa);

        }

    } else {

        printf("\nOops, ocorreu um erro no sistema, favor tentar novamente mais tarde.");
    }

    fclose(arq);

}
/**
 * Função a ser chamada ao se escolher a opção de inserir veículos
 */
void escolhaInserirDados(){

    LISTAVEICULOS carros;
    LISTAVEICULOS carrosOrganizados;
    VEICULO carro;
    carros = lerDBVeiculos();
    if (carros.contador >= 10) {
        printf("\nInfelizmente o sistema já chegou ao máximo de veículos possível. Você não poderá inserir mais veículos.");
    } else {

        carro = dadosVeiculo();


        carrosOrganizados = organizarDB(carros, carro);

        imprimirListaDeCarros(carrosOrganizados);
        gravarDadosVeiculoDBEmOrdem(carrosOrganizados);

    }
}

/**
 * Função para imprimir o cabeçalho das listas de veículos
 */
void imprimirCabecalho() {
    printf("\n******************************");
    printf("\nMarca\tModelo\tAno\tPlaca");
    printf("\n******************************\n");
}

/**
 * Imprimir lista de todos os carros
 * @param carros
 */
void imprimirListaDeCarros(LISTAVEICULOS carros) {
    int i;
    imprimirCabecalho();
    for (i = 0; i < carros.contador; i++) {

        printf("\n%s\t%s\t%d\t%s", carros.lista[i].marca, carros.lista[i].modelo, carros.lista[i].ano,
               carros.lista[i].placa);


    }

}

/**
 * Imprimir a lista de carros filtrando por um ano específico
 * @param carros
 */
void filtrarPorAno(LISTAVEICULOS carros) {
    int ano;
    int i;
    int controle = 0;
    printf("\nDe que ano são os veículos que gostaria de mostrar? ");
    scanf("%d", &ano);
    printf("\n******************************");
    printf("\nSegue a lista de veículos do ano: %d", ano);
    imprimirCabecalho();
    for (i = 0; i < carros.contador; i++) {
        if (carros.lista[i].ano == ano) {
            printf("\n%s\t%s\t%d\t%s", carros.lista[i].marca, carros.lista[i].modelo, carros.lista[i].ano,
                   carros.lista[i].placa);
            controle = 1;
        }


    }
    if(controle == 0){
        printf("\nDesculpe, não há veículos desse ano.");
    }

}

/**
 * Imprimir lista de carros com um ano mínimo
 * @param carros
 */

void filtrarPorAnoMinimo(LISTAVEICULOS carros) {
    int ano;
    int i;
    int controle = 0;
    printf("\nA partir de que ano gostaria de mostrar os veículos? ");
    scanf("%d", &ano);
    printf("\n******************************");
    printf("\nSegue a lista de veículos mais novos que: %d", ano);
    imprimirCabecalho();
    for (i = 0; i < carros.contador; i++) {
        if (carros.lista[i].ano >= ano) {
            printf("\n%s\t%s\t%d\t%s", carros.lista[i].marca, carros.lista[i].modelo, carros.lista[i].ano,
                   carros.lista[i].placa);
            controle = 1;
        }

    }
    if(controle == 0){
        printf("\nDesculpe, não há veículos mais novos do que esse ano.");
    }
}

/**
 * Imprimir a lista de carros filtrando por uma marca específico
 * @param carros
 */
void filtrarPorMarca(LISTAVEICULOS carros) {
    char marca[20];
    int i;
    int controle = 0;
    printf("\nDe que marca são os veículos que gostaria de mostrar? ");
    scanf("%s", marca);
    printf("\n******************************");
    printf("\nSegue a lista de veículos da marca: %s", marca);
    imprimirCabecalho();
    for (i = 0; i < carros.contador; i++) {
        if (strcmp(carros.lista[i].marca, marca) == 0) {
            printf("\n%s\t%s\t%d\t%s", carros.lista[i].marca, carros.lista[i].modelo, carros.lista[i].ano,
                   carros.lista[i].placa);
            controle = 1;
        }

    }
    if(controle == 0){
        printf("\nDesculpe, não há veículos dessa marca.");
    }

}

/**
 * Imprimir a lista de carros filtrando por um modelo específico
 * @param carros
 */
void filtrarPorModelo(LISTAVEICULOS carros) {
    char modelo[20];
    int i;
    int controle = 0;
    printf("\nDe que modelo são os veículos que gostaria de mostrar? ");
    scanf("%s", modelo);
    printf("\n******************************");
    printf("\nSegue a lista de veículos do modelo: %s", modelo);
    imprimirCabecalho();
    for (i = 0; i < carros.contador; i++) {
        if (strcmp(carros.lista[i].modelo, modelo) == 0) {
            printf("\n%s\t%s\t%d\t%s", carros.lista[i].marca, carros.lista[i].modelo, carros.lista[i].ano,
                   carros.lista[i].placa);
            controle = 1;
        }

    }

    if(controle == 0){
        printf("\nDesculpe, não há veículos desse modelo.");
    }

}

/**
 * Ler a base de dados e retornar todos os dados
 * @return
 */
LISTAVEICULOS lerDBVeiculos() {
    FILE *arq;
    VEICULO carro;
    LISTAVEICULOS carros;
    int contador = 0;
    arq = fopen("veiculos.txt", "r");
    if (arq) {
        while (!feof(arq)) {

            fscanf(arq, "%s%s%d%s", carro.marca, carro.modelo, &carro.ano, carro.placa);

            carros.lista[contador] = carro;
            contador++;
        }
    } else {
        printf("\nOops, ocorreu um erro no sistema, favor tentar novamente mais tarde.");

    }
    carros.contador = contador;
    fclose(arq);
    return carros;

}

/**
 * Perguntar para o usuário o que deseja e faz a decisão para chamar as funções apropriadas dependendo da escolha
 */
void sistemaInterativo() {
    int opcao;
    LISTAVEICULOS carros;

    do {
        printf(
                "\nPor favor digite a opcao desejada: \n1 - Inserir Veiculo\n2 - Listar todos os veiculos cadastrados\n3 - Listar os veiculos filtrando por ano de fabricacao\n4 - Listar os veiculos por ano de fabricacao minimo\n5 - Listar os veiculos por modelo\n6 - Listar os veiculos por marca\n7 - Sair do sistema\n");
        scanf("%d", &opcao);
        printf("\n************\n");
        switch (opcao) {
            case 1:
                escolhaInserirDados();

                break;
                case 2:
                    printf("\nSegue a lista completa de veículos\n");
                    carros = lerDBVeiculos();
                    imprimirListaDeCarros(carros);
                    break;
                    case 3:

                        carros = lerDBVeiculos();
                        filtrarPorAno(carros);
                        break;
                        case 4:
                            carros = lerDBVeiculos();
                            filtrarPorAnoMinimo(carros);

                            break;
                            case 5:
                                carros = lerDBVeiculos();
                                filtrarPorModelo(carros);
                                break;
                                case 6:
                                    carros = lerDBVeiculos();
                                    filtrarPorMarca(carros);
                                    break;
                                    case 7:
                                        printf("\nFoi um prazer tê-lo conosco.\n");
                                        break;
                                        default:
                                            printf("\nOpção inválida, favor digitar uma das opções fornecidas\n");
                                            break;
        }
        printf("\n************\n");
    } while (opcao != 7);

    printf("\nAté a próxima.\n");
}


void main() {

    sistemaInterativo();
}


