// To connect with WiFi
#include<WiFi.h>

//  To make our device as server 
#include<WebServer.h>

//  ssid , password
const char ssid[] = "SREE KRISHNA";
const char password[] = "vishnawath@1947";

//  RGb led pins
byte r_pin = 25;
byte g_pin = 26;
byte b_pin = 27;

//  defining channels
#define r_channel 0
#define g_channel 1
#define b_channel 2

//  defining frequency and reolution
#define frequency 5000
#define resolution 8

//  starting a server at port 80
WebServer server(80);

void setup(){

  //  setting frequency and resolution at channels
  ledcSetup(r_channel , frequency , resolution);
  ledcSetup(g_channel , frequency , resolution);
  ledcSetup(b_channel , frequency , resolution);

  //  attaching GPIOs
  ledcAttachPin(r_pin , r_channel);
  ledcAttachPin(g_pin , g_channel);
  ledcAttachPin(b_pin , b_channel);

  //   starting serial communication
  Serial.begin(115200);

  //  connecting with the WiFi and printing IP Address
  Serial.print("Connecting with : ");
  Serial.println(ssid);
  WiFi.begin(ssid , password);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected with the Network !");
  Serial.print("IP address assgined by the access point : ");
  Serial.println(WiFi.localIP());

  //  Define APIs
   server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", generate_html());
  });

  server.on("/red", HTTP_GET, []() {
    color_generator(255, 0, 0);  // Set color to red
    server.send(200, "text/plain", "Color set to Red");
  });

  server.on("/green", HTTP_GET, []() {
    color_generator(0, 255, 0);  // Set color to green
    server.send(200, "text/plain", "Color set to Green");
  });

  server.on("/blue", HTTP_GET, []() {
    color_generator(0, 0, 255);  // Set color to blue
    server.send(200, "text/plain", "Color set to Blue");
  });

  server.on("/yellow", HTTP_GET, []() {
    color_generator(255, 255, 0);  // Set color to yellow
    server.send(200, "text/plain", "Color set to Yellow");
  });

  server.on("/cyan", HTTP_GET, []() {
    color_generator(0, 255, 255);  // Set color to cyan
    server.send(200, "text/plain", "Color set to Cyan");
  });

  server.on("/magenta", HTTP_GET, []() {
    color_generator(255, 0, 255);  // Set color to magenta
    server.send(200, "text/plain", "Color set to Magenta");
  });

  server.on("/orange", HTTP_GET, []() {
    color_generator(255, 165, 0);  // Set color to orange
    server.send(200, "text/plain", "Color set to Orange");


  //  Define API, if other APIs are not found

  server.onNotFound([]() {
  String message = "404 Not Found: " + server.uri();
  server.send(404, "text/plain", message)
  
  //  start the server

  server.begin();

  
  Serial.println("HTTP Server started");
  
}

void loop(){
 
  //  to handle the client requests at APIs
  server.generate_html();

}

void color_generator(byte r , byte g , byte b){
  ledcWrite(r_channel , r);
  ledcWrite(g_channel , g);
  ledcWrite(b_channel , b);
}


//  generating HTML Page
String generate_html(){
  
  String html = "<!DOCTYPE html>\n";
         html += "<html lang=\"en\">\n";
         html += "<head>\n";
         html += "<meta charset=\"UTF-8\">\n";
         html += "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n";
         html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
         html += "<title>ESP32 RGB CONTROLLER</title>\n";
         html += "</head>\n";
         html += "<body>\n";
         html += "<div style=\"padding-left: 50%; padding-top: 10%;\">\n";
         html += "<h1>COLOR GENERATOR</h1>\n";
         html += "</div>\n";

         html += "<div style=\"padding-left: 40%;\">\n";
         html += "<a href=\"/red\"><button>Red</button></a>\n";
         html += "<a href=\"/green\"><button>Green</button></a>\n";
         html += "<a href=\"/blue\"><button>Blue</button></a>\n";
         html += "<a href=\"/yellow\"><button>Yellow</button></a>\n";
         html += "<a href=\"/cyan\"><button>Cyan</button></a>\n";
         html += "<a href=\"/magenta\"><button>Magenta</button></a>\n";
         html += "<a href=\"/orange\"><button>Orange</button></a>\n";
         html += "</div>\n";
    
         html += "</body>\n";
         html += "</html>\n";

  return html;
}
