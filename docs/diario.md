## Ambiente

• Versão do OpenCode (opencode --version):
1.18.33
• Modelo usado:
Big Pickle (OpenCode Zen)

## Parte 1: antes de programar

• O que cada classe guarda:
Astronauta: CPF, nome, idade, se está vivo e se está disponível. Todo astronauta
começa vivo e disponível. Quem muda isso é o próprio astronauta, por métodos
como embarcar(), desembarcar() e morrer().
Voo: código, estado (planejado / em curso / finalizado com sucesso / finalizado
com explosao) e os CPFs dos astronautas a bordo.
Agencia: um vector<Astronauta> e um vector<Voo>. É ela que coordena tudo: confere
se o astronauta existe, se o voo está planejado, se todos estão vivos, e só então
manda o voo e os astronautas mudarem de estado.

• O que acontece em LANCAR_VOO, em palavras:
A Agencia procura o voo. Se não existe, imprime erro. Se não está planejado,
imprime erro. Se não tem astronautas, imprime erro. Depois percorre os CPFs a
bordo, na ordem em que foram adicionados: no primeiro que estiver morto imprime
a mensagem de morto e para; se estiver indisponível, imprime a mensagem de
indisponível e para. Só se todos passarem é que manda cada um embarcar e o voo
mudar para "em curso". Tudo é conferido antes de mudar qualquer coisa.

• Uma dúvida que eu tinha antes de começar:

1. Por que a regra de lançamento fica na Agencia e não dentro do Voo, já que o
   Voo é quem sabe quais CPFs estão a bordo? Se a regra ficasse no Voo, ele
   precisaria conhecer os astronautas para saber quem está vivo, e a classe
   cresceria sem necessidade.

2. Como remover um astronauta do vector de CPFs de um voo? Não sabia que era
   preciso achar a posição com um laço e depois chamar .erase(cpfs.begin() + i).

3. Por que checar "está morto" antes de "está indisponível", se um morto também
   está indisponível? E por que é preciso conferir todos os astronautas antes
   de mudar qualquer um, em vez de embarcar um por um?

4. Por que ler o nome com getline(cin >> ws, nome) em vez de simplesmente
   cin >> nome? Não entendia o que o cin >> ws fazia antes do getline.

5. Como o programa decide a ordem das mensagens de erro quando mais de uma
   verificação falha ao mesmo tempo? Por que a primeira que falha é a única
   que aparece?

6. Por que o size() de um vector devolve size_t e não int? Por que misturar os
   dois na comparação gera aviso do compilador?

No final, creio que, supostamente, eu tenha entendido tudo.

## Parte 1: uso de IA para entender algo

• O que perguntei (ou “não usei”):
Antes de programar, usei a IA para entender o que a atividade pedia. Perguntei
o que significavam os arquivos .in e .out em testes/parte1, como o script
testar.sh comparava a saída do meu programa com a esperada, e por que o
main.cpp já vinha com TODOs nos pontos onde eu deveria chamar os métodos.

• O que aprendi:
Que os testes comparam a saída letra por letra, que os TODOs do main só ligam
os comandos à Agencia, e que testar.sh compila e compara cada .in com o .out.

## Primeiro contato: revisão sem editar

• As três melhorias que a IA sugeriu, em uma linha cada:
1. Verificar se a leitura do cin funcionou, para não cadastrar astronauta com
   idade lixo quando a entrada é inválida.
2. Trocar os textos de estado do Voo por um enum, para o compilador garantir
   que só os quatro valores válidos são usados.
3. Extrair a validação repetida "voo nao cadastrado / nao planejado" para um
   método só na Agencia.

• A que escolhi e por quê:
A 3. Escolhi essa porque é mais didática: mexe só na Agencia, não muda a saída
do programa e me deixa ver na prática como uma validação repetida vira um
método só. Como estou aprendendo a matéria, preferi uma mudança que eu
conseguisse acompanhar linha por linha sem me perder no resto do código.

• O que mudou no código, e se os seis testes continuaram passando:
A Agencia ganhou o método vooPlanejado(codigo), que faz a checagem e devolve
o índice ou -1, já imprimindo o erro. adicionarAstronauta, removerAstronauta
e lancarVoo passaram a usar esse método. Também criei o AGENTS.md com as
instruções para a IA. Os 6 testes da parte1 continuaram passando.

• O que entendi que não sabia antes:
Que dá para juntar validações repetidas num método que já imprime o erro e
devolve -1, e que encerrar a sessão do OpenCode não perde o código, só o
histórico da conversa.

