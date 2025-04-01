#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USUARIOS 100
#define MAX_LIVROS 100
#define MAX_CHAR 100

// STRUCTS
typedef struct
{
    int id;
    char nome[MAX_CHAR];
    char email[MAX_CHAR];
    char telefone[12];
    char data_nascimento[11];
    char senha[9];
    bool adm;
} usuario;

typedef struct
{
    int id;
    char titulo[MAX_CHAR];
    char autor[MAX_CHAR];
    char editora[MAX_CHAR];
    char genero[MAX_CHAR];
    char ano_publicacao[5];
    bool emprestado;
    int id_usuario_emprestimo;
} livro;

int ultimo_id_usuario = 0;
int total_usuarios = 0;
usuario usuarios[MAX_USUARIOS];
usuario novo_usuario;

int ultimo_id_livro = 0;
int total_livros = 0;
livro livros[MAX_LIVROS];
livro novo_livro;

// PROTOTIPOS DE FUNCOES:
void LimparBufferEntrada();
void InicializarUsuarios();
void InicializarLivros();
void ExibirDadosUsuario(usuario u);
void ExibirDadosLivro(livro l);

void MenuInicial();
void LoginUsuario();
int CadastrarUsuario();

void MenuADM();
void MenuUsuario();

void PesquisarUsuario();
void BuscaIdUsuario();
void BuscaNome();
void BuscaEmail();
void BuscaTelefone();
void ListarUsuario();

int CadastrarLivro();
void MeusDados();
void EditarDados();

void PesquisarLivro();
void BuscaIdLivro();
void BuscaTitulo();
void BuscaAutor();
void BuscaEditora();
void BuscaGenero();

void ListarLivros();
void EmprestarLivro();
void DevolverLivro();

int indice_usuario_logado = 0;

int main()
{
    InicializarUsuarios(); //INICIALIZA OS USUARIOS PRE CADASTRADOS NO SISTEMA
    InicializarLivros(); //INICIALIZA OS LIVROS PRE CADASTRADOS NO SISTEMA
    MenuInicial(); // ABRE O MENU INICIAL
    return 0;
}

void MenuInicial()
{
    char opcao = '0';

    do
    {
        printf("\n");
        printf("=====================================\n");
        printf("|     BEM VINDO AO SEA LIBERTY!     |\n");
        printf("=====================================\n");
        printf("| 1. Fazer login                    |\n");
        printf("| 2. Cadastrar-se                   |\n");
        printf("| 0. FECHAR                         |\n");
        printf("=====================================\n");
        printf("Escolha uma opcao: ");
        scanf("%c", &opcao);
        LimparBufferEntrada();
        system("cls");

        switch(opcao)
        {
            case '1':
                LoginUsuario();
                break;
            case '2':
                CadastrarUsuario();
                break;
            case '0':
                printf("Fechando... Ate logo!\n\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.");
                break;
        }
    } while(opcao != '0');
}

int CadastrarUsuario()
{
    if(total_usuarios >= MAX_USUARIOS)
    {
        printf("Limite de usuarios atingido!\n");
        return 1;
    }

    novo_usuario.id = ++ultimo_id_usuario;
    novo_usuario.adm = false;

    printf("\n");
    printf("=====================================\n");
    printf("|             CADASTRO              |\n");
    printf("=====================================\n");

    printf("| Insira seus dados: \n");

    printf("| Nome: ");
    fgets(novo_usuario.nome, MAX_CHAR, stdin);
    strtok(novo_usuario.nome, "\n");

    printf("| Email: ");
    fgets(novo_usuario.email, MAX_CHAR, stdin);
    strtok(novo_usuario.email, "\n");

    do
    {
        printf("| Telefone (com DDD): ");
        fgets(novo_usuario.telefone, 12, stdin);

        if (novo_usuario.telefone[strlen(novo_usuario.telefone) - 1] != '\n')
        {
            LimparBufferEntrada();
        }

        strtok(novo_usuario.telefone, "\n");

        if (strlen(novo_usuario.telefone) != 11)
        {
            printf("Telefone invalido! Deve conter 11 digitos.\n");
        }
    }
    while (strlen(novo_usuario.telefone) != 11);

    printf("| Data de nascimento (DD/MM/AAAA): ");
    fgets(novo_usuario.data_nascimento, 11, stdin);
    if (novo_usuario.data_nascimento[strlen(novo_usuario.data_nascimento) - 1] != '\n')
    {
        LimparBufferEntrada();
    }
    strtok(novo_usuario.data_nascimento, "\n");

    do
    {
        printf("| Senha (8 digitos): ");
        fgets(novo_usuario.senha, 9, stdin);

        if (novo_usuario.senha[strlen(novo_usuario.senha) - 1] != '\n')
        {
            LimparBufferEntrada();
        }

        strtok(novo_usuario.senha, "\n");

        if (strlen(novo_usuario.senha) != 8)
        {
            printf("Senha invalida! Deve conter 8 digitos.\n");
        }
    } while (strlen(novo_usuario.senha) != 8);

    usuarios[total_usuarios] = novo_usuario;
    total_usuarios++;

    system("cls");
    printf("Usuario cadastrado com sucesso! ID: %d\n", novo_usuario.id);
    return 0;
}

