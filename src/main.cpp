/*
  Titre      : Test 2 En ELTE1072
  Auteur     : Anis Aliouachene
  Date       : 16/03/2022
  Description: Detection de conductivity ( Eau ) et demarrage d'une pompe a l'aide d'un relais et 
  la pompe s'arrete lorsque qu'on detecte plus l'eau (Conductivity) 
  Version    : 0.0.1
*/

// Inclus des libraire pour le fonctionemment du WIFI 
#include <Arduino.h>
#include "WIFIConnector_MKR1000.h"
#include "MQTTConnector.h"


const int ConductivityPin = 1;  // broche a la quelle le decteur de conductivity se branche 
const int LED_PIN = 3;  // broche a la quelle le relais se branche 
int EtatLED;  // variable pour l'etat de la led 

// Fonction Led Appeller a chaque fois y a un changement sur la broche 1 a l'aide d'interrupt 
void LED() {
    EtatLED = !EtatLED;  // Changement d'etat de la led de 1 a 0 ou de 0 a 1 

    // Envoi de donnees sur ThingsBoard
    appendPayload("Etat Pompe", EtatLED);  //Ajout de la donnée Etat Pompe au message MQTT
    appendPayload("Conductivity", EtatLED); //Ajout de la donnée Conductivity au message MQTT
    sendPayload();  //Envoie du message via le protocole MQTT

}

void setup() {

  wifiConnect();      //Branchement au réseau WIFI
  MQTTConnect();     //Branchement au MQTT
  
  // Confuguration des broches 
  pinMode(ConductivityPin, INPUT); 
  pinMode(LED_PIN, OUTPUT);

  /** Attachement de la broche relier au capteur de conductivity pour utiliser les interrupt 
   a chaque fois y a un changement sur la broche on appel la fonction LED **/ 
  attachInterrupt(digitalPinToInterrupt(ConductivityPin), LED, CHANGE );
}


void loop() {

  // Mettre le relais soit en HIGH ou LOW selon l'etat de la LED si en HIGH led s'allume si en LOW la LED etteint 
  // ca depend de la detection d'eau 
   digitalWrite(LED_PIN, EtatLED);

}