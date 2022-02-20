/*  ----------------------------------------------------------------
  LucaDg
  AUTOMAQ
  Codigo para la configuracion MultiCeiver con NRF24L01.
  Codigo del PRX (Receptor Maestro y controlador de las alarmas)
  Codigo arduino mega sin dfplayer COMUNICACION I2C escalvo 2
  --------------------------------------------------------------------
*/
//Librerias para el control del modulo nRF
#include <SPI.h> // Libreria de SPI para la comunicacion con el modulo nRF24L01
#include <nRF24L01.h>
#include <RF24.h>
//--------------------------------------------------------------------------------------
//Librerias para comunicacion 12c
#include <Wire.h>
//***************************************************************************************************
RF24 radio(8, 9);//Declaracion de los pines de control CE y CSN para el modulo, se define "radio"
//***************************************************************************************************

//Se crean las 6 direcciones posibles para las Pipes P0 - P5;
//Las direcciones es un numero de 40bits para este caso se usa uint_64_t de 64bits
const uint64_t direccion[] = {0x7838787879LL, 0xC3B4B5B6F9LL, 0xC3B4B5B6C9LL, 0xC3B4B5B6A9LL, 0xC3B4B5B609LL, 0xC3B4B5B699LL };
//                            En esta parte LL significa LongLong para asegurar el dato de 64bits

//***************************************************************************************************
//configuracion de los pines de salidas
int Alarm_out_M1_a = 22; //Pin de salida de la alarma maquina 1 boton a conectar NA del led al relay
int Alarm_out_M1_b = 23; //Pin de salida de la alarma maquina 1 boton b conectar NA del led al relay
int Alarm_out_M1_c = 24; //Pin de salida de la alarma maquina 1 boton c conectar NA del led al relay
int Alarm_out_M1_d = 25; //Pin de salida de la alarma maquina 1 boton d conectar NA del led al relay
int Alarm_out_M1_e = 26; //Pin de salida de la alarma maquina 1 boton c conectar NA del led al relay
int Alarm_out_M1_f = 27; //Pin de salida de la alarma maquina 1 boton d conectar NA del led al relay
int Lampara_ok_M1 = 28; //Pin indicador de alarma ok conectar NA del led al relay
//--------------------------------------------------------------------------------------
int Alarm_out_M2_a = 29; //Pin de salida de la alarma maquina 2 boton a conectar NA del led al relay
int Alarm_out_M2_b = 30; //Pin de salida de la alarma maquina 2 boton b conectar NA del led al relay
int Alarm_out_M2_c = 31; //Pin de salida de la alarma maquina 2 boton c conectar NA del led al relay
int Alarm_out_M2_d = 32; //Pin de salida de la alarma maquina 2 boton d conectar NA del led al relay
int Alarm_out_M2_e = 33; //Pin de salida de la alarma maquina 2 boton c conectar NA del led al relay
int Alarm_out_M2_f = 34; //Pin de salida de la alarma maquina 2 boton d conectar NA del led al relay
int Lampara_ok_M2 = 35; //Pin indicador de alarma ok conectar NA del led al relay
//--------------------------------------------------------------------------------------
int Alarm_out_M3_a = 36; //Pin de salida de la alarma maquina 3 boton a conectar NA del led al relay
int Alarm_out_M3_b = 37; //Pin de salida de la alarma maquina 3 boton b conectar NA del led al relay
int Alarm_out_M3_c = 38; //Pin de salida de la alarma maquina 3 boton c conectar NA del led al relay
int Alarm_out_M3_d = 39; //Pin de salida de la alarma maquina 3 boton d conectar NA del led al relay
int Alarm_out_M3_e = 40; //Pin de salida de la alarma maquina 3 boton c conectar NA del led al relay
int Alarm_out_M3_f = 41; //Pin de salida de la alarma maquina 3 boton d conectar NA del led al relay
int Lampara_ok_M3 = 42; //Pin indicador de alarma ok conectar NA del led al relay
//--------------------------------------------------------------------------------------
int Alarm_out_M4_a = 43; //Pin de salida de la alarma maquina 4 boton a conectar NA del led al relay
int Alarm_out_M4_b = 44; //Pin de salida de la alarma maquina 4 boton b conectar NA del led al relay
int Alarm_out_M4_c = 45; //Pin de salida de la alarma maquina 4 boton c conectar NA del led al relay
int Alarm_out_M4_d = 46; //Pin de salida de la alarma maquina 4 boton d conectar NA del led al relay
int Alarm_out_M4_e = 47; //Pin de salida de la alarma maquina 4 boton c conectar NA del led al relay
int Alarm_out_M4_f = 48; //Pin de salida de la alarma maquina 4 boton d conectar NA del led al relay
int Lampara_ok_M4 = 49; //Pin indicador de alarma ok conectar NA del led al relay
//--------------------------------------------------------------------------------------
int Alarm_out_M5_a = 53; //Pin de salida de la alarma maquina 5 boton a conectar NA del led al relay
int Alarm_out_M5_b = 2; //Pin de salida de la alarma maquina 5 boton b conectar NA del led al relay
int Alarm_out_M5_c = 3; //Pin de salida de la alarma maquina 5 boton c conectar NA del led al relay
int Alarm_out_M5_d = 4; //Pin de salida de la alarma maquina 5 boton d conectar NA del led al relay
int Alarm_out_M5_e = 5; //Pin de salida de la alarma maquina 5 boton c conectar NA del led al relay
int Alarm_out_M5_f = 6; //Pin de salida de la alarma maquina 5 boton d conectar NA del led al relay
int Lampara_ok_M5 = 7; //Pin indicador de alarma ok conectar NA del led al relay
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
bool Alarma1 = true, Alarma2 = true, Alarma3 = true, Alarma4 = true, Alarma5 = true;
bool A_state = 0; //Variable de estado logico de la salida del la alarma intermitente
int valor_M1 = 0, valor_M2 = 0, valor_M3 = 0, valor_M4 = 0, valor_M5 = 0;
//--------------------------------------------------------------------------------------
bool boton_m1a = false, boton_m1b = false, boton_m1c = false, boton_m1d = false, boton_m1e = false, boton_m1f = false;
bool boton_m2a = false, boton_m2b = false, boton_m2c = false, boton_m2d = false, boton_m2e = false, boton_m2f = false;
bool boton_m3a = false, boton_m3b = false, boton_m3c = false, boton_m3d = false, boton_m3e = false, boton_m3f = false;
bool boton_m4a = false, boton_m4b = false, boton_m4c = false, boton_m4d = false, boton_m4e = false, boton_m4f = false;
bool boton_m5a = false, boton_m5b = false, boton_m5c = false, boton_m5d = false, boton_m5e = false, boton_m5f = false;
//--------------------------------------------------------------------------------------
bool Atendido_m1a = false, Atendido_m1b = false, Atendido_m1c = false, Atendido_m1d = false, Atendido_m1e = false, Atendido_m1f = false;
bool Atendido_m2a = false, Atendido_m2b = false, Atendido_m2c = false, Atendido_m2d = false, Atendido_m2e = false, Atendido_m2f = false;
bool Atendido_m3a = false, Atendido_m3b = false, Atendido_m3c = false, Atendido_m3d = false, Atendido_m3e = false, Atendido_m3f = false;
bool Atendido_m4a = false, Atendido_m4b = false, Atendido_m4c = false, Atendido_m4d = false, Atendido_m4e = false, Atendido_m4f = false;
bool Atendido_m5a = false, Atendido_m5b = false, Atendido_m5c = false, Atendido_m5d = false, Atendido_m5e = false, Atendido_m5f = false;
//--------------------------------------------------------------------------------------
//void printDetail(uint8_t type, int value);
void alarmas_sonoras (int play);
void alarmas_sonoras2 ();
//***************************************************************************************************

