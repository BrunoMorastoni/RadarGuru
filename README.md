# RadarGuru
## _Melhor detector de radar, feito até hoje_ (data indefinida)
![GURU](https://i.imgur.com/5sOp6yF.png)

## Descrição
O RadarGuru é um projeto que utiliza os módulos ESP8266, NEO-6M GPS, display OLED, LEDs, botões e um buzzer para auxiliar os usuários na detecção e notificação da proximidade de radares de trânsito. O produto final será modelado e impresso em 3D, proporcionando um dispositivo compacto e funcional.

## Funcionalidades

- **Detecção de Radares**: O RadarGuru utiliza o módulo NEO-6M GPS para detectar a posição atual do usuário e compará-la com uma base de dados de radares, fornecendo notificações quando se aproximar de um radar conhecido.

- **Interface de Usuário**: O display OLED e os LEDs fornecem uma interface intuitiva para o usuário, mostrando informações como velocidade atual, proximidade de radares e status do dispositivo.

- **Interatividade**: Os botões permitem ao usuário interagir com o dispositivo, configurando preferências, silenciando notificações ou alternando entre os modos de exibição.

## Tecnologias Utilizadas
-  **Microcontrolador**: ESP8266
-  **Módulo GPS**: NEO6MV2
-  **Display**: OLED (128x64)
-  **Indicadores Visuais**: LEDs
-  **Interatividade**: Botões
-  **Feedback Sonoro**: Buzzer
-  **Modelagem e Impressão 3D**: Para o desenvolvimento do produto final.

## Atenção
O Radar Guru segue completamente as diretrizes da [Resolução 242](https://www.gov.br/transportes/pt-br/assuntos/transito/conteudo-contran/resolucoes/resolucao_contran_242.pdf) do Contran. 
Sua principal função é avisar o condutor sobre pontos de controle ou de velocidade previamente definidos e informados na via. 
Ele não funciona como um dispositivo antiradar, já que não consegue detectar sinais de radar nem interferir na medição da velocidade real do veículo. 
É fundamental ter em mente que, caso o usuário do Radar Guru exceda o limite de velocidade em uma fiscalização eletrônica, receberá uma multa como de costume.
