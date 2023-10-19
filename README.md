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
1. Button A2 de Incremento de valores
1. Button A1 de Decremento de valores

        - El button de incremento es usado en el menu principal para empezar a disparar las fotos.
        - El button de incremento es usado en el menu de reset para confirmar el reseteo de los valores.
        - El button de decremento es usado en el menu principal para parar el disparo de fotos.

## Intervalometro funcionando

![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/IMG_20231015_211219.jpg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/IMG_20231015_211234.jpg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/IMG_20231015_211238.jpg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/IMG_20231015_211246.jpg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/IMG_20231015_211253.jpg)

## Montaje tipo Barn Door

![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/IMG_20231013_234032.jpg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/IMG_20231013_234036.jpg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/IMG_20231013_234040.jpg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/IMG_20231013_234045.jpg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/IMG_20231013_234050.jpg)

## Usando el motor de SupTig de Amazon

![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/WhatsApp%20Image%202023-10-19%20at%2014.44.10.jpeg)
![schematico](https://github.com/davidsnege/Intervalometer-DSLR-Arduino-nano-for-Astrophoto/blob/main/images/WhatsApp%20Image%202023-10-19%20at%2014.44.11.jpeg)
