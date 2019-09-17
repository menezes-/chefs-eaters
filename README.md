Grupo: Gabriel de Menezes Vieira e Luiz Henrique Alexandretti

## Compilação e execução

Para compilar: 

`mkdir build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release`


OBS: caso não tenha o cmake instalado é possível fazer o download do binário pré compilado diretamente daqui: https://github.com/Kitware/CMake/releases/download/v3.15.3/cmake-3.15.3-Linux-x86_64.sh
Sendo desnecessário a instalação do mesmo no sistema

para rodar: 

`./canibals numero_de_canibais qtde_comida_inicial [qtde_cozinheiros opcional]`

## Arquitetura

Utilizamos o algortimo de peterson que está incluído dentro da classe Mutex (`Mutex.hpp` e `Mutex.cpp`).

O cenário simulado é um onde existem N canibais, M quantidade de comida inicialmente na travessa e P quantidade de cozinheiros
sendo o valor mínimo de cozinheiros 1. Todos esses atores trabalham em cima de uma única instância da classe Travessa (`Travessa.hpp` e `Travessa.cpp`). 

Utilizamos dois métodos de sincronização: 
    
* O primeiro são os [mutexs](https://en.cppreference.com/w/cpp/thread/mutex) e as [variáveis condicionais](https://en.cppreference.com/w/cpp/thread/condition_variable)
  Juntos essas duas features, nativas do C++, proveem um poderoso método de sinalização entre as threads onde um canibal notifica os cozinheiros que não tem comida
  e os cozinheiros notificam os canibais quando terminam de cozinhar 

* O Segundo método utilizado é a nossa própria implementação do algorítmo de peterson, que serve para coordenar os canibais comendo direto da travessa.

Esses dois métodos combinados permitem que os canibais comam direto da travessa de maneira ordenada 
e impede que eles comam mais que o disponível (notificando os cozinheiros assim que a comida for insuficiente).


## Fluxo do programa

A travessa é inicialidade com a quantidade inicial de comida, os cozinheiros e os canibais são inicializados recebendo
uma referência dessa travessa. Com a ajuda da classe de utilidades Randomer (`Randomer.hpp` e `Randomer.cpp`) cada canibal 
decide o quanto quer comer e tentam comer da travessa, se a quantidade disponível de comida é inferior a desejada 
eles notificam todos os cozinheiros de quanto ele quer comer. Assim, então, os cozinheiros começam a cozinhar 
e conforme vão terminando eles vão notificando os canibais de que tem comida na travessa. Eles por sua vez 
vão comendo a quantidade desejada até que estejam satisfeitos.

## Dificuldades
Não encontramos nenhuma dificuldade para fazer este trabalho.