## Missão 1: LISTAR_ASTRONAUTAS e HISTORICO

• Primeira mensagem (o pedido do plano):
Não enviei pedido de plano. Quando fui começar, a IA identificou que os dois
comandos já estavam implementados em src/main.cpp e que os testes da missão1
já passavam.

• O plano que a IA apresentou, resumido:
Não houve plano novo. A IA conferiu o código, rodou os testes e confirmou que
listarAstronautas() e historico() já existiam, usando os mesmos filtros de
listarMortos() e a função tem() do Voo.

• Mudei algo no plano antes de liberar?
Não.

• Resultado de testar.sh missao1 e de testar.sh parte1:
missao1: 2 de 2. parte1: 6 de 6.

• Precisei refazer? O que mudou no pedido:
Não.

• Primeira mensagem:
Este programa em C++11 controla astronautas e voos. As classes estão em
src/main.cpp e os testes da parte1 e missao1 passam.

Quero dois comandos novos: SALVAR nome_do_arquivo e CARREGAR nome_do_arquivo.
O SALVAR grava todos os dados em um arquivo de texto e imprime
OK: dados salvos em nome_do_arquivo. O CARREGAR substitui os dados atuais
pelos do arquivo e imprime OK: dados carregados de nome_do_arquivo. Se não
conseguir abrir o arquivo, imprime ERRO: nao foi possivel salvar/carregar
em/de nome_do_arquivo. No CARREGAR, se o arquivo não existir, os dados atuais
continuam como estavam.

O formato é escolha sua, desde que seja texto e que carregar depois de salvar
reconstrua tudo. Não mude nenhum comando que já existe. Não use nada fora da
biblioteca padrão.

Vou conferir com bash testes/testar.sh missao2 e bash testes/testar.sh parte1.

• Precisei refazer? O que mudou no pedido:
Sim, precisei ajustar o pedido algumas vezes.

Mudanças no pedido:
- Passei a dizer explicitamente quais arquivos podiam ser alterados (só
  src/main.cpp) e que nada em testes/ podia ser tocado.
- Passei a pedir o plano antes de qualquer edição, e só liberar depois de ler.
- Passei a listar as saídas exatas (OK e ERRO) em vez de descrever por cima.
- Passei a pedir que ela rodasse só os testes que eu pedi, sem adiantar as
  outras missões.

Precauções que adotei:
- Conferir o git status e o git diff depois de cada edição, para ver se ela
  não mexeu em arquivo fora do escopo.
- Rodar parte1 depois de cada missão, para garantir que nada quebrou.
- Fazer o commit só no final da missão, com tudo passando.

##Missão 3: RELATORIO

• Primeira mensagem:
Este programa em C++11 controla astronautas e voos. As classes estão em
src/main.cpp e os testes da parte1, missao1 e missao2 passam.

Quero um comando novo: RELATORIO. Ele imprime a linha RELATORIO seguida de
nove linhas: voos planejados, em curso, finalizados com sucesso, finalizados
com explosao, astronautas cadastrados, vivos, mortos, astronauta mais
experiente e taxa de sucesso.

Experiência = número de voos já lançados em que o astronauta estava a bordo.
Voo planejado não conta. Morto continua contando. Empate vale o cadastrado
primeiro. Se ninguém voou: (nenhum). Taxa de sucesso = parte inteira de
sucessos * 100 / finalizados. Sem finalizados: (nenhum voo finalizado).

A experiência precisa sobreviver ao CARREGAR: o teste 05 salva, carrega em
outra execução e pede o RELATORIO de novo, e a resposta tem que ser idêntica.

Não mude nenhum comando que já existe. Não use nada fora da biblioteca padrão.

Vou conferir com bash testes/testar.sh missao3 e bash testes/testar.sh parte1.

• Precisei refazer? O que mudou no pedido:
Sim. O primeiro pedido saiu vago demais e a IA tentou resolver por conta
própria, guardando um contador de experiência dentro do Astronauta. Isso
quebraria o teste 05, que salva, carrega em outra execução e pede o RELATORIO
de novo.

O que mudei:
- Deixei explícito que a experiência não podia ser contador guardado, e que
  tinha que ser reconstruída ao carregar.
- Fechei o escopo: só src/main.cpp, nada em testes/.
- Forcei a IA a explicar antes de editar como a experiência sobreviveria ao
  SALVAR/CARREGAR, em vez de sair codando.
