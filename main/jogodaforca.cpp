#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <cctype>
#include <limits>
#include <locale>

using namespace std;

// Códigos ANSI para cores (caso seu terminal suporte)
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_CYAN "\033[36m"

// Funcao para pausar e aguardar que o usuario pressione ENTER
void pressEnterToContinue() {
    cout << "\nPressione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Limpa a tela de forma cross-platform
void limpaTela() {
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}

// Exibe a forca de acordo com o numero de erros (0 ate 6)
void exibeForca(int erros) {
    cout << COLOR_RED;
    switch(erros) {
        case 0:
            cout << "  +---+\n";
            cout << "  |   |\n";
            cout << "      |\n";
            cout << "      |\n";
            cout << "      |\n";
            cout << "      |\n";
            cout << "=========\n";
            break;
        case 1:
            cout << "  +---+\n";
            cout << "  |   |\n";
            cout << "  O   |\n";
            cout << "      |\n";
            cout << "      |\n";
            cout << "      |\n";
            cout << "=========\n";
            break;
        case 2:
            cout << "  +---+\n";
            cout << "  |   |\n";
            cout << "  O   |\n";
            cout << "  |   |\n";
            cout << "      |\n";
            cout << "      |\n";
            cout << "=========\n";
            break;
        case 3:
            cout << "  +---+\n";
            cout << "  |   |\n";
            cout << "  O   |\n";
            cout << " /|   |\n";
            cout << "      |\n";
            cout << "      |\n";
            cout << "=========\n";
            break;
        case 4:
            cout << "  +---+\n";
            cout << "  |   |\n";
            cout << "  O   |\n";
            cout << " /|\\  |\n";
            cout << "      |\n";
            cout << "      |\n";
            cout << "=========\n";
            break;
        case 5:
            cout << "  +---+\n";
            cout << "  |   |\n";
            cout << "  O   |\n";
            cout << " /|\\  |\n";
            cout << " /    |\n";
            cout << "      |\n";
            cout << "=========\n";
            break;
        case 6:
            cout << "  +---+\n";
            cout << "  |   |\n";
            cout << "  O   |\n";
            cout << " /|\\  |\n";
            cout << " / \\  |\n";
            cout << "      |\n";
            cout << "=========\n";
            break;
        default:
            cout << "  +---+\n";
            cout << "  |   |\n";
            cout << "  O   |\n";
            cout << " /|\\  |\n";
            cout << " / \\  |\n";
            cout << "      |\n";
            cout << "=========\n";
            break;
    }
    cout << COLOR_RESET;
}

// Retorna uma palavra aleatoria de uma lista
string retornaPalavraAleatoria() {
    vector<string> palavras = {"abacaxi", "manga", "morango", "laranja", "uva", "pera"};
    int indiceAleatorio = rand() % palavras.size();
    return palavras[indiceAleatorio];
}

// Retorna a palavra mascarada (ex: "_____" para "manga")
string retornaPalavraComMascara(const string &palavra) {
    return string(palavra.size(), '_');
}

// Exibe o status atual do jogo
void exibeStatus(const string &palavraComMascara, int chancesRestantes,
                 const string &letrasJaArriscadas, const string &mensagem) {
    cout << COLOR_CYAN;
    cout << "====================================\n";
    cout << mensagem << "\n";
    cout << "====================================\n";
    cout << "Palavra: " << palavraComMascara
         << " (Tamanho: " << palavraComMascara.size() << ")\n";
    cout << "Chances Restantes: " << chancesRestantes << "\n";
    cout << "Letras ja arriscadas: ";
    for (char letra : letrasJaArriscadas) {
        cout << letra << " ";
    }
    cout << "\n====================================\n";
    cout << COLOR_RESET;
}

// Funcao que executa o jogo (modo um ou dois jogadores)
// Retorna true se o jogador optar por reiniciar, ou false para sair
bool jogar(int numeroDeJogadores) {
    string palavra;
    if (numeroDeJogadores == 1) {
        palavra = retornaPalavraAleatoria();
    } else {
        limpaTela();
        cout << "Modo Dupla: Jogador 1, digite a palavra secreta: ";
        cin >> palavra;
        limpaTela();
    }
    
    string palavraComMascara = retornaPalavraComMascara(palavra);
    const int maxErros = 6;
    int erros = 0;
    char letra;
    string letrasJaArriscadas;
    string mensagem = "Bem vindo ao jogo!";
    string palavraArriscada;
    
    // Loop principal: enquanto a palavra nao for descoberta e os erros forem menores que o maximo
    while (palavra != palavraComMascara && erros < maxErros) {
        limpaTela();
        exibeStatus(palavraComMascara, maxErros - erros, letrasJaArriscadas, mensagem);
        exibeForca(erros);
        
        cout << "\nDigite uma letra (ou digite 1 para arriscar a palavra): ";
        cin >> letra;
        
        // Opcao de arriscar a palavra completa
        if (letra == '1') {
            cout << "Digite sua tentativa para a palavra completa: ";
            cin >> palavraArriscada;
            if (palavraArriscada == palavra) {
                palavraComMascara = palavra;
                mensagem = "Voce acertou a palavra!";
            } else {
                mensagem = "Palavra incorreta!";
                erros = maxErros; // Forca o fim do jogo
            }
            pressEnterToContinue();
            continue;
        }
        
        letra = tolower(letra);
        
        // Verifica se a letra ja foi digitada
        if (letrasJaArriscadas.find(letra) != string::npos) {
            mensagem = "Letra ja utilizada!";
            pressEnterToContinue();
            continue;
        }
        
        letrasJaArriscadas.push_back(letra);
        
        bool acertouLetra = false;
        for (size_t i = 0; i < palavra.size(); i++) {
            if (tolower(palavra[i]) == letra) {
                palavraComMascara[i] = palavra[i];
                acertouLetra = true;
            }
        }
        
        if (!acertouLetra) {
            mensagem = "Voce errou a letra!";
            erros++;
        } else {
            mensagem = "Voce acertou a letra!";
        }
        
        pressEnterToContinue();
    }
    
    limpaTela();
    int opcao;
    if (palavra == palavraComMascara) {
        cout << COLOR_GREEN;
        cout << "====================================\n";
        cout << "      PARABENS, VOCE VENCEU!\n";
        cout << "====================================\n";
        cout << COLOR_RESET;
    } else {
        cout << COLOR_RED;
        cout << "====================================\n";
        cout << "      QUE PENA, VOCE PERDEU!\n";
        cout << "A palavra era: " << palavra << "\n";
        cout << "====================================\n";
        cout << COLOR_RESET;
    }
    
    cout << "\nDeseja reiniciar?\n";
    cout << "1 - Sim\n";
    cout << "2 - Nao\n";
    cout << "Opcao: ";
    cin >> opcao;
    return (opcao == 1);
}

// Menu principal do jogo
void menuInicial() {
    int opcao;
    bool continuar = true;
    while (continuar) {
        limpaTela();
        cout << COLOR_CYAN;
        cout << "====================================\n";
        cout << "       JOGO DA FORCA - VERSAO 2.0\n";
        cout << "====================================\n";
        cout << "1 - Jogar Sozinho\n";
        cout << "2 - Jogar em Dupla\n";
        cout << "3 - Sobre\n";
        cout << "4 - Sair\n";
        cout << "====================================\n";
        cout << COLOR_RESET;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        
        switch (opcao) {
            case 1:
                if (jogar(1)) continue;
                else continuar = false;
                break;
            case 2:
                if (jogar(2)) continue;
                else continuar = false;
                break;
            case 3:
                limpaTela();
                cout << COLOR_YELLOW;
                cout << "====================================\n";
                cout << "             SOBRE O JOGO\n";
                cout << "====================================\n";
                cout << "Jogo da Forca desenvolvido por Joao em 2017.\n";
                cout << "Projeto revisado e melhorado para uma melhor experiencia.\n";
                cout << "====================================\n";
                cout << COLOR_RESET;
                cout << "\n1 - Voltar\n";
                cout << "2 - Sair\n";
                cout << "Opcao: ";
                cin >> opcao;
                if (opcao == 2) continuar = false;
                break;
            case 4:
                cout << "\nObrigado por jogar! Ate mais.\n";
                continuar = false;
                break;
            default:
                cout << "\nOpcao invalida!";
                pressEnterToContinue();
                break;
        }
    }
}

int main() {
    // Define a localidade para evitar problemas com caracteres especiais
    setlocale(LC_ALL, "en_US.UTF-8");
    
    // Semente para gerar numeros aleatorios
    srand(static_cast<unsigned>(time(nullptr)));
    
    menuInicial();
    return 0;
}
