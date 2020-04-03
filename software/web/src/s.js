var w={w:0,c:0};

try{
    w.w=new WebSocket(c.w);
    w.w.onopen=function(){
        w.c=1
    };
    w.w.onerror=function(){
        w.c=0
    };
}catch(e){
    console.log('E',e);
};

function s(d){
    if(w.c){
        w.w.send(d);
    }
}