void setup()
{
  //***************************************************************************************************

  radio.begin(); //Inicio del modulo nRF24L01+
  radio.setPALevel(RF24_PA_MAX);  // Se configura a la maxima potencia
  radio.setChannel(100); // Apertura del canal especifico

  //Apertura de las lineas de comunicacion con un maximo de 6 direcciones
  radio.openReadingPipe(0, direccion[0]);
  radio.openReadingPipe(1, direccion[1]);
  radio.openReadingPipe(2, direccion[2]);
  radio.openReadingPipe(3, direccion[3]);
  radio.openReadingPipe(4, direccion[4]);
  radio.openReadingPipe(5, direccion[5]);

  radio.startListening(); //Se inicia en modo de escucha, a la espera de alertas de las alarmas
  //--------------------------------------------------------------------------------------
  //Wire.begin();
  Wire.begin(2);                // unirse al bus i2c con la direccion #2
  Wire.onRequest(eventoSolicitud); // registrar evento de solicitud de datos
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
  pinMode(Lampara_ok_M1, OUTPUT);
  //--------------------------------------------------------------------------------------
  pinMode(Alarm_out_M2_a, OUTPUT);
  pinMode(Alarm_out_M2_b, OUTPUT);
  pinMode(Alarm_out_M2_c, OUTPUT);
  pinMode(Alarm_out_M2_d, OUTPUT);
  pinMode(Alarm_out_M2_e, OUTPUT);
  pinMode(Alarm_out_M2_f, OUTPUT);
  pinMode(Lampara_ok_M2, OUTPUT);
  //--------------------------------------------------------------------------------------
  pinMode(Alarm_out_M3_a, OUTPUT);
  pinMode(Alarm_out_M3_b, OUTPUT);
  pinMode(Alarm_out_M3_c, OUTPUT);
  pinMode(Alarm_out_M3_d, OUTPUT);
  pinMode(Alarm_out_M3_e, OUTPUT);
  pinMode(Alarm_out_M3_f, OUTPUT);
  pinMode(Lampara_ok_M3, OUTPUT);
  //--------------------------------------------------------------------------------------
  pinMode(Alarm_out_M4_a, OUTPUT);
  pinMode(Alarm_out_M4_b, OUTPUT);
  pinMode(Alarm_out_M4_c, OUTPUT);
  pinMode(Alarm_out_M4_d, OUTPUT);
  pinMode(Alarm_out_M4_e, OUTPUT);
  pinMode(Alarm_out_M4_f, OUTPUT);
  pinMode(Lampara_ok_M4, OUTPUT);
  //--------------------------------------------------------------------------------------
  pinMode(Alarm_out_M5_a, OUTPUT);
  pinMode(Alarm_out_M5_b, OUTPUT);
  pinMode(Alarm_out_M5_c, OUTPUT);
  pinMode(Alarm_out_M5_d, OUTPUT);
  pinMode(Alarm_out_M5_e, OUTPUT);
  pinMode(Alarm_out_M5_f, OUTPUT);
  pinMode(Lampara_ok_M5, OUTPUT);
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
  digitalWrite(Lampara_ok_M1, LOW);
  //--------------------------------------------------------------------------------------
  digitalWrite(Alarm_out_M2_a, HIGH);
  digitalWrite(Alarm_out_M2_b, HIGH);
  digitalWrite(Alarm_out_M2_c, HIGH);
  digitalWrite(Alarm_out_M2_d, HIGH);
  digitalWrite(Alarm_out_M2_e, HIGH);
  digitalWrite(Alarm_out_M2_f, HIGH);
  digitalWrite(Lampara_ok_M2, LOW);
  //--------------------------------------------------------------------------------------
  digitalWrite(Alarm_out_M3_a, HIGH);
  digitalWrite(Alarm_out_M3_b, HIGH);
  digitalWrite(Alarm_out_M3_c, HIGH);
  digitalWrite(Alarm_out_M3_d, HIGH);
  digitalWrite(Alarm_out_M3_e, HIGH);
  digitalWrite(Alarm_out_M3_f, HIGH);
  digitalWrite(Lampara_ok_M3, LOW);
  //--------------------------------------------------------------------------------------
  digitalWrite(Alarm_out_M4_a, HIGH);
  digitalWrite(Alarm_out_M4_b, HIGH);
  digitalWrite(Alarm_out_M4_c, HIGH);
  digitalWrite(Alarm_out_M4_d, HIGH);
  digitalWrite(Alarm_out_M4_e, HIGH);
  digitalWrite(Alarm_out_M4_f, HIGH);
  digitalWrite(Lampara_ok_M4, LOW);
  //--------------------------------------------------------------------------------------
  digitalWrite(Alarm_out_M5_a, HIGH);
  digitalWrite(Alarm_out_M5_b, HIGH);
  digitalWrite(Alarm_out_M5_c, HIGH);
  digitalWrite(Alarm_out_M5_d, HIGH);
  digitalWrite(Alarm_out_M5_e, HIGH);
  digitalWrite(Alarm_out_M5_f, HIGH);
  digitalWrite(Lampara_ok_M5, LOW);
  //--------------------------------------------------------------------------------------
}
//***************************************************************************************************

