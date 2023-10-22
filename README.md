## ARDUINTER 

# Arduino Intervalometro para uso en Astrofotografia

![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/Schema.png)

## OBJETIVOS:

  El principal objetivo de este software es que aficcionados en astronomia y astrofotografia con pocos recursos (como yo)
  tengan un medio de crear su proprio "intervalometro" con caracteristicas utiles mas a la astrofotografia que otros fines
  pero aun así se podria usar para hacer timelapses de tiempo o otras cosas, el desarollo de este se da por hace poco haber
  creado (modo manitas) una "barn door" para mis astrofotos, y he automatizado la misma con un motor de Amazon que dejo el
  enlace aqui (https://amzn.eu/d/7RQ12mw) se llama (Suptig - Soporte de trípode para cámara de fotos) por si te encantas
  a hacer uno. La idea futura es cambiar el motor de Amazon por un motor de paso (Nema 17) y automatizar las velocidades
  de este motor con arduino, transformando eso en una unica plataforma accequible para astrofotografia amadora con uso de
  DSLRs.

### ! ATENCIÓN !

  No soy responsable por daños a su equipo de fotografia, antes de hacer uso mejor que tu verifique los parámetros para
  ser usados en el cable disparador de su cámara, adaptadores etc...
  
  He testeado en mis equipos, y el riesgo para testear en sus equipos es su responsabilidad, no enviar voltages maiores que 
  5v a ningun cable disparador, y antes verificar si tu cámara funciona com un positivo para disparar o si funciona en modo
  corto de cables para disparar.

  Si teneis dudas mejor adaptar un relay de disparo para funcionar en modo de corto de cables, ya que la maior parte de camaras
  funciona como si fuera un push button en la punta del disparador.

  Si necesário añadir una resistência en la salida del cable para disminuir el voltage del mismo.

  * Es tu responsabilidad saber como el disparador de su cámara funciona.

## USOS:

  Se puede usar para automatizar:

  - Astrofotografias
  - Timelapses

  * Solo testeado en cámaras EVIL DSLR CANON hasta el momento.
  * Si encontrais otros usos hacer un commit de estes usos en mi github.

## CREDITOS:

  Hola, soy David Belleti, un aficcionado de la astronomia en todas sus areas de actuación, y este programa surge de la 
  necesidad de conseguir automatizar las sessiones de astrofotografia utilizando un montaje casero amador del tipo
  "barn door". Lo unico pedido es que no se quite esta descripción y tampoco los creditos del codigo y mencione el 
  autor y si eres un aficcionado de la astronomia comparte este codigo con los demás.

## REPOSITORIO:

  https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto

## LICENCIA:

  El uso es libre con excepción de usos comerciales, esto debe ser compartido de manera gratuita y nadie debe llevar
  lucro o ganancias con uso de este código.

## COMPONENTES USADOS:

  - Arduino Nano (generico de Amazon)
  - 2 Leds (Rojo, Amarillo)
  - 2 Resistencias de 10k
  - 3 Push Buttons
  - LCD 16x2 (Interfaz I2C 'El que tiene solo 4 conectores')

## TESTEADO EN:
    
      - Canon EOS 100D
      - Canon EOS 250D
      - Canon EOS 500D
      - Canon EOS 550D
      - Canon EOS 600D

    * Creo que funcione en todas las DSLR de Canon, pero no testeado en todas.

## FUNCIONAMIENTO:

1. Button A0 de navegación ciclica para el menu
2. Button A2 de Incremento de valores
3. Button A1 de Decremento de valores
4. Button A3 de Decremento de menu

        - El button de incremento es usado en el menu principal para empezar a disparar las fotos.
        - El button de incremento es usado en el menu de reset para confirmar el reseteo de los valores.
        - El button de decremento es usado en el menu principal para parar el disparo de fotos.
        
## Intervalometro funcionando

![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/int_01.jpg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/int_02.jpg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/int_03.jpg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/int_04.jpg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/int_05.jpg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/int_06.jpg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/int_07.jpg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/int_08.jpg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/int_09.jpg)

## Montaje tipo Barn Door

![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/barn_06.jpg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/barn_07.jpg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/barn_08.jpg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/barn_09.jpg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/barn_01.jpg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/barn_02.jpg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/barn_03.jpg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/barn_04.jpg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/barn_05.jpg)


