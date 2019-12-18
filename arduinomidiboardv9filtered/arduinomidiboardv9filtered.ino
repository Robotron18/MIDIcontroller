#include <MIDI.h>
#include <EEPROM.h>
#include <Wire.h>

#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

#define CONTROL0 11//4    
#define CONTROL1 12// 5
#define CONTROL2 10//3
#define CONTROL3 9//2
#define MUXA A0
#define MUXB A1
#define VELOCITY 127
#define CHANNEL 1
#define BOTONRUEDA 4
#define ENCODERA 2
#define ENCODERB 3
#define MIDIOUSB 1 //1 midi  0 Serial
#define MUXATIPO 1    //1 boton 0 pote
#define MUXBTIPO 0 //1 boton 0 pote

volatile int encoderPos = 0;  // a counter for the dial
static boolean rotating = false;    // debounce management
// interrupt service routine vars
boolean A_set = false;
boolean B_set = false;

SSD1306AsciiWire oled;

MIDI_CREATE_DEFAULT_INSTANCE();

byte mux[32]; //declara que en el array hay 32 valores
byte muxPrev[32]; //declara otro para comparar valores
boolean estadobotones[32];
unsigned long debounceboton[32];
int tiempodebounce = 10;
int pagina = 1;
boolean screenActive = true;
unsigned long temporalpote;
int alpha=3;
int beta=2;

struct Preset {
  unsigned long tipoboton;// = 0;  //0 o 1 para retencion o no una sola variable para cambiar el estado de todo el preset
  byte channel[32];// = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 11, 16, 16, 5, 3, 3, 3, 5, 7, 7, 7, 8, 2, 2, 2, 3, 4, 4, 4, 5, 5, 6};
  byte numero[32];// =  {4, 6, 5, 40, 60, 85, 00, 20, 10, 20, 30, 40, 50, 10, 30, 44, 55, 6, 34, 4, 1, 55, 2, 127, 4, 7, 6, 127, 127, 4, 33, 127};
  // byte velocity[32]= {127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127};
  char nombrePreset[9];// = {'P', 'a', 'l', 'o', 'f', 'a', 'G', 'G',};
  char numeroPreset;
};

Preset arrayPresets[2];  // en array[0] se guarda el preset actual y en [1] el futuro
byte presetActual = 0;
boolean botonlargo = false;
boolean botoncorto = false;
unsigned long ultimomensaje = 0;
int wheel = 0;

void setup()
{

  bitSet( arrayPresets[presetActual].tipoboton, 12);
  if (MIDIOUSB) MIDI.begin(1);
  else Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000L);
  oled.begin(&Adafruit128x64, 0x3C);

  oled.setFont(lcd5x7);
  EEPROM.get(0, arrayPresets[0]);
  /*uint32_t m = millis();
    oled.clear();
    oled.set2X();
    oled.println((String) " " + arrayPresets[presetActual].nombrePreset);
    // oled.println("Hello world!");
    // oled.println("lalalala");
    oled.set1X();
    oled.println();
    oled.set2X();
    oled.println("TRUCHOTOYS");
    oled.set1X();
    oled.print("\nmicros: ");
    oled.println(millis() - m);
    oled.print("TRUCHOTOYS");

    delay(10000);*/

  //tira 4 bits a los mux para poder leer 16 valores
  pinMode(CONTROL0, OUTPUT);
  pinMode(CONTROL1, OUTPUT);
  pinMode(CONTROL2, OUTPUT);
  pinMode(CONTROL3, OUTPUT);
  pinMode(BOTONRUEDA, INPUT);
  pinMode(ENCODERA, INPUT);
  pinMode(ENCODERB, INPUT);
  pinMode(MUXA, INPUT);
  pinMode(MUXB, INPUT);
  attachInterrupt(0, doEncoderA, CHANGE);
  // encoder pin on interrupt 1 (pin 3)
  attachInterrupt(1, doEncoderB, CHANGE);

  //incrementa de a uno para recorrer todo el array para
  //no tener que fijarse de a uno y arrancar en cero, todo apagado
  for (int i = 0; i < 32; i++) {
    //le asigna un valor a ambos arrays
    mux[i] = muxPrev[i] = false;
    debounceboton[i] = 0;
    estadobotones[i] = false;
  }
  /*
    for (int i = 0; i < 16; i++) {
      if (MIDIOUSB) MIDI.sendNoteOff(i, 0, 1);
      else Serial.println((String) F("Apago nota ") + i); //  //nota, velocity, channel
    }*/
  for (int i = 0; i < 16; i++)
  {
    //tira voltaje a los mux
    digitalWrite(CONTROL0, (i & 15) >> 3);
    digitalWrite(CONTROL1, (i & 7) >> 2);
    digitalWrite(CONTROL2, (i & 3) >> 1);
    digitalWrite(CONTROL3, (i & 1));
    //direcciona los 3 mux

    if (MUXATIPO == 1)  mux[i] = !digitalRead(MUXA); //signo de exclamación invierte 0 y 1, hay pull-up que está en 1 con botón sin apretar
    else{
      mux[i] = (byte) ( analogRead(MUXA) >> 3); //hago la lectura y divido por 3 para tener un rango de 0 a 127
    }

    if (MUXBTIPO == 1)  mux[i + 16] = !digitalRead(MUXB); //signo de exclamación invierte 0 y 1, hay pull-up que está en 1 con botón sin apretar
    else {
      
      mux[i + 16] = (byte) ( analogRead(MUXB) >> 3); //hago la lectura y divido por 3 para tener un rango de 0 a 127
    }
    muxPrev[i] = mux[i];
    muxPrev[i + 16] = mux[i + 16];
  }
  /*
    Serial.print("Mux:    ");
    for (int i = 0; i < 32; i++) {
      Serial.print((String)  mux[i]+" ");
    }
    Serial.println("");
    Serial.print("MuxPrev ");
      for (int i = 0; i < 32; i++) {
      Serial.print((String)  muxPrev[i]+" ");
    }
    Serial.println("");
  */
    mensajemain();

}


