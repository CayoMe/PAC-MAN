# paCman

O jogo, rodando estritamente no console, funciona a partir de um loop localizado no `int main()` do documento principal, que ocorre logo após alguns preparos do cenário e a renderização do cenário em si.

**Este loop consiste em 4 funções principais:**
- `makeMove()`: recebe uma entrada do usuário. Podem ser setas para movimentar o Pacman ou letras para algumas funções básicas como encerrar ou reiniciar.
- `moverFantasma()`: move o fantasma de acordo com a sua velocidade, armazenada no `struct` *"Fantasma"*. Será trocada pela função `moverFantasmas()` quando terminarmos a lógica do fantasma.
- `checkWin()`: verifica algumas condições para encerrar o jogo. Se o Pacman tiver comido todas as bolinhas, o jogador vence. Se o Pacman estiver na mesma coordenada que um fantasma, Game Over.
- `renderGrid()`: busca as informações do mapa após todas as movimentações e printa no console cada uma das células do mapa.
---
### Debugs
Em alguns locais do código estão presentes o comentário `// DEBUG` seguido de um número. **Ex:** `// DEBUG 2`.
Estas linhas servem como algumas ferramentas visuais que podem ser utilizadas para debugar o jogo. Comentá-las faz com que elas não apareçam mais no console, permitindo ver como o jogo seria ao finalizá-lo.
> Dica: Use `crtl + F` para buscar o debug específico que quer habilitar/desabilitar, selecione o texto, `ctrl + shift + L` para criar um cursor em cada debug, `ctrl + ;` para comentar todas as linhas.