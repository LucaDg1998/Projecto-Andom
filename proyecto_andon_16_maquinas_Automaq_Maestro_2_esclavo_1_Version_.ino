/*  ----------------------------------------------------------------
  LucaDg
  AUTOMAQ
  Codigo para la configuracion MultiCeiver con NRF24L01.
  Codigo del PRX (Receptor Maestro y controlador de las alarmas)
  Codigo arduino mega sin dfplayer COMUNICACION I2C escalvo 1
  --------------------------------------------------------------------
*/
//Librerias para el control del modulo nRF
#include <SPI.h> // Libreria de SPI para la comunicacion con el modulo nRF24L01
#include <nRF24L01.h>
#include <RF24.h>
//--------------------------------------------------------------------------------------
/*
   omitido para este maestro
  //Librerias para el control del modulo mp3
  #include "Arduino.h"
  #include "SoftwareSerial.h"
  #include "DFRobotDFPlayerMini.h"*/

//--------------------------------------------------------------------------------------
//Librerias para comunicacion 12c
#include <Wire.h>
//***************************************************************************************************
RF24 radio(8, 9);//Declaracion de los pines de control CE y CSN para el modulo, se define "radio"
//--------------------------------------------------------------------------------------
/*
 * * omitido para este maestro
  SoftwareSerial mySoftwareSerial(10, 11); // tX, rX
  DFRobotDFPlayerMini myDFPlayer;
*/
//***************************************************************************************************

//Se crean las 6 direcciones posibles para las Pipes P0 - P5;
//Las direcciones es un numero de 40bits para este caso se usa uint_64_t de 64bits
const uint64_t direccion[] = {0x7878787879LL, 0xB3B4B5B6F9LL, 0xB3B4B5B6C9LL, 0xB3B4B5B6A9LL, 0xB3B4B5B609LL, 0xB3B4B5B699LL };
//                            En esta parte LL significa LongLong para asegurar el dato de 64bits

//***************************************************************************************************
//configuracion de los pines de salidas
int Alarm_out_M1_a = 22; //Pin de salida de la alarma maquina 1 boton a conectar NA del led al relay
int Alarm_out_M1_b = 23; //Pin de salida de la alarma maquina 1 boton b conectar NA del led al relay
int Alarm_out_M1_c = 24; //Pin de salida de la alarma maquina 1 boton c conectar NA del led al relay
int Alarm_out_M1_d = 25; //Pin de salida de la alarma maquina 1 boton d conectar NA del led al relay
int Alarm_out_M1_e = 26; //Pin de salida de la alarma maquina 1 boton c conectar NA del led al relay
int Alarm_out_M1_f = 27; //Pin de salida de la alarma maquina 1 boton d conectar NA del led al relay
int Alarm_modo_M1 = 28; //Pin indicador de alarma ok conectar NA del led al relay
//--------------------------------------------------------------------------------------
int Alarm_out_M2_a = 29; //Pin de salida de la alarma maquina 2 boton a conectar NA del led al relay
int Alarm_out_M2_b = 30; //Pin de salida de la alarma maquina 2 boton b conectar NA del led al relay
int Alarm_out_M2_c = 31; //Pin de salida de la alarma maquina 2 boton c conectar NA del led al relay
int Alarm_out_M2_d = 32; //Pin de salida de la alarma maquina 2 boton d conectar NA del led al relay
int Alarm_out_M2_e = 33; //Pin de salida de la alarma maquina 2 boton c conectar NA del led al relay
int Alarm_out_M2_f = 34; //Pin de salida de la alarma maquina 2 boton d conectar NA del led al relay
int Alarm_modo_M2 = 35; //Pin indicador de alarma ok conectar NA del led al relay
//--------------------------------------------------------------------------------------
int Alarm_out_M3_a = 36; //Pin de salida de la alarma maquina 3 boton a conectar NA del led al relay
int Alarm_out_M3_b = 37; //Pin de salida de la alarma maquina 3 boton b conectar NA del led al relay
int Alarm_out_M3_c = 38; //Pin de salida de la alarma maquina 3 boton c conectar NA del led al relay
int Alarm_out_M3_d = 39; //Pin de salida de la alarma maquina 3 boton d conectar NA del led al relay
int Alarm_out_M3_e = 40; //Pin de salida de la alarma maquina 3 boton c conectar NA del led al relay
int Alarm_out_M3_f = 41; //Pin de salida de la alarma maquina 3 boton d conectar NA del led al relay
int Alarm_modo_M3 = 42; //Pin indicador de alarma ok conectar NA del led al relay
//--------------------------------------------------------------------------------------
int Alarm_out_M4_a = 43; //Pin de salida de la alarma maquina 4 boton a conectar NA del led al relay
int Alarm_out_M4_b = 44; //Pin de salida de la alarma maquina 4 boton b conectar NA del led al relay
int Alarm_out_M4_c = 45; //Pin de salida de la alarma maquina 4 boton c conectar NA del led al relay
int Alarm_out_M4_d = 46; //Pin de salida de la alarma maquina 4 boton d conectar NA del led al relay
int Alarm_out_M4_e = 47; //Pin de salida de la alarma maquina 4 boton c conectar NA del led al relay
int Alarm_out_M4_f = 48; //Pin de salida de la alarma maquina 4 boton d conectar NA del led al relay
int Alarm_modo_M4 = 49; //Pin indicador de alarma ok conectar NA del led al relay
//--------------------------------------------------------------------------------------
int Alarm_out_M5_a = 53; //Pin de salida de la alarma maquina 5 boton a conectar NA del led al relay
int Alarm_out_M5_b = 2; //Pin de salida de la alarma maquina 5 boton b conectar NA del led al relay
int Alarm_out_M5_c = 3; //Pin de salida de la alarma maquina 5 boton c conectar NA del led al relay
int Alarm_out_M5_d = 4; //Pin de salida de la alarma maquina 5 boton d conectar NA del led al relay
int Alarm_out_M5_e = 5; //Pin de salida de la alarma maquina 5 boton c conectar NA del led al relay
int Alarm_out_M5_f = 6; //Pin de salida de la alarma maquina 5 boton d conectar NA del led al relay
int Alarm_modo_M5 = 7; //Pin indicador de alarma ok conectar NA del led al relay
//--------------------------------------------------------------------------------------
/* * omitido para este maestro
   int Alarm_out_M6_a = 12; //Pin de salida de la alarma maquina 6 boton a conectar NA del led al relay
  int Alarm_out_M6_b = 13; //Pin de salida de la alarma maquina 6 boton b conectar NA del led al relay
  int Alarm_out_M6_c = 14; //Pin de salida de la alarma maquina 6 boton c conectar NA del led al relay
  int Alarm_out_M6_d = 15; //Pin de salida de la alarma maquina 6 boton d conectar NA del led al relay
  int Alarm_out_M6_e = 16; //Pin de salida de la alarma maquina 6 boton c conectar NA del led al relay
  int Alarm_out_M6_f = 17; //Pin de salida de la alarma maquina 6 boton d conectar NA del led al relay
  int Alarm_modo_M6 = 18; //Pin indicador de alarma ok conectar NA del led al relay del led al relay
*/
//--------------------------------------------------------------------------------------
//***************************************************************************************************

// comunicacion wire
int Alarma_activa;

//***************************************************************************************************
//Variles para Millis
int periodo = 1000;
unsigned long TiempoAhora = 0;
//***************************************************************************************************
//Variables de estado de las alarmas
bool Alarma1 = false, Alarma2 = false, Alarma3 = false, Alarma4 = false, Alarma5 = false; //, Alarma6 = false;
bool A_state = 0; //Variable de estado logico de la salida del la alarma intermitente
int valor_ma = 0, valor_mb = 0, valor_mc = 0, valor_md = 0, valor_me = 0;
//--------------------------------------------------------------------------------------
bool boton_m1a = false, boton_m1b = false, boton_m1c = false, boton_m1d = false, boton_m1e = false, boton_m1f = false;
bool boton_m2a = false, boton_m2b = false, boton_m2c = false, boton_m2d = false, boton_m2e = false, boton_m2f = false;
bool boton_m3a = false, boton_m3b = false, boton_m3c = false, boton_m3d = false, boton_m3e = false, boton_m3f = false;
bool boton_m4a = false, boton_m4b = false, boton_m4c = false, boton_m4d = false, boton_m4e = false, boton_m4f = false;
bool boton_m5a = false, boton_m5b = false, boton_m5c = false, boton_m5d = false, boton_m5e = false, boton_m5f = false;
//bool boton_m6a = false, boton_m6b = false, boton_m6c = false, boton_m6d = false, boton_m6e = false, boton_m6f = false;
//--------------------------------------------------------------------------------------
bool Atendido_m1a = false, Atendido_m1b = false, Atendido_m1c = false, Atendido_m1d = false, Atendido_m1e = false, Atendido_m1f = false;
bool Atendido_m2a = false, Atendido_m2b = false, Atendido_m2c = false, Atendido_m2d = false, Atendido_m2e = false, Atendido_m2f = false;
bool Atendido_m3a = false, Atendido_m3b = false, Atendido_m3c = false, Atendido_m3d = false, Atendido_m3e = false, Atendido_m3f = false;
bool Atendido_m4a = false, Atendido_m4b = false, Atendido_m4c = false, Atendido_m4d = false, Atendido_m4e = false, Atendido_m4f = false;
bool Atendido_m5a = false, Atendido_m5b = false, Atendido_m5c = false, Atendido_m5d = false, Atendido_m5e = false, Atendido_m5f = false;
//bool Atendido_m6a = false, Atendido_m6b = false, Atendido_m6c = false, Atendido_m6d = false, Atendido_m6e = false, Atendido_m6f = false;
//--------------------------------------------------------------------------------------
//void printDetail(uint8_t type, int value);
void alarmas_sonoras (int play);
void alarmas_sonoras2 (int activas);
//***************************************************************************************************

