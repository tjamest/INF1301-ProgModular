# INF1301 - Programação Modular

## T1: Elaboração da documentação do projeto

- Requisitos Funcionais e Não-Funcionais
- Visão de Módulos e Visão de Interface
- Estrutura Lista de Listas
- Estrutura de Tipos


## T2: Criação dos módulos Baralho e TesteBaralho

- Baralho:
    ````
    BARALHO.c - Implementação do módulo BARALHO
    BARALHO.h - Definição do módulo BARALHO
    LISTA.c - Implementação do módulo LISTA
    LISTA.h - Definição do módulo LISTA
    ````
- TesteBaralho:
    ````
    TestBAR.c - Implementação do teste do módulo BARALHO
    TesteBaralho.script - Massa de testes para testes do módulo BARALHO
    GENERICO.h - Módulo de suporte para testes (não deve ser alterado)
    LERPARM.h - Módulo de suporte para testes (não deve ser alterado)
    TST_ESPC.h - Módulo de suporte para testes (não deve ser alterado)
    ArcaboucoTeste.lib - Biblioteca do Arcabouço
    LimpaTudo.bat - Deleta os arquivos gerados por testes anteriores
    TestaBaralho.bat - Realiza o teste automatizado
    vsvars32.bat - Seta o ambiente para uso do Visual Studio (não clicar nem chamar)
    exbestat.exe - Programa que exibe as estatísticas do teste (não clicar nem chamar)
    ````

## T3: Criação dos módulos Mesa e TesteMesa

- Mesa:
    ````
    MESA.c - Implementação do módulo MESA
    MESA.h - Definição do módulo MESA
    BARALHO.c - Implementação do módulo BARALHO
    BARALHO.h - Definição do módulo BARALHO
    LISTA.c - Implementação do módulo LISTA
    LISTA.h - Definição do módulo LISTA
    ````
- TesteMesa:
    ````
    TestMES.c - Implementação do teste do módulo MESA
    TesteMesa.script - Massa de testes para testes do módulo MESA
    GENERICO.h - Módulo de suporte para testes (não deve ser alterado)
    LERPARM.h - Módulo de suporte para testes (não deve ser alterado)
    TST_ESPC.h - Módulo de suporte para testes (não deve ser alterado)
    ````
    
## T4: Criação dos módulos Interface e TesteInterface

- Interface:
    ```
    INTERFACE.c - Implementação do módulo MESA
    INTERFACE.h - Definição do módulo MESA
    MESA.c - Implementação do módulo MESA
    MESA.h - Definição do módulo MESA
    BARALHO.c - Implementação do módulo BARALHO
    BARALHO.h - Definição do módulo BARALHO
    LISTA.c - Implementação do módulo LISTA
    LISTA.h - Definição do módulo LISTA
    ```   
- TesteInterface:
    ```
    TestINT.c - Implementação do teste do módulo MESA
    TesteInterface.script - Massa de testes para testes do módulo MESA
    GENERICO.h - Módulo de suporte para testes (não deve ser alterado)
    LERPARM.h - Módulo de suporte para testes (não deve ser alterado)
    TST_ESPC.h - Módulo de suporte para testes (não deve ser alterado)
    ```
