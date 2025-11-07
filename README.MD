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

## Funções
### `moverFantasma()`
`void moverFantasma(Fantasma *fan, char fm[ROWS][COLS]);`
Recebe um ponteiro para o fantasma e a matriz do [Fantasmapa](#fantasmapa) DONKEY

---

### Debugs
Em alguns locais do código estão presentes o comentário `// DEBUG` seguido de um número. **Ex:** `// DEBUG 2`.
Estas linhas servem como algumas ferramentas visuais que podem ser utilizadas para debugar o jogo. Comentá-las faz com que elas não apareçam mais no console, permitindo ver como o jogo seria ao finalizá-lo.
> Dica: Use `crtl + F` para buscar o debug específico que quer habilitar/desabilitar, selecione o texto, `ctrl + shift + L` para criar um cursor em cada debug, `ctrl + ;` para comentar todas as linhas.