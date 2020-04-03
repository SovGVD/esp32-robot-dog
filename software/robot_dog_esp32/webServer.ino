void initWebServer() {
  display.print(" WebServer ");
  initWebServerRoutes();
  display.display();
}

void initWebServerRoutes() {  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", index_html);
  });
  server.on("/w.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "application/x-javascript", scripts_ws_js);
  });
  // Dinamic config
  server.on("/c.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "application/x-javascript", "var c={w:'ws://" + WiFiIP.toString() + "/ws'}");
  });

  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
 
  server.begin();
}

void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
 
  if(type == WS_EVT_CONNECT){ 
    client->text("Ok");
    clientOnline = true;
  } else if (clientOnline && type == WS_EVT_DATA) {
    if (data[0] == 70) {
      // TODO
    }
  } else if(type == WS_EVT_DISCONNECT){
    clientOnline = false;
  }
}