- Listeias saídas exatas, inclusive "(nenhum)" e "(nenhum voo finalizado)",
  em vez de deixar por conta dela.

O que passei a fazer por precaução:
- Ler o git diff depois de cada edição, para pegar qualquer mudança fora do
  escopo.
- Rodar parte1, missao1 e missao2 depois da missao3, para garantir que nada
  quebrou por tabela.
- Commitar só no final, com todos os testes verdes.

## Missão 4: livre

• O que escolhi e por quê:
Escolhi o comando DESFAZER. É útil, não mexe em nenhum comando existente e
cabe no prazo.

• O comando novo, a saída que eu esperava e o nome do meu arquivo de comandos:
Comando: DESFAZER
Saída esperada para meus_testes/missao4.in:

OK: astronauta 111 cadastrado
OK: voo 10 cadastrado
OK: astronauta 111 adicionado ao voo 10
LISTA DE VOOS
== planejado ==
Voo 10: 111 Ana Maria
== em curso ==
(nenhum)
== finalizado com sucesso ==
(nenhum)
== finalizado com explosao ==
(nenhum)
OK: ultimo comando desfeito
LISTA DE VOOS
== planejado ==
Voo 10: sem astronautas
== em curso ==
(nenhum)
== finalizado com sucesso ==
(nenhum)
== finalizado com explosao ==
(nenhum)
ERRO: nada para desfazer

Arquivo: meus_testes/missao4.in

• Primeira mensagem:
Este programa em C++11 controla astronautas e voos. As classes estão em
src/main.cpp e os testes da parte1, missao1, missao2 e missao3 passam.

Quero um comando novo: DESFAZER. Ele volta o sistema ao estado anterior ao
último comando. Se der certo, imprime OK: ultimo comando desfeito. Se não
tiver o que desfazer, imprime ERRO: nada para desfazer.

Criei o arquivo meus_testes/missao4.in com um cenário de teste.

Não mude nenhum comando que já existe. Não use nada fora da biblioteca padrão.

Vou conferir com bash testes/testar.sh parte1.

• O que veio, comparado com o que eu esperava:
A primeira resposta veio solta. A IA propôs um plano genérico, não deixou claro
o que contava como "último comando" nem se comandos de leitura criariam
snapshot, e tentou editar antes de eu liberar. Também rodou testes das missões
1, 2 e 3 sem eu pedir, e os testes não rodavam no ambiente (bash fora do PATH,
depois g++ não encontrado).

Refiz o pedido especificando o comportamento, as saídas exatas e que só
src/main.cpp podia ser alterado. Depois disso, a saída do meus_testes/missao4.in
ficou como eu esperava: o primeiro DESFAZER desfez o ADICIONAR_ASTRONAUTA (voo
10 sem astronautas) e o segundo deu ERRO: nada para desfazer.

• testar.sh parte1 continuou passando?
No começo os testes nem rodavam (bash/g++ fora do PATH). Depois de acertar o
ambiente, parte1 passou 6 de 6. Rodei também missao1 (2/2), missao2 (3/3) e
missao3 (5/5).

• Aceitei, ajustei ou descartei? Por quê:
Aceitei depois de ajustar. A saída final bateu com o que eu esperava e nenhum
teste quebrou.

## Fechamento

• O que a IA fez que eu não conseguiria fazer sozinho nesse prazo:
Implementou SALVAR/CARREGAR, RELATORIO e DESFAZER com todos os testes
passando. Sozinho eu provavelmente ia travar em detalhes como reconstruir
a experiência ao carregar e guardar o snapshot antes de cada comando.
Também me ajudou a montar o AGENTS.md e a organizar os pedidos em duas
etapas (plano antes de editar).

• Onde ela errou ou fez algo que eu não pedi:
Foi muito proativa. Rodou missao1, missao2 e missao3 sem eu pedir, veio
com edição pronta antes de eu ler o plano, tentou usar wsl em vez do Git
Bash e em uma das sessões removeu por engano a verificação "astronauta nao
cadastrado" do removerAstronauta. Também modificou o AGENTS.md numa sessão.
Tive que ser bem específico sobre o que queria e o que não podia ser
alterado.

• O que eu faria diferente da próxima vez:
Deixaria o bash do Git no PATH antes de começar, para não perder tempo
procurando o compilador toda vez. Também escreveria os pedidos com mais
detalhe desde a primeira mensagem, em vez de ajustar no meio do caminho,
e conferiria o git diff imediatamente após cada edição para pegar mudanças
fora do escopo mais cedo.