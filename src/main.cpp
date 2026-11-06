#include <Arduino.h>
#include <WiFi.h>
#include <ezTime.h>

//Funçoes
void conexaoWifi();
void reconexaoWiFi();

const char  *SSID = "SENAI EDUCACIONAL";
const char  *SENHA = "info@134";

const unsigned long tempoConexao = 10000;
const unsigned long tempoReconexao = 5000;


Timezone sp;


void setup() {
  Serial.begin(115200);
  
  //Conexao WiFi
  conexaoWifi();

  waitForSync();

  sp.setLocation("America/Sao_Paulo");


  // sp.dateTime("d/m/Y H:i:s");


  // Serial.println(sp.minute()); 
  // Serial.println(sp.second()); 
  // Serial.println(sp.hour()); 
  // Serial.println(sp.hourFormat12()); 
  // Serial.println(sp.day()); 
  // Serial.println(sp.dayOfYear()); 
  // Serial.println(sp.month()); 
  // Serial.println(sp.year()); 
  // Serial.println(sp.isAM()); 
  // Serial.println(sp.isPM()); 

  //Caracteres uteis
  //Y -> ano completo (2026)
  //y -> ano com 2 digitos(26)
  //d -> dia
  //H -> hora
  //i -> minuto (00-59)
  //s -> segundo (00-59)
  //l -> dia da semana por extenso (Thursday)
  //D -> dia da semana abreviado (Thu)
  //F -> nome completo do mes (November)
  //M -> nome abreviado do mes (Nov)
  //a/A >- am/pm 
  // T -> Sigla do Fuso (BRT)
  // z -> dia do ano (1-365)

  String diadia = sp.dateTime("d");
  String ano = sp.dateTime("Y");
  String faltam = sp.dateTime("z");

  int resto = faltam.toInt();

  resto = 365 - resto;

const String diasDaSemana[] = {"Domingo","Segunda-feira","Terça-feira","Quarta-feira","Quinta-feira","Sexta-feira","Sabado"};
const String diasDoMes[] = {"Janeiro","Fevereiro","Março","Abril","Maio","Junho","Julho","Agosto","Outubro","Novembro","Dezembro"};

String diaSemana = diasDaSemana[sp.weekday()-1];
String diadomes = diasDoMes[sp.dateTime("m").toInt() -1];

Serial.printf("Hoje é %s de %s de %s,%s e faltam %i dias para o ano novo",diadia,diasDoMes,ano,diasDaSemana,resto);
}

void loop() {
  reconexaoWiFi();
}


void conexaoWifi(){
  Serial.printf("Conectando ao WIFI: %s", SSID);

  WiFi.begin(SSID, SENHA);

  unsigned long tempoWifi = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - tempoWifi < tempoConexao)
  {
    Serial.print(".");
    delay(500);
  }

  if(WiFi.status() == WL_CONNECTED){
    Serial.println("Wifi conectado com sucesso");
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());
  }
  else{
    Serial.println("Falha ao se conectar");
  }
}

void reconexaoWiFi(){
  unsigned long tempoAtual = millis();
  unsigned long tempoUltimaConexao = 0;

  if(tempoAtual - tempoUltimaConexao > tempoReconexao){
    if(WiFi.status() != WL_CONNECTED){
      Serial.println("Conexao Wifi perdida");
      conexaoWifi();
    }
    tempoUltimaConexao = tempoAtual;
  }
}