void setup()
{
  //***************************************************************************************************

  radio.begin(); //Inicio del modulo nRF24L01+
  radio.setPALevel(RF24_PA_MAX);  // Se configura a la maxima potencia
  radio.setChannel(101); // Apertura del canal especifico

  //Apertura de las lineas de comunicacion con un maximo de 6 direcciones
  radio.openReadingPipe(0, direccion[0]);
  radio.openReadingPipe(1, direccion[1]);
  radio.openReadingPipe(2, direccion[2]);
  //para el caso de tenes mas modulos
  radio.openReadingPipe(3, direccion[3]);
  radio.openReadingPipe(4, direccion[4]);
  radio.openReadingPipe(5, direccion[5]);

  radio.startListening(); //Se inicia en modo de escucha, a la espera de alertas de las alarmas
  //--------------------------------------------------------------------------------------
  /*
   * * omitido para este maestro
    mySoftwareSerial.begin(9600);
    Serial.begin(115200);
    Serial.println();
    Serial.println(F("DFRobot DFPlayer Mini Demo"));
    Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
    if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
    }
    Serial.println(F("DFPlayer Mini online."));
    myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms

    //----Set volume----
    myDFPlayer.volume(30);  //Set volume value (0~30).
    myDFPlayer.volumeUp(); //Volume Up
    // myDFPlayer.volumeDown(); //Volume Down

    //----Set different EQ----
    myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);

    //----Set device we use SD as default----
    myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
    //  myDFPlayer.outputDevice(DFPLAYER_DEVICE_FLASH);

    //----Mp3 control----
    //  myDFPlayer.sleep();     //sleep
    //  myDFPlayer.reset();     //Reset the module
    // myDFPlayer.enableDAC();  //Enable On-chip DAC
    //  myDFPlayer.disableDAC();  //Disable On-chip DAC
    //  myDFPlayer.outputSetting(true, 15); //output setting, enable the output and set the gain to 15

    //----Mp3 play----
    //----Read imformation----
    Serial.println(myDFPlayer.readState()); //read mp3 state
    Serial.println(myDFPlayer.readVolume()); //read current volume
    Serial.println(myDFPlayer.readEQ()); //read EQ setting
    Serial.println(myDFPlayer.readFileCounts()); //read all file counts in SD card
    Serial.println(myDFPlayer.readCurrentFileNumber()); //read current play file number
  */
  //--------------------------------------------------------------------------------------
  //Wire.begin();
  Wire.begin(1);                // unirse al bus i2c con la direccion #23
  Wire.onRequest(eventoSolicitud); // registrar evento de solicitud de datos
  //  Wire.onReceive(eventoRecepcion); // registrar evento de recepcion de datos

  //--------------------------------------------------------------------------------------

  //***************************************************************************************************
  /* configuracion de pines de salida  */
  //--------------------------------------------------------------------------------------
  pinMode(Alarm_out_M1_a, OUTPUT);
  pinMode(Alarm_out_M1_b, OUTPUT);
  pinMode(Alarm_out_M1_c, OUTPUT);
  pinMode(Alarm_out_M1_d, OUTPUT);
  pinMode(Alarm_out_M1_e, OUTPUT);
  pinMode(Alarm_out_M1_f, OUTPUT);
  pinMode(Alarm_modo_M1, OUTPUT);
  //--------------------------------------------------------------------------------------
  pinMode(Alarm_out_M2_a, OUTPUT);
  pinMode(Alarm_out_M2_b, OUTPUT);
  pinMode(Alarm_out_M2_c, OUTPUT);
  pinMode(Alarm_out_M2_d, OUTPUT);
  pinMode(Alarm_out_M2_e, OUTPUT);
  pinMode(Alarm_out_M2_f, OUTPUT);
  pinMode(Alarm_modo_M2, OUTPUT);
  //--------------------------------------------------------------------------------------
  pinMode(Alarm_out_M3_a, OUTPUT);
  pinMode(Alarm_out_M3_b, OUTPUT);
  pinMode(Alarm_out_M3_c, OUTPUT);
  pinMode(Alarm_out_M3_d, OUTPUT);
  pinMode(Alarm_out_M3_e, OUTPUT);
  pinMode(Alarm_out_M3_f, OUTPUT);
  pinMode(Alarm_modo_M3, OUTPUT);
  //--------------------------------------------------------------------------------------
  pinMode(Alarm_out_M4_a, OUTPUT);
  pinMode(Alarm_out_M4_b, OUTPUT);
  pinMode(Alarm_out_M4_c, OUTPUT);
  pinMode(Alarm_out_M4_d, OUTPUT);
  pinMode(Alarm_modo_M4, OUTPUT);
  //--------------------------------------------------------------------------------------
  pinMode(Alarm_out_M5_a, OUTPUT);
  pinMode(Alarm_out_M5_b, OUTPUT);
  pinMode(Alarm_out_M5_c, OUTPUT);
  pinMode(Alarm_out_M5_d, OUTPUT);
  pinMode(Alarm_out_M5_e, OUTPUT);
  pinMode(Alarm_out_M5_f, OUTPUT);
  pinMode(Alarm_modo_M5, OUTPUT);
  //--------------------------------------------------------------------------------------
  /*
   * * omitido para este maestro
    pinMode(Alarm_out_M6_a, OUTPUT);
    pinMode(Alarm_out_M6_b, OUTPUT);
    pinMode(Alarm_out_M6_c, OUTPUT);
    pinMode(Alarm_out_M6_d, OUTPUT);
    pinMode(Alarm_out_M6_e, OUTPUT);
    pinMode(Alarm_out_M6_f, OUTPUT);
    pinMode(Alarm_modo_M6, OUTPUT);
  */

  //--------------------------------------------------------------------------------------

  //**************************************************************************************
  /*se inicia cada alarma en estado alto, el modulo se activa con estado bajo*/
  //--------------------------------------------------------------------------------------
  digitalWrite(Alarm_out_M1_a, HIGH);
  digitalWrite(Alarm_out_M1_b, HIGH);
  digitalWrite(Alarm_out_M1_c, HIGH);
  digitalWrite(Alarm_out_M1_d, HIGH);
  digitalWrite(Alarm_out_M1_e, HIGH);
  digitalWrite(Alarm_out_M1_f, HIGH);
  digitalWrite(Alarm_modo_M1, HIGH);
  //--------------------------------------------------------------------------------------
  digitalWrite(Alarm_out_M2_a, HIGH);
  digitalWrite(Alarm_out_M2_b, HIGH);
  digitalWrite(Alarm_out_M2_c, HIGH);
  digitalWrite(Alarm_out_M2_d, HIGH);
  digitalWrite(Alarm_out_M2_e, HIGH);
  digitalWrite(Alarm_out_M2_f, HIGH);
  digitalWrite(Alarm_modo_M2, HIGH);
  //--------------------------------------------------------------------------------------
  digitalWrite(Alarm_out_M3_a, HIGH);
  digitalWrite(Alarm_out_M3_b, HIGH);
  digitalWrite(Alarm_out_M3_c, HIGH);
  digitalWrite(Alarm_out_M3_d, HIGH);
  digitalWrite(Alarm_out_M3_e, HIGH);
  digitalWrite(Alarm_out_M3_f, HIGH);
  digitalWrite(Alarm_modo_M3, HIGH);
  //--------------------------------------------------------------------------------------
  digitalWrite(Alarm_out_M4_a, HIGH);
  digitalWrite(Alarm_out_M4_b, HIGH);
  digitalWrite(Alarm_out_M4_c, HIGH);
  digitalWrite(Alarm_out_M4_d, HIGH);
  digitalWrite(Alarm_out_M4_e, HIGH);
  digitalWrite(Alarm_out_M4_f, HIGH);
  digitalWrite(Alarm_modo_M4, HIGH);
  //--------------------------------------------------------------------------------------
  digitalWrite(Alarm_out_M5_a, HIGH);
  digitalWrite(Alarm_out_M5_b, HIGH);
  digitalWrite(Alarm_out_M5_c, HIGH);
  digitalWrite(Alarm_out_M5_d, HIGH);
  digitalWrite(Alarm_out_M5_e, HIGH);
  digitalWrite(Alarm_out_M5_f, HIGH);
  digitalWrite(Alarm_modo_M5, HIGH);
  //--------------------------------------------------------------------------------------
  /*
   * * omitido para este maestro
    digitalWrite(Alarm_out_M6_a, HIGH);
    digitalWrite(Alarm_out_M6_b, HIGH);
    digitalWrite(Alarm_out_M6_c, HIGH);
    digitalWrite(Alarm_out_M6_d, HIGH);
    digitalWrite(Alarm_out_M6_e, HIGH);
    digitalWrite(Alarm_out_M6_f, HIGH);
    digitalWrite(Alarm_modo_M6, HIGH);
  */
  //--------------------------------------------------------------------------------------
}
//***************************************************************************************************


