# paCman, um Pacman em C

O jogo, rodando *estritamente* no console, funciona a partir de um loop localizado no `int main()` do documento `pacman.c`, que ocorre logo após a exibição da tela inicial e alguns preparos 

**Este loop consiste em 3 funções principais:**
- [`moverJogador()`](#moverJogador) para pegar uma entrada do jogador, seja um movimento ou um comando, e processá-la;
- [`moverFantasma()`](#moverfantasma): para mover os fantasmas de acordo com as suas personalidades; e
- [`renderGrid()`](#rendergrid): busca as informações do mapa após todas as movimentações e printa no console cada uma das células do mapa.
> *Dica:* - Os nomes de algumas funções são links pra facilitar a navegação. **Clique nelas** :^]


---
## As Entidades
### Pacman `C`
É o jogador. Todas as vezes que a função `makeMove()` é chamada, o jogador deverá pressionar uma das teclas permitidas: qualquer seta, (Q)uit, (R)einiciar.

### Fantasmas `F P I O`
São monstrinhos que andam aleatoriamente pelo mapa e se, ao final do turno, as suas coordenadas forem iguais à do Pacman, o jogador perde e o jogo acaba.
Possuem variáveis de coordenadas (`xPos` e `yPos`), de velocidade (`xVel` e `yVel`), e de `skin`. A *skin* é o símbolo que aparece no mapa para representar o fantasma.
Em cada turno, as coordenadas do fantasma são incrementadas por suas respectivas velocidades atrávés das lógicas `yPos = yPos + yVel` para a coordenada das linhas, e `xPos = xPos + xVel` para a coordenada das colunas.
> *Exemplo:* um fantasma posicionado na célula **(3, 7)** e com os os valores de velocidade `xVel = -1` e `yVel = 0` se movimentará para a célula **(2, 7)** no turno seguinte. *Veja [coordenadas](#coordenadas).*

O código garente que um dos valores de velocidade será sempre 0, caso contrário, o fantasma se moveria em diagonais.
Sempre que um fantasma fica de frente com uma parede, os valores de sua velocidade mudam para que no próximo turno ele se mova em outra direção. Há mais detalhes na descrição da função [`moverFantasma()`](#moverfantasma).

---

## Os Mapas
Para evitar que as lógica do jogador e a dos fantasmas entrem em conflito, o jogador e os fantasmas vivem em mapas diferentes, o [mapa principal](#mapa-principal) e o [fantasmapa](#fantasmapa).
Estes mapas são reflexos um do outro. Toda parede no mapa principal também é uma parede no fantasmapa. Apesar das [entidades](#as-entidades) habitarem mapas diferentes, o código permite que elas se "comuniquem".

### Mapa principal
Referido apenas como *"mapa"*, é o mapa em que o Pacman habita. Nele estarão presentes o [Pacman](#pacman), os pontos (que são, adequadamente, `.` *pontos*), e os pontões `o` que valem mais pontos.

### Fantasmapa
É o mapa em que os fantasmas habitam. Aqui é só parede e fantasma mesmo.

---
## Coordenadas
Devido a como o C e outras linguagens de programação representam os índices de matrizes, há um pouco de espaço para confusão na maneira em que nos referimos às coordenadas.
No plano de coordenadas cartesianas (x, y), "andar pra direita" é incrementar o valor de x, enquanto "andar para cima" é incrementar o valor de y.
Em matrizes, não funciona bem assim. A linguagem C indexa as células da esquerda pra direita, de cima pra baixo, assim como a nossa leitura, portanto, **o menor valor de x (colunas) fica na esquerda, enquanto o menor valor de y (linha) fica no topo.**
Em cima de tudo isso, para acessar uma célula em uma matriz `char m[4][4]`, devemos chamá-la da seguinte forma: `m[#linha][#coluna]`, ou seja **o valor de y vem primeiro.**
A tabela abaixo mostra a notação tanto em forma cartesiana quanto em indexação do C.

| .         | x = 0               | x = 1               | x = 2               | x = 3               |
|----------:|:-------------------:|:-------------------:|:-------------------:|:-------------------:|
| **y = 0** | (0, 0)<br>`m[0][0]` | (1, 0)<br>`m[0][1]` | (2, 0)<br>`m[0][2]` | (3, 0)<br>`m[0][3]` |
| **y = 1** | (0, 1)<br>`m[1][0]` | (1, 1)<br>`m[1][1]` | (2, 1)<br>`m[1][2]` | (3, 1)<br>`m[1][3]` |
| **y = 2** | (0, 2)<br>`m[2][0]` | (1, 2)<br>`m[2][1]` | (2, 2)<br>`m[2][2]` | (3, 2)<br>`m[2][3]` |
| **y = 3** | (0, 3)<br>`m[3][0]` | (1, 3)<br>`m[3][1]` | (2, 3)<br>`m[3][2]` | (3, 3)<br>`m[3][3]` |

Por conta disso, sempre que, no código, é necessário referenciar alguma célula no mapa, você verá algo do tipo: `fm[ fan->yPos + fan->yVel ][ fan->xPos + fan->xVel ]`. **O valor de y SEMPRE virá antes do valor de x**. É confuso assim mesmo e tá tudo bem 😶🤙

---

## Funções

### `saveGame()`
`void saveGame(Player p, Fantasma f[])`
Utiliza a função `fprintf()` para salvar o estado atual do jogo no arquivo `savefile.txt`. Salva apenas as coordenadas do Pacman e dos fantasmas.

### `carregarMapa()`
`void carregarMapa(char mapa[ROWS][COLS])`
Carrega o cenário salvo em `savefile.txt`. Este carregamento é efetuado utilizando a função `fgets()` que lê linha por linha do arquivo. Caso a linha contenha um p como primeiro caractere, esta linha contém informações do Pacman, caso contrário, esta linha contém informações de um fantasma.

### `reiniciarJogo()`
`void reiniciarJogo(Player *p, Fantasma f[], char mapa[ROWS][COLS])`
Coloca o Pacman e os fantasmas em suas posições originais, efetivamente reiniciando o jogo.

### getInput()
`char getInput()`
Utiliza a função `getch()` da biblioteca `conio.h` para receber uma entrada do usuário sem a necessidade de apertar enter no console para enviar o comando. A função getch() é meio complexa, mas ela basicamente guarda um `char` em uma variável `int`. Foi utilizado para processar o que o usuário gostaria de fazer no próximo turno, podendo este optar por se mover em uma das 4 direções (`u`, `d`, `l`, `r`) utilizando as setinhas, fechar o programa apertando **Q**, ou salvar o jogo apertando **S**.

### telaInicial()
`void telaInicial()`
Renderiza uma arte em ASCII colorida do Pacman clássico e espera o usuário apertar enter para dar início ao jogo.

### `gerarFantasmapa()`
`void gerarFantasmapa(char s[ROWS][COLS], char d[ROWS][COLS])`
Loopa por todo o mapa → para cada célula, se a célula for uma parede `'█'`, escreve uma parede `'#'` no fantasmapa, se não, escreve um espaço `' '`.

### `renderGrid()`
`void renderGrid(char m[ROWS][COLS], char fm[ROWS][COLS], Player *player, Fantasma fantasmas[], int num_fantasmas, int *pontos)`
Posiciona o jogador e os fantasmas nas células com suas coordenadas → loopa por todas as coordenadas do mapa → verifica se a célula está vazia no fantasmapa, se estiver, printa a célula do mapa, se não estiver vazia, printa o fantasma.

### `moverJogador()`
`char moverJogador(Player *pacman, Fantasma fantasmas[], int rows, int cols, char mapa[ROWS][COLS], char fm[ROWS][COLS], int *pontos)`
Recebe a entrada do jogador com [getInput()](#getinput). Caso a entrada do jogador seja uma setinha, incrementa a posição do Pacman a depender da direção escolhida. Caso a entrada seja um comando, chama as funções [`reiniciarJogo()`](#reiniciarjogo) ou [`saveGame()`](#saveGame).

### `moverFantasma()`
`void moverFantasma(Fantasma *fan, char fm[ROWS][COLS], Player p)`
Apaga a célula que o fantasma estava → escolhe o alvo do fantasma de acordo com a sua personalidade → escreve a `skin` do fantasma na posição que o fantasma se moverá → altera os valores das coordenadas do fantasma para os da nova célula → "olha" qual será a próxima célula, se estiver vazia nada acontece, se for uma parede, chama [`mudarDirecao()`](#mudardirecao) para alterar as velocidades do fantasma.

### `mudarDirecao()`
`mudarDirecao(Fantasma *fan, char fm[ROWS][COLS], int alvoY, int alvoX)`
Escolhe qual direção é a melhor para o colocar mais próximo de seu alvo. Se o caminho é inválido, o fantasma dá uma meia volta.

---

### Debugs
Em alguns locais do código estão presentes o comentário `// DEBUG` seguido de um número. **Ex:** `// DEBUG 2`.
Estas linhas servem como algumas ferramentas visuais que podem ser utilizadas para debugar o jogo. Comentá-las faz com que elas não apareçam mais no console, permitindo ver como o jogo seria ao finalizá-lo.
> Dica: Use `crtl + F` para buscar o debug específico que quer habilitar/desabilitar, selecione o texto, `ctrl + shift + L` para criar um cursor em cada debug, `ctrl + ;` para comentar todas as linhas.

---

## Referências:
- [MDN Web Docs](https://developer.mozilla.org/en-US/docs/Web/HTML)
- [Cheatsheet do C](https://manual.cs50.io/)
- [Playsound](https://learn.microsoft.com/pt-pt/previous-versions//dd743680(v=vs.85))
- [`conio.h`](https://code-reference.com/c/conio.h)
- [Fantasmas e suas personalidades](https://www.quora.com/What-are-the-different-gameplay-of-the-ghosts-in-the-classic-80s-video-game-Pac-Man)


> *paCman foi um jogo feito com muito amor (e uso quase nulo de IA, sendo usada como referência aos compiladores de C / CMD) por 5 estudantes do curso de Ciência da Computação.*