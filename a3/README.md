# A3 - UAM - Ténicas de Programação
### Minha resolução para a A3 de Técnicas de Programação do meu curso de Ciência da Computação da Universidade Anhembi Morumbi.

#### O enunciado da questão era o seguinte:

Em algumas situações, para a implementação de um sistema computacional, não se conhece, previamente, qual o tamanho da massa de dados que será efetivamente manipulada. Em tais casos, pode ser usado o recurso de alocação dinâmica de memória. Com tal recurso, uma região de memória poderá ser alocada, sob demanda de modo a tornar o programa mais flexível em relação à quantidade de itens a serem manipulados. Essa flexibilidade torna o programa escalável.

O objetivo desta questão é exercitar a manipulação de ponteiros em um cenário onde se exige a alocação dinâmica de memória através da implementação de um programa computacional.

Antes de falarmos das funcionalidades do programa a ser implementado, convém mencionar que, em algumas situações o espaço previamente alocado deve ser redimensionado devido, à por exemplo, um aumento ou diminuição inesperada na quantidade de itens manipulados. Para realizar o redimensionamento, pode-se, na linguagem C, utilizar a função “realloc()”. Essa função segue a seguinte sintaxe:

void *realloc (void *ptr_original, size_t);

A função “realloc()” retorna a posição do bloco realocado com a nova dimensão. No trecho de código acima, o parâmetro “ptr_original” representa o bloco previamente alocado com a função “malloc()” ou “calloc()”. Detalhes destas funções, inclusive a “realloc()” poderão ser obtidas acessando-se (GARCIA, 2016) através do link: <https://www.embarcados.com.br/ponteiro-em-c-alocacao-dinamica/>.

Para a realização desta atividade, suponha a necessidade de cadastrar clientes de uma loja. Por ser uma loja nova e com produtos inovadores, pouco se sabe do mercado a ser atingido, sendo assim, não se sabe a quantidade de clientes poderão ser cadastrados. Estima-se, inicialmente, em 10 clientes. Cada cliente terá os seguintes
campos:

- nome (suponha um nome com, no máximo, 30 caracteres)

- ano de nascimento

- montante de gastos realizados no mês (quanto o clinte pagou em suas compras dentro do mês corrente)

Para tanto, o sistema deverá oferecer as seguintes funcionalidades:

- incluir um novo cliente

- remover cliente - atualizar o montante de compras do cliente realizadas no mês corrente

- zerar todos os montantes de compras por ocasião da virada de mês

- listar o cliente melhor comprador

- exibir um montante de compras de um cliente específico.

O programa deverá, ainda, prever a situação que a quantidade de clientes a ser cadastrados supere a previsão inicial. Neste caso, quando o espaço de memória destinado a receber dados dos clientes estiver cheia, deve-se ampliar esse espaço – sempre em blocos de 10.

Poste o código, implementado em C, em seu portfólio.

Bons Estudos!


## A minha solução foi criada em C, como pedido pelo tutor. Espero que ajude a inspirar outros alunos.
