# Tarefa 2 06/02 - Controle de Servomotor por PWM

Este projeto implementa o controle de um servomotor utilizando o módulo PWM do microcontrolador RP2040. A simulação ocorre no ambiente online Wokwi entretanto pose ser alterada para ser usada em LEDs também, alterando sua intensidade.

## Componentes Utilizados

Microcontrolador: Raspberry Pi Pico W

Servomotor: Motor micro servo padrão (Wokwi)

## Funcionalidades Implementadas

Configuração do PWM

GPIO 22 configurada com frequência de 50Hz (período de 20ms).

Controle de Posição do Servomotor

180 graus: Ciclo ativo de 2400µs (Duty Cycle de 0,12%) → Aguarda 5s.

90 graus: Ciclo ativo de 1470µs (Duty Cycle de 0,0735%) → Aguarda 5s.

0 graus: Ciclo ativo de 500µs (Duty Cycle de 0,025%) → Aguarda 5s.

Rotina de movimentação suave

Rotina para movimentação entre 0 e 180 graus, com incrementos de ±5µs a cada 10ms.

Experimento com LED RGB

E para testes, utilização da GPIO 12 para avaliar o comportamento da iluminação do LED RGB com BitDogLab.

## Como Executar o Projeto

Clone o repositório do projeto para o seu ambiente local e abri-lo no VS Code.

Antes de compilar o código, é necessário garantir que todas as extensões e ferramentas estão devidamente instaladas.

Instalar o Pico SDK e extensão Raspberry Pi Pico: Siga as instruções do Pico SDK para configurar o ambiente de desenvolvimento no VS Code e instale a extensão Raspberry Pi Pico.

Instalar a Extensão Wokwi: Permite simular o Raspberry Pi Pico W no ambiente de desenvolvimento. Instale a extensão Wokwi Simulator no catálogo extensões do VS Code e depois habilite a mesma com uma licença de 30 dias gratuita.

Com o ambiente devidamente configurado, abra o código no VS Code e compile o projeto a partir do menu de compilação da extensão Raspberry Pi Pico.

Após a compilação, abra o arquivo diagram.json dentro do proprio VS Code localizado na pasta principal do projeto. Ao abrir o arquivo diagram.json, o Wokwi Simulator será automaticamente ativado e sera exibido a simulação já configurada para o projeto.

Aperte o botão play no canto superior esquerdo e agora você pode interagir com o sistema diretamente no simulador e testar as funções.

## Link para video demonstração:

[DRIVE](https://drive.google.com/drive/u/4/folders/1TW-0zyrKWxDmwOV1_yGmCA-ZwnncRgmx)

# Projeto por : Alex Rodrigo Porto Barbosa

