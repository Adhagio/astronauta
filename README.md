# Astronautas — Linguagem de Programação I

Sistema em C++11 para uma agência espacial: cadastra astronautas e voos,
adiciona/remove astronautas, lança, explode e finaliza voos, lista voos,
lista mortos, mostra histórico, salva/carrega em arquivo, gera relatório
e desfaz o último comando.

## Como compilar
g++ -std=c++11 -Wall -Wno-sign-compare src/main.cpp -o agencia

## Como rodar
./agencia < testes/parte1/01_cadastros.in

## Como testar
bash testes/testar.sh parte1
bash testes/testar.sh missao1
bash testes/testar.sh missao2
bash testes/testar.sh missao3

## Missão 4 (DESFAZER)
Arquivo de comandos: meus_testes/missao4.in
Rodar: Get-Content meus_testes\missao4.in | .\agencia