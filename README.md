📌 Projeto: Jogo da Velha em C

Um Jogo da Velha (Tic-Tac-Toe) desenvolvido em linguagem C com interface de texto no terminal, sistema de ranking persistente e opção de jogar contra outro jogador ou contra o computador.

Este projeto demonstra uso de:
✔ Manipulação de arquivos
✔ Estruturas (struct)
✔ Ordenação de dados (ranking)
✔ Modularização em funções
✔ Compatibilidade Windows/Linux

🧠 Sobre o Jogo

Este é um jogo clássico de Jogo da Velha que:

Permite dois jogadores humano ou jogar contra o computador.

Mostra o tabuleiro no terminal.

Verifica automaticamente vitória, empate e jogadas inválidas.

Salva um ranking de vitórias em arquivo local (data/ranking.txt).

📁 Estrutura do Projeto
projeto-jogo-da-velha/
├── data/
│   └── ranking.txt   ← arquivo que guarda nomes das vitórias
├── main.c            ← código-fonte em C
├── Makefile.txt      ← arquivo para compilar (se desejar)
├── LICENSE           ← licença MIT
└── README.md         ← este arquivo

⚙️ Como Compilar e Executar
🛠 Requisitos

Compilador C (como gcc ou equivalente)

Linha de comando ou terminal

🧾 Compilar usando C99

Este projeto usa recursos de padrão moderno C, então compile assim:

gcc main.c -o jogo -std=c99


ou

gcc main.c -o jogo -std=gnu99


💡 No Dev-C++ (em português), vá em Ferramentas → Opções do Compilador → Configurações → Padrão da linguagem e selecione ISO C99 ou adicione -std=c99.

▶️ Jogar o Jogo

Depois de compilar, execute:

./jogo


No menu você pode:

👉 Jogar

Escolher contra computador ou outro jogador.

Inserir nomes dos jogadores.

Jogar até vitória ou empate.

👉 Ver Ranking

Mostra as principais vitórias por jogador.

Ordenado por número de vitórias.

👉 Créditos

Lista dos participantes do projeto.

👉 Sair

🏆 Funcionalidades Principais

✔ Interface de texto clara e interativa
✔ Validação de entradas erradas
✔ Impede jogadas em posições já ocupadas
✔ Salva ranking e contabiliza vitórias por nome
✔ Permite jogar contra o computador com jogadas randômicas

✨ Melhorias Futuras (opcionais)

Algumas ideias para evoluir este projeto:

💡 IA mais inteligente (Minimax)

💡 Suporte a mais modos de jogo

💡 Replay automático

💡 Interface gráfica

📜 Licença

Este projeto está licenciado sob a MIT License.
(Use, modifique e compartilhe livremente.)

📌 Créditos

José Gustavo Martinho Araujo de Almeida
