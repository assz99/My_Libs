#include <SPI.h>              
#include <LoRa.h>

const int LORA_SCK_PIN = 5;
const int LORA_MISO_PIN = 19;
const int LORA_MOSI_PIN = 27;
const int LORA_SS_PIN = 18;
const int LORA_RST_PIN = 14;
const int LORA_DI00_PIN = 26;
#define BAND 915E6

bool loraBegin()
{
  
  SPI.begin(LORA_SCK_PIN, LORA_MISO_PIN, LORA_MOSI_PIN, LORA_SS_PIN);
  // Setamos os pinos do lora
  LoRa.setPins(LORA_SS_PIN, LORA_RST_PIN, LORA_DI00_PIN);
  return LoRa.begin(BAND);
}

void setup() {
 
LoRa.onReceive(onReceive);
  LoRa.receive();
}



void sendMessage(String mensagem)
{
  LoRa.beginPacket();            // Inicia o pacote da mensagem
  LoRa.write(mensagem.length()); // Tamanho da mensagem em bytes
  LoRa.print(mensagem);          // Vetor da mensagem
  LoRa.endPacket();              // Finaliza o pacote e envia
  Serial.println(mensagem);
  LoRa.receive();
}

void onReceive(int packetSize) {
  // received a packet
  Serial.print("Received packet '");

  // read packet
  for (int i = 0; i < packetSize; i++) {
    Serial.print((char)LoRa.read());
  }

  // print RSSI of packet
  Serial.print("' with RSSI ");
  Serial.println(LoRa.packetRssi());
}
