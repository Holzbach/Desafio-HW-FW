//Author: Eduardo Holzbach
//Date: 17/09/2021
//Title: Resolução PD Soluções

const int  bot = 12 ;       // Pino em que o botão está ligado
const int led = 7 ;         // Pino em que o LED está ligado
const int buzzer = 6 ;      // Pino em que o Buzzer está ligado

int TPomodoro = 0;          // Variável com Tempo de Pomodoro em minutos
int TPomodoro_aux = 0;      // Auxíliar na leitura do tempo

int bot_cont = 0;           // Contador para o número de prensas botão
int bot_estado = 0;         // Estado atual do botão
int bot_estado_ant = 0;     // Estado anterior do botão

int estado = 0;
int cont = 0;


void setup() {

  pinMode(bot, INPUT);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
}


void loop() {

  bot_estado = digitalRead(bot);

  if (bot_estado != bot_estado_ant) {
    if (bot_estado == LOW) {
      bot_cont++;
      //Serial.println(bot_cont);
      delay(100);
    }
    bot_estado_ant = bot_estado;
    if (bot_cont % 2 == 1) {
      estado = 1; // Estado Ligado
    }
    else {
      estado = 0; // Estado Desligado
    }
  }

  switch (estado) {
    case 0: //Estado Desligado
      digitalWrite(led, LOW);
      if (Serial.available()) {
        TPomodoro_aux = Serial.parseInt();
        if ((TPomodoro_aux != 0) && (TPomodoro != TPomodoro_aux)) {
          TPomodoro = TPomodoro_aux;
          Serial.println("Novo valor recebido!");
        }
        //Serial.println(TPomodoro);
      }
      break;
    case 1: // Estado Ligado
      if (cont <= (TPomodoro * 100)) {
        cont++;
        Serial.println(cont);
        delay(10);
        digitalWrite(led, HIGH);
      } else {
        cont = 0;
        estado = 2; // Tempo Acabou
        digitalWrite(led, LOW);
      }
      break;
    case 2: // Tempo Acabou
      if (cont <= 5 * 100) { // 5 segundos
        cont++;
        delay(10);
        digitalWrite(buzzer, HIGH);
        } else {
        cont = 0;
        digitalWrite(buzzer, LOW);
        estado = 0;
        }
      break;
  }
}