void LoginUsuario()
{
    char email[MAX_CHAR];
    char senha[9];

    printf("\n");
    printf("=====================================\n");
    printf("|              LOGIN                |\n");
    printf("=====================================\n");

    printf("| Email: ");
    fgets(email, MAX_CHAR, stdin);
    strtok(email, "\n");

    printf("| Senha (8 digitos): ");
    fgets(senha, 9, stdin);
    strtok(senha, "\n");
    system("cls");
    for(int i = 0; i < total_usuarios; i++)
    {
        if(strcmp(usuarios[i].email, email) == 0 && strcmp(usuarios[i].senha, senha) == 0)
        {
            indice_usuario_logado = i;
            printf("Login bem-sucedido! Bem-vindo, %s!\n", usuarios[i].nome);
            if (usuarios[i].adm) {
                MenuADM();
            } else {
                MenuUsuario();
            }
            return;
        }
    }
    printf("Email ou senha incorretos. Tente novamente.\n");
}


void MenuADM()
{

   char opcao = '0';

    do
    {
        printf("\n");
        printf("=====================================\n");
        printf("|       MENU PRINCIPAL (ADM)        |\n");
        printf("=====================================\n");
        printf("| 1. Cadastrar Usuario              |\n");
        printf("| 2. Pesquisar Usuario              |\n");
        printf("| 3. Cadastrar Livro                |\n");
        printf("| 4. Pesquisar Livro                |\n");
        printf("| 5. Emprestar Livro                |\n");
        printf("| 6. Devolver Livro                 |\n");
        printf("| 0. SAIR                           |\n");
        printf("=====================================\n");
        printf("Escolha uma opcao: ");
        scanf("%c", &opcao);
        LimparBufferEntrada();
        system("cls");

        switch(opcao)
        {
            case '1': // FUNCAO DE CADASTRAR USUARIO
            {
                CadastrarUsuario();
                break;
            }
            case '2': // PESQUISA USUARIO CONFORME A OPCAO DE BUSCA SELECIONADO
            {
                PesquisarUsuario();
                break;
            }
            case '3': // FUNCAO DE CADASTRAR LIVRO
            {
                CadastrarLivro();
                break;
            }
            case '4': // PESQUISA LIVRO CONFORME A OPCAO DE BUSCA SELECIONADO
            {
                PesquisarLivro();
                break;
            }
            case '5': // FUNCAO DE EMPRESTAR LIVRO
            {
                EmprestarLivro();
                break;
            }
            case '6': // FUNCAO DE DEVOLVER LIVRO EMPRESTADO
            {
                DevolverLivro();
                break;
            }
            case '0': // SAIR
            {
                printf("Saindo...\n\n");
                system("pause");
                system("cls");
                break;
            }
            default: // MESNSAGEM DE OPCAO INVALIDA
            {
                printf("Opcao invalida! Tente novamente.");
                break;
            }
        }
    } while(opcao != '0');
}

void MenuUsuario()
{
   char opcao = '0';

    do
    {
        printf("\n");
        printf("=====================================\n");
        printf("|          MENU PRINCIPAL           |\n");
        printf("=====================================\n");
        printf("| 1. Meus dados                     |\n");
        printf("| 2. Pesquisar Livro                |\n");
        printf("| 3. Emprestar Livro                |\n");
        printf("| 4. Devolver Livro                 |\n");
        printf("| 0. SAIR                           |\n");
        printf("=====================================\n");
        printf("Escolha uma opcao: ");
        scanf("%c", &opcao);
        LimparBufferEntrada();
        system("cls");

        switch(opcao)
        {
            case '1': // EXIBE OS DADOS DO USUARIO LOGADO
            {
                MeusDados();
                break;
            }
            case '2': // PESQUISA LIVRO CONFORME A OPCAO DE BUSCA SELECIONADO
            {
                PesquisarLivro();
                break;
            }
            case '3': // FUNCAO DE EMPRESTAR LIVRO
            {
                EmprestarLivro();
                break;
            }
            case '4': // FUNCAO DE DEVOLVER LIVRO EMPRESTADO
            {
                DevolverLivro();
                break;
            }
            case '0': // SAIR
            {
                printf("Saindo...\n\n");
                system("pause");
                system("cls");
                break;
            }
            default: // MESNSAGEM DE OPCAO INVALIDA
            {
                printf("Opcao invalida! Tente novamente.");
                break;
            }
        }
    } while(opcao != '0');
}

