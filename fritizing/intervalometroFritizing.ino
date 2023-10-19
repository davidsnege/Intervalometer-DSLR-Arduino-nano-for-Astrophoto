////////////////////////////////////////////////////////
// ARDUINO INTERVALOMETRO //////////////////////////////
////////////////////////////////////////////////////////
/*
Estamos usando arduino para disparar uma Canon 250D con
un cable tipo P2 de audio con adaptador para Mini P2 que
es la entrada de disparadores de Canon.

Estamos usando un LCD tipo I2C para exhibir las informaciones.

Tenemos un menu inicial para iniciar las tomas de fotos, pero
donde no se puede iniciar nada si no configuramos los otros menus.

Tenemos un menu para configurar los segundos de exposición de cada
foto, con un intervalo automatico de 4 segundos para que la 
cámara pueda guardar el archivo antes de que se tome la próxima foto.

Tenemos un menu para configurar la cantidad de fotos que queremos tomar
en cada start, y un contador que suma la cantidad y para cuando se llega
al maximo.

Cuando se acaba vuelve al menu inicial, y podemos ir hasta el menu de cantidad
de fotos, incrementar más fotos, y volver a iniciar en el menu home para
que se llegue a su nuevo numero.

Ej: 

1 config : 10 tomas (cuando llega a 10 para y volve al home)
2 volvemos al menu de tomas, donde tenemos ya el valor 10, agregamos mas 5 y ahora tenemos 15
3 volvemos al menu de home, y hacemos start.
4 volve a tomar las fotos hasta que llegue ahora en 15 o sea saca más 5 fotos.
5 para el contador y vuelve al home.

La idea es mejorar esto y hacer una integración con una montaje Barn Door que tenemos, movimentando un
motor de paso para acompañar el movimiento del cielo y hacer astrofotografias.
*/


////////////////////////////////////////////////////////



//////////////////////////////////////////////////////// INCLUDE LIBS

#include "LiquidCrystal_I2C.h"                        // LCD LIBRERIA
LiquidCrystal_I2C lcd(0x27, 16, 2);                   // Instancia de Libreria y puerto + 16 columnas / 2 Lineas

//////////////////////////////////////////////////////// DECALRE VARS

int   posMenu = 0;                                      // Indicador de Menu que se esta seleccionado
int   delayBuffer = 2000;                               // Delay que se espera para la camara guardar la foto depende de la cámara
int   numBuffer = 2;                                    // Se usa para incrementar y despues se suma a los mili del arduino
int   fotosTotal = 0;                                   // Cantidad de fotos a sacar cuando se de en Start en el menu home
float obturador = 0;                                    // Tiempo de Obturador Abierto en la cámara, dejar cámara en modo BULB
int   obturadorDelay = 0;                               // Delay real en Milisegundos que Arduino debe esperar
int   fotosTomadas = 0;                                 // Cantidad de fotos que se ha tomado hasta el momento
int   startStop = 0;                                    // activa desactiva en el menu 1 todo

//////////////////////////////////////////////////////// START SETUP
void setup() {

Serial.begin(9600);                                     // Iniciamos el Serial Monitor por debugs

if (!i2CAddrTest(0x27)) {                               // Testeo de la puerta I2C de la libreria del LCD
lcd = LiquidCrystal_I2C(0x3F, 16, 2);
}

pinMode(A0, INPUT_PULLUP);                              // Button de Menu
pinMode(A1, INPUT_PULLUP);                              // Button de decremento / Stop 
pinMode(A2, INPUT_PULLUP);                              // Button de incremento / Start

pinMode(7, OUTPUT);                                     // Indicador LED de buffer rojo
pinMode(6, OUTPUT);                                     // Disparador de la cámara / Led indicador amarillo

lcd.init();                                             // Iniciamos el LCD -- Si no se hace la libreria no funciona  
lcd.backlight();                                        // Encendemos la luz de background del LCD 0/1 si no hay nada es 1

digitalWrite(7, LOW);                                   // Primer estado del LED de Buffer
digitalWrite(6, HIGH);                                  // Primer estado del disparador (Funciona al reves en la camara [ HIGH = Apagado / LOW = Disparando ])

// Escribimos por primera vez 
// LCD después del Setup
lcd.setCursor(0, 0);                                    // Posicionamos cursor    
lcd.print("Intervalometer  ");                          // Escribimos
delay(500);                                             // La camara va sacar una foto inicial, borrar después
lcd.clear();                                            // Limpiamos el LCD

}
//////////////////////////////////////////////////////// END SETUP


