#include <iostream>
#include <cstdlib>  // biblioteca utilizada pela função limpaTela
#include <limits>   // biblioteca utilizada para sanitizar as entradas de usuário
#include <iomanip>  // biblioteca utilizada para formatar as saídas de dados na tela

using namespace std;

void limpaTela();
void bemVindo();
void estoque(bool admin);
void cadastroProdutos();
void vendaProduto(int codigo);
int usuario();
bool validaProduto(int codigo);
void administracao();
void reposicaoEstoque();
void relatorioFinanceiro();
void retiraSaldo(double& valorTotalVendas);


const int MAX_PRODUTO = 50; // indica a quantidade máxima de diferentes produtos que a Vending Machine poderá ter
const string ADMIN_PASSWORD = "admin"; // indica qual senha deverá ser digitada para acecssar o menu de administração

struct Produto {
    int codigo;
    string nome;
    double valor;
    int quantidade;
}; // cria a estrutura de dados para receber as informações dos produtos

Produto produto[MAX_PRODUTO]; //cria um vetor do tipo Produto para armazenar as informações dos produtos
int conta_produto = 0; // mantem registro de quantos produtos estão cadastrados
double valorTotalVendas = 0.0; // Variável para armazenar o valor total das vendas realizadas


void limpaTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void bemVindo() {
    cout << "Bem-vindo(a) à Vending Machine!" << endl;
    cout << "------------------------------" << endl;
}

void relatorioFinanceiro() {
    cout << "\nRelatório Financeiro" << endl;
    cout << "--------------------" << endl;

    cout << "Faturamento com as vendas realizadas: R$" << fixed << setprecision(2) << valorTotalVendas << endl;

    double valorTotalEstoque = 0.0;
    for (int i = 0; i < conta_produto; i++) {
        valorTotalEstoque += produto[i].valor * produto[i].quantidade;
    }

    cout << "Faturamento previsto com o estoque disponível: R$" << fixed << setprecision(2) << valorTotalEstoque << endl;
}

void retiraSaldo(double& valorTotalVendas) {
    cout << "\nRetirada de Saldo" << endl;
    cout << "------------------" << endl;

    if (valorTotalVendas == 0.0) {
        cout << "Não há saldo disponível para retirada." << endl;
    } else {
        cout << "Saldo atual: R$" << fixed << setprecision(2) << valorTotalVendas << endl;
        cout << "Realizando a retirada de saldo..." << endl;
        valorTotalVendas = 0.0;
        cout << "Retirada de saldo concluída com sucesso." << endl;
    }
}

// A função estoque recebe como parâmetro a informação se ela foi chamada por administrador ou por usuário
void estoque(bool admin) {
	// Se não existir estoque para venda, é chamado o menu de administração
    if (conta_produto == 0) {
        cout << "Sem produtos em estoque." << endl;
        administracao();
    } 
	cout << "Produtos em estoque:" << endl;
	cout << "-------------------" << endl;
	double valorTotal = 0.0;
	int quantidadeTotal = 0;
	// Imprime o cabeçalho da tabela de estoque
	cout << left << setw(7) << setfill(' ')  << "Código" << " | "
				 << setw(20) << setfill(' ') << "Nome"   << " | "
				 << setw(8) << setfill(' ')  << "Preço R$" << " | "
											 << "Quantidade " ;
	// Se a função foi chamada pelo administrador, exibe também o valor total de cada item
	if (admin)
		cout << " | Total";

	cout << endl;

	// Imprime a tabela de estoque
	for (int i = 0; i < conta_produto; i++) {
		cout << right << "  " 
					<< setw(2)  << setfill('0') << produto[i].codigo << "  " << " | "
			<< left  << setw(20) << setfill(' ') << produto[i].nome << " | "
			<< right << setw(8)  << setfill(' ') << fixed << setprecision(2) << produto[i].valor << " | "
			<< "    " << setw(2)  << setfill(' ') << produto[i].quantidade;

	// Se a função foi chamada pelo administrador, exibe também o valor total de cada item
		if (admin)
			cout << setw(8)  << " | " << produto[i].valor * produto[i].quantidade;

		cout << endl;
		quantidadeTotal += produto[i].quantidade;
		valorTotal += produto[i].valor * produto[i].quantidade;
	}

	// Se a função foi chamada pelo administrador, exibe também a quantidade de itens em inventario e o valor total do estoque
	if (admin) {
		cout << "-------------------" << endl;
		cout << "Total de itens em estoque: " << fixed << quantidadeTotal << endl;
		cout << "Valor total em estoque: R$ " << fixed << setprecision(2) << valorTotal << endl;
	}
}

