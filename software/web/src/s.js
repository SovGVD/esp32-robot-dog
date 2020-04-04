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
		// TODO failsafe!!!
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
    },

    axeData: function (raw) {
		if (raw >= -gamepad.dead && raw <= gamepad.dead) raw = 0;
		let value = parseInt(raw*1000)/1000;
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
			// TODO failsafe!!!
			ws.updateInterval = setInterval(ws.update, 50);
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
		
		gui.updateInterval = setInterval(gui.update, 100);
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
	init: function () {
		packet.pMove = new ArrayBuffer(9);
		packet.vMove = new Uint8Array(packet.pMove);
	},
    _uint16: function (view, num, offset) {
		view[offset]   = (num>>8)&255;
		view[offset+1] = num&255;
    },

    move: function () {
		packet.vMove[0] = 77;
		packet._uint16(packet.vMove, (vector.x+1)*10000, 1);
		packet._uint16(packet.vMove, (vector.y+1)*10000, 3);
		packet._uint16(packet.vMove, (vector.z+1)*10000, 5);
		packet._uint16(packet.vMove, (vector.angZ+1)*10000, 7);
		return packet.pMove;
	}
}

packet.init();
gui.init();
ws.init();
gamepad.init();
