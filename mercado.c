#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

typedef struct {
    int codigo;
    char nome[30];
    float preco;
} Produto;

typedef struct {
    Produto produto;
    int quantidade;
} Carrinho;

void infoProduto(Produto prod);
void menu();
void cadastrarProduto();
void listarProdutos();
void comprarProduto();
void visualizarCarrinho();
Produto pegarProdutoPorCodigo(int codigo);
int *temNoCarrinho(int codigo);
void fecharPedido();

static int contador_produto = 0;
static int contador_carrinho = 0;
static Carrinho carrinho[50];
static Produto produtos[50];

int main(void) {
    menu();
    return 0;
}

void infoProduto(Produto prod) {
    printf("Codigo: %d\nNome: %s\nPreco: %.2f\n", prod.codigo, strtok(prod.nome, "\n"), prod.preco); // remove \n do nome
}

void menu() {
    system("cls");
    printf("=====================================================\n");
    printf("==================== Bem-vindo(a) ===================\n");
    printf("======================= shop ========================\n");
    printf("=====================================================\n");

    printf("Selecione uma opcao abaixo:\n");
    printf("1 - Cadastrar produto\n");
    printf("2 - Listar produtos\n");
    printf("3 - Comprar produto\n");
    printf("4 - Visualizar Carrinho\n");
    printf("5 - Fechar pedido\n");
    printf("6 - Sair do sistema\n");

    int opcao;
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
    case 1:
        cadastrarProduto();
        break;
    case 2:
        listarProdutos();
        break;
    case 3:
        comprarProduto();
        break;
    case 4:
        visualizarCarrinho();
        break;
    case 5:
        fecharPedido();
        break;
    case 6:
        printf("Volte sempre!\n");
        Sleep(2000);
        exit(0);
    default:
        printf("Opção invalida!\n");
        Sleep(2000);
        menu();
        break;
    }
}

void cadastrarProduto() {
    printf("Cadastro de produto\n");
    printf("====================\n");

    printf("Informe o nome do produto: ");
    fgets(produtos[contador_produto].nome, 30, stdin);

    printf("Informe o preco do produto: ");
    scanf("%f", &produtos[contador_produto].preco);

    printf("O produto %s foi cadastrado com sucesso.\n", strtok(produtos[contador_produto].nome, "\n"));

    produtos[contador_produto].codigo = (contador_produto + 1);
    contador_produto++;
    system("pause");
    menu();
}

void listarProdutos() {
    if (contador_produto > 0) {
        printf("Listagem de produtos\n");
        printf("====================\n");
        for (int i = 0; i < contador_produto; i++) {
            infoProduto(produtos[i]);
            printf("====================\n");
        }
        system("pause");
        menu();
    } else {
        printf("Nao temos produtos cadastrados\n");
        system("pause");
        menu();
    }
}

void comprarProduto() {
    if (contador_produto > 0) {
        printf("Informe o codigo do produto que deseja adicionar ao carrinho\n");

        printf("======== Produtos disponiveis ========\n");
        for (int i = 0; i < contador_produto; i++) {
            infoProduto(produtos[i]);
            printf("====================\n");
        }
        int codigo;
        scanf("%d", &codigo);
        getchar();

        int tem_no_carrinho = 0;
        for (int i = 0; i < contador_produto; i++) {
            if (produtos[i].codigo == codigo) {
                tem_no_carrinho = 1;

                if (contador_carrinho > 0) {
                    int *retorno = temNoCarrinho(codigo);

                    if (retorno[0] == 1) {
                        carrinho[retorno[1]].quantidade++;
                        printf("Aumentei a quantidade do produto %s ja existente no carrinho.\n", strtok(carrinho[retorno[1]].produto.nome, "\n"));
                        system("pause");
                        menu();
                    } else {
                        Produto p = pegarProdutoPorCodigo(codigo);
                        carrinho[contador_carrinho].produto = p;
                        carrinho[contador_carrinho].quantidade = 1;
                        contador_carrinho++;
                        printf("O produto %s foi adicionado ao carrinho.\n", strtok(carrinho[contador_carrinho - 1].produto.nome, "\n"));
                        system("pause");
                        menu();
                    }
                } else {
                    Produto p = pegarProdutoPorCodigo(codigo);
                    carrinho[contador_carrinho].produto = p;
                    carrinho[contador_carrinho].quantidade = 1;
                    contador_carrinho++;
                    printf("O produto %s foi adicionado ao carrinho.\n", strtok(carrinho[contador_carrinho - 1].produto.nome, "\n"));
                    system("pause");
                    menu();
                }
            }
        }
        if (tem_no_carrinho < 1) {
            printf("Nao foi encontrado o produto com código %d\n", codigo);
            system("pause");
            menu();
        }
    } else {
        printf("Ainda nao existem produtos para vender\n");
        system("pause");
        menu();
    }
}

void visualizarCarrinho() {
    if (contador_carrinho > 0) {
        printf("Produtos do Carrinho\n");
        printf("====================\n");
        for (int i = 0; i < contador_carrinho; i++) {
            infoProduto(carrinho[i].produto);
            printf("Quantidade: %d\n", carrinho[i].quantidade);
            printf("====================\n");
        }
        system("pause");
        menu();
    } else {
        printf("Nao temos produtos no carrinho\n");
        system("pause");
        menu();
    }
}

Produto pegarProdutoPorCodigo(int codigo) {
    Produto p;
    for (int i = 0; i < contador_produto; i++) {
        if (produtos[i].codigo == codigo) {
            p = produtos[i];
        }
    }
    return p;
}

int *temNoCarrinho(int codigo) {
    static int retorno[2] = {0, 0};
    for (int i = 0; i < contador_carrinho; i++) {
        if (carrinho[i].produto.codigo == codigo) {
            retorno[0] = 1; // tem o produto no carrinho;
            retorno[1] = i; // o índice do produto no carrinho
        }
    }
    return retorno;
}

void fecharPedido() {
    if (contador_carrinho > 0) {
        float valorTotal = 0.0;
        printf("Produtos do Carrinho\n");
        printf("====================\n");
        for (int i = 0; i < contador_carrinho; i++) {
            Produto p = carrinho[i].produto;
            int quantidade = carrinho[i].quantidade;
            valorTotal += p.preco * quantidade;
            infoProduto(p);
            printf("Quantidade: %d\n", quantidade);
            printf("====================\n");
        }
        printf("Sua fatura eh R$ %.2f\n", valorTotal);

        // Limpar carrinho
        contador_carrinho = 0;
        printf("Obrigado pela preferencia.\n");
        system("pause");
        menu();
    } else {
        printf("Você não tem nenhum produto no carrinho ainda\n");
        system("pause");
        menu();
    }
}