void reposicaoEstoque() {
    string entrada;
    while (true) {
		limpaTela();
	    cout << "\nReposição de Estoque" << endl;
		cout << "---------------------" << endl;

		estoque(true); // Exibe o estoque atual na tela. O parâmetro true indica que é execução do administrador.

        cout << "\nDigite o código do produto que deseja repor (ou 'fim' para sair): ";
        cin >> entrada;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer de entrada

        // Verifica se o usuário deseja sair da rotina de reposição de estoque
        if (entrada == "fim") {
            cout << "Encerrando reposição de estoque..." << endl;
            break;
        }

        int codigo;

		// O valor informado pelo usuário é convertivo de str para int.
		// Se resultar em erro, é solicitada nova entrada de dados.
        try {
            codigo = stoi(entrada);
        } catch (...) {
            cout << "Código de produto inválido. Por favor, tente novamente." << endl;
            continue;
        }

        if (!validaProduto(codigo)) {
            cout << "Código de produto inválido. Por favor, tente novamente." << endl;
            continue;
        }

        // Procura o produto no estoque
        int indice = -1;
        for (int i = 0; i < conta_produto; i++) {
            if (produto[i].codigo == codigo) {
                indice = i;
                break;
            }
        }

        if (indice == -1) {
            cout << "Produto não encontrado no estoque." << endl;
            continue;
        }

        cout << "Digite a quantidade a ser acrescentada para o produto '" << produto[indice].nome << "': ";
        int quantidade;
		
		// Recebe do usuário a quantidade a ser acrescentada no estoque. Caso não seja um valor válido, é solicitado novamente.
        if (!(cin >> quantidade)) {
            cout << "Entrada inválida. Insira um valor numérico." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer de entrada

        if (quantidade <= 0) {
            cout << "Quantidade inválida. A quantidade deve ser maior que zero." << endl;
            continue;
        }

        // Atualiza a quantidade do produto no estoque
        produto[indice].quantidade += quantidade;

        cout << "Estoque do produto '" << produto[indice].nome << "' atualizado com sucesso!" << endl;
    }
}

void cadastroProdutos() {
	limpaTela();
    cout << "\nCadastro de Produtos" << endl;
    cout << "---------------------" << endl;

    int codigo;
    string nome;
    double valor;
    int quantidade;
    string entrada;

    while (true) {
        // Verifica se atingiu o limite de produtos cadastrados
        if (conta_produto == MAX_PRODUTO) {
            cout << "Limite máximo de produtos cadastrados atingido." << endl;
            break;
        }

        cout << "Digite o código do produto (01-" << MAX_PRODUTO - 1 << ") ou 'fim' para sair: ";
        cin >> entrada;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer de entrada

        // Verifica se o usuário deseja sair do cadastro de produtos
        if (entrada == "fim"){
			limpaTela();
           break;
		}

		// O valor informado pelo usuário é convertivo de str para int.
		// Se resultar em erro, é solicitada nova entrada de dados.
		try {
			codigo = stoi(entrada); 
			}
		catch (const invalid_argument& e) {
			cout << "Entrada inválida." << endl;
			cout << "Digite o código do produto (01-" << MAX_PRODUTO - 1 << ") ou 'fim' para sair: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

        // Verifica se o código já está sendo utilizado
        bool codigoExiste = false;
        for (int i = 0; i < conta_produto; i++) {
            if (produto[i].codigo == codigo) {
                codigoExiste = true;
                break;
            }
        }

        if (codigoExiste) {
            cout << "Código já cadastrado. Tente novamente." << endl;
            continue;
        }
		
		// Verifica se o código está fora do intervalo permitido
		if (codigo < 1 || codigo > MAX_PRODUTO - 1){
			cout << "Entrada inválida." << endl;
			cout << "Digite o código do produto (01-" << MAX_PRODUTO - 1 << ") ou 'fim' para sair: ";
			continue;
		}
		
		// Estando tudo ok com o código informado, procede com o cadastramento do produto.
        cout << "Digite o nome do produto: ";
        getline(cin, nome);

        cout << "Digite o valor do produto: ";
        cin >> valor;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer de entrada

        cout << "Digite a quantidade em estoque: ";
        cin >> quantidade;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer de entrada
        
        // Realiza o cadastro do produto na struct
        produto[conta_produto].codigo = codigo;
        produto[conta_produto].nome = nome;
        produto[conta_produto].valor = valor;
        produto[conta_produto].quantidade = quantidade;
        
        conta_produto++; // variável para acompanhar a quantidade de produtos cadastrados
        
        cout << "Produto cadastrado com sucesso!" << endl;
    }
}

void vendaProduto(int codigo) {
    // Verifica se o produto existe
    int indiceProduto = -1;
    for (int i = 0; i < conta_produto; i++) {
        if (produto[i].codigo == codigo) {
            indiceProduto = i;
            break;
        }
    }

    if (indiceProduto == -1) {
        cout << "Produto não encontrado. Aperte enter para continuar" << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // pausa a tela para o usuário ler a mensagem aguardando Enter para continuar
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // não consegui identificar o motivo, mas apenas 1 instrução não pausava a tela.
        return;
    }

    Produto produtoVendido = produto[indiceProduto];

    // Verifica se há estoque suficiente
    if (produtoVendido.quantidade == 0) {
        cout << "Produto indisponível no momento. Aperte enter para continuar" << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "Produto selecionado: " << produtoVendido.nome << endl;

    // Solicita ao usuário para inserir o dinheiro na máquina
    double valorInserido = 0.0;
    double valorTotal = 0.0;
    while (valorTotal < produtoVendido.valor) {
        cout << "Valor total inserido: R$" << fixed << setprecision(2) << valorTotal << endl;
        cout << "Insira o dinheiro na máquina e informe o valor: R$";
        double valor;
        if (!(cin >> valor)) {
            cout << "Entrada inválida. Insira um valor numérico." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (valor <= 0) {
            cout << "Valor inválido. Insira um valor positivo." << endl;
            continue;
        }

        valorInserido += valor;
        valorTotal += valor;
    }

    // Calcula o troco 
    double troco = valorTotal - produtoVendido.valor;

    // Atualiza estoque
    produto[indiceProduto].quantidade--;

	// Atualiza o valor total das vendas
    valorTotalVendas += produtoVendido.valor;

    cout << "Compra realizada com sucesso!" << endl;

    // Verifica se já troco e mprime a mensagem correspondente
    if (troco > 0) {
        cout << "Troco: R$" << fixed << setprecision(2) << troco << endl;
        cout << "Retire o troco." << endl;
    }

    cout << "Retire o produto." << endl;
    cout << "Pressione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return;
}

// Interface do modo usuário - essa interface abre por padrão, exceto se não tiver estoque dos produtos.
int usuario() {
    int codigo;
	
	 // O valor recebido do usuário será do tipo str para permitir os comandos fim e adm
	 // Verificando que não ocorreu nenhuma dessas entradas, o valor será convertido para int
	string entrada;

	limpaTela();
    bemVindo();
	
	// A função estoque vai verificar o estoque e imprimir na tela os produtos disponíveis para o usuário efetuar a compra
    estoque(false); // o parâmetro false indica que a função não foi chamada pelo administrador

    cout << "Digite o código do produto desejado (ou 'fim' para encerrar): ";

	cin >> entrada;

	// Na interface do usuário, pode-se utilizar a entrada adm para acessar a interface de Administração
	if (entrada == "adm") {
		administracao();
		return usuario();
	}

	if (entrada == "fim") {
		cout << "Encerrando programa..." << endl;
		return -1;
	}

	// O valor informado pelo usuário é convertivo de str para int.
	// Se resultar em erro, é solicitada nova entrada de dados.
	try {
		codigo = stoi(entrada);
	} catch (...) {
		cout << "Código de produto inválido. Por favor, tente novamente." << endl;
		return usuario();
	}
	if (validaProduto(codigo)) {
	    vendaProduto(codigo);

	} else {
		cout << "Código de produto inválido. Por favor, tente novamente." << endl;
		return usuario();
	}

    return codigo;
}

// Função utilizada para verificar se o código de produto está dentro do esperado.
bool validaProduto(int codigo) {
    return (codigo >= 0 && codigo < MAX_PRODUTO);
}

// Interface de administração
void administracao() {
    string senha;
    cout << "Digite a senha de administrador: (admin) ";
    cin >> senha;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer de entrada

    // Verifica se a senha está correta
    if (senha != ADMIN_PASSWORD) {
        return;
    }

    cout << "Acesso autorizado!" << endl;
    while (true) {

        cout << "\nMenu de Administração:" << endl;
        cout << "1. Cadastro de Produtos" << endl;
        cout << "2. Mostrar Estoque" << endl;
        cout << "3. Reposição do Estoque" << endl;
        cout << "4. Relatório Financeiro" << endl;
        cout << "5. Retirada de Saldo" << endl;
        cout << "0. Sair" << endl;

        int opcao;
        cout << "\nEscolha uma opção: ";
        cin >> opcao;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer de entrada

        switch (opcao) {
            case 1:
                cadastroProdutos();
                break;
            case 2:
				limpaTela();
                estoque(true);
                break;
            case 3:
                reposicaoEstoque();
                break;
            case 4:
				limpaTela();
                relatorioFinanceiro();
                break;
            case 5:
				limpaTela();
                retiraSaldo(valorTotalVendas);
                break;
            case 0:
                cout << "Encerrando menu de Administração..." << endl;
                limpaTela();
                return;
            default:
                cout << "Opção inválida. Tente novamente." << endl;
                break;
        }
    }
}

int main() {
    int codigo = 0;
    while (codigo != -1) {
        codigo = usuario();
    }
    return 0;
}
