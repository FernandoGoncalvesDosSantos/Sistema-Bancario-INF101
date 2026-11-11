#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

// Procura uma conta pelo número e devolve a POSIÇÃO dela nos vetores
// (não o número da conta). Se não encontrar, devolve -1.
// Recebe: o vetor de números, quantas contas existem e o número procurado.
int buscarConta(int numeroConta[], int quantidade, int numero) {
    // Percorre as posições 0, 1, 2... até a última conta cadastrada.
    for (int i = 0; i < quantidade; i++) {
        // Achou o número: devolve a posição onde ele está.
        if (numeroConta[i] == numero) {
            return i;
        }
    }
    // Terminou o for sem achar nada.
    return -1;
}

// Função principal: o programa começa a ser executado aqui.
int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);


    // Limite de contas (const = valor que não muda durante a execução).
    const int MAX_CONTAS = 100;

    // Vetores paralelos: o mesmo índice em todos pertence à mesma conta.
    // Ex.: nomeCliente[0] e numeroConta[0] são da mesma conta.
    int numeroConta[MAX_CONTAS];
    string nomeCliente[MAX_CONTAS];
    string cpf[MAX_CONTAS];
    int tipoConta[MAX_CONTAS];      // 1 = Corrente, 2 = Poupança
    double saldo[MAX_CONTAS];
    bool contaAtiva[MAX_CONTAS];    // true = ativa, false = desativada
    int opcao;                      // opção escolhida no menu

    // Contadores: quantas contas / movimentações já existem.
    // Também indicam a próxima posição livre dos vetores.
    int quantidadeContas = 0;
    int quantidadeMovimentacoes = 0;

    // Limite do histórico de movimentações.
    const int MAX_MOVIMENTACOES = 500;

    // Histórico: cada posição é uma movimentação.
    int contaMovimentacao[MAX_MOVIMENTACOES];    // número da conta
    char tipoMovimentacao[MAX_MOVIMENTACOES];    // 'D' = depósito, 'S' = saque
    double valorMovimentacao[MAX_MOVIMENTACOES]; // valor movimentado

    // do-while: mostra o menu pelo menos uma vez e repete até digitar 8.
    do {
        // Menu principal.
        cout << "=============================================="<< endl;
        cout << "                 Banco INF101                 "<< endl;
        cout << "=============================================="<< endl;
        cout << "1 - Cadastrar contas."                         << endl;
        cout << "2 - Listar as contas cadastradas."             << endl;
        cout << "3 - Consultar uma conta pelo número."          << endl;
        cout << "4 - Realizar depósitos."                       << endl;
        cout << "5 - Realizar saques."                          << endl;
        cout << "6 - Realizar transferências entre duas contas."<< endl;
        cout << "7 - Exibir o extrato de uma conta."            << endl;
        cout << "8 - Sair"                                      << endl;
        cout << "Escolha uma opção: ";
        cin >> opcao;

        // Direciona para o bloco certo de acordo com a opção digitada.
        // O break no fim de cada case impede de cair no case seguinte.
        switch (opcao) {

            // CASE 1 - CADASTRO
            // Confere se há espaço, pede e valida os dados e guarda tudo
            // na mesma posição i para manter os dados do cliente juntos.
            case 1: {

                // Se já tem 100 contas, não cabe mais nenhuma.
                if (quantidadeContas >= MAX_CONTAS) {
                cout << "Limite de contas atingido!"                     << endl;
                break;
                }

                // Próxima posição livre. Ex.: com 2 contas (posições 0 e 1),
                // a nova vai para i = 2, sem sobrescrever as anteriores.
                int i = quantidadeContas;
                cout << "===========CADASTRO==========="                 << endl;

                // Nome
                cout << "Digite o seu nome: "                            << endl;
                // O cin >> opcao deixa o Enter pendente; o cin.ignore() descarta
                // essa quebra de linha, senão o getline leria uma linha vazia.
                cin.ignore();
                getline(cin, nomeCliente[i]); // lê a linha toda, aceita nomes com espaço

                // CPF
                cout << "Digite o seu CPF: "                             << endl;
                cin >> cpf[i];
                // Repete enquanto o CPF não tiver 11 caracteres
                // (só confere o tamanho, não se o CPF é válido de verdade).
                while (cpf[i].length() != 11) {
                    cout << "CPF invalido!"                              << endl;
                    cin >> cpf[i];
                }

                // Tipo da conta
                cout <<"Qual o tipo de conta? (1-Corrente, 2-Poupança):" << endl;
                cin >> tipoConta[i];
                // Só aceita 1 ou 2 (&& = E: repete se for diferente de 1 E de 2).
                while (tipoConta[i] != 1 && tipoConta[i] != 2) {
                    cout << "Opção invalida!"                            << endl;
                    cin >> tipoConta[i];
                }

                // Saldo inicial
                cout << "Quanto voce quer depositar? "                   << endl;
                cin >> saldo[i];
                // Bloqueia valores negativos; zero é permitido como saldo inicial.
                while (saldo[i] < 0) {
                    cout << "Saldo invalido!"                            << endl;
                    cin >> saldo[i];
                }

                // Número da conta (lido numa variável temporária para validar antes de gravar)
                int numero;
                cout << "Digite o numero da sua conta: "                 << endl;
                cin >> numero;
                // Repete se o número for <= 0 OU (||) se já existir em outra conta:
                // buscarConta devolve algo diferente de -1 quando acha o número.
                while (numero <= 0 || buscarConta(numeroConta, quantidadeContas, numero) != -1) {
                    cout << "Numero invalido ou ja existe!"              << endl;
                    cin >> numero;
                }
                numeroConta[i] = numero;   // só grava depois de validado

                contaAtiva[i] = true;      // toda conta nova começa ativa
                quantidadeContas++;        // agora existe mais uma conta

                // Resumo do cadastro.
                cout << "==============================================" << endl;
                cout << "             CADASTRO FINALIZADO              " << endl;
                cout << "==============================================" << endl;
                cout << "Nome: "                                         << nomeCliente[i] << endl;
                cout << "CPF: "                                          << cpf[i]         << endl;
                cout << "Numero da conta: "                              << numeroConta[i] << endl;
                cout << "Tipo da conta: "                                << tipoConta[i]   << endl;
                cout << "Saldo atual: R$ "                               << saldo[i]       << endl;

                break;
            }

            // CASE 2 - LISTAGEM
            // O for percorre todas as contas cadastradas, mostrando os dados
            // de cada posição i.
            case 2:

                // Sem contas cadastradas, avisa e volta ao menu.
                if (quantidadeContas == 0) {
                    cout << "Nenhuma conta cadastrada!"                  <<  endl;
                    break;
                }
                // Vai até quantidadeContas (e não MAX_CONTAS): o resto do vetor está vazio.
                for ( int i = 0; i <quantidadeContas; i++) {
                cout << " Numero da conta: " << numeroConta[i]           << endl;
                cout << " Nome: " << nomeCliente[i]                      << endl;
                cout << " cpf: " << cpf[i]                               << endl;
                // Troca o número guardado (1 ou 2) pelo nome do tipo.
                if (tipoConta[i] == 1) {
                    cout << " Tipo da conta: Corrente"                   << endl;
                }
                else {
                    cout << " Tipo da conta: Poupança"                   << endl;
                }
                // Mostra a situação da conta (true/false) como texto.
                if (contaAtiva[i] == true) {
                    cout << " Situação: Ativa"                           << endl;
                }
                else {
                    cout << " Situação: Desativada"                      << endl;
                }
                cout << "==============================================" << endl;
                cout << " Saldo atual: R$ " << saldo[i]                  << endl;
                }

                break;

            // CASE 3 - CONSULTA
            // O usuário informa o número da conta e buscarConta devolve a posição.
            case 3:
            {
                // Pede o número da conta a consultar.
                int numero;
                cout << "Digite o numero da conta: "                     << endl;
                cin >> numero;

                // i = posição da conta nos vetores (ou -1 se não existir).
                int i = buscarConta(numeroConta, quantidadeContas, numero);

                // Testa o -1 ANTES de usar [i]: a posição -1 não existe no vetor.
                if ( i== -1 ){
                    cout << "Conta não encontrada!"                      << endl;
                    break;
                }

                // daqui para baixo a conta existe
                cout << "================DADOS DA CONTA================" << endl;
                cout << "Numero da conta: " << numeroConta[i]            << endl;
                cout << "Nome: " << nomeCliente[i]                       << endl;
                cout << "Cpf: " << cpf[i]                                << endl;

                // Tipo da conta por extenso.
                if ( tipoConta[i] == 1){
                    cout << "Conta corrente."                            << endl;
                }
                else {
                    cout << "Conta poupança."                            << endl;
                }
                cout << "Saldo: " <<saldo[i]                             << endl;
                // Situação da conta.
                if ( contaAtiva[i] == true ){
                    cout << "Conta Ativa!"                               << endl;
                }
                else {
                    cout << " Conta bloqueada!"                          << endl;
                }

                break;
            }

            // CASE 4 - DEPÓSITO
            // Primeiro valida tudo (conta, situação, valor, espaço no histórico);
            // só depois altera o saldo e grava a movimentação.
            case 4:
            {
                // Pede o número da conta e acha a posição dela.
                int numero;
                cout << "Digite o numero da conta: ";
                cin >> numero;

                int i = buscarConta(numeroConta, quantidadeContas, numero);

                // Conta inexistente.
                if (i == -1) {
                    cout << "Conta nao encontrada!"                      << endl;
                    break;
                }

                // Conta desativada não pode receber depósito.
                if (contaAtiva[i] == false) {
                    cout << "Conta desativada. Nao e possivel depositar."<< endl;
                    break;
                }

                // Pede o valor do depósito.
                double valor;
                cout << "Valor do deposito: R$ ";
                cin >> valor;

                // Valor zero ou negativo não é depósito válido.
                if (valor <= 0) {
                    cout << "Valor invalido! Deve ser maior que zero."   << endl;
                    break;
                }

                // Se o histórico estiver cheio, não deposita (senão o saldo mudaria
                // sem ficar registrado no extrato).
                if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) {
                    cout << "Historico de movimentacoes cheio!"          << endl;
                    break;
                }

                // Soma o valor ao saldo da conta.
                saldo[i] = saldo[i] + valor;

                // Grava a movimentação na próxima posição livre do histórico.
                // Guarda o NÚMERO da conta (não a posição i) para o extrato filtrar depois.
                contaMovimentacao[quantidadeMovimentacoes] = numeroConta[i];
                tipoMovimentacao[quantidadeMovimentacoes]  = 'D';
                valorMovimentacao[quantidadeMovimentacoes] = valor;
                quantidadeMovimentacoes++;  // próxima movimentação usará a posição seguinte

                cout << "Deposito realizado! Novo saldo: R$ " << saldo[i]<< endl;
                break;
            }

            // CASE 5 - SAQUE
            // Parecido com o depósito, mas também confere se há saldo suficiente.
            case 5:
            {
                // Pede o número da conta e acha a posição dela.
                int numero;
                cout << "Digite o numero da conta: ";
                cin >> numero;

                int i = buscarConta(numeroConta, quantidadeContas, numero);

                // Conta inexistente.
                if (i == -1) {
                    cout << "Conta nao encontrada!"                    << endl;
                    break;
                }

                // Conta desativada não pode sacar.
                if (contaAtiva[i] == false) {
                    cout << "Conta desativada. Nao e possivel sacar."  << endl;
                    break;
                }

                // Pede o valor do saque.
                double valor;
                cout << "Valor do saque: R$ ";
                cin >> valor;

                // Valor zero ou negativo não é saque válido.
                if (valor <= 0) {
                    cout << "Valor invalido! Deve ser maior que zero." << endl;
                    break;
                }

                // Não deixa sacar mais do que existe na conta.
                if (valor > saldo[i]) {
                    cout << "Saldo insuficiente! Saldo atual: R$ " << saldo[i] << endl;
                    break;
                }

                // Precisa haver espaço no histórico para registrar o saque.
                if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) {
                    cout << "Historico de movimentacoes cheio!"        << endl;
                    break;
                }

                // Subtrai o valor do saldo da conta.
                saldo[i] = saldo[i] - valor;

                // Registra o saque ('S') no histórico.
                contaMovimentacao[quantidadeMovimentacoes] = numeroConta[i];
                tipoMovimentacao[quantidadeMovimentacoes]  = 'S';
                valorMovimentacao[quantidadeMovimentacoes] = valor;
                quantidadeMovimentacoes++;

                cout << "Saque realizado! Novo saldo: R$ " << saldo[i] << endl;
                break;
            }

            // CASE 6 - TRANSFERÊNCIA
            // Envolve duas contas (a que envia e a que recebe), então são
            // duas posições: iOrigem e iDestino.
            case 6:
            {
                // Pede os números das duas contas.
                int numeroOrigem;
                int numeroDestino;

                cout << "Digite o numero da conta de origem: ";
                cin >> numeroOrigem;
                cout << "Digite o numero da conta de destino: ";
                cin >> numeroDestino;

                // Cada busca devolve a posição da conta correspondente nos vetores.
                int iOrigem  = buscarConta(numeroConta, quantidadeContas, numeroOrigem);
                int iDestino = buscarConta(numeroConta, quantidadeContas, numeroDestino);

                // As duas contas precisam existir.
                if (iOrigem == -1) {
                    cout << "Conta de origem nao encontrada!"         << endl;
                    break;
                }

                if (iDestino == -1) {
                    cout << "Conta de destino nao encontrada!"        << endl;
                    break;
                }

                // Mesma posição = mesma conta nos dois campos: transferência cancelada.
                if (iOrigem == iDestino) {
                    cout << "A conta de origem e a de destino devem ser diferentes!" << endl;
                    break;
                }

                // As duas contas precisam estar ativas.
                if (contaAtiva[iOrigem] == false || contaAtiva[iDestino] == false) {
                    cout << "Uma das contas esta desativada. Transferencia nao realizada." << endl;
                    break;
                }

                // Pede o valor da transferência.
                double valor;
                cout << "Valor da transferencia: R$ ";
                cin >> valor;

                // Valor precisa ser positivo.
                if (valor <= 0) {
                    cout << "Valor invalido! Deve ser maior que zero." << endl;
                    break;
                }

                // A origem precisa ter saldo suficiente.
                if (valor > saldo[iOrigem]) {
                    cout << "Saldo insuficiente na conta de origem! Saldo atual: R$ "
                         << saldo[iOrigem] << endl;
                    break;
                }

                // Uma transferência grava DUAS movimentações (saída + entrada),
                // então precisa haver espaço para as duas no histórico.
                if (quantidadeMovimentacoes + 2 > MAX_MOVIMENTACOES) {
                    cout << "Historico de movimentacoes sem espaco para a transferencia!" << endl;
                    break;
                }

                // Tira o valor da origem e coloca no destino.
                saldo[iOrigem]  = saldo[iOrigem]  - valor;
                saldo[iDestino] = saldo[iDestino] + valor;

                // Registro 1: saída da conta de origem.
                contaMovimentacao[quantidadeMovimentacoes] = numeroConta[iOrigem];
                tipoMovimentacao[quantidadeMovimentacoes]  = 'S';
                valorMovimentacao[quantidadeMovimentacoes] = valor;
                quantidadeMovimentacoes++;

                // Registro 2: entrada na conta de destino.
                contaMovimentacao[quantidadeMovimentacoes] = numeroConta[iDestino];
                tipoMovimentacao[quantidadeMovimentacoes]  = 'D';
                valorMovimentacao[quantidadeMovimentacoes] = valor;
                quantidadeMovimentacoes++;

                // Mostra o novo saldo das duas contas.
                cout << "Transferencia realizada!"                      << endl;
                cout << "Novo saldo da conta " << numeroConta[iOrigem]
                     << ": R$ " << saldo[iOrigem]                       << endl;
                cout << "Novo saldo da conta " << numeroConta[iDestino]
                     << ": R$ " << saldo[iDestino]                      << endl;
                break;
            }

            // CASE 7 - EXTRATO
            // Só consulta o histórico (não altera saldo): percorre todas as
            // movimentações e mostra as da conta escolhida.
            case 7:
            {
                // Pede o número da conta e acha a posição dela.
                int numero;
                cout << "Digite o numero da conta: ";
                cin >> numero;

                int i = buscarConta(numeroConta, quantidadeContas, numero);

                // Conta inexistente.
                if (i == -1) {
                    cout << "Conta nao encontrada!"                       << endl;
                    break;
                }

                cout << "============ EXTRATO DA CONTA " << numeroConta[i] << " ============" << endl;

                int encontradas = 0;   // quantas movimentações essa conta tem

                // k percorre o histórico (o i já é a posição da conta).
                for (int k = 0; k < quantidadeMovimentacoes; k++) {
                    // Só mostra a movimentação se for dessa conta.
                    if (contaMovimentacao[k] == numeroConta[i]) {
                        if (tipoMovimentacao[k] == 'D') {
                            cout << "Deposito: R$ " << valorMovimentacao[k]<< endl;
                        }
                        else if (tipoMovimentacao[k] == 'S') {
                            cout << "Saque: R$ " << valorMovimentacao[k]   << endl;
                        }
                        encontradas++;
                    }
                }

                // Nenhuma movimentação encontrada para essa conta.
                if (encontradas == 0) {
                    cout << "Nenhuma movimentacao registrada."             << endl;
                }

                cout << "Saldo atual: R$ " << saldo[i]                     << endl;
                break;
            }

            // CASE 8 - SAIR (o do-while encerra quando opcao for 8)
            case 8:

            cout << "Saindo..."                                            << endl;

                break;

            default: // Número que não é nenhuma opção do menu.
                cout << "Opcao invalida!"                                  << endl;
            }

        }
    while (opcao != 8);

return 0;
}
