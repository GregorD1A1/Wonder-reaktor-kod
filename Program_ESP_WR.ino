/////////////////////////////////
// Generated with a lot of love//
// with TUNIOT FOR ESP32     //
// Website: Easycoding.tn      //
/////////////////////////////////
#include <WiFi.h>

String  ClientRequest;
WiFiServer server(80);

WiFiClient client;

String myresultat;

String ReadIncomingRequest(){
while(client.available()) {
ClientRequest = (client.readStringUntil('\r'));
 if ((ClientRequest.indexOf("HTTP/1.1")>0)&&(ClientRequest.indexOf("/favicon.ico")<0)){
myresultat = ClientRequest;
}
}
return myresultat;
}

void setup()
{
ClientRequest = "";

Serial.begin(9600);

pinMode(21, OUTPUT);
  WiFi.disconnect();
  delay(3000);
  Serial.println("START");
  WiFi.begin("UPC3814465","DELPHI93g125");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");

  }
  Serial.println("Connected");
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP()));
  server.begin();

}


void loop()
{

    client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    ClientRequest = (ReadIncomingRequest());

    // czyśczenie stringa requesta
    ClientRequest.remove(0, 5);
    ClientRequest.remove(ClientRequest.length()-9,9);

    // Odpowiedź serwera (nic nie daje, ale musi być)
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println(ClientRequest);
    client.println("</html>");
    client.stop();
    delay(1);
    
    if (ClientRequest.equals("program1")) {
      digitalWrite(21,HIGH);
      delay(10000);
      digitalWrite(21,LOW);

    }
    client.flush();

}
