// This is the content for pages
const char* index_html = "<html><head><title>ToDoV1</title></head><body><script src='c.js'></script><script src='/w.js'></script></body></html>";
const char* scripts_ws_js = "var w={w:0,c:0};try{w.w=new WebSocket(c.w);w.w.onopen=function(){w.c=1};w.w.onerror=function(){w.c=0};}catch(e){console.log('E',e)};function s(d){if(w.c){w.w.send(d)}}";
