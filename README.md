# campo-minado
Implementação básica do clássico Campo Minado, desenvolvida para o processo seletivo da Manifesto Games.

## Ações
**Botão esquerdo do mouse:** Revelar o conteúdo de uma casa.
**Botão direito do mouse:** Marcar a casa com uma bandeira.
**Botão do meio do mouse:** Usar um especialista para revelar uma casa sem risco de perder o jogo.

## Observações
- Como sugerido, foi implementado um "super-poder". No caso, o jogoador pode chamar especialistas, os quais poderão revelar qualquer casa, incluindo as que contém bombas, sem que isso ocasione o fim do jogo.

- O código-fonte está devidamente comentado, seguindo o formato Doxygen de documentação.

## Bugs conhecidos
- Em algumas situações aleatórias, o conteúdo do tabuleiro aparece vazio, com apenas as bombas ativas. Por se tratar de um erro intermitente, ainda não foi encontrada a razão.
