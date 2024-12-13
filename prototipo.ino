#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

// Configurações de Wi-Fi
const char* ssid = "Inteli.Iot";
const char* password = "@Intelix10T#";




const int led_vermelho = 1; // Pino utilizado para controle do led vermelho
const int led_verde =  2; // Pino utilizado para controle do led verde
const int led_amarelo = 9; // Pino utilizado para controle do led amarelo

const int botao = 18;   // Pino utilizado para controle do botão
int estadoDoBotao = 0;  // Variavel que le o estado do botão que inicia desligado (0)
const int ldr = 4;  // pino do Ldr
const int VCC = 15;
int threshold = 600;

void setup() {

  // Configuração inicial dos pinos para controle dos leds e o VCC como OUTPUTs (saídas) do ESP32
  pinMode(led_amarelo,OUTPUT);
  pinMode(led_verde,OUTPUT);
  pinMode(led_vermelho,OUTPUT);
  pinMode(VCC, OUTPUT);

  // Inicialização das entradas
  pinMode(botao, INPUT); // Configuração inicial do botão como entrada do ESP32

  // inidia os leds como desligados (LOW)
  digitalWrite(led_amarelo, LOW);
  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho, LOW);

  Serial.begin(9600); // Configuração para debug por interface serial entre ESP e computador com baud rate de 9600


// ..................

  // Verifica estado do botão
  estadoDoBotao = digitalRead(botao);
  if (estadoDoBotao == HIGH) {
    Serial.println("Botão pressionado!");
  } else {
    Serial.println("Botão não pressionado!");
  }

  // --------------------
}

void loop() {
  int ldrstatus=analogRead(ldr);

  if(ldrstatus<threshold){
    Serial.print("Está escuro, ligue o led");
     delay(1000);
    Serial.println(ldrstatus);
    digitalWrite(led_amarelo, HIGH);
    digitalWrite(led_verde, LOW);
    digitalWrite(led_vermelho, LOW);
    delay(100);
    digitalWrite(led_amarelo, LOW);
    delay(100);

  }else if(ldrstatus>threshold) {
    Serial.print("Está muito claro, deslige o led");
    Serial.println(ldrstatus);
    delay(1000);
    digitalWrite(led_amarelo, LOW);
    digitalWrite(led_verde, HIGH);
    digitalWrite(led_vermelho, LOW);
    delay(3000);
    digitalWrite(led_amarelo, HIGH);
    digitalWrite(led_verde, LOW);
    digitalWrite(led_vermelho, LOW);
    delay(2000);
    digitalWrite(led_amarelo, LOW);
    digitalWrite(led_verde, LOW);
    digitalWrite(led_vermelho, HIGH);
    delay(5000);
  }
}