void MeusDados()
{
    usuario u = usuarios[indice_usuario_logado];
    char opcao = '0';

    do
    {
        printf("\n");
        printf("=====================================\n");
        printf("|          MEUS DADOS               |\n");
        printf("=====================================\n");
        printf("| ID: %d\n", u.id);
        printf("| Nome: %s\n", u.nome);
        printf("| Email: %s\n", u.email);
        printf("| Telefone: %s\n", u.telefone);
        printf("| Data de Nascimento: %s\n", u.data_nascimento);
        printf("| Administrador: %s\n", u.adm ? "Sim" : "Nao");
        printf("=====================================\n");
        printf("| 1. Editar dados                   |\n");
        printf("| 0. VOLTAR                         |\n");
        printf("=====================================\n");
        scanf("%c", &opcao);
        LimparBufferEntrada();
        system("cls");

        switch(opcao)
        {
            case '1':
            {
                EditarDados();
                break;
            }
            case '0':
            {
                break;
            }
            default:
            {
                printf("Opcao invalida! Tente novamente.");
                break;
            }
        }
    }while (opcao != '0');
}

void EditarDados()
{
    char opcao = '0';
    usuario *u = &usuarios[indice_usuario_logado];

    do
    {
        printf("\n");
        printf("=====================================\n");
        printf("|           EDITAR DADOS            |\n");
        printf("=====================================\n");
        printf("| 1. Editar Nome                    |\n");
        printf("| 2. Editar Email                   |\n");
        printf("| 3. Editar Telefone                |\n");
        printf("| 4. Editar Data de Nascimento      |\n");
        printf("| 5. Editar Senha                   |\n");
        printf("| 0. VOLTAR                         |\n");
        printf("=====================================\n");
        printf("Escolha uma opcao: ");
        scanf("%c", &opcao);
        LimparBufferEntrada();
        system("cls");

        switch(opcao)
        {
            case '1':
                printf("\n");
                printf("=====================================\n");
                printf("|           EDITAR NOME             |\n");
                printf("=====================================\n");
                printf("Novo Nome: ");
                fgets(u->nome, MAX_CHAR, stdin);
                strtok(u->nome, "\n");
                system("cls");
                printf("Nome atualizado com sucesso!\n");
                break;
            case '2':
                printf("\n");
                printf("=====================================\n");
                printf("|           EDITAR EMAIL            |\n");
                printf("=====================================\n");
                printf("Novo Email: ");
                fgets(u->email, MAX_CHAR, stdin);
                strtok(u->email, "\n");
                system("cls");
                printf("Email atualizado com sucesso!\n");
                break;
            case '3':
                do
                {
                    printf("\n");
                    printf("=====================================\n");
                    printf("|         EDITAR TELEFONE           |\n");
                    printf("=====================================\n");
                    printf("Novo Telefone (com DDD): ");
                    fgets(u->telefone, 12, stdin);
                    strtok(u->telefone, "\n");
                    if (strlen(u->telefone) != 11)
                    {
                        printf("Telefone invalido! Deve conter 11 digitos.\n");
                    }
                } while (strlen(u->telefone) != 11);
                system("cls");
                printf("Telefone atualizado com sucesso!\n");
                break;
            case '4':
                printf("\n");
                printf("=====================================\n");
                printf("|     EDITAR DATA DE NASCIMENTO     |\n");
                printf("=====================================\n");
                printf("Nova Data de Nascimento (DD/MM/AAAA): ");
                fgets(u->data_nascimento, 11, stdin);
                strtok(u->data_nascimento, "\n");
                system("cls");
                printf("Data de nascimento atualizada com sucesso!\n");
                break;
            case '5':
                do
                {
                    printf("\n");
                    printf("=====================================\n");
                    printf("|           EDITAR SENHA            |\n");
                    printf("=====================================\n");
                    printf("Nova Senha (8 digitos): ");
                    fgets(u->senha, 9, stdin);
                    strtok(u->senha, "\n");
                    if (strlen(u->senha) != 8)
                    {
                        printf("Senha invalida! Deve conter 8 digitos.\n");
                    }
                } while (strlen(u->senha) != 8);
                system("cls");
                printf("Senha atualizada com sucesso!\n");
                break;
            case '0':
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while(opcao != '0');
}

void PesquisarUsuario()
{
    char opcao = '0';

    do
    {
        printf("\n");
        printf("=====================================\n");
        printf("|      PESQUISAR USUARIO POR        |\n");
        printf("=====================================\n");
        printf("| 1. ID                             |\n");
        printf("| 2. Nome                           |\n");
        printf("| 3. Email                          |\n");
        printf("| 4. Telefone                       |\n");
        printf("| 5. Exibir todos                   |\n");
        printf("| 0. VOLTAR                         |\n");
        printf("=====================================\n");
        printf("Escolha uma opcao de pesquisar por: \n");
        scanf("%c", &opcao);
        LimparBufferEntrada();
        system("cls");

        switch(opcao)
        {
            case '1': // BUSCA USUARIO POR ID
            {
                int id_busca;
                bool encontrado = false;

                printf("\n");
                printf("=====================================\n");
                printf("|      PESQUISAR USUARIO POR ID     |\n");
                printf("=====================================\n");
                printf("| Digite o ID do usuario: ");
                scanf("%d", &id_busca);
                LimparBufferEntrada();
                system("cls");

                for (int i = 0; i < total_usuarios; i++)
                {
                    if (usuarios[i].id == id_busca)
                    {
                        char opcao = '0';

                        encontrado = true;

                        printf("Usuario encontrado!\n");
                        ExibirDadosUsuario(usuarios[i]);
                        printf("=====================================\n");
                        printf("| 0. VOLTAR                         |\n");
                        printf("=====================================\n");
                        scanf(" %c", &opcao);
                        LimparBufferEntrada();
                        system("cls");

                        if (opcao != '0')
                        {
                            printf("Opcao invalida! Tente novamente.");
                        }
                        break;
                    }
                }
                if (!encontrado)
                {
                    printf("Nenhum usuario encontrado com esse ID.");
                }
                break;
            }
            case '2': // BUSCA USUARIO POR NOME
            {
                char nome_busca[MAX_CHAR];
                char opcao = '0';
                bool encontrado = false;

                printf("\n");
                printf("=====================================\n");
                printf("|    PESQUISAR USUARIO POR NOME     |\n");
                printf("=====================================\n");
                printf("| Digite o nome do usuario: ");
                fgets(nome_busca, MAX_CHAR, stdin);
                strtok(nome_busca, "\n");
                system("cls");

                for (int i = 0; i < total_usuarios; i++)
                {
                    if (strcmp(usuarios[i].nome, nome_busca) == 0)
                    {
                        encontrado = true;
                        printf("Usuario encontrado!\n");
                        ExibirDadosUsuario(usuarios[i]);
                        printf("| 0. VOLTAR                         |\n");
                        printf("=====================================\n");
                        scanf(" %c", &opcao);
                        LimparBufferEntrada();
                        system("cls");

                        if (opcao != '0')
                        {
                            printf("Opcao invalida! Tente novamente.");
                        }
                        break;
                    }
                }

                if (!encontrado)
                {
                    printf("Nenhum usuario encontrado com esse nome");
                }
                break;
            }
            case '3': // BUSCA USUARIO POR EMAIL
            {
                char email_busca[MAX_CHAR];
                char opcao = '0';
                bool encontrado = false;

                printf("\n");
                printf("=====================================\n");
                printf("|    PESQUISAR USUARIO POR EMAIL    |\n");
                printf("=====================================\n");
                printf("| Digite o email do usuario: ");
                fgets(email_busca, MAX_CHAR, stdin);
                strtok(email_busca, "\n");
                system("cls");

                for (int i = 0; i < total_usuarios; i++)
                {
                    if (strcmp(usuarios[i].email, email_busca) == 0)
                    {
                        encontrado = true;
                        printf("Usuario encontrado!\n");
                        ExibirDadosUsuario(usuarios[i]);
                        printf("| 0. VOLTAR                         |\n");
                        printf("=====================================\n");
                        scanf(" %c", &opcao);
                        LimparBufferEntrada();
                        system("cls");

                        if (opcao != '0')
                        {
                            printf("Opcao invalida! Tente novamente.");
                        }
                        break;
                    }
                }
                if (!encontrado)
                {
                    printf("Nenhum usuario encontrado com esse email");
                }
                break;
            }
            case '4': // BUSCA USUARIO POR TELEFONE
            {
                char telefone_busca[MAX_CHAR];
                char opcao = '0';
                bool encontrado = false;

                printf("\n");
                printf("=====================================\n");
                printf("|  PESQUISAR USUARIO POR TELEFONE   |\n");
                printf("=====================================\n");
                printf("| Digite o telefone do usuario: ");
                fgets(telefone_busca, MAX_CHAR, stdin);
                strtok(telefone_busca, "\n");
                system("cls");

                for (int i = 0; i < total_usuarios; i++)
                {
                    if (strcmp(usuarios[i].telefone, telefone_busca) == 0)
                    {
                        encontrado = true;
                        printf("Usuario encontrado!\n");
                        ExibirDadosUsuario(usuarios[i]);
                        printf("| 0. VOLTAR                         |\n");
                        printf("=====================================\n");
                        scanf(" %c", &opcao);
                        LimparBufferEntrada();
                        system("cls");

                        if (opcao != '0')
                        {
                            printf("Opcao invalida! Tente novamente.");
                        }
                        break;
                    }
                }
                if (!encontrado)
                {
                    printf("Nenhum usuario encontrado com esse telefone");
                }
                break;
            }
            case '5': // LISTA TODOS OS USUARIOS CADASTRADOS
            {
                char opcao = '0';

                if(total_usuarios == 0)
                {
                    printf("Nenhum usuario cadastrado. \n");
                    return;
                }
                printf("\n");
                printf("=====================================\n");
                printf("|             USUARIOS              |\n");
                printf("=====================================\n");

                for(int i = 0; i < total_usuarios; i++)
                {
                    ExibirDadosUsuario(usuarios[i]);
                }
                printf("=====================================\n");
                printf("| 0. VOLTAR                         |\n");
                printf("=====================================\n");
                scanf("%s", &opcao);
                LimparBufferEntrada();
                system("cls");

                if (opcao != '0')
                {
                    printf("Opcao invalida! Tente novamente.");
                }
                break;
            }
            case '0': // VOLTAR
            {
                break;
            }
            default: // MESNSAGEM DE OPCAO INVALIDA
            {
                printf("Opcao invalida! Tente novamente.");
                break;
            }
        }
    }
    while(opcao != '0');
}

int CadastrarLivro()
{
    if(total_livros >= MAX_LIVROS)
    {
        printf("Limite de livros atingido!\n");
        return 1;
    }

    printf("\n");
    printf("=====================================\n");
    printf("|          CADASTRO LIVRO           |\n");
    printf("=====================================\n");

    printf("| Insira os dados: \n");

    printf("| Titulo: ");
    fgets(novo_livro.titulo, MAX_CHAR, stdin);
    strtok(novo_livro.titulo, "\n");

    printf("| Autor: ");
    fgets(novo_livro.autor, MAX_CHAR, stdin);
    strtok(novo_livro.autor, "\n");

    printf("| Editora: ");
    fgets(novo_livro.editora, MAX_CHAR, stdin);
    strtok(novo_livro.editora, "\n");

    printf("| Genero: ");
    fgets(novo_livro.genero, MAX_CHAR, stdin);
    strtok(novo_livro.genero, "\n");

    do
    {
        printf("| Ano de publicacao : ");
        fgets(novo_livro.ano_publicacao, 5, stdin);

        if (novo_livro.ano_publicacao[strlen(novo_livro.ano_publicacao) - 1] != '\n')
        {
            LimparBufferEntrada();
        }

        strtok(novo_livro.ano_publicacao, "\n");

        if (strlen(novo_livro.ano_publicacao) != 4)
        {
            printf("Ano invalido! Deve conter 4 digitos.\n");
        }
    }
    while (strlen(novo_livro.ano_publicacao) != 4);

    livros[total_livros] = novo_livro;
    total_livros++;

    system("cls");
    printf("Livro cadastrado com sucesso!\n");
    return 0;
}

void PesquisarLivro()
{
    char opcao = '0';

    do
    {
        printf("\n");
        printf("=====================================\n");
        printf("|       PESQUISAR LIVRO POR         |\n");
        printf("=====================================\n");
        printf("| 1. ID                             |\n");
        printf("| 2. Titulo                         |\n");
        printf("| 3. Autor                          |\n");
        printf("| 4. Editora                        |\n");
        printf("| 5. Genero                         |\n");
        printf("| 6. Exibir todos                   |\n");
        printf("| 0. VOLTAR                         |\n");
        printf("=====================================\n");
        printf("Escolha uma opcao de pesquisar por: \n");
        scanf("%c", &opcao);
        LimparBufferEntrada();
        system("cls");

        switch(opcao)
        {
            case '1': // BUSCA LIVRO POR ID
            {
                int id_busca;
                char opcao = '0';
                bool encontrado = false;

                printf("\n");
                printf("=====================================\n");
                printf("|      PESQUISAR LIVRO POR ID       |\n");
                printf("=====================================\n");
                printf("| Digite o ID do livro: ");
                scanf("%d", &id_busca);
                LimparBufferEntrada();
                system("cls");

                for (int i = 0; i < total_livros; i++)
                {
                    if (livros[i].id == id_busca)
                    {
                        encontrado = true;
                        printf("Livro encontrado!\n");
                        ExibirDadosLivro(livros[i]);
                        printf("| 0. VOLTAR                         |\n");
                        printf("=====================================\n");
                        scanf(" %c", &opcao);
                        LimparBufferEntrada();
                        system("cls");

                        if (opcao != '0')
                        {
                            printf("Opcao invalida! Tente novamente.");
                        }
                        break;
                    }
                }
                if (!encontrado)
                {
                    printf("Nenhum livro encontrado com esse ID.");
                }
                break;
            }
            case '2': // BUSCA LIVRO POR TITULO
            {
                char titulo_busca[MAX_CHAR];
                char opcao = '0';
                bool encontrado = false;

                printf("\n");
                printf("=====================================\n");
                printf("|    PESQUISAR LIVRO POR TITULO     |\n");
                printf("=====================================\n");
                printf("| Digite o titulo do livro: ");
                fgets(titulo_busca, MAX_CHAR, stdin);
                strtok(titulo_busca, "\n");
                system("cls");

                for (int i = 0; i < total_livros; i++)
                {
                    if (strcmp(livros[i].titulo, titulo_busca) == 0)
                    {
                        encontrado = true;
                        printf("Livro encontrado!\n");
                        ExibirDadosLivro(livros[i]);
                        printf("| 0. VOLTAR                         |\n");
                        printf("=====================================\n");
                        scanf(" %c", &opcao);
                        LimparBufferEntrada();
                        system("cls");

                        if (opcao != '0')
                        {
                            printf("Opcao invalida! Tente novamente.");
                        }
                        break;
                    }
                }
                if (!encontrado)
                {
                    printf("Nenhum livro encontrado com esse titulo");
                }
                break;
            }
            case '3': // BUSCA LIVRO POR AUTOR
            {
                char autor_busca[MAX_CHAR];
                char opcao = '0';
                bool encontrado = false;

                printf("\n");
                printf("=====================================\n");
                printf("|    PESQUISAR LIVRO POR AUTOR      |\n");
                printf("=====================================\n");
                printf("| Digite o autor do livro: ");
                fgets(autor_busca, MAX_CHAR, stdin);
                strtok(autor_busca, "\n");
                system("cls");

                for (int i = 0; i < total_livros; i++)
                {
                    if (strcmp(livros[i].autor, autor_busca) == 0)
                    {
                        encontrado = true;
                        printf("Livro encontrado!\n");
                        ExibirDadosLivro(livros[i]);
                        printf("| 0. VOLTAR                         |\n");
                        printf("=====================================\n");
                        scanf(" %c", &opcao);
                        LimparBufferEntrada();
                        system("cls");

                        if (opcao != '0')
                        {
                            printf("Opcao invalida! Tente novamente.");
                        }
                        break;
                    }
                }
                if (!encontrado)
                {
                    printf("Nenhum livro encontrado com esse autor");
                }
                break;
            }
            case '4': // LISTA LIVRO POR EDITORA
            {
                char editora_busca[MAX_CHAR];
                char opcao = '0';
                bool encontrado = false;

                printf("\n");
                printf("=====================================\n");
                printf("|    PESQUISAR LIVRO POR EDITORA     |\n");
                printf("=====================================\n");
                printf("| Digite o editora do livro: ");
                fgets(editora_busca, MAX_CHAR, stdin);
                strtok(editora_busca, "\n");
                system("cls");

                for (int i = 0; i < total_livros; i++)
                {
                    if (strcmp(livros[i].editora, editora_busca) == 0)
                    {
                        encontrado = true;
                        ExibirDadosLivro(livros[i]);
                        printf("| 0. VOLTAR                         |\n");
                        printf("=====================================\n");
                        scanf(" %c", &opcao);
                        LimparBufferEntrada();
                        system("cls");

                        if (opcao != '0')
                        {
                            printf("Opcao invalida! Tente novamente.");
                        }
                        break;
                    }
                }
                if (!encontrado)
                {
                    printf("Nenhum livro encontrado com esse editora");
                }
                break;
            }
            case '5': // BUSCA LIVRO POR GENERO
            {
                char genero_busca[MAX_CHAR];
                char opcao = '0';
                bool encontrado = false;

                printf("\n");
                printf("=====================================\n");
                printf("|    PESQUISAR LIVRO POR GENERO     |\n");
                printf("=====================================\n");
                printf("| Digite o genero do livro: ");
                fgets(genero_busca, MAX_CHAR, stdin);
                strtok(genero_busca, "\n");
                system("cls");

                for (int i = 0; i < total_livros; i++)
                {
                    if (strcmp(livros[i].genero, genero_busca) == 0)
                    {
                        encontrado = true;
                        ExibirDadosLivro(livros[i]);
                        printf("| 0. VOLTAR                         |\n");
                        printf("=====================================\n");
                        scanf(" %c", &opcao);
                        LimparBufferEntrada();
                        system("cls");

                        if (opcao != '0')
                        {
                            printf("Opcao invalida! Tente novamente.");
                        }
                        break;
                    }
                }
                if (!encontrado)
                {
                    printf("Nenhum livro encontrado com esse genero");
                }
                break;
            }
            case '6': // LISTA TODOS OS LIVROS CADASTRADOS
            {
                char opcao = '0';

                if(total_livros == 0)
                {
                    printf("Nenhum livro cadastrado. \n");
                    return;
                }
                printf("\n");
                printf("=====================================\n");
                printf("|              LIVROS               |\n");
                printf("=====================================\n");

                for(int i = 0; i < total_livros; i++)
                {
                    ExibirDadosLivro(livros[i]);
                }
                printf("=====================================\n");
                printf("| 0. VOLTAR                         |\n");
                printf("=====================================\n");
                scanf("%s", &opcao);
                LimparBufferEntrada();
                system("cls");
                if (opcao != '0')
                {
                    printf("Opcao invalida! Tente novamente.");
                }
                break;
            }
            case '0': // VOLTAR
            {
                break;
            }
            default: // MESNSAGEM DE OPCAO INVALIDA
            {
                printf("Opcao invalida! Tente novamente.");
                break;
            }
        }
    } while(opcao != '0');
}

void EmprestarLivro()
{
    int id_busca;
    bool encontrado = false;

    printf("\n");
    printf("=====================================\n");
    printf("|          EMPRESTAR LIVRO          |\n");
    printf("=====================================\n");
    printf("Digite o ID do livro que deseja emprestar: ");
    scanf("%d", &id_busca);
    LimparBufferEntrada();

    for(int i = 0; i < total_livros; i++)
    {
        if(livros[i].id == id_busca)
        {
            encontrado = true;
            if (livros[i].emprestado) {
                system("cls");
                printf("O livro '%s' ja esta emprestado.\n", livros[i].titulo);
            } else {
                livros[i].emprestado = true;
                livros[i].id_usuario_emprestimo = usuarios[indice_usuario_logado].id;
                system("cls");
                printf("Livro '%s' emprestado com sucesso para o usuario '%s'.\n", livros[i].titulo, usuarios[indice_usuario_logado].nome);
            }
            break;
        }
    }
    if(!encontrado)
    {
        system("cls");
        printf("Nenhum livro encontrado com esse ID.\n");
    }
}

void DevolverLivro()
{
    int id_livro;
    bool encontrado = false;

    printf("\n");
    printf("=====================================\n");
    printf("|          DEVOLVER LIVRO           |\n");
    printf("=====================================\n");
    printf("Digite o ID do livro que deseja devolver: ");
    scanf("%d", &id_livro);
    LimparBufferEntrada();

    for (int i = 0; i < total_livros; i++)
    {
        if (livros[i].id == id_livro)
        {
            encontrado = true;
            if (livros[i].emprestado && livros[i].id_usuario_emprestimo == usuarios[indice_usuario_logado].id)
            {
                livros[i].emprestado = false;
                livros[i].id_usuario_emprestimo = 0;  // Zera o ID do usuário que tinha emprestado o livro
                system("cls");
                printf("Livro '%s' devolvido com sucesso.\n", livros[i].titulo);
            }
            else if (livros[i].emprestado)
            {
                system("cls");
                printf("O livro '%s' foi emprestado por outro usuario.\n", livros[i].titulo);
            }
            else
            {
                system("cls");
                printf("O livro '%s' ja esta disponível.\n", livros[i].titulo);
            }
            break;
        }
    }

    if (!encontrado) {
            system("cls");
        printf("Nenhum livro encontrado com esse ID.\n");
    }
}


void ExibirDadosLivro(livro l)
{
    printf("=====================================\n");
    printf("| ID: %d\n", l.id);
    printf("| Titulo: %s\n", l.titulo);
    printf("| Autor: %s\n", l.autor);
    printf("| Editora: %s\n", l.editora);
    printf("| Genero: %s\n", l.genero);
    printf("| Ano de publicacao: %s\n", l.ano_publicacao);
    printf("=====================================\n");
}

void ExibirDadosUsuario(usuario u)
{
    printf("=====================================\n");
    printf("| ID: %d\n", u.id);
    printf("| Nome: %s\n", u.nome);
    printf("| Email: %s\n", u.email);
    printf("| Telefone: %s\n", u.telefone);
    printf("| Data de Nascimento: %s\n", u.data_nascimento);
    printf("| Administrador: %s\n", u.adm ? "Sim" : "Nao");
    printf("=====================================\n");
}

void InicializarUsuarios()
{
    usuarios[total_usuarios].id = 100;
    strcpy(usuarios[total_usuarios].nome, "Fabio Fernandes");
    strcpy(usuarios[total_usuarios].email, "fabiogjunior2005@gmail.com");
    strcpy(usuarios[total_usuarios].telefone, "15988191026");
    strcpy(usuarios[total_usuarios].data_nascimento, "01/02/2005");
    strcpy(usuarios[total_usuarios].senha, "12341234");
    usuarios[total_usuarios].adm = true;
    total_usuarios++;

    usuarios[total_usuarios].id = 101;
    strcpy(usuarios[total_usuarios].nome, "Wellington");
    strcpy(usuarios[total_usuarios].email, "wellingtonruizdasilva07@gmail.com");
    strcpy(usuarios[total_usuarios].telefone, "15996048306");
    strcpy(usuarios[total_usuarios].data_nascimento, "25/09/2003");
    strcpy(usuarios[total_usuarios].senha, "12345678");
    usuarios[total_usuarios].adm = false;
    total_usuarios++;
}

void InicializarLivros()
{
    livros[total_livros].id = 100;
    strcpy(livros[total_livros].titulo, "Codigo Limpo: Habilidades Praticas do Agile Software");
    strcpy(livros[total_livros].autor, "Robert C. Martin");
    strcpy(livros[total_livros].editora, "Alta Books");
    strcpy(livros[total_livros].genero, "Programacao");
    strcpy(livros[total_livros].ano_publicacao, "2008");
    total_livros++;

    livros[total_livros].id = 101;
    strcpy(livros[total_livros].titulo, "A Psicologia Financeira");
    strcpy(livros[total_livros].autor, "Morgan Housel");
    strcpy(livros[total_livros].editora, "Harper Collins");
    strcpy(livros[total_livros].genero, "Financas");
    strcpy(livros[total_livros].ano_publicacao, "2021");
    total_livros++;

    livros[total_livros].id = 102;
    strcpy(livros[total_livros].titulo, "Pai Rico, Pai Pobre");
    strcpy(livros[total_livros].autor, "Robert T. Kiyosaki");
    strcpy(livros[total_livros].editora, "Alta Books");
    strcpy(livros[total_livros].genero, "Financas");
    strcpy(livros[total_livros].ano_publicacao, "2017");
    total_livros++;

    livros[total_livros].id = 103;
    strcpy(livros[total_livros].titulo, "Dom Casmurro");
    strcpy(livros[total_livros].autor, "Machado de Assis");
    strcpy(livros[total_livros].editora, "Principis");
    strcpy(livros[total_livros].genero, "Romance");
    strcpy(livros[total_livros].ano_publicacao, "2019");
    total_livros++;
}

void LimparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