void loop() {
  //--------------------------------------------------------------------------------------
  /* Wire.beginTransmission(1); // Comunicarse con esclavo #1
    Wire.write('S');
    Wire.endTransmission();


    Wire.requestFrom(1, 1);    // Solicitar 1 byte del esclavo #1

    byte len = Wire.read();

    Wire.requestFrom(1, (int)len);  // Solicitar 'len' byte del esclavo #1

    while (Wire.available()) { // slave may send less than requested
     int Alarmas_activas1 = Wire.read();    // receive a byte as character
     alarmas_sonoras2(Alarmas_activas1);
    }
    delay(200);
    Wire.beginTransmission(2); // Comunicarse con esclavo #2
    Wire.write('S');
    Wire.endTransmission();
    Wire.requestFrom(2, 1);    // Solicitar 1 byte del esclavo #2

    Wire.requestFrom(2, (int)len);  // Solicitar 'len' byte del esclavo #2
    byte len2 = Wire.read();

    Wire.requestFrom(1, (int)len2);  // Solicitar 'len' byte del esclavo #2

    while (Wire.available()) { // slave may send less than requested
     int Alarmas_activas2 = Wire.read();    // receive a byte as character
     alarmas_sonoras2(Alarmas_activas2);
    }

  */
  //--------------------------------------------------------------------------------------

  byte pipeNum = 0; //Variable para leer que Modulo envio el dato
  byte dataRX = 0; //Variable para guardar el dato recibido

  while (radio.available(&pipeNum)) { //Verificar si hay datos de los esclavos
    radio.read(&dataRX, 1 ); //Se lee un byte, ya que hemos configurado solo en envio de una letra
    //--------------------------------------------------------------------------------------
    if (110 < dataRX < 120) //Letra correspondiente al transmisor 1
    {
      if (dataRX == 111) //Letra correspondiente al transmisor 1 boton a
      {
        valor_ma = 1; //
        delay(100);
      } else if (dataRX == 112) //Letra correspondiente al transmisor 1 boton b
      {
        valor_ma = 2; //
        delay(100);
      } else if (dataRX == 113) //Letra correspondiente al transmisor 1 boton c
      {
        valor_ma = 3; //
        delay(100);
      } else if (dataRX == 114) //Letra correspondiente al transmisor 1 boton d
      {
        valor_ma = 4; //
        delay(100);
      } else if (dataRX == 115) //Letra correspondiente al transmisor 1 boton e
      {
        valor_ma = 5; //
        delay(100);
      }
      else if (dataRX == 116) //Letra correspondiente al transmisor 1 boton f
      {
        valor_ma = 6; //
        delay(100);
      }
      else if (dataRX == 117) //Letra correspondiente al transmisor 1 boton ok
      {
        valor_ma = 7; //
        delay(100);
      }
    }
    //--------------------------------------------------------------------------------------
    if (120 < dataRX < 130) //Letra correspondiente al transmisor 2
    {
      if (dataRX == 121) //Letra correspondiente al transmisor 2 boton a
      {
        valor_mb = 1; //
        delay(100);
      } else if (dataRX == 122) //Letra correspondiente al transmisor 2 boton b
      {
        valor_mb = 2; //
        delay(100);
      } else if (dataRX == 123) //Letra correspondiente al transmisor 2 boton c
      {
        valor_mb = 3; //
        delay(100);
      } else if (dataRX == 124) //Letra correspondiente al transmisor 2 boton d
      {
        valor_mb = 4; //
        delay(100);
      } else if (dataRX == 125) //Letra correspondiente al transmisor 2 boton e
      {
        valor_mb = 5; //
        delay(100);
      } else if (dataRX == 126) //Letra correspondiente al transmisor 2 boton f
      {
        valor_mb = 6; //
        delay(100);
      } else if (dataRX == 127) //Letra correspondiente al transmisor 2 boton ok
      {
        valor_mb = 7; //
        delay(100);
      }
    }
    //--------------------------------------------------------------------------------------
    if (130 < dataRX < 140) //Letra correspondiente al transmisor 3
    {
      if (dataRX == 131) //Letra correspondiente al transmisor 3 boton a
      {
        valor_mc = 1; //
        delay(100);
      } else if (dataRX == 132) //Letra correspondiente al transmisor 3 boton b
      {
        valor_mc = 2; //
        delay(100);
      } else if (dataRX == 133) //Letra correspondiente al transmisor 3 boton c
      {
        valor_mc = 3; //
        delay(100);
      } else if (dataRX == 134) //Letra correspondiente al transmisor 3 boton d
      {
        valor_mc = 4; //
        delay(100);
      } else if (dataRX == 135) //Letra correspondiente al transmisor 3 boton e
      {
        valor_mc = 5; //
        delay(100);
      } else if (dataRX == 136) //Letra correspondiente al transmisor 3 boton f
      {
        valor_mc = 6; //
        delay(100);
      } else if (dataRX == 137) //Letra correspondiente al transmisor 3 boton ok
      {
        valor_mc = 7; //
        delay(100);
      }
    }
    //--------------------------------------------------------------------------------------
    if (140 < dataRX < 150) //Letra correspondiente al transmisor 4
    {
      if (dataRX == 141) //Letra correspondiente al transmisor 4 boton a
      {
        valor_md = 1; //
        delay(100);
      } else if (dataRX == 142) //Letra correspondiente al transmisor 4 boton b
      {
        valor_md = 2; //
        delay(100);
      } else if (dataRX == 143) //Letra correspondiente al transmisor 4 boton c
      {
        valor_md = 3; //
        delay(100);
      } else if (dataRX == 144) //Letra correspondiente al transmisor 4 boton d
      {
        valor_md = 4; //
        delay(100);
      } else if (dataRX == 145) //Letra correspondiente al transmisor 4 boton e
      { valor_md = 5; //
        delay(100);
      } else if (dataRX == 146) //Letra correspondiente al transmisor 4 boton f
      {
        valor_md = 6; //
        delay(100);
      } else if (dataRX == 147) //Letra correspondiente al transmisor 4 boton ok
      {
        valor_md = 7; //
        delay(100);
      }
    }
    //--------------------------------------------------------------------------------------
    if (150 < dataRX < 160) //Letra correspondiente al transmisor 5
    {
      if (dataRX == 151) //Letra correspondiente al transmisor 5 boton a
      {
        valor_me = 1; //
        delay(100);
      } else if (dataRX == 152) //Letra correspondiente al transmisor 5 boton b
      {
        valor_me = 2; //
        delay(100);
      } else if (dataRX == 153) //Letra correspondiente al transmisor 5 boton c
      {
        valor_me = 3; //
        delay(100);
      } else if (dataRX == 154) //Letra correspondiente al transmisor 5 boton d
      {
        valor_me = 4; //
        delay(100);
      } else if (dataRX == 155) //Letra correspondiente al transmisor 5 boton e
      {
        valor_me = 5; //
        delay(100);
      } else if (dataRX == 156) //Letra correspondiente al transmisor 5 boton f
      {
        valor_me = 6; //
        delay(100);
      } else if (dataRX == 157) //Letra correspondiente al transmisor 5 boton ok
      {
        valor_me = 7; //
        delay(100);
      }

    }
    //--------------------------------------------------------------------------------------
    /*
     * * omitido para este maestro
      if (60 < dataRX < 70) //Letra correspondiente al transmisor 6
      {
        if (dataRX == 61) //Letra correspondiente al transmisor 6 boton a
        {
          valor_mf = 1; //
          delay(100);
        } else if (dataRX == 62) //Letra correspondiente al transmisor 6 boton b
        {
          valor_mf = 2; //
          delay(100);
        } else if (dataRX == 63) //Letra correspondiente al transmisor 6 boton c
        {
          valor_mf = 3; //
          delay(100);
        } else if (dataRX == 64) //Letra correspondiente al transmisor 6 boton d
        {
          valor_mf = 4; //
          delay(100);
        } else if (dataRX == 65) //Letra correspondiente al transmisor 6 boton e
        {
          valor_mf = 5; //
          delay(100);
        } else if (dataRX == 66) //Letra correspondiente al transmisor 6 boton f
        {
          valor_mf = 6; //
          delay(100);
        } else if (dataRX == 67) //Letra correspondiente al transmisor 6 boton ok
        {
          valor_mf = 7; //
          delay(100);
        }

      }
    */
    //--------------------------------------------------------------------------------------

  }

  //***************************************************************************************************
  /*--------------------------------------------------------------------
    Verificacion si las maquinas estan operando
    si esta se encuentra activadas se encendera la lamapara ok correspondiente
    --------------------------------------------------------------------*/
  if (Alarma1 == true)
  {
    digitalWrite(Alarm_modo_M1, LOW);
  }
  else
  {
    digitalWrite(Alarm_modo_M1, HIGH);
  }

  if (Alarma2 == true)
  {
    digitalWrite(Alarm_modo_M2, LOW);
  }
  else
  {
    digitalWrite(Alarm_modo_M2, HIGH);
  }

  if (Alarma3 == true)
  {
    digitalWrite(Alarm_modo_M3, LOW);
  }
  else
  {
    digitalWrite(Alarm_modo_M3, HIGH);
  }

  if (Alarma4 == true)
  {
    digitalWrite(Alarm_modo_M4, LOW);
  }
  else
  {
    digitalWrite(Alarm_modo_M4, HIGH);
  }

  if (Alarma5 == true)
  {
    digitalWrite(Alarm_modo_M5, LOW);
  }
  else
  {
    digitalWrite(Alarm_modo_M5, HIGH);
  }

  /*
      omitido para este maestro
      if (Alarma6 == true)
    {
     digitalWrite(Alarm_modo_M6, LOW);
    }
    else
    {
     digitalWrite(Alarm_modo_M6, HIGH);
    }*/

  //***************************************************************************************************
  /*--------------------------------------------------------------------------------------
    Esta linea realiza la fucion de parpadeo de las lamparas
    Si mas de una lampara esta activada al mismo tiempo su frecuencia
    sera la misma.
    No afecta a la lampara de OK de cada maquina.
    --------------------------------------------------------------------------------------*/

  if (millis() > TiempoAhora + periodo) {
    TiempoAhora = millis();
    A_state = !A_state;

  }
  //*****************************************************************************************************

  /*--------------------------------------------------------------------------------------
                                         Maquina 1
    --------------------------------------------------------------------------------------*/
  if (boton_m1a == true) // si esta se encuentra armada  boton A
  {
    if (Atendido_m1a == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M1_a, A_state);//Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M1_a, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m1b == true) // si esta se encuentra armada boton B
  {
    if (Atendido_m1b == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M1_b, A_state);//Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M1_b, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m1c == true) // si esta se encuentra armada
  {
    if (Atendido_m1c == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M1_c, A_state);//Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M1_c, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m1d == true) // si esta se encuentra armada
  {
    if (Atendido_m1d == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M1_d, A_state);//Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M1_d, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m1e == true) // si esta se encuentra armada
  {
    if (Atendido_m1e == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M1_e, A_state);//Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M1_e, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m1f == true) // si esta se encuentra armada
  {
    if (Atendido_m1f == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M1_f, A_state);//Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M1_f, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  // ****************************************************************************************************
  /*--------------------------------------------------------------------------------------
                                          Maquina 2
     --------------------------------------------------------------------------------------*/
  if (boton_m2a == true) // si esta se encuentra armada  boton A
  {
    if (Atendido_m2a == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M2_a, A_state);
      //Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M2_a, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m2b == true) // si esta se encuentra armada boton B
  {
    if (Atendido_m2b == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M2_b, A_state);
      //Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M2_b, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m2c == true) // si esta se encuentra armada
  {
    if (Atendido_m2c == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M2_c, A_state);
      //Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M2_c, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m2d == true) // si esta se encuentra armada
  {
    if (Atendido_m2d == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M2_d, A_state);
      //Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M2_d, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m2e == true) // si esta se encuentra armada
  {
    if (Atendido_m2e == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M2_e, A_state);
      //Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M2_e, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m2e == true) // si esta se encuentra armada
  {
    if (Atendido_m2e == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M2_e, A_state);
      //Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M2_e, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  // ****************************************************************************************************
  /*--------------------------------------------------------------------------------------
                                          Maquina 3
     --------------------------------------------------------------------------------------*/
  if (boton_m3a == true) // si esta se encuentra armada  boton A
  {
    if (Atendido_m3a == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M3_a, A_state);
      //Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M3_a, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m3b == true) // si esta se encuentra armada boton B
  {
    if (Atendido_m3b == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M3_b, A_state);
      //Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M3_b, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m3c == true) // si esta se encuentra armada
  {
    if (Atendido_m3c == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M3_c, A_state);
      //Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M3_c, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m3d == true) // si esta se encuentra armada
  {
    if (Atendido_m3d == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M3_d, A_state);
      //Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M3_d, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m3e == true) // si esta se encuentra armada
  {
    if (Atendido_m3e == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M3_e, A_state);
      //Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M3_e, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m3f == true) // si esta se encuentra armada
  {
    if (Atendido_m3f == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M3_f, A_state);
      //Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M3_f, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  // ****************************************************************************************************
  /*--------------------------------------------------------------------------------------
                                          Maquina 4
     --------------------------------------------------------------------------------------*/
  if (boton_m4a == true) // si esta se encuentra armada  boton A
  {
    if (Atendido_m4a == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M4_a, A_state);
      //Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M4_a, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m4b == true) // si esta se encuentra armada boton B
  {
    if (Atendido_m4b == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M4_b, A_state);
      //Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M4_b, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m4c == true) // si esta se encuentra armada
  {
    if (Atendido_m4c == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M4_c, A_state);
      // delay(4000); //Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M4_c, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m4d == true) // si esta se encuentra armada
  {
    if (Atendido_m4d == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M4_d, A_state);
      //delay(1000); //Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M4_d, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m4e == true) // si esta se encuentra armada
  {
    if (Atendido_m4e == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M4_e, A_state);
      //delay(1000); //Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M4_e, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m4f == true) // si esta se encuentra armada
  {
    if (Atendido_m4f == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M4_f, A_state);
      //delay(1000); //Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M4_f, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  // ****************************************************************************************************
  /*--------------------------------------------------------------------------------------
                                          Maquina 5
     --------------------------------------------------------------------------------------*/
  if (boton_m5a == true) // si esta se encuentra armada  boton A
  {
    if (Atendido_m5a == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M5_a, A_state);
      //Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M5_a, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m5b == true) // si esta se encuentra armada boton B
  {
    if (Atendido_m5b == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M5_b, A_state);
      //Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M5_b, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m5c == true) // si esta se encuentra armada
  {
    if (Atendido_m5c == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M5_c, A_state);
      // delay(5000); //Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M5_c, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m5d == true) // si esta se encuentra armada
  {
    if (Atendido_m5d == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M5_d, A_state);
      //delay(5000); //Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M5_d, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m5e == true) // si esta se encuentra armada
  {
    if (Atendido_m5e == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M5_e, A_state);
      //delay(5000); //Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M5_e, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m5f == true) // si esta se encuentra armada
  {
    if (Atendido_m5f == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M5_f, A_state);
      //delay(5000); //Realiza el parpadeo deacuerdo a la funcion millis()
    }
    else {
      digitalWrite(Alarm_out_M5_f, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  // ****************************************************************************************************
  /*--------------------------------------------------------------------------------------
                                           Maquina 6
                                     omitido para este maestro
      --------------------------------------------------------------------------------------*/
  /*
    if (boton_m6a == true) // si esta se encuentra armada  boton A
    {
     if (Atendido_m6a == false) // si no ha sido atendida pulsando otra vez
     {
       digitalWrite(Alarm_out_M6_a, A_state);
       //Realiza el parpadeo deacuerdo a la funcion millis()
     }
     else {
       digitalWrite(Alarm_out_M6_a, LOW); // deja activada la lampara
     }
    }
    //--------------------------------------------------------------------------------------
    if (boton_m6b == true) // si esta se encuentra armada boton B
    {
     if (Atendido_m6b == false) // si no ha sido atendida pulsando otra vez
     {
       digitalWrite(Alarm_out_M6_b, A_state);
       //Realiza el parpadeo deacuerdo a la funcion millis()
     }
     else {
       digitalWrite(Alarm_out_M6_b, LOW); // deja activada la lampara
     }
    }
    //--------------------------------------------------------------------------------------
    if (boton_m6c == true) // si esta se encuentra armada
    {
     if (Atendido_m6c == false) // si no ha sido atendida pulsando otra vez
     {
       digitalWrite(Alarm_out_M6_c, A_state);
       // delay(5000); //Realiza el parpadeo deacuerdo a la funcion millis()
     }
     else {
       digitalWrite(Alarm_out_M6_c, LOW); // deja activada la lampara
     }
    }
    //--------------------------------------------------------------------------------------
    if (boton_m6d == true) // si esta se encuentra armada
    {
     if (Atendido_m6d == false) // si no ha sido atendida pulsando otra vez
     {
       digitalWrite(Alarm_out_M6_d, A_state);
       //delay(5000); //Realiza el parpadeo deacuerdo a la funcion millis()
     }
     else {
       digitalWrite(Alarm_out_M6_d, LOW); // deja activada la lampara
     }
    }
    //--------------------------------------------------------------------------------------
    if (boton_m6e == true) // si esta se encuentra armada
    {
     if (Atendido_m6e == false) // si no ha sido atendida pulsando otra vez
     {
       digitalWrite(Alarm_out_M6_e, A_state);
       //delay(5000); //Realiza el parpadeo deacuerdo a la funcion millis()
     }
     else {
       digitalWrite(Alarm_out_M6_e, LOW); // deja activada la lampara
     }
    }
    //--------------------------------------------------------------------------------------
    if (boton_m6f == true) // si esta se encuentra armada
    {
     if (Atendido_m6f == false) // si no ha sido atendida pulsando otra vez
     {
       digitalWrite(Alarm_out_M6_f, A_state);
       //delay(5000); //Realiza el parpadeo deacuerdo a la funcion millis()
     }
     else {
       digitalWrite(Alarm_out_M6_f, LOW); // deja activada la lampara
     }
    }
  */
  //--------------------------------------------------------------------------------------

  // ****************************************************************************************************
  //*********************************Rutinas de interrupcion*********************************************
  // ****************************************************************************************************




  // ****************************************************************************************************
  /*--------------------------------------------------------------------------------------
                                          Maquina 1
     --------------------------------------------------------------------------------------*/
  if ((boton_m1a == false) && (valor_ma == 1) /* && (Alarma1 == true) */) //Activar alarma mantenimiento con  melodia e intermirente
  {
    boton_m1a = true;
    Atendido_m1a = false;
    delay(200);
    valor_ma = 0;
    alarmas_sonoras (1);

  }
  if ((Atendido_m1a == false)  && (boton_m1a == true) && (valor_ma == 1)) //Alarma atendida,detener musica e inidcador fijo
  {
    Atendido_m1a = true;
    delay(200);
    valor_ma = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m1a == true) && (boton_m1a == true) && (valor_ma == 1)) //apagar alarma
  {
    Atendido_m1a = false;
    boton_m1a = false;
    digitalWrite(Alarm_out_M1_a, HIGH);
    delay(200);
    valor_ma = 0;
  }

  //--------------------------------------------------------------------------------------

  if ((boton_m1b == false) && (valor_ma == 2))  //Activar alarma produccion con  melodia e intermirente
  {
    boton_m1b = true;
    Atendido_m1b = false;
    delay(200);
    valor_ma = 0;
    alarmas_sonoras (2);
  }

  if ((Atendido_m1b == false) && (boton_m1b == true) && (valor_ma == 2)) //Alarma atendida,detener musica e inidcador fijo
  {
    Atendido_m1b = true;
    delay(200);
    valor_ma = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m1b == true) && (boton_m1b == true) && (valor_ma == 2)) //apagar alarma
  {
    Atendido_m1b = false;
    boton_m1b = false;
    digitalWrite(Alarm_out_M1_b, HIGH);
    delay(200);
    valor_ma = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m1c == false) && (valor_ma == 3))//Activar alarma materiales con  melodia e intermirente
  {
    boton_m1c = true;
    Atendido_m1c = false;
    delay(200);
    valor_ma = 0;
    alarmas_sonoras (3);

  }

  if ((Atendido_m1c == false) && (boton_m1c == true) && (valor_ma == 3)) //
  {
    Atendido_m1c = true;
    delay(200);
    valor_ma = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m1c == true) && (boton_m1c == true) && (valor_ma == 3)) //
  {
    Atendido_m1c = false;
    boton_m1c = false;
    digitalWrite(Alarm_out_M1_c, HIGH);
    delay(200);
    valor_ma = 0;
  }

  //--------------------------------------------------------------------------------------
  if ((boton_m1d == false) && (valor_ma == 4))//Activar alarma cambio fr moldes con  melodia e intermirente
  {
    boton_m1d = true;
    Atendido_m1d = false;
    delay(200);
    valor_ma = 0;
    alarmas_sonoras (4);
  }

  if ((Atendido_m1d == false) && (boton_m1d == true) && (valor_ma == 4)) //
  {
    Atendido_m1d = true;
    delay(200);
    valor_ma = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m1d == true) && (boton_m1d == true) && (valor_ma == 4)) //
  {
    Atendido_m1d = false;
    boton_m1d = false;
    digitalWrite(Alarm_out_M1_d, HIGH);
    delay(200);
    valor_ma = 0;
  }
  //--------------------------------------------------------------------------------------
  if ((boton_m1e == false) && (valor_ma == 5))//Activar alarma cambio fr moldes con  melodia e intermirente
  {
    boton_m1e = true;
    Atendido_m1e = false;
    delay(200);
    valor_ma = 0;
    alarmas_sonoras (5);
  }

  if ((Atendido_m1e == false) && (boton_m1e == true) && (valor_ma == 5)) //
  {
    Atendido_m1e = true;
    delay(200);
    valor_ma = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m1e == true) && (boton_m1e == true) && (valor_ma == 5)) //
  {
    Atendido_m1e = false;
    boton_m1e = false;
    digitalWrite(Alarm_out_M1_e, HIGH);
    delay(200);
    valor_ma = 0;
  }
  //--------------------------------------------------------------------------------------
  if ((boton_m1f == false) && (valor_ma == 6))//Activar alarma cambio fr moldes con  melodia e intermirente
  {
    boton_m1f = true;
    Atendido_m1f = false;
    delay(200);
    valor_ma = 0;
    alarmas_sonoras (6);
  }

  if ((Atendido_m1f == false) && (boton_m1f == true) && (valor_ma == 6)) //
  {
    Atendido_m1f = true;
    delay(200);
    valor_ma = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m1f == true) && (boton_m1f == true) && (valor_ma == 6)) //
  {
    Atendido_m1f = false;
    boton_m1f = false;
    digitalWrite(Alarm_out_M1_f, HIGH);
    delay(200);
    valor_ma = 0;
  }
  //--------------------------------------------------------------------------------------
  if (valor_ma == 7)
  {
    Alarma1 = !Alarma1; //cambia el  estado de la Alarma
    delay(200);
    valor_ma = 0;
  }
  //--------------------------------------------------------------------------------------
  // ****************************************************************************************************
  /*--------------------------------------------------------------------------------------
                                           Maquina 2
      --------------------------------------------------------------------------------------*/

  if ((boton_m2a == false) &&  (valor_mb == 1))//Activar alarma mantenimiento con  melodia e intermirente
  {
    boton_m2a = true;
    Atendido_m2a = false;
    delay(200);
    valor_mb = 0;
    alarmas_sonoras (1);
  }

  if ((Atendido_m2a == false) && (boton_m2a == true) && (valor_mb == 1)) //
  {
    Atendido_m2a = true;
    delay(200);
    valor_mb = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m2a == true) && (boton_m2a == true) && (valor_mb == 1)) //
  {
    Atendido_m2a = false;
    boton_m2a = false;
    digitalWrite(Alarm_out_M2_a, HIGH);
    delay(200);
    valor_mb = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m2b == false) && (valor_mb == 2)) //Activar alarma produccion con  melodia e intermirente
  {
    boton_m2b = true;
    Atendido_m2b = false;
    delay(200);
    valor_mb = 0;
    alarmas_sonoras (2);
  }

  if ((Atendido_m2b == false) && (boton_m2b == true) && (valor_mb == 2)) //
  {
    Atendido_m2b = true;
    delay(200);
    valor_mb = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m2b == true) && (boton_m2b == true) && (valor_mb == 2)) //
  {
    Atendido_m2b = false;
    boton_m2b = false;
    digitalWrite(Alarm_out_M2_b, HIGH);
    delay(200);
    valor_mb = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m2c == false) && (valor_mb == 3))//
  {
    boton_m2c = true;
    Atendido_m2c = false;
    delay(200);
    valor_mb = 0;
    alarmas_sonoras (3);
  }

  if ((Atendido_m2c == false) && (boton_m2c == true) && (valor_mb == 3)) //
  {
    Atendido_m2c = true;
    delay(200);
    valor_mb = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m2c == true) && (boton_m2c == true) && (valor_mb == 3)) //
  {
    Atendido_m2c = false;
    boton_m2c = false;
    digitalWrite(Alarm_out_M2_c, HIGH);
    delay(200);
    valor_mb = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m2d == false) && (valor_mb == 4)) //
  {
    boton_m2d = true;
    Atendido_m2d = false;
    delay(200);
    valor_mb = 0;
    alarmas_sonoras (4);
  }

  if ((Atendido_m2d == false) && (boton_m2d == true) && (valor_mb == 4)) //
  {
    Atendido_m2d = true;
    delay(200);
    valor_mb = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m2d == true) && (boton_m2d == true) && (valor_mb == 4)) //
  {
    Atendido_m2d = false;
    boton_m2d = false;
    digitalWrite(Alarm_out_M2_d, HIGH);
    delay(200);
    valor_mb = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m2e == false) && (valor_mb == 5)) //
  {
    boton_m2e = true;
    Atendido_m2e = false;
    delay(200);
    valor_mb = 0;
    alarmas_sonoras (5);
  }

  if ((Atendido_m2e == false) && (boton_m2e == true) && (valor_mb == 5)) //
  {
    Atendido_m2e = true;
    delay(200);
    valor_mb = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m2e == true) && (boton_m2e == true) && (valor_mb == 5)) //
  {
    Atendido_m2e = false;
    boton_m2e = false;
    digitalWrite(Alarm_out_M2_e, HIGH);
    delay(200);
    valor_mb = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m2f == false) && (valor_mb == 6)) //
  {
    boton_m2f = true;
    Atendido_m2f = false;
    delay(200);
    valor_mb = 0;
    alarmas_sonoras (6);
  }

  if ((Atendido_m2f == false) && (boton_m2f == true) && (valor_mb == 6)) //
  {
    Atendido_m2f = true;
    delay(200);
    valor_mb = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m2f == true) && (boton_m2f == true) && (valor_mb == 6)) //
  {
    Atendido_m2f = false;
    boton_m2f = false;
    digitalWrite(Alarm_out_M2_f, HIGH);
    delay(200);
    valor_mb = 0;
  }
  //--------------------------------------------------------------------------------------

  if (valor_mb == 7)
  {
    Alarma2 = !Alarma2; //cambia el  estado de la Alarma
    delay(200);
    valor_mb = 0;
  }
  //--------------------------------------------------------------------------------------
  // ****************************************************************************************************
  /*--------------------------------------------------------------------------------------
                                           Maquina 3
      --------------------------------------------------------------------------------------*/

  if ((boton_m3a == false) &&  (valor_mc == 1))//Activar alarma mantenimiento con  melodia e intermirente
  {
    boton_m3a = true;
    Atendido_m3a = false;
    delay(200);
    valor_mc = 0;
    alarmas_sonoras (1);

  }

  if ((Atendido_m3a == false) && (boton_m3a == true) && (valor_mc == 1)) //
  {
    Atendido_m3a = true;
    delay(200);
    valor_mc = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m3a == true) && (boton_m3a == true) && (valor_mc == 1)) //
  {
    Atendido_m3a = false;
    boton_m3a = false;
    digitalWrite(Alarm_out_M3_a, HIGH);
    delay(200);
    valor_mc = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m3b == false) && (valor_mc == 2)) //Activar alarma produccion con  melodia e intermirente
  {
    boton_m3b = true;
    Atendido_m3b = false;
    delay(200);
    valor_mc = 0;
    alarmas_sonoras (2);
  }

  if ((Atendido_m3b == false) && (boton_m3b == true) && (valor_mc == 2)) //
  {
    Atendido_m3b = true;
    delay(200);
    valor_mc = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m3b == true) && (boton_m3b == true) && (valor_mc == 2)) //
  {
    Atendido_m3b = false;
    boton_m3b = false;
    digitalWrite(Alarm_out_M3_b, HIGH);
    delay(200);
    valor_mc = 0;
  } //--------------------------------------------------------------------------------------

  if ((boton_m3c == false) && (valor_mc == 3))//
  {
    boton_m3c = true;
    Atendido_m3c = false;
    delay(200);
    valor_mc = 0;
    alarmas_sonoras (3);
  }

  if ((Atendido_m3c == false) && (boton_m3c == true) && (valor_mc == 3)) //
  {
    Atendido_m3c = true;
    delay(200);
    valor_mc = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m3c == true) && (boton_m3c == true) && (valor_mc == 3)) //
  {
    Atendido_m3c = false;
    boton_m3c = false;
    digitalWrite(Alarm_out_M3_c, HIGH);
    delay(200);
    valor_mc = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m3d == false) && (valor_mc == 4)) //
  {
    boton_m3d = true;
    Atendido_m3d = false;
    delay(200);
    valor_mc = 0;
    alarmas_sonoras (4);
  }

  if ((Atendido_m3d == false) && (boton_m3d == true) && (valor_mc == 4)) //
  {
    Atendido_m3d = true;
    delay(200);
    valor_mc = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m3d == true) && (boton_m3d == true) && (valor_mc == 4)) //
  {
    Atendido_m3d = false;
    boton_m3d = false;
    digitalWrite(Alarm_out_M3_d, HIGH);
    delay(200);
    valor_mc = 0;

  }
  //--------------------------------------------------------------------------------------

  if ((boton_m3e == false) && (valor_mc == 5)) //
  {
    boton_m3e = true;
    Atendido_m3e = false;
    delay(200);
    valor_mc = 0;
    alarmas_sonoras (5);
  }

  if ((Atendido_m3e == false) && (boton_m3e == true) && (valor_mc == 5)) //
  {
    Atendido_m3e = true;
    delay(200);
    valor_mc = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m3e == true) && (boton_m3e == true) && (valor_mc == 5)) //
  {
    Atendido_m3e = false;
    boton_m3e = false;
    digitalWrite(Alarm_out_M3_e, HIGH);
    delay(200);
    valor_mc = 0;

  }
  //--------------------------------------------------------------------------------------

  if ((boton_m3f == false) && (valor_mc == 6)) //
  {
    boton_m3f = true;
    Atendido_m3f = false;
    delay(200);
    valor_mc = 0;
    alarmas_sonoras (6);
  }

  if ((Atendido_m3f == false) && (boton_m3f == true) && (valor_mc == 6)) //
  {
    Atendido_m3f = true;
    delay(200);
    valor_mc = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m3f == true) && (boton_m3f == true) && (valor_mc == 6)) //
  {
    Atendido_m3f = false;
    boton_m3f = false;
    digitalWrite(Alarm_out_M3_f, HIGH);
    delay(200);
    valor_mc = 0;

  }
  //--------------------------------------------------------------------------------------

  if (valor_mc == 7)
  {
    Alarma3 = !Alarma3; //cambia el  estado de la Alarma
    delay(200);
    valor_mc = 0;
  }
  //--------------------------------------------------------------------------------------
  // ****************************************************************************************************
  /*--------------------------------------------------------------------------------------
                                           Maquina 4
      --------------------------------------------------------------------------------------*/
  if ((boton_m4a == false) &&  (valor_md == 1))//Activar alarma mantenimiento con  melodia e intermirente
  {
    boton_m4a = true;
    Atendido_m4a = false;
    delay(200);
    valor_md = 0;
    alarmas_sonoras (1);
  }

  if ((Atendido_m4a == false) && (boton_m4a == true) && (valor_md == 1)) //
  {
    Atendido_m4a = true;
    delay(200);
    valor_md = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m4a == true) && (boton_m4a == true) && (valor_md == 1)) //
  {
    Atendido_m4a = false;
    boton_m4a = false;
    digitalWrite(Alarm_out_M4_a, HIGH);
    delay(200);
    valor_md = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m4b == false) && (valor_md == 2)) //Activar alarma produccion con  melodia e intermirente
  {
    boton_m4b = true;
    Atendido_m4b = false;
    delay(200);
    valor_md = 0;
    alarmas_sonoras (2);
  }

  if ((Atendido_m4b == false) && (boton_m4b == true) && (valor_md == 2)) //
  {
    Atendido_m4b = true;
    delay(200);
    valor_md = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m4b == true) && (boton_m4b == true) && (valor_md == 2)) //
  {
    Atendido_m4b = false;
    boton_m4b = false;
    digitalWrite(Alarm_out_M4_b, HIGH);
    delay(200);
    valor_md = 0;
  } //--------------------------------------------------------------------------------------

  if ((boton_m4c == false) && (valor_md == 3))//
  {
    boton_m4c = true;
    Atendido_m4c = false;
    delay(200);
    valor_md = 0;
    alarmas_sonoras (3);
  }

  if ((Atendido_m4c == false)  && (boton_m4c == true) && (valor_md == 3)) //
  {
    Atendido_m4c = true;
    delay(200);
    valor_md = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m4c == true)  && (boton_m4c == true) && (valor_md == 3)) //
  {
    Atendido_m4c = false;
    boton_m4c = false;
    digitalWrite(Alarm_out_M4_c, HIGH);
    delay(200);
    valor_md = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m4d == false) && (valor_md == 4)) //
  {
    boton_m4d = true;
    Atendido_m4d = false;
    delay(200);
    valor_md = 0;
    alarmas_sonoras (4);
  }

  if ((Atendido_m4d == false) && (boton_m4d == true) && (valor_md == 4)) //
  {
    Atendido_m4d = true;
    delay(200);
    valor_md = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m4d == true) && (boton_m4d == true) && (valor_md == 4)) //
  {
    Atendido_m4d = false;
    boton_m4d = false;
    digitalWrite(Alarm_out_M4_d, HIGH);
    delay(200);
    valor_md = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m4e == false) && (valor_md == 5)) //
  {
    boton_m4e = true;
    Atendido_m4e = false;
    delay(200);
    valor_md = 0;
    alarmas_sonoras (5);
  }

  if ((Atendido_m4e == false) && (boton_m4e == true) && (valor_md == 5)) //
  {
    Atendido_m4e = true;
    delay(200);
    valor_md = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m4e == true) && (boton_m4e == true) && (valor_md == 5)) //
  {
    Atendido_m4e = false;
    boton_m4e = false;
    digitalWrite(Alarm_out_M4_e, HIGH);
    delay(200);
    valor_md = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m4f == false) && (valor_md == 6)) //
  {
    boton_m4f = true;
    Atendido_m4f = false;
    delay(200);
    valor_md = 0;
    alarmas_sonoras (6);
  }

  if ((Atendido_m4f == false) && (boton_m4f == true) && (valor_md == 6)) //
  {
    Atendido_m4f = true;
    delay(200);
    valor_md = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m4f == true) && (boton_m4f == true) && (valor_md == 6)) //
  {
    Atendido_m4f = false;
    boton_m4f = false;
    digitalWrite(Alarm_out_M4_f, HIGH);
    delay(200);
    valor_md = 0;
  }
  //--------------------------------------------------------------------------------------
  if (valor_md == 7)
  {
    Alarma4 = !Alarma4; //cambia el  estado de la Alarma
    delay(200);
    valor_md = 0;
  }
  //--------------------------------------------------------------------------------------
  // ****************************************************************************************************
  /*--------------------------------------------------------------------------------------
                                           Maquina 5
      --------------------------------------------------------------------------------------*/

  if ((boton_m5a == false) &&  (valor_me == 1))//Activar alarma mantenimiento con  melodia e intermirente
  {
    boton_m5a = true;
    Atendido_m5a = false;
    delay(200);
    valor_me = 0;
    alarmas_sonoras (1);
  }

  if ((Atendido_m5a == false) && (boton_m5a == true) && (valor_me == 1)) //
  {
    Atendido_m5a = true;
    delay(200);
    valor_me = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m5a == true) && (boton_m5a == true) && (valor_me == 1)) //
  {
    Atendido_m5a = false;
    boton_m5a = false;
    digitalWrite(Alarm_out_M5_a, HIGH);
    delay(200);
    valor_me = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m5b == false) && (valor_me == 2)) //Activar alarma produccion con  melodia e intermirente
  {
    boton_m5b = true;
    Atendido_m5b = false;
    delay(200);
    valor_me = 0;
    alarmas_sonoras (2);
  }

  if ((Atendido_m5b == false) && (boton_m5b == true) && (valor_me == 2)) //
  {
    Atendido_m5b = true;
    delay(200);
    valor_me = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m5b == true) && (boton_m5b == true) && (valor_me == 2)) //
  {
    Atendido_m5b = false;
    boton_m5b = false;
    digitalWrite(Alarm_out_M5_b, HIGH);
    delay(200);
    valor_me = 0;
  } //--------------------------------------------------------------------------------------

  if ((boton_m5c == false) && (valor_me == 3))//
  {
    boton_m5c = true;
    Atendido_m5c = false;
    delay(200);
    valor_me = 0;
    alarmas_sonoras (3);
  }

  if ((Atendido_m5c == false) && (boton_m5c == true) && (valor_me == 3)) //
  {
    Atendido_m5c = true;
    delay(200);
    valor_me = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m5c == true) && (boton_m5c == true) && (valor_me == 3)) //
  {

    Atendido_m5c = false;
    boton_m5c = false;
    digitalWrite(Alarm_out_M5_c, HIGH);
    delay(200);
    valor_me = 0;
  }

  //--------------------------------------------------------------------------------------

  if ((boton_m5d == false) && (valor_me == 4)) //
  {
    boton_m5d = true;
    Atendido_m5d = false;
    delay(200);
    valor_me = 0;
    alarmas_sonoras (4);
  }

  if ((Atendido_m5d == false) && (boton_m5d == true) && (valor_me == 4)) //
  {
    Atendido_m5d = true;
    delay(200);
    valor_me = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m5d == true) && (boton_m5d == true) && (valor_me == 4)) //
  {
    Atendido_m5d = false;
    boton_m5d = false;
    digitalWrite(Alarm_out_M5_d, HIGH);
    delay(200);
    valor_me = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m5e == false) && (valor_me == 5)) //
  {
    boton_m5e = true;
    Atendido_m5e = false;
    delay(200);
    valor_me = 0;
    alarmas_sonoras (5);
  }

  if ((Atendido_m5e == false) && (boton_m5e == true) && (valor_me == 5)) //
  {
    Atendido_m5e = true;
    delay(200);
    valor_me = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m5e == true) && (boton_m5e == true) && (valor_me == 5)) //
  {
    Atendido_m5e = false;
    boton_m5e = false;
    digitalWrite(Alarm_out_M5_e, HIGH);
    delay(200);
    valor_me = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m5f == false) && (valor_me == 6)) //
  {
    boton_m5f = true;
    Atendido_m5f = false;
    delay(200);
    valor_me = 0;
    alarmas_sonoras (6);
  }

  if ((Atendido_m5f == false) && (boton_m5f == true) && (valor_me == 6)) //
  {
    Atendido_m5f = true;
    delay(200);
    valor_me = 0;
    alarmas_sonoras2(0);
  }

  if ((Atendido_m5f == true) && (boton_m5f == true) && (valor_me == 6)) //
  {
    Atendido_m5f = false;
    boton_m5f = false;
    digitalWrite(Alarm_out_M5_f, HIGH);
    delay(200);
    valor_me = 0;
  }
  //--------------------------------------------------------------------------------------
  if (valor_me == 7)
  {
    Alarma5 = !Alarma5; //cambia el  estado de la Alarma
    delay(200);
    valor_me = 0;
  }
  //--------------------------------------------------------------------------------------

  // ****************************************************************************************************
  /*--------------------------------------------------------------------------------------
                                           Maquina 6
      --------------------------------------------------------------------------------------*/
  /*
                                       omitido para este maestro
    if ((boton_m6a == false) &&  (valor_mf == 1))//Activar alarma mantenimiento con  melodia e intermirente
    {
      boton_m6a = true;
      Atendido_m6a = false;
      delay(200);
      valor_mf = 0;
      alarmas_sonoras (1);
    }

    if ((Atendido_m6a == false) && (boton_m6a == true) && (valor_mf == 1)) //
    {
      Atendido_m6a = true;
      delay(200);
      valor_mf = 0;
      alarmas_sonoras2(0);
    }


    if ((Atendido_m6a == true) && (boton_m6a == true) && (valor_mf == 1)) //
    {
      Atendido_m6a = false;
      boton_m6a = false;
      digitalWrite(Alarm_out_M6_a, HIGH);
      delay(200);
      valor_mf = 0;
    }

    //--------------------------------------------------------------------------------------

    if ((boton_m6b == false) && (valor_mf == 2)) //Activar alarma produccion con  melodia e intermirente
    {
      boton_m6b = true;
      Atendido_m6b = false;
      delay(200);
      valor_mf = 0;
      alarmas_sonoras (2);
    }

    if ((Atendido_m6b == false) && (boton_m6b == true) && (valor_mf == 2)) //
    {
      Atendido_m6b = true;
      delay(200);
      valor_mf = 0;
      alarmas_sonoras2(0);
    }

    if ((Atendido_m6b == true) && (boton_m6b == true) && (valor_mf == 2)) //
    {
      Atendido_m6b = false;
      boton_m6b = false;
      digitalWrite(Alarm_out_M6_b, HIGH);
      delay(200);
      valor_mf = 0;
    }
    //--------------------------------------------------------------------------------------

    if ((boton_m6c == false) && (valor_mf == 3))//
    {
      boton_m6c = true;
      Atendido_m6c = false;
      delay(200);
      valor_mf = 0;
      alarmas_sonoras (3);
    }

    if ((Atendido_m6c == false) && (boton_m6c == true) && (valor_mf == 3)) //
    {
      Atendido_m6c = true;
      delay(200);
      valor_mf = 0;
      alarmas_sonoras2(0);
    }

    if ((Atendido_m6c == true) && (boton_m6c == true) && (valor_mf == 3)) //
    {
      Atendido_m6c = false;
      boton_m6c = false;
      digitalWrite(Alarm_out_M6_c, HIGH);
      delay(200);
      valor_mf = 0;
    }

    //--------------------------------------------------------------------------------------

    if ((boton_m6d == false) && (valor_mf == 4)) //
    {
      boton_m6d = true;
      Atendido_m6d = false;
      delay(200);
      valor_mf = 0;
      alarmas_sonoras (4);
    }

    if ((Atendido_m6d == false) && (boton_m6d == true) && (valor_mf == 4)) //
    {
      Atendido_m6d = true;
      delay(200);
      valor_mf = 0;
      alarmas_sonoras2(0);
    }

    if ((Atendido_m6d == true) && (boton_m6d == true) && (valor_mf == 4)) //
    {
      Atendido_m6d = false;
      boton_m6d = false;
      digitalWrite(Alarm_out_M6_d, HIGH);
      delay(200);
      valor_mf = 0;
    }
    //--------------------------------------------------------------------------------------

    if ((boton_m6e == false) && (valor_mf == 5)) //
    {
      boton_m6e = true;
      Atendido_m6e = false;
      delay(200);
      valor_mf = 0;
      alarmas_sonoras (5);
    }

    if ((Atendido_m6e == false) && (boton_m6e == true) && (valor_mf == 5)) //
    {
      Atendido_m6e = true;
      delay(200);
      valor_mf = 0;
      alarmas_sonoras2(0);
    }

    if ((Atendido_m6e == true) && (boton_m6e == true) && (valor_mf == 5)) //
    {
      Atendido_m6e = false;
      boton_m6e = false;
      digitalWrite(Alarm_out_M6_e, HIGH);
      delay(200);
      valor_mf = 0;
    }
    //--------------------------------------------------------------------------------------

    if ((boton_m6f == false) && (valor_mf == 6)) //
    {
      boton_m6f = true;
      Atendido_m6f = false;
      delay(200);
      valor_mf = 0;
      alarmas_sonoras (6);
    }

    if ((Atendido_m6f == false) && (boton_m6f == true) && (valor_mf == 6)) //
    {
      Atendido_m6f = true;
      delay(200);
      valor_mf = 0;
      alarmas_sonoras2(0);
    }

    if ((Atendido_m6f == true) && (boton_m6f == true) && (valor_mf == 6)) //
    {
      Atendido_m6f = false;
      boton_m6f = false;
      digitalWrite(Alarm_out_M6_f, HIGH);
      delay(200);
      valor_mf = 0;
    }
    //--------------------------------------------------------------------------------------
    if (valor_mf == 7)
    {
      Alarma6 = !Alarma6; //cambia el  estado de la Alarma
      delay(200);
      valor_mf = 0;
    }
  */
  //--------------------------------------------------------------------------------------
  // ****************************************************************************************************

  /*
      omitido para este maestro
      if (myDFPlayer.available()) {
     printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
    }*/
  // ****************************************************************************************************
} //cierre de loop