void loop()
{
  if (pagina == 1) pagina1();
  else if (pagina == 2) pagina2();
  //pagina1();
  lecturaboton();
  if (botonlargo) {
    pagina = 2;
    botonlargo = false;
  }
  else if (botoncorto) {
    if (pagina == 1 && botoncorto) {
      arrayPresets[0] = arrayPresets[1];
      botoncorto = false;

     for (int i = 0; i < 32; i++) {
    if (mux[i] ==1){
      screenActive=!screenActive; 
      i=32;
      if(screenActive){
    oled.clear();
    oled.set2X();
    oled.println("");
    oled.println("MONITOR ON");
ultimomensaje=millis();
mensajemain();
  }
    
  else{
    oled.clear();
    oled.set2X();
    oled.println("");
    oled.println("MONITOR OFF");
ultimomensaje=millis();
    mensajemain();
  }
    }
  }
  

      
    }
  }
  mensajemain();

  nombresiguiente();
}

void lecturaboton() {
  static boolean estadoboton = false;
  static unsigned long tiempoapretado = 0;
  static boolean toggle = false;
  if(digitalRead(BOTONRUEDA)){
    botonlargo=false;
    botoncorto=false;
  }
  
  if (!estadoboton && !digitalRead(BOTONRUEDA)) {
    estadoboton = true;
    tiempoapretado = millis();
  }
  
  if (estadoboton && (millis() - tiempoapretado) > 1000 && !toggle) {
    botonlargo = true;
    toggle = true;
    //  Serial.println("largo");
  }
  if (estadoboton && digitalRead(BOTONRUEDA)&& ((millis() - tiempoapretado) > 50))  {
    estadoboton = false;
    if (toggle) {
      toggle = false;
    }
    else  {
      botoncorto = true;
      //  Serial.println("corto");
    }
  }
}

void mensajemain() {
  static String nombreactual = "";
  static String nombresiguiente = "";
  if (nombreactual != arrayPresets[presetActual].nombrePreset || nombresiguiente != arrayPresets[1].nombrePreset || ((millis()-ultimomensaje)>700) && ultimomensaje!=0 ) {
    nombreactual = arrayPresets[presetActual].nombrePreset;
    nombresiguiente = arrayPresets[1].nombrePreset;
    oled.clear();
    oled.set2X();
    oled.println((String) " " + nombreactual);
    oled.set1X();
    oled.setFont(newbasic3x5);
    oled.println();
    oled.setFont(lcd5x7);
    oled.set2X();
    oled.println((String) "  ------  ");
    oled.set1X();
    oled.println(" ");
    oled.println();
    oled.println((String)nombresiguiente);
    ultimomensaje = 0;
  }

}
