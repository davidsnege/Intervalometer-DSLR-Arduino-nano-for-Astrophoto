///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ARDUINO INTERVALOMETRO - USADO PARA TOMAR ASTROFOTOGRAFIAS AUTOMATICAMENTE USANDO UNA MONTAGEM TIPO - BARN DOOR ////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++ D E S C R I P C I O N  Y  R E S U M E N  D E L  P R O G R A M A +++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*
OBJETIVOS:

  El principal objetivo de este software es que aficcionados en astronomia y astrofotografia con pocos recursos (como yo)
  tengan un medio de crear su proprio "intervalometro" con caracteristicas utiles mas a la astrofotografia que otros fines
  pero aun así se podria usar para hacer timelapses de tiempo o otras cosas, el desarollo de este se da por hace poco haber
  creado (modo manitas) una "barn door" para mis astrofotos, y he automatizado la misma con un motor de Amazon que dejo el
  enlace aqui (https://amzn.eu/d/7RQ12mw) se llama (Suptig - Soporte de trípode para cámara de fotos) por si te encantas
  a hacer uno. La idea futura es cambiar el motor de Amazon por un motor de paso (Nema 17) y automatizar las velocidades
  de este motor con arduino, transformando eso en una unica plataforma accequible para astrofotografia amadora con uso de
  DSLRs.

USOS:

  Se puede usar para automatizar:

  - Astrofotografias
  - Timelipses

  * Solo testeado en cámaras EVIL DSLR CANON hasta el momento.
  * Si encontrais otros usos hacer un commit de estes usos en mi github.

CREDITOS:

  El desarollador es un aficcionado de la astronomia en todas sus areas de actuación, y este programa surge de la 
  necesidad de conseguir automatizar las sessiones de astrofotografia utilizando un montaje casero amador del tipo
  "barn door". Lo unico pedido es que no se quite esta descripción y tampoco los creditos del codigo y mencione el 
  autor y si eres un aficcionado de la astronomia comparte este codigo con los demás.

REPOSITORIO:

  https://github.com/davidsnege/ArduinoGeneralCodes/blob/main/Intervalometro_Canon/Intervalometro_Canon.ino

LICENCIA:

  El uso es libre con excepción de usos comerciales, esto debe ser compartido de manera gratuita y nadie debe llevar
  lucro o ganancias con uso de este código.

COMPONENTES USADOS:

  - Arduino Nano (generico de Amazon)
  - 2 Leds (Rojo, Amarillo)
  - 2 Resistencias de 10k
  - 3 Push Buttons
  - LCD 16x2 (Interfaz I2C 'El que tiene solo 4 conectores')
    
*/

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++ L I B R E R I A S  C A R G A D A S ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//////////////////////////////////////////////////////// INCLUDE LIBS
#include "LiquidCrystal_I2C.h"                        // LCD LIBRERIA
LiquidCrystal_I2C lcd(0x27, 16, 2);                   // Instancia de Libreria y puerto + 16 columnas / 2 Lineas

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++ V A R I A B L E S  G L O B A L E S D E C L A R A D A S ++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//////////////////////////////////////////////////////// DECALRE VARS
int   posMenu = 0;                                      // Indicador de Menu que se esta seleccionado
int   delayBuffer = 2000;                               // Delay que se espera para la camara guardar la foto depende de la cámara
int   numBuffer = 2;                                    // Se usa para incrementar y despues se suma a los mili del arduino
int   fotosTotal = 0;                                   // Cantidad de fotos a sacar cuando se de en Start en el menu home
float obturador = 0;                                    // Tiempo de Obturador Abierto en la cámara, dejar cámara en modo BULB
int   obturadorDelay = 0;                               // Delay real en Milisegundos que Arduino debe esperar
int   fotosTomadas = 0;                                 // Cantidad de fotos que se ha tomado hasta el momento
int   startStop = 0;                                    // activa desactiva en el menu 1 todo

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++ S E T U P  N A T I V O  A R D U I N O +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//////////////////////////////////////////////////////// START SETUP
void setup() {

Serial.begin(9600);                                     // Iniciamos el Serial Monitor por debugs

if (!i2CAddrTest(0x27)) {                               // Testeo de la puerta I2C de la libreria del LCD
lcd = LiquidCrystal_I2C(0x3F, 16, 2);                   // Asignamos lcd a la entidad de la libreria si todo va bien
}

pinMode(A0, INPUT_PULLUP);                              // Button de Menu
pinMode(A1, INPUT_PULLUP);                              // Button de decremento / Stop 
pinMode(A2, INPUT_PULLUP);                              // Button de incremento / Start

pinMode(7, OUTPUT);                                     // Indicador LED de buffer rojo
pinMode(6, OUTPUT);                                     // Disparador de la cámara / Led indicador amarillo

lcd.init();                                             // Iniciamos el LCD -- Si no se hace la libreria no funciona  
lcd.backlight();                                        // Encendemos la luz de background del LCD 0/1 si no hay nada es 1

digitalWrite(7, LOW);                                   // Primer estado del LED de Buffer
digitalWrite(6, 10);                                    // Primer estado del disparador (Funciona al reves en la camara [ HIGH = Apagado / LOW = Disparando ])

// Escribimos por primera vez 
lcd.setCursor(0, 0);                                    // Posicionamos cursor    
lcd.print("Intervalometer  ");                          // Escribimos
delay(500);                                             // La camara va sacar una foto inicial, borrar después
lcd.clear();                                            // Limpiamos el LCD

}
//////////////////////////////////////////////////////// END SETUP

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++ L O O P  N A T I V O  A R D U I N O +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//////////////////////////////////////////////////////// START LOOP 
void loop() {
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Nuestro If se encarga de saber en que menu estamos por el estado del posMenu en este momento.
  if (posMenu == 0){
    lcd.setCursor(0, 1);            
    lcd.print("                ");  
    StartStop();                    // Llamamos la función de Start o Stop que inicia las tomas de fotos si es verdadero
  }else if (posMenu == 1){
    lcd.setCursor(0, 1);            
    lcd.print("                ");  
    ConfigObturador();              // Llamamos la funcion de configuración de tiempo del obturador abierto
  }else if (posMenu == 2){
    lcd.setCursor(0, 1);            
    lcd.print("                ");  
    ConfigFotos();                  // Llamamos la funcion de configuración de cantida de fotos a sacar por sessión
  }else if (posMenu == 4){
    lcd.setCursor(0, 1);            
    lcd.print("                ");     
    BufferDelay();                  // Llamamos la funcion de configuración de Buffer de guardado de la camara
  }else if (posMenu == 5){
    lcd.setCursor(0, 1);            
    lcd.print("                ");     
    ResetParams();                  // Llamamos la funcion de limpieza de variables de parametros de las otras funciones lo que resulta en un reset
  }else{
    //                              // Nos prevenimos que no debe hacer nada si viene otro valor de posMenu
  }
  delay(500);                       // Esperamos que se use los buttons eso es el tiempo de respuesta de los buttons
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Ponemos valor en el estado del button para el menu rotatorio de incremento    
  if (digitalRead(A0) == LOW) {    // Si el button esta presionado (No se por que se inverte el LOW y no HIGH)
    posMenu += 1;                  // Sumamos uno al posMenu
  }
  if (posMenu == 6) {              // Si el menu llega a ser mayor que las opciones que tenemos que son 5 o sea si atinge 6
    posMenu = 0;                   // Volvemos a cero para reiniciar como un bucle de menu sin fim (Si añadimos un button más podemos decrementar esto y ir a frente o atraś)
  }
}
//////////////////////////////////////////////////////// END LOOP

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++++++++++ F U N C I O N E S  D E  M E N U  Y  C O N F I G U R A C I O N E S +++++++++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//////////////////////////////////////////////////////// START START o STOP
void StartStop(){
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Verificamos el estado del button A2 para saber si cambiamos startStop a uno (verdadero) y si es true empezamos a tomar fotos    
  if (digitalRead(A2) == LOW) {    // Si el button A2 es presionado
    startStop = 1;                 // Cambiamos el estado de startStop a uno para que sea verdadero
    TakeFotos();                   // Llamamos la función que hace las tomas de fotos
  }
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Verificamos el estado del button A1 para saber si cambiamos startStop a cero (falso) y si es true paramos las tomas de fotos    
  if (digitalRead(A1) == LOW) {    // Si el button A1 es presionado
    startStop = 0;                 // Cambiamos el estado de startStop a cero para que sea verdadero
    lcd.setCursor(6, 0);            
    lcd.print("Arduinter   Stop"); 
  }
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Si startStop es verdadero (true/1) entonces informamos en la pantalla mientras se esta ejecutando, cuando termine volve a parado    
  if (startStop == 1) {
    lcd.setCursor(0, 0);           
    lcd.print("-- Ejecutando ---");
  }else{
    lcd.setCursor(0, 0);           
    lcd.print("---- Parado -----");     
  }
}
//////////////////////////////////////////////////////// END START o STOP
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//////////////////////////////////////////////////////// START CONFIG OBTURADOR
void ConfigObturador(){
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Aqui empezamos imprimiendo en la pantalla en que Menu estamos    
  lcd.setCursor(0, 0);            
  lcd.print("Obturador Timer "); 
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Si presionamos el button A2 incrementamos la cantidad de segundos del obturador en decimales de 0.25 por vez 
  if (digitalRead(A2) == LOW) {  // Si el button A2 es presionado
    obturador += 0.25;           // Incrementamos 0.25 al tiempo de obturador abierto
  }
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Si presionamos el button A1 decrementamos la cantidad de segundos del obturador en decimales de 0.25 por vez  
  if (digitalRead(A1) == LOW) { // Si el button A1 es presionado
    obturador -= 0.25;          // Decrementamos 0.25 al tiempo de obturador abierto
  }
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Aqui hacemos las matematicas para que Arduino sepa en milisegundos el tiempo que acabamos de definir 
  obturadorDelay = obturador * 1000 + 1000;
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Imprimimos en la pantalla mientras vamos cambiando la configuración
  lcd.setCursor(0, 1);          
  lcd.print("T");              
  lcd.setCursor(1, 1);         
  lcd.print(obturador);        
}
//////////////////////////////////////////////////////// END CONFIG OBTURADOR
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//////////////////////////////////////////////////////// START CONFIG FOTOS
void ConfigFotos(){
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Aqui empezamos imprimiendo en la pantalla en que Menu estamos    
  lcd.setCursor(0, 0);          
  lcd.print("Fotos Cuantidad "); 
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Si presionamos el button A2 incrementamos la cantidad de fotos que vamos tomar por sesion.  
  if (digitalRead(A2) == LOW) { // Si el button A2 es presionado
    fotosTotal += 1;            // Incrementamos la cantidad de fotos a tomar de uno en uno
  }
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Si presionamos el button A1 decrementamos la cantidad de fotos que vamos tomar por sesion.  
  if (digitalRead(A1) == LOW) { // Si el button A1 es presionado
    fotosTotal -= 1;            // Decrementamos la cantidad de fotos a tomar de uno en uno
  }
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Imprimimos en la pantalla mientras vamos cambiando la configuración
  lcd.setCursor(6, 1);          
  lcd.print("F");              
  lcd.setCursor(7, 1);          
  lcd.print(fotosTotal);       
}
//////////////////////////////////////////////////////// END CONFIG FOTOS
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//////////////////////////////////////////////////////// START CONFIG BUFFER
void BufferDelay(){
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Aqui empezamos imprimiendo en la pantalla en que Menu estamos  
  lcd.setCursor(0, 0);          
  lcd.print("Buffer Delay    "); 
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Si presionamos el button A2 incrementamos el tiempo del buffer, o sea cuanto la camara tarda en guardar la foto, antes de sacar otra.
  if (digitalRead(A2) == LOW) { // Si el button A2 es presionado
    numBuffer += 1;             // Incrementamos el buffer de uno segundo en uno segundo
  }
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Si presionamos el button A1 decrementamos el tiempo del buffer, o sea cuanto la camara tarda en guardar la foto, antes de sacar otra. 
  if (digitalRead(A1) == LOW) { // Si el button A1 es presionado
    numBuffer -= 1;             // Decrementamos el buffer de uno segundo en uno segundo
  }
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Aqui hacemos las matematicas para que Arduino sepa en milisegundos el tiempo que acabamos de definir 
  delayBuffer = numBuffer * 1000 + 1000;
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Imprimimos en la pantalla mientras vamos cambiando la configuración
  lcd.setCursor(14, 1);        
  lcd.print("B");              
  lcd.setCursor(15, 1);        
  lcd.print(numBuffer);        
}
//////////////////////////////////////////////////////// END CONFIG BUFFER
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//////////////////////////////////////////////////////// START TAKE FOTOS
void TakeFotos(){
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Esta es la funcción que se ejecuta desde "StartStop()" para hacer las fotos con los parametros configurados en las otras funciones
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Verificamos que las fotos que ya tomamos son diferentes de las fotos que configuramos para tomar, si son diferentes es true
  if (fotosTomadas != fotosTotal){
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Creamos un bucle, mientras las fotos que configuramos sean más que las tomadas sacamos fotos    
    while(fotosTomadas < fotosTotal){
      digitalWrite(6, LOW); // Abre BULB foto       // Ponemos en true (encendido) el pin 6 (donde esta el cable disparador y el led amarillo) (LOW y HIGH estan invertidos OK)
      lcd.setCursor(0, 0);                          
      lcd.print("Sacando Fotos   ");                
      delay(obturadorDelay);                        // Esperamos el tiempo que configuramos en la función del obturador
      digitalWrite(6, HIGH); // Cierra BULB foto    // Ponemos en false (apagado) el pin 6 (donde esta el cable disparador y el led amarillo) para que deje el obturador cerrar (LOW y HIGH estan invertidos OK)
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Atualizando la pantalla con el status actual de la toma y el led de control rojo 
      lcd.setCursor(0, 0);                          
      lcd.print("Guardando Fotos ");                
      digitalWrite(7, HIGH);                        
      delay(delayBuffer);                           // Esperamos el tiempo configurado en el Buffer para que la camara tenga tiempo de guardar la foto antes que intentemos sacar otra
      digitalWrite(7, LOW);                         
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Atualizando el contador de fotos tomadas      
      fotosTomadas++;                               // Incrementamos el contador de fotos ya tomadas
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Atualizando la pantalla con el status actual despues de la ultima toma    
      lcd.setCursor(6, 1);                          
      lcd.print("F");                               
      lcd.setCursor(7, 1);                          
      lcd.print(fotosTotal);                        
      lcd.setCursor(10, 1);                         
      lcd.print("T");                               
      lcd.setCursor(11, 1);                         
      lcd.print(fotosTomadas);                                      
    }
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Este bucle es responsable por parar de tomar fotos, volver el estado de startStop y printar las infos en la pantalla
      if(fotosTomadas == fotosTotal){               // Si ya tomamos todas las fotos, paramos todo y volvemos valores a cero
        startStop = 0;                              // Eso hace que el menu de Start Stop vuelva a cero
        digitalWrite(6, HIGH);                      // Dejamos el Obturador Cerrado (pero el led encendido, porque los LOW y HIGH estan invertidos)
        digitalWrite(7, LOW);                       // Apagamos el led rojo para saber que no estamos ejecutando nada  
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Actualizamos todas las infos de la pantalla       
        lcd.setCursor(0, 0);
        lcd.print("Arduinter   Stop"); 
        
        lcd.setCursor(0, 1); 
        lcd.print("T");          
        lcd.setCursor(1, 1); 
        lcd.print(obturador);
          
        lcd.setCursor(6, 1); 
        lcd.print("F");             
        lcd.setCursor(7, 1); 
        lcd.print(fotosTotal);

        lcd.setCursor(10, 1); 
        lcd.print("T");         
        lcd.setCursor(11, 1); 
        lcd.print(fotosTomadas);                        
     }      
  }
}
//////////////////////////////////////////////////////// END TAKE FOTOS
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//////////////////////////////////////////////////////// START RESET PARAMETROS
void ResetParams(){
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Esta es la funcción que borra todos los datos configurados (solo mantenemos el buffer por seguridad)
  lcd.setCursor(0, 0); 
  lcd.print("Borrar   Config?"); 
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Verificamos si el button de reset A2 es presionado
  if (digitalRead(A2) == LOW) {
    lcd.setCursor(0, 0); 
    lcd.print("Borrando Config!"); 
    delay(2000);
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Borrando configuraciones    
    startStop = 0;                                  // Vaciamos startStop
    fotosTomadas = 0;                               // Vaciamos fotosTomadas
    fotosTotal = 0;                                 // Vaciamos fotosTotal
    obturador = 0;                                  // Vaciamos obturador
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Actualizando pantalla
        lcd.setCursor(0, 1); 
        lcd.print("T");          
        lcd.setCursor(1, 1); 
        lcd.print(obturador);
          
        lcd.setCursor(6, 1); 
        lcd.print("F");             
        lcd.setCursor(7, 1); 
        lcd.print(fotosTotal);

        lcd.setCursor(10, 1); 
        lcd.print("T");         
        lcd.setCursor(11, 1); 
        lcd.print(fotosTomadas); 

        lcd.setCursor(14, 1); 
        lcd.print("B"); 
        lcd.setCursor(15, 1); 
        lcd.print(numBuffer); 
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Esperamos 1 segundo   
    delay(1000);
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Volvemos al menu inicial    
        posMenu = 0;   
  }
}
//////////////////////////////////////////////////////// END RESET PARAMETROS
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//////////////////////////////////////////////////////// START TEST DEL LCD - LA LIBRERIA LO PIDE QUE SE EJECUTE POR SI ACASO
// I2C Address TEST 
bool i2CAddrTest(uint8_t addr) {
  Wire.begin();
  Wire.beginTransmission(addr);
  if (Wire.endTransmission() == 0) {
    return true;
  }
  return false;
}
//////////////////////////////////////////////////////// END TEST DEL LCD - LA LIBRERIA LO PIDE QUE SE EJECUTE POR SI ACASO
