"use strict";

let pb = { };
let ve = { };

let OBJECTS = ["starts", "bounds", "entities"]
for (let o of OBJECTS) {
    ve[o] = [];
}

protobuf.load("pb/level.proto", function(err, root) {
    pb.Level = root.lookupType("pb.Level");
});

function destroyArray(a) {
    while (a.length > 0) {
	a.pop().destroy();
    }
};

function loadLevel(room) {
    for (let o of OBJECTS) {
	destroyArray(ve[o]);
    }
    $.getNative("room/" + room).then(function(data, status, xhr) {
        ve.level = pb.Level.decode(
            new Uint8Array(data, 0, data.byteLength));
	loadBackground(ve.level.texture);
	for (let bound of ve.level.bounds) {
	    ve.bounds.push(new Boundary(bound, ve.stage));
	}
	for (let start of ve.level.positions) {
	    ve.starts.push(new StartPosition(start, ve.stage, ve.playerimg));
	}
	for (let entity of ve.level.entities) {
	    if (ENTITIES[entity.name]) {
		ve.entities.push(new ENTITIES[entity.name](entity, ve.stage));
	    } else {
		ve.entities.push(new Entity(entity, ve.stage));
	    }
	}
    }, function(xhr, status, error) {
        console.log(status, error);
	ve.level = pb.Level.fromObject({});
    });
};

function saveLevel(room) {

};

function loadBackground(t) {
    ve.level.texture = t;
    if (ve.bg) {
	ve.stage.removeChild(ve.bg);
    }
    ve.bg = new createjs.Bitmap("art/room/" + t);
    ve.updateSize = true;
    ve.stage.addChildAt(ve.bg, 0);
};

function render() {
    if (ve.updateSize) {
	let r = ve.bg.getBounds();
	if (r) {
	    ve.canvas.width = r.width * 2;
	    ve.canvas.height = r.height * 2;
	    ve.updateSize = false;
	}
    }
    ve.stage.update();
    if (ve.level) {
	$("#text").text(JSON.stringify(pb.Level.toObject(ve.level),
				       undefined, 4));
    };
};

function zeropad(n) {
    return ("000" + n).slice(-3);
};

function disableImageSmoothing(oldUpdate, ctx) {
    oldUpdate(ctx);
    ctx.imageSmoothingEnabled = false;
};

$(function(){
    $("#save").click(function(){
        saveLevel(zeropad($("#roomid").val()));
    });
    $("#load").click(function(){
        loadLevel(zeropad($("#roomid").val()));
    });

    $("form").on("submit", function(e) {
	e.preventDefault();
	$(this).children("button").eq(0).click();
    });

    ve.playerimg = document.getElementById("playerimg");
    ve.canvas = document.getElementById("c");
    ve.stage = new createjs.Stage(ve.canvas);
    
    let oldUpdate = ve.stage.updateContext.bind(ve.stage);
    ve.stage.updateContext = disableImageSmoothing.bind(ve.stage, oldUpdate);
    ve.stage.scaleX = 2;
    ve.stage.scaleY = 2;

    loadLevel("001");
    ve._ticker = createjs.Ticker.addEventListener("tick", render);
});
