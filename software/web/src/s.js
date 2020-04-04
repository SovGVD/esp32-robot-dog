function G(id) {
    return document.getElementById(id);
}

var vector = {
    x    : 0,
    y    : 0,
    z    : 0,
    angZ : 0
};

var gamepad = {
    init: function () {
		window.addEventListener("gamepadconnected", gamepad.connect);
		window.addEventListener("gamepaddisconnected", gamepad.disconnect);
    },

    connect: function(evt) {
		clearInterval(gamepad.updateInterval);
		gamepad.updateInterval = setInterval(gamepad.update, 50);
    },

    disconnect: function(evt) {
		clearInterval(gamepad.updateInterval);
		gamepad.updateInterval = null;
    },

    update: function() {
		var gp = navigator.getGamepads ? navigator.getGamepads() : (navigator.webkitGetGamepads ? navigator.webkitGetGamepads : []);
		if (gp.length === 0) {
			return;
		}
		gp = gp[0];
		
		vector.angZ = gamepad.axeData(gp.axes[0]);
		vector.z    = gamepad.axeData(gp.axes[1]);
		vector.x    = gamepad.axeData(gp.axes[2]);
		vector.y    = gamepad.axeData(gp.axes[3]);
		
		ws.update();
    },

    axeData: function (raw) {
		let value = parseInt(raw*1000)/1000;
		if (value >= - gamepad.gpDead && value <= gamepad.gpDead) value = 0;
		return -value;
    },

    dead: 0.005,
    updateInterval: null,
};

var ws = {
    ws: null,
    status: false,
    error: false,
    updateInterval: null,
    init: function () {
		clearInterval(ws.updateInterval);
		try {
			ws.ws = new WebSocket(c.w);
			ws.ws.onopen = function() {
			ws.status = true;
			};
			ws.ws.onerror = function() {
			ws.status = false;
			};
			
			//ws.updateInterval = setInterval(ws.update, 50);
		} catch(e) {
			clearInterval(ws.updateInterval);
			ws.status = false;
			ws.error = true;
			console.log(e);
		};
    },
    update: function(data) {
		if (ws.status) {
			ws.ws.send(packet.move());
		}
    }
};

var gui ={
    init: function () {
		gui.obj.vector_x    = G('vector_x');
		gui.obj.vector_y    = G('vector_y');
		gui.obj.vector_z    = G('vector_z');
		gui.obj.vector_angZ = G('vector_angZ');
		
		gui.updateInterval = setInterval(gui.update, 500);
    },
    update: function () {
		gui.showVector();
    },
    showVector: function () {
		gui.obj.vector_x.innerHTML    = vector.x;
		gui.obj.vector_y.innerHTML    = vector.y;
		gui.obj.vector_z.innerHTML    = vector.z;
		gui.obj.vector_angZ.innerHTML = vector.angZ;
    },
    obj: {},
    updateInterval: null,
};

var packet = {
    _int16LE: function (num) {
	var ascii='';
	for (let i=1;i>=0;i--) {
	    ascii+=String.fromCharCode((num>>(8*i))&255);
	}
	return ascii;
    },
    move: function () {
		return 'M' 
		+ packet._int16LE(vector.x*10000) 
		+ packet._int16LE(vector.y*10000) 
		+ packet._int16LE(vector.z*10000) 
		+ packet._int16LE(vector.angZ*10000);
		}
}

gui.init();
ws.init();
gamepad.init();
