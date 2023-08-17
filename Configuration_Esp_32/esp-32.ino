//Librerias
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>
#include <Ultrasonic.h>
#include <Ticker.h>

//Se definen las variables
#define Led 2
#define Leds 32
#define Ledss 26

Ultrasonic ultrasonic(13, 12);
Ultrasonic ultrasonic2(33, 25);
Ultrasonic ultrasonic3(18, 5);

int distance;
int distance2;
int distance3;
int indicador;
int indicador2;
int indicador3;

//Se colocan las credenciales de la red para realizar la conexion a la red 
const char* ssid     = "Totalplay-BCAA";
const char* password = "F8071FR234511";
//Se crea la funcion
void enviarDatos();

//Funcion de libreria de tiempo
Ticker timer;

AsyncWebServer server(80); //server port 80
WebSocketsServer webSocket = WebSocketsServer(81);

//Indica error en caso de no encontrar el recurso
void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Page Not Found");
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\n", num); //inidica el numero de usuario que se desconecto
            break;
        case WStype_CONNECTED:
            {
                IPAddress ip = webSocket.remoteIP(num);
                Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload); //indica la ip del usuario que se conecto y se le asigna un nuemro en el array

				// send message to client
				webSocket.sendTXT(num, "Connected on server: "); //inidca la ip con la que se conecto
            }
            break;
        case WStype_TEXT:
            Serial.printf("[%u] get Text: %s\n", num, payload);
            String mensaje = String((char*)(payload));
            Serial.println(mensaje);
             DynamicJsonDocument doc(200);
             DeserializationError error = deserializeJson(doc, mensaje); //Recibe una intsruccion en formato JSON y la decodifica 
             if(error){
               Serial.print("deserializeJson() failed: "); //Inidica el error en caso de fallar la decodificacion
               Serial.println(error.c_str());
               return;
             }
    }
}

void setup(void) {
  //Indica los baudios
  Serial.begin(115200);
  pinMode(Led, OUTPUT); //Inidca que el led va tener una salida
  pinMode(Leds, OUTPUT);
  
//establece la conexion con la red 
 WiFi.begin(ssid, password);
  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  //Indica la ip donde se aloja el servidor local
  Serial.print("Conectado, dirección IP: ");
  Serial.println(WiFi.localIP());


 //intialize SPIFFS (subir archivos a la memoria)
 if(!SPIFFS.begin(true)){
  Serial.println("A ocurrido un error al montado SPIFFS"); //indica el error en caso de no poder subir el archivo
  return;
 }
  
  // se hace la peticion a la pagina web
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) //inicia el sevidor usando el protocolo HTTP 
  {
    request->send(SPIFFS, "/index.html", "text/html"); //indica donde se aloja la pagina web
  });

  server.onNotFound(notFound);//Error en caso de no encontrar el recurso
  server.begin(); //Finalemente inciamos el servidor

  webSocket.begin();//inica el websocket
  webSocket.onEvent(webSocketEvent);

  timer.attach(1, enviarDatos); //Llama a las funciones cada 2 segundos
}


void loop() 
{
  webSocket.loop(); //inicia un bucle del websocket
 }

//Envia los datos
void enviarDatos()
{
  distance = ultrasonic.read(CM); //Lee los datos que envia el sensor ultrasonico
  distance2 = ultrasonic2.read(CM);
  distance3 = ultrasonic3.read(CM);

  //valida que se este enviando un valor numerico
   if (isnan(distance || distance2 || distance3)){
     Serial.println(F("Fallo al detectar!")); 
     return;
   }
   //Distancia 1 
   // actualiza el valor del LED para encenderlo
   if(distance >= 10)
   {
    indicador = 0; //variable indica un valor booleano
    digitalWrite(Led,indicador);//indica que encienda el LED
   }else if(distance <= 20){ //caso contrario menor a la distancia indicada
    indicador = 1; //varibale indica un valor booleano
    digitalWrite(Led,indicador);//indica que apague el LED
   }
   //Distancia 2
   if(distance2 >=10)
   {
    indicador2 = 0;
    digitalWrite(Leds,indicador2);//indica que encienda el LED
   }else if ( distance2 <=20)
   {
    indicador2 = 1;
    digitalWrite(Leds,indicador2);
   }
   //Distancia 3 
    if(distance3 >=10)
   {
    indicador3 = 0;
    digitalWrite(Ledss,indicador3);//indica que encienda el LED
   }else if ( distance3 <=20)
   {
    indicador3 = 1;
    digitalWrite(Ledss,indicador3);
   }

   //Envia los datos en formato JSON para ser interpretados por JS
  String JSON_Data = "{\"distancia\":";
         JSON_Data += distance;
         JSON_Data +=",\"distancia2\":";
         JSON_Data += distance2;
         JSON_Data +=",\"distancia3\":";
         JSON_Data += distance3;
         JSON_Data += ",\"indicador\":";
         JSON_Data += indicador;
         JSON_Data += ",\"indicador2\":";
         JSON_Data += indicador2;
         JSON_Data += ",\"indicador3\":";
         JSON_Data += indicador3;
         JSON_Data += "}";
         
  // imprime los datos en el monitor serial
  Serial.println(JSON_Data);
  //Envia los datos a todos los clientes conectados
  webSocket.broadcastTXT(JSON_Data);
}
