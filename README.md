# Simulação de Incêndio na Floresta

Este projeto simula o monitoramento de incêndios em uma floresta utilizando múltiplos sensores. O código implementa um sistema onde sensores detectam incêndios e notifica a central de controle, além de espalhar a informação para sensores vizinhos. A floresta é representada por uma matriz e os estados das células são monitorados em tempo real.

## Estrutura do Projeto

O projeto é dividido em três arquivos principais:

1. `main.c`: Contém a lógica principal da aplicação, incluindo a inicialização da floresta e a criação das threads dos sensores e do gerador de incêndios.
2. `funcoes.c`: Implementa as funções que controlam o comportamento dos sensores, a inicialização da floresta e a propagação do incêndio.
3. `funcoes.h`: Declaração das funções e definições de constantes utilizadas em todo o projeto.

## Estados do Mapa

O mapa da floresta possui os seguintes estados representados por caracteres:

- `-`: Área livre.
- `T`: Célula monitorada por um nó sensor ativo.
- `@`: Célula em chamas (fogo ativo).
- `/`: Célula queimada.

## Como Funciona

1. **Inicialização**:
   - A floresta é inicializada com sensores e áreas livres aleatoriamente.
   - Cada célula da matriz da floresta é protegida por um mutex para garantir acesso seguro em um ambiente multi-thread.

2. **Sensores**:
   - Cada sensor opera em uma thread separada.
   - Eles monitoram constantemente sua célula para detectar se há fogo.
   - Se um sensor detecta fogo, ele notifica a central de controle se estiver na borda da floresta ou alerta os sensores vizinhos caso contrário.

3. **Gerador de Incêndios**:
   - Uma thread separada é responsável por iniciar incêndios aleatoriamente na floresta.
   - Se um incêndio é iniciado em uma célula monitorada, ele altera seu estado para fogo.

4. **Comunicação**:
   - Os sensores usam mutexes para garantir que as alterações ao estado da floresta sejam feitas de maneira segura.
   - A notificação de incêndios entre sensores vizinhos e a central de controle é feita por chamadas de função que modificam o estado da matriz da floresta.

## Compilação e Execução

### Requisitos

- Um compilador C (ex: `gcc`)
- `pthread` para suportar multi-threading

### Passos

1. Clone o repositório:
   ```bash
   git clone <URL_DO_REPOSITORIO>
   cd <NOME_DA_PASTA>
