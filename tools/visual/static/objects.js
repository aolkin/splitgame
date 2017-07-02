"use strict";

class Drawable {
    constructor(stage) {
	this._stage = stage;
	this._drawables = [];
    }
    addDrawable(d, bind, bottom) {
	this._drawables.push(d);
	if (bottom) {
	    this._stage.addChildAt(d, 1);
	} else {
	    this._stage.addChild(d);
	}
	d.on("click", this);
	d.on("pressmove", this);
	d.on("mousedown", this);
	d.on("pressup", this);
	d.moving = false;
    }
    destroy() {
	for (let d of this._drawables) {
	    d.stage.removeChild(d);
	}
    }
    handleEvent(e) {
	let obj = {
	    x: e.stageX / 2,
	    y: e.stageY / 2,
	    event: e,
	    target: e.target
	};
	if (e.type == "mousedown") {
	    e.target.moveOffset = { x: e.localX, y: e.localY };
	    e.target.originalPosition = { x: e.target.x, y: e.target.y };
	    if (this.startMove) {
		this.startMove(obj);
	    }
	}
	obj.moveX = obj.x - e.target.moveOffset.x;
	obj.moveY = obj.y - e.target.moveOffset.y;
	if (e.type == "pressmove") {
	    e.target.moving = true;
	    if (this.continueMove) {
		this.continueMove(obj);
	    }
	} else if (e.type == "click") {
	    if (this.handleSelect) {
		this.handleSelect(obj);
	    }
	} else if (e.type == "pressup" && e.target.moving) {
	    if (this.endMove) {
		this.endMove(obj);
	    }
	    e.target.moving = false;
	};
	console.log(e.type, obj);
    }
    continueMove(o) {
	o.target.x = o.moveX;
	o.target.y = o.moveY;
    }
    endMove(o) {
	o.target.x = o.target.originalPosition.x;
	o.target.y = o.target.originalPosition.y;
    }
}

class StartPosition extends Drawable {
    constructor(vector, stage, img) {
	super(stage);
	this.p = new createjs.Bitmap(img);
	this.addDrawable(this.p, true);
	this.p.sourceRect = new createjs.Rectangle(0, 0, 22, 60);
	this.v = vector;
	this.p.x = vector.x - this.p.sourceRect.width / 2;
	this.p.y = vector.y - this.p.sourceRect.height;
    }
}

class Boundary extends Drawable {
    constructor(rect, stage) {
	super(stage);
	this.s = new createjs.Shape();
	this.addDrawable(this.s, true, true);
	this.g = this.s.graphics;
	this.r = rect;
	this.g.beginStroke("#ff0000");
	this.g.drawRect(rect.pos.x, rect.pos.y,
			rect.size.x, rect.size.y);
	this.g.endStroke();
    }
}

class Entity extends Drawable {
    constructor(entity, stage) {
	super(stage);
	this.e = entity;
	this.bounds = new createjs.Shape();
	this.addDrawable(this.bounds, true);
	this.bounds.graphics.beginStroke("#0000ff");
	this.bounds.graphics.drawRect(entity.nargs[0], entity.nargs[1],
				      entity.nargs[2], entity.nargs[3]);
	this.bounds.graphics.endStroke();
    }
}

class Generic extends Entity {
    constructor(entity, stage) {
	super(entity, stage);
	this.img = new createjs.Bitmap("art/entity/" + entity.sargs[0]);
	this.addDrawable(this.img);
	this.img.sourceRect = new createjs.Rectangle(0, 0, entity.nargs[2],
						     entity.nargs[3]);
	this.img.x = entity.nargs[0];
	this.img.y = entity.nargs[1];
    }
}

let ENTITIES = {
    "generic": Generic,
};