//////////////////////////////////////////////////////// START LOOP 
void loop() {
// Nuestro Switch se encarga de saber en que menu estamos por el
// estado del posMenu en este momento.
 
  switch (posMenu) {
  case 0:
      StartStop();
    break;
  case 1:
      ConfigObturador();
    break;
  case 2:
      ConfigFotos();
    break;
  case 3:
      BufferDelay();
    break;    
  case 4:
      ResetParams();
    break;  
  default:
    // statements
    break;
  }

  delay(1000);                                          // Esperamos que se use los buttons

// Ponemos valor en el estado del button para el menu rotatorio de incremento    
  if (digitalRead(A0) == LOW) {
    posMenu += 1;
  }
  if (posMenu == 5) {
    posMenu = 0;
  }

}
//////////////////////////////////////////////////////// END LOOP


////////////////////////////////////////////////////////
void StartStop(){
////////////////////////
  lcd.setCursor(0, 0); 
  lcd.print("Arduinter Home      "); 

////////////////////////  
  if (digitalRead(A2) == LOW) {
    startStop = 1;
    TakeFotos();
    lcd.setCursor(6, 0); 
    lcd.print("Arduinter   Take");  
  }
////////////////////////  
  if (digitalRead(A1) == LOW) {
    startStop = 0;
    lcd.setCursor(6, 0); 
    lcd.print("Arduinter   Stop");    
  }
}
////////////////////////////////////////////////////////



////////////////////////////////////////////////////////
void ConfigObturador(){
////////////////////////
  lcd.setCursor(0, 0); 
  lcd.print("Obturador Timer "); 
////////////////////////  
  if (digitalRead(A2) == LOW) {
    obturador += 0.25;
  }
////////////////////////  
  if (digitalRead(A1) == LOW) {
    obturador -= 0.25;
  }

  obturadorDelay = obturador * 1000 + 1000;

  lcd.setCursor(0, 1); 
  lcd.print("T");          
  lcd.setCursor(1, 1); 
  lcd.print(obturador); 
//////////////////////// 
}
////////////////////////////////////////////////////////



////////////////////////////////////////////////////////
void ConfigFotos(){
////////////////////////
  lcd.setCursor(0, 0); 
  lcd.print("Fotos Cuantidad "); 
////////////////////////  
  if (digitalRead(A2) == LOW) {
    fotosTotal += 1;
  }
////////////////////////  
  if (digitalRead(A1) == LOW) {
    fotosTotal -= 1;
  }

  lcd.setCursor(6, 1); 
  lcd.print("F");             
  lcd.setCursor(7, 1); 
  lcd.print(fotosTotal);  
//////////////////////// 
}
////////////////////////////////////////////////////////



////////////////////////////////////////////////////////
void TakeFotos(){
////////////////////////
  //Tomamos fotos con los parametros 
  //Hasta que se cumpla
  if (fotosTomadas != fotosTotal){
    while(fotosTomadas < fotosTotal){
      digitalWrite(6, LOW); // Abre BULB foto
      lcd.setCursor(0, 0);
      lcd.print("Sacando Fotos   "); 
      delay(obturadorDelay);
      digitalWrite(6, HIGH); // Cierra BULB foto

      lcd.setCursor(0, 0);
      lcd.print("Guardando Fotos "); 
      digitalWrite(7, HIGH);        
      delay(delayBuffer);
      digitalWrite(7, LOW);
      
      fotosTomadas++;
    
        lcd.setCursor(10, 1); 
        lcd.print("T");         
        lcd.setCursor(11, 1); 
        lcd.print(fotosTomadas);  
    }
      if(fotosTomadas == fotosTotal){ // Paramos todo y volvemos valores a cero
        startStop = 0;
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
        
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
     
//////////////////////// 
}
////////////////////////////////////////////////////////



////////////////////////////////////////////////////////
void BufferDelay(){
////////////////////////
  lcd.setCursor(0, 0); 
  lcd.print("Buffer Delay    "); 
////////////////////////  
  if (digitalRead(A2) == LOW) {
    numBuffer += 1;
  }
////////////////////////  
  if (digitalRead(A1) == LOW) {
    numBuffer -= 1;
  }

  delayBuffer = numBuffer * 1000 + 1000;

  lcd.setCursor(14, 1); 
  lcd.print("B"); 
  lcd.setCursor(15, 1); 
  lcd.print(numBuffer);  
//////////////////////// 
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void ResetParams(){
////////////////////////
    lcd.setCursor(0, 0); 
    lcd.print("Borrar   Config?"); 
////////////////////////  
  if (digitalRead(A2) == LOW) {
    lcd.setCursor(0, 0); 
    lcd.print("Borrando Config!"); 
    delay(2000);
    startStop = 0;
    fotosTomadas = 0;
    fotosTotal = 0;
    obturador = 0; 

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

    delay(1000);

        posMenu = 0;
    
  }
//////////////////////// 
}
////////////////////////////////////////////////////////



////////////////////////////////////////////////////////
// I2C Address TEST 
bool i2CAddrTest(uint8_t addr) {
  Wire.begin();
  Wire.beginTransmission(addr);
  if (Wire.endTransmission() == 0) {
    return true;
  }
  return false;
}
////////////////////////////////////////////////////////