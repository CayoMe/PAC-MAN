# paCman, um Pacman em C

O jogo, rodando estritamente no console, funciona a partir de um loop localizado no `int main()` do documento principal, que ocorre logo após alguns preparos do cenário e a renderização do cenário em si.

**Este loop consiste em 4 funções principais:**
- `makeMove()`: recebe uma entrada do usuário. Podem ser setas para movimentar o Pacman ou letras para algumas funções básicas como encerrar ou reiniciar.
- `moverFantasma()`: move o fantasma de acordo com a sua velocidade, armazenada no `struct` *"Fantasma"*. Será trocada pela função `moverFantasmas()` quando terminarmos a lógica do fantasma.
- `checkWin()`: verifica algumas condições para encerrar o jogo. Se o Pacman tiver comido todas as bolinhas, o jogador vence. Se o Pacman estiver na mesma coordenada que um fantasma, Game Over.
- `renderGrid()`: busca as informações do mapa após todas as movimentações e printa no console cada uma das células do mapa.
---
## Notas
- Os nomes de algumas funções são links pra facilitar a navegação. Clique nelas :^]
- Os macros `ROWS` e `COLS` são necessários porque o C exije que, sempre que uma matriz for passada para uma função, a quantidade de linhas e colunas têm de ser passadas também. Utilizar esses macros é útil pois assim não precisamos ficar mudando todas as dimensões toda vez que decidirmos alterar o tamanho dos [mapas](#mapas), é só mudar a constante lá no `#define`.

---
## As Entidades
### Pacman `C`
É o jogador. Todas as vezes que a função `makeMove()` é chamada, o jogador deverá pressionar uma das teclas permitidas: qualquer seta, (Q)uit, (R)einiciar.

### Fantasmas `F`
São monstrinhos que andam aleatoriamente pelo mapa e se, ao final do turno, as suas coordenadas forem iguais à do Pacman, o jogador perde e o jogo acaba.
Possuem variáveis de coordenadas (`xPos` e `yPos`), de velocidade (`xVel` e `yVel`), e de `skin`. A *skin* é o símbolo que aparece no mapa para representar o fantasma.
Em cada turno, as coordenadas do fantasma são incrementadas por suas respectivas velocidades atrávés das lógicas `yPos = yPos + yVel` para a coordenada das linhas, e `xPos = xPos + xVel` para a coordenada das colunas.
> *Exemplo:* um fantasma posicionado na célula **(3, 7)** e com os os valores de velocidade `xVel = -1` e `yVel = 0` se movimentará para a célula **(2, 7)** no turno seguinte. *Veja [coordenadas](#coordenadas).*

Note que um dos valores de velocidade tem de ser 0, se não o fantasma se moverá em diagonais.
Sempre que um fantasma fica de frente com uma parede, os valores de sua velocidade mudam para que no próximo turno ele se mova em outra direção. Há mais detalhes na descrição da função [`moverFantasma()`](#moverfantasma).
**TODO:** podemos fazer com que os fantasmas sigam o Pacman sempre que eles tiverem "visão" dele. Será necessário uma função `olhar()` dentro da [`moverFantasma()`](#moverfantasma) que seja chamada antes de tudo. Caso ele esteja na visão, a uma versão especial da função [`mudarDirecao()`](#mudardirecao) é chamada.

---

## Os Mapas
Para evitar que as lógica do jogador e a dos fantasmas entrem em conflito, o jogador e os fantasmas vivem em mapas diferentes, o [mapa principal](#mapa-principal) e o [fantasmapa](#fantasmapa).
Estes mapas são reflexos um do outro. Toda parede no mapa principal também é uma parede no fantasmapa. mas as [entidades](#as-entidades) de um não habitam o outro, mas o código permite que elas se "comuniquem".

### Mapa principal
Referido apenas como *"mapa"*, é o mapa em que o Pacman vive. Nele estarão presentes o [Pacman](#pacman), 

### Fantasmapa

---
## Coordenadas
Devido a como o C e outras linguagens de programação representam os índices de matrizes, há um pouco de espaço para confusão na maneira em que nos referimos à coordenadas.
No plano coordenadas cartesianas (x, y), "andar pra direita" é incrementar o valor de x, enquanto "andar para cima" é incrementar o valor de y.
Em matrizes, não funciona bem assim. A linguagem C indexa as células da esquerda pra direita, de cima pra baixo, como a nossa leitura, portanto, **o menor valor de x (colunas) fica na esquerda, enquanto o menor valor de y (linha) fica no topo.**
Em cima de tudo isso, para acessar uma célula em uma matriz `char m[4][4]`, devemos chamá-la da seguinte forma: `m[#linha][#coluna]`, ou seja **o valor de y vem primeiro!**
A tabela abaixo mostra a notação tanto em forma cartesiana quanto em indexação do C.

| .         | x = 0             | x = 1             | x = 2             | x = 3             |
|----------:|:-----------------:|:-----------------:|:-----------------:|:-----------------:|
| **y = 0** | (0, 0)<br>m[0][0] | (1, 0)<br>m[0][1] | (2, 0)<br>m[0][2] | (3, 0)<br>m[0][3] |
| **y = 1** | (0, 1)<br>m[1][0] | (1, 1)<br>m[1][1] | (2, 1)<br>m[1][2] | (3, 1)<br>m[1][3] |
| **y = 2** | (0, 2)<br>m[2][0] | (1, 2)<br>m[2][1] | (2, 2)<br>m[2][2] | (3, 2)<br>m[2][3] |
| **y = 3** | (0, 3)<br>m[3][0] | (1, 3)<br>m[3][1] | (2, 3)<br>m[3][2] | (3, 3)<br>m[3][3] |

Por conta disso, sempre que, no código, é necessário referenciar alguma célula no mapa, você verá algo do tipo: `fm[ fan->yPos + fan->yVel ][ fan->xPos + fan->xVel ]`. **O valor de y SEMPRE virá antes do valor de x**. É confuso assim mesmo e tá tudo bem 😶🤙

---

## Funções
### `moverFantasma()`
`void moverFantasma(Fantasma *fan, char fm[ROWS][COLS]);`
Recebe um ponteiro para o fantasma e a matriz do [Fantasmapa](#fantasmapa) DONKEY

---

### Debugs
Em alguns locais do código estão presentes o comentário `// DEBUG` seguido de um número. **Ex:** `// DEBUG 2`.
Estas linhas servem como algumas ferramentas visuais que podem ser utilizadas para debugar o jogo. Comentá-las faz com que elas não apareçam mais no console, permitindo ver como o jogo seria ao finalizá-lo.
> Dica: Use `crtl + F` para buscar o debug específico que quer habilitar/desabilitar, selecione o texto, `ctrl + shift + L` para criar um cursor em cada debug, `ctrl + ;` para comentar todas as linhas.