void loop() {
  //--------------------------------------------------------------------------------------
  byte pipeNum = 0; //Variable para leer que Modulo envio el dato
  int dataRX = 0; //Variable para guardar el dato recibido

  while (radio.available(&pipeNum)) { //Verificar si hay datos de los esclavos
    radio.read(&dataRX, 1 ); //Se lee un byte, ya que hemos configurado solo en envio de una letra
    //--------------------------------------------------------------------------------------
    if (160 < dataRX < 170) //Letra correspondiente al transmisor 1
    {
      if (dataRX == 161) //Letra correspondiente al transmisor 1 boton a
      {
        valor_M1 = 1; //
        delay(100);
      } else if (dataRX == 162) //Letra correspondiente al transmisor 1 boton b
      {
        valor_M1 = 2; //
        delay(100);
      } else if (dataRX == 163) //Letra correspondiente al transmisor 1 boton c
      {
        valor_M1 = 3; //
        delay(100);
      } else if (dataRX == 164) //Letra correspondiente al transmisor 1 boton d
      {
        valor_M1 = 4; //
        delay(100);
      } else if (dataRX == 165) //Letra correspondiente al transmisor 1 boton e
      {
        valor_M1 = 5; //
        delay(100);
      }
      else if (dataRX == 166) //Letra correspondiente al transmisor 1 boton f
      {
        valor_M1 = 6; //
        delay(100);
      }
      else if (dataRX == 167) //Letra correspondiente al transmisor 1 boton ok
      {
        valor_M1 = 7; //
        delay(100);
      }
    }
    //--------------------------------------------------------------------------------------
    if (170 < dataRX < 180) //Letra correspondiente al transmisor 2
    {
      if (dataRX == 171) //Letra correspondiente al transmisor 2 boton a
      {
        valor_M2 = 1; //
        delay(100);
      } else if (dataRX == 172) //Letra correspondiente al transmisor 2 boton b
      {
        valor_M2 = 2; //
        delay(100);
      } else if (dataRX == 173) //Letra correspondiente al transmisor 2 boton c
      {
        valor_M2 = 3; //
        delay(100);
      } else if (dataRX == 174) //Letra correspondiente al transmisor 2 boton d
      {
        valor_M2 = 4; //
        delay(100);
      } else if (dataRX == 175) //Letra correspondiente al transmisor 2 boton e
      {
        valor_M2 = 5; //
        delay(100);
      } else if (dataRX == 176) //Letra correspondiente al transmisor 2 boton f
      {
        valor_M2 = 6; //
        delay(100);
      } else if (dataRX == 177) //Letra correspondiente al transmisor 2 boton ok
      {
        valor_M2 = 7; //
        delay(100);
      }
    }
    //--------------------------------------------------------------------------------------
    if (180 < dataRX < 190) //Letra correspondiente al transmisor 3
    {
      if (dataRX == 181) //Letra correspondiente al transmisor 3 boton a
      {
        valor_M3 = 1; //
        delay(100);
      } else if (dataRX == 182) //Letra correspondiente al transmisor 3 boton b
      {
        valor_M3 = 2; //
        delay(100);
      } else if (dataRX == 183) //Letra correspondiente al transmisor 3 boton c
      {
        valor_M3 = 3; //
        delay(100);
      } else if (dataRX == 184) //Letra correspondiente al transmisor 3 boton d
      {
        valor_M3 = 4; //
        delay(100);
      } else if (dataRX == 185) //Letra correspondiente al transmisor 3 boton e
      {
        valor_M3 = 5; //
        delay(100);
      } else if (dataRX == 186) //Letra correspondiente al transmisor 3 boton f
      {
        valor_M3 = 6; //
        delay(100);
      } else if (dataRX == 187) //Letra correspondiente al transmisor 3 boton ok
      {
        valor_M3 = 7; //
        delay(100);
      }
    }
    //--------------------------------------------------------------------------------------
    if (190 < dataRX < 200) //Letra correspondiente al transmisor 4
    {
      if (dataRX == 191) //Letra correspondiente al transmisor 4 boton a
      {
        valor_M4 = 1; //
        delay(100);
      } else if (dataRX == 192) //Letra correspondiente al transmisor 4 boton b
      {
        valor_M4 = 2; //
        delay(100);
      } else if (dataRX == 193) //Letra correspondiente al transmisor 4 boton c
      {
        valor_M4 = 3; //
        delay(100);
      } else if (dataRX == 194) //Letra correspondiente al transmisor 4 boton d
      {
        valor_M4 = 4; //
        delay(100);
      } else if (dataRX == 195) //Letra correspondiente al transmisor 4 boton e
      { valor_M4 = 5; //
        delay(100);
      } else if (dataRX == 196) //Letra correspondiente al transmisor 4 boton f
      {
        valor_M4 = 6; //
        delay(100);
      } else if (dataRX == 197) //Letra correspondiente al transmisor 4 boton ok
      {
        valor_M4 = 7; //
        delay(100);
      }
    }
    //--------------------------------------------------------------------------------------
    if (200 < dataRX < 210) //Letra correspondiente al transmisor 5
    {
      if (dataRX == 201) //Letra correspondiente al transmisor 5 boton a
      {
        valor_M5 = 1; //
        delay(100);
      } else if (dataRX == 202) //Letra correspondiente al transmisor 5 boton b
      {
        valor_M5 = 2; //
        delay(100);
      } else if (dataRX == 203) //Letra correspondiente al transmisor 5 boton c
      {
        valor_M5 = 3; //
        delay(100);
      } else if (dataRX == 204) //Letra correspondiente al transmisor 5 boton d
      {
        valor_M5 = 4; //
        delay(100);
      } else if (dataRX == 205) //Letra correspondiente al transmisor 5 boton e
      {
        valor_M5 = 5; //
        delay(100);
      } else if (dataRX == 206) //Letra correspondiente al transmisor 5 boton f
      {
        valor_M5 = 6; //
        delay(100);
      } else if (dataRX == 207) //Letra correspondiente al transmisor 5 boton ok
      {
        valor_M5 = 7; //
        delay(100);
      }
    }
  }

  //***************************************************************************************************
  /*--------------------------------------------------------------------
    Verificacion si las maquinas estan operando
    si esta se encuentra activadas se encendera la lamapara ok correspondiente
    --------------------------------------------------------------------*/
  if (Alarma1 == true)
  {
    digitalWrite(Lampara_ok_M1, LOW);
  }
  else
  {
    digitalWrite(Lampara_ok_M1, HIGH);
  }

  if (Alarma2 == true)
  {
    digitalWrite(Lampara_ok_M2, LOW);
  }
  else
  {
    digitalWrite(Lampara_ok_M2, HIGH);
  }

  if (Alarma3 == true)
  {
    digitalWrite(Lampara_ok_M3, LOW);
  }
  else
  {
    digitalWrite(Lampara_ok_M3, HIGH);
  }

  if (Alarma4 == true)
  {
    digitalWrite(Lampara_ok_M4, LOW);
  }
  else
  {
    digitalWrite(Lampara_ok_M4, HIGH);
  }

  if (Alarma5 == true)
  {
    digitalWrite(Lampara_ok_M5, LOW);
  }
  else
  {
    digitalWrite(Lampara_ok_M5, HIGH);
  }
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
      digitalWrite(Alarm_out_M1_a, A_state);
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
      digitalWrite(Alarm_out_M1_b, A_state);
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
      digitalWrite(Alarm_out_M1_c, A_state);
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
      digitalWrite(Alarm_out_M1_d, A_state);
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
      digitalWrite(Alarm_out_M1_e, A_state);
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
      digitalWrite(Alarm_out_M1_f, A_state);
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

    }
    else {
      digitalWrite(Alarm_out_M2_e, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------
  if (boton_m2f == true) // si esta se encuentra armada
  {
    if (Atendido_m2f == false) // si no ha sido atendida pulsando otra vez
    {
      digitalWrite(Alarm_out_M2_f, A_state);

    }
    else {
      digitalWrite(Alarm_out_M2_f, LOW); // deja activada la lampara
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
      // delay(4000);
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
    }
    else {
      digitalWrite(Alarm_out_M5_f, LOW); // deja activada la lampara
    }
  }
  //--------------------------------------------------------------------------------------

  // ****************************************************************************************************

  // ****************************************************************************************************
  //*********************************Rutinas de interrupcion*********************************************
  // ****************************************************************************************************

  // ****************************************************************************************************
  /*--------------------------------------------------------------------------------------
                                          Maquina 1
     --------------------------------------------------------------------------------------*/
  if ((boton_m1a == false) && (valor_M1 == 1) /* && (Alarma1 == true) */) //Activar alarma mantenimiento con  melodia e intermirente
  {
    boton_m1a = true;
    Atendido_m1a = false;
    delay(200);
    valor_M1 = 0;
    alarmas_sonoras (1);

  }
  if ((Atendido_m1a == false)  && (boton_m1a == true) && (valor_M1 == 1)) //Alarma atendida,detener musica e inidcador fijo
  {
    Atendido_m1a = true;
    delay(200);
    valor_M1 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m1a == true) && (boton_m1a == true) && (valor_M1 == 1)) //apagar alarma
  {
    Atendido_m1a = false;
    boton_m1a = false;
    digitalWrite(Alarm_out_M1_a, HIGH);
    delay(200);
    valor_M1 = 0;
  }

  //--------------------------------------------------------------------------------------

  if ((boton_m1b == false) && (valor_M1 == 2))  //Activar alarma produccion con  melodia e intermirente
  {
    boton_m1b = true;
    Atendido_m1b = false;
    delay(200);
    valor_M1 = 0;
    alarmas_sonoras (2);
  }

  if ((Atendido_m1b == false) && (boton_m1b == true) && (valor_M1 == 2)) //Alarma atendida,detener musica e inidcador fijo
  {
    Atendido_m1b = true;
    delay(200);
    valor_M1 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m1b == true) && (boton_m1b == true) && (valor_M1 == 2)) //apagar alarma
  {
    Atendido_m1b = false;
    boton_m1b = false;
    digitalWrite(Alarm_out_M1_b, HIGH);
    delay(200);
    valor_M1 = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m1c == false) && (valor_M1 == 3))//Activar alarma materiales con  melodia e intermirente
  {
    boton_m1c = true;
    Atendido_m1c = false;
    delay(200);
    valor_M1 = 0;
    alarmas_sonoras (3);

  }

  if ((Atendido_m1c == false) && (boton_m1c == true) && (valor_M1 == 3)) //
  {
    Atendido_m1c = true;
    delay(200);
    valor_M1 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m1c == true) && (boton_m1c == true) && (valor_M1 == 3)) //
  {
    Atendido_m1c = false;
    boton_m1c = false;
    digitalWrite(Alarm_out_M1_c, HIGH);
    delay(200);
    valor_M1 = 0;
  }

  //--------------------------------------------------------------------------------------
  if ((boton_m1d == false) && (valor_M1 == 4))//Activar alarma cambio fr moldes con  melodia e intermirente
  {
    boton_m1d = true;
    Atendido_m1d = false;
    delay(200);
    valor_M1 = 0;
    alarmas_sonoras (4);
  }

  if ((Atendido_m1d == false) && (boton_m1d == true) && (valor_M1 == 4)) //
  {
    Atendido_m1d = true;
    delay(200);
    valor_M1 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m1d == true) && (boton_m1d == true) && (valor_M1 == 4)) //
  {
    Atendido_m1d = false;
    boton_m1d = false;
    digitalWrite(Alarm_out_M1_d, HIGH);
    delay(200);
    valor_M1 = 0;
  }
  //--------------------------------------------------------------------------------------
  if ((boton_m1e == false) && (valor_M1 == 5))//Activar alarma cambio fr moldes con  melodia e intermirente
  {
    boton_m1e = true;
    Atendido_m1e = false;
    delay(200);
    valor_M1 = 0;
    alarmas_sonoras (5);
  }

  if ((Atendido_m1e == false) && (boton_m1e == true) && (valor_M1 == 5)) //
  {
    Atendido_m1e = true;
    delay(200);
    valor_M1 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m1e == true) && (boton_m1e == true) && (valor_M1 == 5)) //
  {
    Atendido_m1e = false;
    boton_m1e = false;
    digitalWrite(Alarm_out_M1_e, HIGH);
    delay(200);
    valor_M1 = 0;
  }
  //--------------------------------------------------------------------------------------
  if ((boton_m1f == false) && (valor_M1 == 6))//Activar alarma cambio fr moldes con  melodia e intermirente
  {
    boton_m1f = true;
    Atendido_m1f = false;
    delay(200);
    valor_M1 = 0;
    alarmas_sonoras (6);
  }

  if ((Atendido_m1f == false) && (boton_m1f == true) && (valor_M1 == 6)) //
  {
    Atendido_m1f = true;
    delay(200);
    valor_M1 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m1f == true) && (boton_m1f == true) && (valor_M1 == 6)) //
  {
    Atendido_m1f = false;
    boton_m1f = false;
    digitalWrite(Alarm_out_M1_f, HIGH);
    delay(200);
    valor_M1 = 0;
  }
  //--------------------------------------------------------------------------------------
  if (valor_M1 == 7)
  {
    Alarma1 = !Alarma1; //cambia el  estado de la Alarma
    delay(200);
    valor_M1 = 0;
  }
  //--------------------------------------------------------------------------------------
  // ****************************************************************************************************
  /*--------------------------------------------------------------------------------------
                                           Maquina 2
      --------------------------------------------------------------------------------------*/

  if ((boton_m2a == false) &&  (valor_M2 == 1))//Activar alarma mantenimiento con  melodia e intermirente
  {
    boton_m2a = true;
    Atendido_m2a = false;
    delay(200);
    valor_M2 = 0;
    alarmas_sonoras (1);
  }

  if ((Atendido_m2a == false) && (boton_m2a == true) && (valor_M2 == 1)) //
  {
    Atendido_m2a = true;
    delay(200);
    valor_M2 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m2a == true) && (boton_m2a == true) && (valor_M2 == 1)) //
  {
    Atendido_m2a = false;
    boton_m2a = false;
    digitalWrite(Alarm_out_M2_a, HIGH);
    delay(200);
    valor_M2 = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m2b == false) && (valor_M2 == 2)) //Activar alarma produccion con  melodia e intermirente
  {
    boton_m2b = true;
    Atendido_m2b = false;
    delay(200);
    valor_M2 = 0;
    alarmas_sonoras (2);
  }

  if ((Atendido_m2b == false) && (boton_m2b == true) && (valor_M2 == 2)) //
  {
    Atendido_m2b = true;
    delay(200);
    valor_M2 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m2b == true) && (boton_m2b == true) && (valor_M2 == 2)) //
  {
    Atendido_m2b = false;
    boton_m2b = false;
    digitalWrite(Alarm_out_M2_b, HIGH);
    delay(200);
    valor_M2 = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m2c == false) && (valor_M2 == 3))//
  {
    boton_m2c = true;
    Atendido_m2c = false;
    delay(200);
    valor_M2 = 0;
    alarmas_sonoras (3);
  }

  if ((Atendido_m2c == false) && (boton_m2c == true) && (valor_M2 == 3)) //
  {
    Atendido_m2c = true;
    delay(200);
    valor_M2 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m2c == true) && (boton_m2c == true) && (valor_M2 == 3)) //
  {
    Atendido_m2c = false;
    boton_m2c = false;
    digitalWrite(Alarm_out_M2_c, HIGH);
    delay(200);
    valor_M2 = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m2d == false) && (valor_M2 == 4)) //
  {
    boton_m2d = true;
    Atendido_m2d = false;
    delay(200);
    valor_M2 = 0;
    alarmas_sonoras (4);
  }

  if ((Atendido_m2d == false) && (boton_m2d == true) && (valor_M2 == 4)) //
  {
    Atendido_m2d = true;
    delay(200);
    valor_M2 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m2d == true) && (boton_m2d == true) && (valor_M2 == 4)) //
  {
    Atendido_m2d = false;
    boton_m2d = false;
    digitalWrite(Alarm_out_M2_d, HIGH);
    delay(200);
    valor_M2 = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m2e == false) && (valor_M2 == 5)) //
  {
    boton_m2e = true;
    Atendido_m2e = false;
    delay(200);
    valor_M2 = 0;
    alarmas_sonoras (5);
  }

  if ((Atendido_m2e == false) && (boton_m2e == true) && (valor_M2 == 5)) //
  {
    Atendido_m2e = true;
    delay(200);
    valor_M2 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m2e == true) && (boton_m2e == true) && (valor_M2 == 5)) //
  {
    Atendido_m2e = false;
    boton_m2e = false;
    digitalWrite(Alarm_out_M2_e, HIGH);
    delay(200);
    valor_M2 = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m2f == false) && (valor_M2 == 6)) //
  {
    boton_m2f = true;
    Atendido_m2f = false;
    delay(200);
    valor_M2 = 0;
    alarmas_sonoras (6);
  }

  if ((Atendido_m2f == false) && (boton_m2f == true) && (valor_M2 == 6)) //
  {
    Atendido_m2f = true;
    delay(200);
    valor_M2 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m2f == true) && (boton_m2f == true) && (valor_M2 == 6)) //
  {
    Atendido_m2f = false;
    boton_m2f = false;
    digitalWrite(Alarm_out_M2_f, HIGH);
    delay(200);
    valor_M2 = 0;
  }
  //--------------------------------------------------------------------------------------

  if (valor_M2 == 7)
  {
    Alarma2 = !Alarma2; //cambia el  estado de la Alarma
    delay(200);
    valor_M2 = 0;
  }
  //--------------------------------------------------------------------------------------
  // ****************************************************************************************************
  /*--------------------------------------------------------------------------------------
                                           Maquina 3
      --------------------------------------------------------------------------------------*/

  if ((boton_m3a == false) &&  (valor_M3 == 1))//Activar alarma mantenimiento con  melodia e intermirente
  {
    boton_m3a = true;
    Atendido_m3a = false;
    delay(200);
    valor_M3 = 0;
    alarmas_sonoras (1);

  }

  if ((Atendido_m3a == false) && (boton_m3a == true) && (valor_M3 == 1)) //
  {
    Atendido_m3a = true;
    delay(200);
    valor_M3 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m3a == true) && (boton_m3a == true) && (valor_M3 == 1)) //
  {
    Atendido_m3a = false;
    boton_m3a = false;
    digitalWrite(Alarm_out_M3_a, HIGH);
    delay(200);
    valor_M3 = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m3b == false) && (valor_M3 == 2)) //Activar alarma produccion con  melodia e intermirente
  {
    boton_m3b = true;
    Atendido_m3b = false;
    delay(200);
    valor_M3 = 0;
    alarmas_sonoras (2);
  }

  if ((Atendido_m3b == false) && (boton_m3b == true) && (valor_M3 == 2)) //
  {
    Atendido_m3b = true;
    delay(200);
    valor_M3 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m3b == true) && (boton_m3b == true) && (valor_M3 == 2)) //
  {
    Atendido_m3b = false;
    boton_m3b = false;
    digitalWrite(Alarm_out_M3_b, HIGH);
    delay(200);
    valor_M3 = 0;
  } //--------------------------------------------------------------------------------------

  if ((boton_m3c == false) && (valor_M3 == 3))//
  {
    boton_m3c = true;
    Atendido_m3c = false;
    delay(200);
    valor_M3 = 0;
    alarmas_sonoras (3);
  }

  if ((Atendido_m3c == false) && (boton_m3c == true) && (valor_M3 == 3)) //
  {
    Atendido_m3c = true;
    delay(200);
    valor_M3 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m3c == true) && (boton_m3c == true) && (valor_M3 == 3)) //
  {
    Atendido_m3c = false;
    boton_m3c = false;
    digitalWrite(Alarm_out_M3_c, HIGH);
    delay(200);
    valor_M3 = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m3d == false) && (valor_M3 == 4)) //
  {
    boton_m3d = true;
    Atendido_m3d = false;
    delay(200);
    valor_M3 = 0;
    alarmas_sonoras (4);
  }

  if ((Atendido_m3d == false) && (boton_m3d == true) && (valor_M3 == 4)) //
  {
    Atendido_m3d = true;
    delay(200);
    valor_M3 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m3d == true) && (boton_m3d == true) && (valor_M3 == 4)) //
  {
    Atendido_m3d = false;
    boton_m3d = false;
    digitalWrite(Alarm_out_M3_d, HIGH);
    delay(200);
    valor_M3 = 0;

  }
  //--------------------------------------------------------------------------------------

  if ((boton_m3e == false) && (valor_M3 == 5)) //
  {
    boton_m3e = true;
    Atendido_m3e = false;
    delay(200);
    valor_M3 = 0;
    alarmas_sonoras (5);
  }

  if ((Atendido_m3e == false) && (boton_m3e == true) && (valor_M3 == 5)) //
  {
    Atendido_m3e = true;
    delay(200);
    valor_M3 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m3e == true) && (boton_m3e == true) && (valor_M3 == 5)) //
  {
    Atendido_m3e = false;
    boton_m3e = false;
    digitalWrite(Alarm_out_M3_e, HIGH);
    delay(200);
    valor_M3 = 0;

  }
  //--------------------------------------------------------------------------------------

  if ((boton_m3f == false) && (valor_M3 == 6)) //
  {
    boton_m3f = true;
    Atendido_m3f = false;
    delay(200);
    valor_M3 = 0;
    alarmas_sonoras (6);
  }

  if ((Atendido_m3f == false) && (boton_m3f == true) && (valor_M3 == 6)) //
  {
    Atendido_m3f = true;
    delay(200);
    valor_M3 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m3f == true) && (boton_m3f == true) && (valor_M3 == 6)) //
  {
    Atendido_m3f = false;
    boton_m3f = false;
    digitalWrite(Alarm_out_M3_f, HIGH);
    delay(200);
    valor_M3 = 0;

  }
  //--------------------------------------------------------------------------------------

  if (valor_M3 == 7)
  {
    Alarma3 = !Alarma3; //cambia el  estado de la Alarma
    delay(200);
    valor_M3 = 0;
  }
  //--------------------------------------------------------------------------------------
  // ****************************************************************************************************
  /*--------------------------------------------------------------------------------------
                                           Maquina 4
      --------------------------------------------------------------------------------------*/
  if ((boton_m4a == false) &&  (valor_M4 == 1))//Activar alarma mantenimiento con  melodia e intermirente
  {
    boton_m4a = true;
    Atendido_m4a = false;
    delay(200);
    valor_M4 = 0;
    alarmas_sonoras (1);
  }

  if ((Atendido_m4a == false) && (boton_m4a == true) && (valor_M4 == 1)) //
  {
    Atendido_m4a = true;
    delay(200);
    valor_M4 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m4a == true) && (boton_m4a == true) && (valor_M4 == 1)) //
  {
    Atendido_m4a = false;
    boton_m4a = false;
    digitalWrite(Alarm_out_M4_a, HIGH);
    delay(200);
    valor_M4 = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m4b == false) && (valor_M4 == 2)) //Activar alarma produccion con  melodia e intermirente
  {
    boton_m4b = true;
    Atendido_m4b = false;
    delay(200);
    valor_M4 = 0;
    alarmas_sonoras (2);
  }

  if ((Atendido_m4b == false) && (boton_m4b == true) && (valor_M4 == 2)) //
  {
    Atendido_m4b = true;
    delay(200);
    valor_M4 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m4b == true) && (boton_m4b == true) && (valor_M4 == 2)) //
  {
    Atendido_m4b = false;
    boton_m4b = false;
    digitalWrite(Alarm_out_M4_b, HIGH);
    delay(200);
    valor_M4 = 0;
  } //--------------------------------------------------------------------------------------

  if ((boton_m4c == false) && (valor_M4 == 3))//
  {
    boton_m4c = true;
    Atendido_m4c = false;
    delay(200);
    valor_M4 = 0;
    alarmas_sonoras (3);
  }

  if ((Atendido_m4c == false)  && (boton_m4c == true) && (valor_M4 == 3)) //
  {
    Atendido_m4c = true;
    delay(200);
    valor_M4 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m4c == true)  && (boton_m4c == true) && (valor_M4 == 3)) //
  {
    Atendido_m4c = false;
    boton_m4c = false;
    digitalWrite(Alarm_out_M4_c, HIGH);
    delay(200);
    valor_M4 = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m4d == false) && (valor_M4 == 4)) //
  {
    boton_m4d = true;
    Atendido_m4d = false;
    delay(200);
    valor_M4 = 0;
    alarmas_sonoras (4);
  }

  if ((Atendido_m4d == false) && (boton_m4d == true) && (valor_M4 == 4)) //
  {
    Atendido_m4d = true;
    delay(200);
    valor_M4 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m4d == true) && (boton_m4d == true) && (valor_M4 == 4)) //
  {
    Atendido_m4d = false;
    boton_m4d = false;
    digitalWrite(Alarm_out_M4_d, HIGH);
    delay(200);
    valor_M4 = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m4e == false) && (valor_M4 == 5)) //
  {
    boton_m4e = true;
    Atendido_m4e = false;
    delay(200);
    valor_M4 = 0;
    alarmas_sonoras (5);
  }

  if ((Atendido_m4e == false) && (boton_m4e == true) && (valor_M4 == 5)) //
  {
    Atendido_m4e = true;
    delay(200);
    valor_M4 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m4e == true) && (boton_m4e == true) && (valor_M4 == 5)) //
  {
    Atendido_m4e = false;
    boton_m4e = false;
    digitalWrite(Alarm_out_M4_e, HIGH);
    delay(200);
    valor_M4 = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m4f == false) && (valor_M4 == 6)) //
  {
    boton_m4f = true;
    Atendido_m4f = false;
    delay(200);
    valor_M4 = 0;
    alarmas_sonoras (6);
  }

  if ((Atendido_m4f == false) && (boton_m4f == true) && (valor_M4 == 6)) //
  {
    Atendido_m4f = true;
    delay(200);
    valor_M4 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m4f == true) && (boton_m4f == true) && (valor_M4 == 6)) //
  {
    Atendido_m4f = false;
    boton_m4f = false;
    digitalWrite(Alarm_out_M4_f, HIGH);
    delay(200);
    valor_M4 = 0;
  }
  //--------------------------------------------------------------------------------------
  if (valor_M4 == 7)
  {
    Alarma4 = !Alarma4; //cambia el  estado de la Alarma
    delay(200);
    valor_M4 = 0;
  }
  //--------------------------------------------------------------------------------------
  // ****************************************************************************************************
  /*--------------------------------------------------------------------------------------
                                           Maquina 5
      --------------------------------------------------------------------------------------*/

  if ((boton_m5a == false) &&  (valor_M5 == 1))//Activar alarma mantenimiento con  melodia e intermirente
  {
    boton_m5a = true;
    Atendido_m5a = false;
    delay(200);
    valor_M5 = 0;
    alarmas_sonoras (1);
  }

  if ((Atendido_m5a == false) && (boton_m5a == true) && (valor_M5 == 1)) //
  {
    Atendido_m5a = true;
    delay(200);
    valor_M5 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m5a == true) && (boton_m5a == true) && (valor_M5 == 1)) //
  {
    Atendido_m5a = false;
    boton_m5a = false;
    digitalWrite(Alarm_out_M5_a, HIGH);
    delay(200);
    valor_M5 = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m5b == false) && (valor_M5 == 2)) //Activar alarma produccion con  melodia e intermirente
  {
    boton_m5b = true;
    Atendido_m5b = false;
    delay(200);
    valor_M5 = 0;
    alarmas_sonoras (2);
  }

  if ((Atendido_m5b == false) && (boton_m5b == true) && (valor_M5 == 2)) //
  {
    Atendido_m5b = true;
    delay(200);
    valor_M5 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m5b == true) && (boton_m5b == true) && (valor_M5 == 2)) //
  {
    Atendido_m5b = false;
    boton_m5b = false;
    digitalWrite(Alarm_out_M5_b, HIGH);
    delay(200);
    valor_M5 = 0;
  } //--------------------------------------------------------------------------------------

  if ((boton_m5c == false) && (valor_M5 == 3))//
  {
    boton_m5c = true;
    Atendido_m5c = false;
    delay(200);
    valor_M5 = 0;
    alarmas_sonoras (3);
  }

  if ((Atendido_m5c == false) && (boton_m5c == true) && (valor_M5 == 3)) //
  {
    Atendido_m5c = true;
    delay(200);
    valor_M5 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m5c == true) && (boton_m5c == true) && (valor_M5 == 3)) //
  {

    Atendido_m5c = false;
    boton_m5c = false;
    digitalWrite(Alarm_out_M5_c, HIGH);
    delay(200);
    valor_M5 = 0;
  }

  //--------------------------------------------------------------------------------------

  if ((boton_m5d == false) && (valor_M5 == 4)) //
  {
    boton_m5d = true;
    Atendido_m5d = false;
    delay(200);
    valor_M5 = 0;
    alarmas_sonoras (4);
  }

  if ((Atendido_m5d == false) && (boton_m5d == true) && (valor_M5 == 4)) //
  {
    Atendido_m5d = true;
    delay(200);
    valor_M5 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m5d == true) && (boton_m5d == true) && (valor_M5 == 4)) //
  {
    Atendido_m5d = false;
    boton_m5d = false;
    digitalWrite(Alarm_out_M5_d, HIGH);
    delay(200);
    valor_M5 = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m5e == false) && (valor_M5 == 5)) //
  {
    boton_m5e = true;
    Atendido_m5e = false;
    delay(200);
    valor_M5 = 0;
    alarmas_sonoras (5);
  }

  if ((Atendido_m5e == false) && (boton_m5e == true) && (valor_M5 == 5)) //
  {
    Atendido_m5e = true;
    delay(200);
    valor_M5 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m5e == true) && (boton_m5e == true) && (valor_M5 == 5)) //
  {
    Atendido_m5e = false;
    boton_m5e = false;
    digitalWrite(Alarm_out_M5_e, HIGH);
    delay(200);
    valor_M5 = 0;
  }
  //--------------------------------------------------------------------------------------

  if ((boton_m5f == false) && (valor_M5 == 6)) //
  {
    boton_m5f = true;
    Atendido_m5f = false;
    delay(200);
    valor_M5 = 0;
    alarmas_sonoras (6);
  }

  if ((Atendido_m5f == false) && (boton_m5f == true) && (valor_M5 == 6)) //
  {
    Atendido_m5f = true;
    delay(200);
    valor_M5 = 0;
    alarmas_sonoras2();
  }

  if ((Atendido_m5f == true) && (boton_m5f == true) && (valor_M5 == 6)) //
  {
    Atendido_m5f = false;
    boton_m5f = false;
    digitalWrite(Alarm_out_M5_f, HIGH);
    delay(200);
    valor_M5 = 0;
  }
  //--------------------------------------------------------------------------------------
  if (valor_M5 == 7)
  {
    Alarma5 = !Alarma5; //cambia el  estado de la Alarma
    delay(200);
    valor_M5 = 0;
  }
  //--------------------------------------------------------------------------------------
  // ****************************************************************************************************

} //cierre de loop

