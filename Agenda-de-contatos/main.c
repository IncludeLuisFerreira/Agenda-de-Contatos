#include "agendaContato.h"

int main(){
    Lista lista;
    Contato *aux = NULL;
    int user_int, user_pos;
    char user_string[MAX_NAME];
    initLista(&lista);

    setlocale(LC_ALL, "Portuguese_Brazil");
    do
    {
        printf("1-Inserir na lista\n2-Remover da lista\n3-Imprimir a lista\n4-Buscar contato\n5-Editar contato\n6-Sair\n: ");
        scanf("%d", &user_int);

        switch (user_int)
        {
        case 1:
            printf("Digite a posicao: ");
            scanf("%d", &user_pos);
            if (valid_position(user_pos, lista.TAM))
                insert(&lista, lerContato(), user_pos);
            else
                printf("Posicao invalida.\n");
            break;
        case 2:
            printf("Digite a posicao: ");
            scanf("%d", &user_pos);
            removeNode(&lista, user_pos);
            break;
        case 3:
            imprimir(&lista);
            break;
        case 4:
            fflush(stdin);
            printf("Digite o nome: ");
            fgets(user_string, 50, stdin);
            aux = busca(&lista, user_string);
            if (aux) imprimirNode(aux, 0);
            else printf(NOTFOUND);
            break;
        case 5:
            printf("Digite a posicao: ");
            scanf("%d", &user_pos);
            if (valid_position(user_pos, lista.TAM - 1))
                editarContato(&lista, user_pos);
            else
                printf("Posicao invalida.\n");
            break;
        default:
            if (user_int != 6)
                printf("Opcao invalida!\n");
            break;
        }
    } while (user_int != 6);

    safe_free(&lista, &aux);
    printf("Executado com sucesso.\n");
    return 0;
}