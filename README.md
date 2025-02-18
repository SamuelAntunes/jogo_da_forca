# Jogo da Forca - Versão 2.0

Este é um projeto simples em C++ que implementa o clássico jogo da forca. A versão 2.0 apresenta uma interface aprimorada com arte ASCII, cores via códigos ANSI e modos de jogo para um ou dois jogadores.

## Funcionalidades

- **Modos de Jogo:**  
  - *Single-player:* O jogo seleciona uma palavra aleatória para você adivinhar.  
  - *Multiplayer:* Um jogador informa a palavra e o outro tenta adivinhar.

- **Interface Melhorada:**  
  - Exibição de uma forca em ASCII que é atualizada conforme os erros.
  - Uso de cores (via códigos ANSI) para destacar mensagens e status.
  - Layout com divisórias e mensagens claras para facilitar a leitura.

- **Compatibilidade Cross-Platform:**  
  - Função de limpeza de tela adaptada para Windows e sistemas Unix-like.
  - Localidade configurada para evitar problemas com caracteres especiais (acentuação).

## Pré-requisitos

- **Compilador C++:**  
  É necessário um compilador que suporte C++11 ou superior (por exemplo, g++, clang++ ou Visual Studio).

- **Terminal com suporte a ANSI (opcional):**  
  Para exibição correta das cores, seu terminal deve suportar códigos ANSI. Caso contrário, as cores poderão não ser exibidas.

## Instalação e Compilação

1. **Clone o repositório ou faça o download do arquivo `jogo_forca.cpp`.**

2. **Abra o terminal na pasta do projeto e compile utilizando:**

   ```bash
   g++ -o jogo_forca jogo_forca.cpp