// ****************************************************************************************************

// ****************************************************************************************************
void alarmas_sonoras (int play)
{
  Alarma_activa = play;
}
// ****************************************************************************************************


// ****************************************************************************************************************************************************************************************************************************************************************************************************
void alarmas_sonoras2()
{
  if (((Atendido_m1a == false) && (boton_m1a == true)) || ((Atendido_m2a == false) && (boton_m2a == true)) || ((Atendido_m3a == false) && (boton_m3a == true)) || ((Atendido_m4a == false) && (boton_m4a == true)) || ((Atendido_m5a == false) && (boton_m5a == true)))
  {
    alarmas_sonoras (1);
  }
  else  if (((Atendido_m1b == false) && (boton_m1b == true)) || ((Atendido_m2b == false) && (boton_m2b == true)) || ((Atendido_m3b == false) && (boton_m3b == true)) || ((Atendido_m4b == false) && (boton_m4b == true)) || ((Atendido_m5b == false) && (boton_m5b == true)))
  {
    alarmas_sonoras (2);

  }
  else  if (((Atendido_m1c == false) && (boton_m1c == true)) || ((Atendido_m2c == false) && (boton_m2c == true)) || ((Atendido_m3c == false) && (boton_m3c == true)) || ((Atendido_m4c == false) && (boton_m4c == true)) || ((Atendido_m5c == false) && (boton_m5c == true)))
  {
    alarmas_sonoras (3);

  }
  else  if (((Atendido_m1d == false) && (boton_m1d == true)) || ((Atendido_m2d == false) && (boton_m2d == true)) || ((Atendido_m3d == false) && (boton_m3d == true)) || ((Atendido_m4d == false) && (boton_m4d == true)) || ((Atendido_m5d == false) && (boton_m5d == true)))
  {
    alarmas_sonoras (4);

  }
  else  if (((Atendido_m1e == false) && (boton_m1e == true)) || ((Atendido_m2e == false) && (boton_m2e == true)) || ((Atendido_m3e == false) && (boton_m3e == true)) || ((Atendido_m4e == false) && (boton_m4e == true)) || ((Atendido_m5e == false) && (boton_m5e == true)))
  {
    alarmas_sonoras (5);

  }
  else  if (((Atendido_m1f == false) && (boton_m1f == true)) || ((Atendido_m2f == false) && (boton_m2f == true)) || ((Atendido_m3f == false) && (boton_m3f == true)) || ((Atendido_m4f == false) && (boton_m4f == true)) || ((Atendido_m5f == false) && (boton_m5f == true)))
  {
    alarmas_sonoras (6);

  }

  else
  {
    Alarma_activa = 0;
  }

}

// ****************************************************************************************************************************************************************************************************************************************************************************************************

// function that executes whenever data is requested by master
void eventoSolicitud() {
  Wire.write(Alarma_activa);
}
// ****************************************************************************************************