// ****************************************************************************************************
/*
   omitido para este maestro
   void printDetail(uint8_t type, int value) {
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      //  alarmas_sonoras2(0);
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  }*/
// ****************************************************************************************************

// ****************************************************************************************************
void alarmas_sonoras (int play)
{
  if (play == 1)
  {
    Alarma_activa = 1;
  }

  else  if (play == 2)
  {
    Alarma_activa = 2;
  }

  else  if (play == 3)
  {
    Alarma_activa = 3;
  }
  else  if (play == 4)
  {
    Alarma_activa = 4;
  }
  else  if (play == 5)
  {
    Alarma_activa = 5;
  }
  else  if (play == 6)
  {
    Alarma_activa = 6;
  }
}


// ********************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************

void alarmas_sonoras2(int activas)
{
  if (((Atendido_m1a == false) && (boton_m1a == true)) || ((Atendido_m2a == false) && (boton_m2a == true)) || ((Atendido_m3a == false) && (boton_m3a == true)) || ((Atendido_m4a == false) && (boton_m4a == true)) || ((Atendido_m5a == false) && (boton_m5a == true)))/* || ((Atendido_m6a == false) && (boton_m6a == true)) || ((activas == 1) ) || ((activas == 11)))*/
  {
    alarmas_sonoras (1);
  }
  else  if (((Atendido_m1b == false) && (boton_m1b == true)) || ((Atendido_m2b == false) && (boton_m2b == true)) || ((Atendido_m3b == false) && (boton_m3b == true)) || ((Atendido_m4b == false) && (boton_m4b == true)) || ((Atendido_m5b == false) && (boton_m5b == true)))/* || ((Atendido_m6b == false) && (boton_m6b == true)) || ((activas == 2) ) || ((activas == 12)))*/
  {
    alarmas_sonoras (2);

  }
  else  if (((Atendido_m1c == false) && (boton_m1c == true)) || ((Atendido_m2c == false) && (boton_m2c == true)) || ((Atendido_m3c == false) && (boton_m3c == true)) || ((Atendido_m4c == false) && (boton_m4c == true)) || ((Atendido_m5c == false) && (boton_m5c == true)))/* || ((Atendido_m6c == false) && (boton_m6c == true)) || ((activas == 3) ) || ((activas == 13)))*/
  {
    alarmas_sonoras (3);

  }
  else  if (((Atendido_m1d == false) && (boton_m1d == true)) || ((Atendido_m2d == false) && (boton_m2d == true)) || ((Atendido_m3d == false) && (boton_m3d == true)) || ((Atendido_m4d == false) && (boton_m4d == true)) || ((Atendido_m5d == false) && (boton_m5d == true)))/* || ((Atendido_m6d == false) && (boton_m6d == true)) || ((activas == 4) ) || ((activas == 14)))*/
  {
    alarmas_sonoras (4);

  }
  else  if (((Atendido_m1e == false) && (boton_m1e == true)) || ((Atendido_m2e == false) && (boton_m2e == true)) || ((Atendido_m3e == false) && (boton_m3e == true)) || ((Atendido_m4e == false) && (boton_m4e == true)) || ((Atendido_m5e == false) && (boton_m5e == true))) /*|| ((Atendido_m6e == false) && (boton_m6e == true)) || ((activas == 5) ) || ((activas == 15)))*/
  {
    alarmas_sonoras (5);

  }
  else  if (((Atendido_m1f == false) && (boton_m1f == true)) || ((Atendido_m2f == false) && (boton_m2f == true)) || ((Atendido_m3f == false) && (boton_m3f == true)) || ((Atendido_m4f == false) && (boton_m4f == true)) || ((Atendido_m5f == false) && (boton_m5f == true))) /*|| ((Atendido_m6f == false) && (boton_m6f == true)) || ((activas == 6) ) || ((activas == 16)))*/
  {
    alarmas_sonoras (6);

  }

  else
  {
    //  myDFPlayer.sleep();
    Alarma_activa = 0;
  }

}
// ********************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************



// ****************************************************************************************************
// function that executes whenever data is requested by master
void eventoSolicitud() {
  Wire.write(Alarma_activa);
  Alarma_activa = 0;
}
// ****************************************************************************************************
