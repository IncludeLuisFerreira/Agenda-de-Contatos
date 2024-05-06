<h1 align = "center" > Agenda de contato </h1> 

![Logo do Instituto Federal sul de Minas Gerais (Poços de Caldas)](https://yt3.googleusercontent.com/hS9nnf_X6H_5Cjm_zkZa9SGFuS375xurWdx3U0QO_QZYihmbqLLdU0sYaGkfkGCjBQWVTBRq=s900-c-k-c0x00ffffff-no-rj)

Este projeto é parte do trabalho de programação estruturada 2 do Instituto Federal Sul de Minas (Poços de Caldas), onde foi requisitado o desenvolvimento de uma agenda de contatos usando os conceitos de alocação dinâmica de memória e lista simplesmente encadeada.

### Instruções para a criação do trabalho:

Desenvolva as estruturas para representar os contatos de uma agenda conforme a descrição a seguir:


1. endereço com char rua[50], int numero, char bairro[50] e char cidade[50];
2. telefone com char ddd[2] e char numero[9];
3. contato com char nome[50], char email[30], endereco e um array para armazenar 2 telefones um para o xo e outro para o celular telefone[2];

* Observação: Utilize a diretiva #define para estabelecer os valores dos tamanhos de cada string.

Crie uma agenda com capacidade de armazenar contatos através de um ponteiro com o nome agenda
para contato. Faça todo o gerenciamento de memória com alocação dinâmica calloc() ou malloc() e libere
a memória com free() quando não for mais necessária, para otimizar o uso da memória.
Crie uma lista simplesmente encadeada e utilize modularização por meio de funções para as seguintes
operações. Todas as operações é necessário fazer o uso das funções scanf() ou do fgets().

1. Adicionar um contato em qualquer posição.
2. Remover um contato em qualquer posição.
3. Editar um contato qualquer.
4. Listar todos os contatos.
5. Buscar um contato através do nome, se houver mais de um contato com o mesmo nome listar todos os contatos encontrados.
6. Por último, para exibir o menu de opções para o usuário utilize o comando switch/case.

* Observação: Apenas para facilitar as correções pelo professor, armazene na memória da agenda os dados
de 5 contatos xos, faça uso das funções strcpy() ou do strncpy(), essas duas funções possibilitam armazenar
copiar um valor para os respectivos campos de um contato sem precisar utilizar a função scanf() para isso. O
objetivo de armazenar esses valores xo seria apenas para o professor poder realizar os testes já na primeira
execução e não precisar car preenchendo sempre os dados de um contato através do scanf() na correção dos
trabalhos. Quem não zer essa parte vai perder nota!

### Criação de bibliotecas
Fazer uso de 2 bibliotecas uma para armazenar as estruturas e outra para armazenar as funções das listas. Deixar apenas a função main() com o menu de opções com switch/case no arquivo principal. Faça o **#include** das bibliotecas no arquivo principal.

1. No arquivo de cabeçalho (header le .h) vão as declarações de funções (assinaturas) e definições de
estruturas;
2. No arquivo de unidade (arquivo .c) vão as definições de funções (corpo da função);
3. Então, para usar as funções, é necessário incluir o arquivo de cabeçalho (.h) com o uso de aspas duplas


### Instruções de uso

Você pode compilar o arquivo principal "main.c" usando o compilador GCC digitando a seguinte linha no terminal de comando

```bash
gcc .\main.c -o .\main.exe
```
Para executar o código como executavel

```bash
.\main.exe
```
Tenha certeza que o terminal de comando está no mesmo diretório onde está os arquivos "main.c" e "agendaContato.h", dessa forma receberá um menu idêntico à imagem abaixo no terminal de comando.

![Exemplo de execução do terminal de comando](https://i.imgur.com/WbLCMCT.png)

### Documentação do código

O arquivo de cabeçalho "agendaContato.h" é o local onde está todas as declarações das funções e structs , assim como também os algoritmos usados na manipulação de dados do arquivo principal "main.c".


#### Bibliotecas externas

1. stdio.h: biblioteca padrão em C de input e output.
2. stdlib.h: biblioteca padrão em C para alocação dinâmica de memória.
3. string.h: biblioteca de manipulação de strings .

#### Macros

1. MALLOCERROR: mensagem de erro para falhas de alocação dinâmica.
2. EMPTYLIST: mensagem de erro para lista vazia.
3. NOTFOUND: mensagem de erro para contato não encontrado.
4. MAX_NAME, MAX_EMAIL, MAX_FONE, MAX_DDD: tamanhos máximos para campos de strings.

#### Structs

No header foram declaradas quatro structs, três representando a pessoa que terá seu contato salvo.

```

struct endereco{
    char rua[MAX_NAME];
    int numero;
    char bairro[MAX_NAME];
    char cidade[MAX_NAME];
};

struct telefone{
    char DDD[MAX_DDD];
    char numero_telefone[MAX_FONE];
};

typedef struct contato{
    char nome[MAX_NAME];
    char email[MAX_EMAIL];
    struct endereco end;
    struct telefone fone[2];
    struct contato *proximo;
} Contato;
```

A quarta struct representa o início da estrutura de dados lista, como também o seu tamanho.

```
typedef struct lista{
    Contato *inicio;
    int TAM;
}Lista;
```
#### Funções

1. initLista(Lista *ptr): inicializa uma lista encadeada.
2. lerContato(): solicita ao usuário para preencher os campos de um novo contato e o retorna.
3. insert(Lista *lista, Contato contato, int pos): insere um novo contato em qualquer posição na lista.
4. removeNode(Lista *lista, int pos): remove um contato da lista em uma posição específica.
5. editarContato(Lista *lista, int pos): edita um contato existente na lista.
6. imprimir(Lista *lista): imprime todos os contatos da lista.
7. buscarContato(Lista *lista, char *nome): busca um contato pelo nome na lista.
### Licença

Este projeto está licenciado sob a [Licença MIT](https://opensource.org/licenses/MIT).É permitido o uso e modificar os códigos.