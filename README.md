# alp-vending

FATEC / ALP / 2023

Automação de Vending Machine


### Funcionamento do programa:
Na inicialização será verificado se existe estoque de produtos na máquina.  
Caso não existam produtos em estoque, será solicitada a senha de administrador (admin)  
  
### Interface de Usuário  
Na interface de usuário, o programa vai exibir os produtos e quantidades disponíveis.  
O usuário pode informar o código do produto desejado, digitar fim para sair do programa
ou digitar adm para acessar o menu de administração.  

Ao um código de produto nessa interface,  programa irá verificar se o código informado pelo usuário é válido.  
Sendo um código de produto válido, será solicitado ao usuário informar o valor do pagamento.  
Para o valor, deverá ser utilizado . (ponto) como separador decimal, caso não seja um valor inteiro.  
Caso o valor não seja suficiente, o usuário deverá complementar (em uma vending machine é inserida uma nota de cada vez).  
  
Ao realizar a venda, o programa verificará:
- Se existe estoque do produto solicitado
- Se o usuário informou valor suficiente para pagar pelo produto  
  
Atendidas as 2 condições acima, será realizada:
- A baixa de estoque
- Soma do valor da venda no faturamento da máquina
- Cálculo do troco

Após a conclusão da venda, será apresentada ao usuário a tela inicial, com o estoque atualizado, permitindo realizar nova venda.  
  
### Interface de Administração
Na interface de administração, o usuário poderá realizar:
- O cadastramento de produtos
- Mostrar o estoque (inventário)
- Reposição de produtos
- Relatório Financeiro (faturamento)
- Retirada de Saldo (zera o caixa da máquina)
  
#### Cadastramento de produtos
O cadastramento dos produtos será realizado com a inclusão do código do produto, nome, preço e quantidade.  
O código de produto é um valor inteiro definido entre 01 e 49 (esse valor é ajustável no código fonte).  
O nome do produto não foi limitado, mas a interface está preparada para até 20 caracteres na exibição do estoque.  
Para o valor, deverá ser utilizado . (ponto) como separador decimal.  
A rotina de cadastramento se repete até o usuário digitar "fim".  
  
#### Mostra o Estoque
O programa irá mostrar o inventário de produtos com as seguintes informações:
- Código
- Nome do produto
- Valor do Produto
- Quantidade em Estoque
- Valor total para cada item
- Quantidade total de itens no inventário
- Valor total do estoque
  
#### Reposição de Produtos
Na reposição de produtos, será apresentado ao usuário o inventário atual e solicitado informar qual item será reposto.  
Após a informação do item, será solicitada a quantidade que será reposta.  
A rotina de reposição se repete até o usuário digitar "fim".  
  
#### Relatório Financeiro (faturamento)
É mostrado ao usuário o valor faturado até aquele momento (saldo em caixa).  
É mostrado ao usuário o valor total do estoque (faturamento previsto).  

#### Retirada de Saldo
Esta função registra a retirada do saldo existente na máquina, zerando o caixa.  
  
  
   
## Requisitos do trabalho:

Programa para automatizar o funcionamento de uma vending machine.

##### Modo Usuário
-	Listar produtos e valores
-	Usuário escolhe o produto
-	Usuário informa o valor inserido na máquina
-	Verifica estoque do ítem escolhido
-	Retira o produto
-	Verifica se existe troco
-	Retira o troco
	
##### Modo Administrador
-	Listar estoque
-	Abastecer Produtos
-	Listar faturamento
-	Listar faturamento previsto

##### Critérios de Avaliação:

Rubrica de avaliação (o que será avaliado no seu código-fonte):
- Você deve publicar seu projeto no github contendo a identicação (RA/Nome) dos
autores no arquivo README.
- Para entregar seu projeto você deve acessar a respectiva tarefa no Teams e submeter
o link (público) do projeto do github.
- A data de entrega está especificada na respectiva tarefa no Teams.

1. Código-fonte identicado.
2. Código-fonte formatado.
3. Variáveis com nomes auto-explicativos.
4. Uso de estruturas de repetição adequadas.
5. Uso de funções de maneira adequada.
6. A solução algorítmica propriamente dita.
