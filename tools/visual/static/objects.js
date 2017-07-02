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
	if (bind != false) {
	    d.on("click", this);
	    d.on("pressmove", this);
	    d.on("mousedown", this);
	    d.on("pressup", this);
	}
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

function markDirty() {
    ve.updateText = true;
    ve.dirty = true;
}

class StartPosition extends Drawable {
    constructor(vector, stage, img) {
	super(stage);
	this.p = new createjs.Bitmap(img);
	this.addDrawable(this.p);
	this.p.sourceRect = new createjs.Rectangle(0, 0, 22, 60);
	this.v = vector;
	this.p.x = vector.x - this.p.sourceRect.width / 2;
	this.p.y = vector.y - this.p.sourceRect.height;
    }
    endMove(o) {
	this.v.x = this.p.x + this.p.sourceRect.width / 2;
	this.v.y = this.p.y + this.p.sourceRect.height;
	markDirty();
    }
}

class Boundary extends Drawable {
    constructor(rect, stage) {
	super(stage);
	this.s = new createjs.Shape();
	this.addDrawable(this.s, true, true);
	this.g = this.s.graphics;
	this.r = rect;
	this.g.setStrokeStyle(2);
	this.g.beginStroke("#ff0000");
	this.g.drawRect(0, 0, rect.size.x, rect.size.y);
	this.g.endStroke();
	this.s.x = rect.pos.x;
	this.s.y = rect.pos.y;
    }
    endMove(o) {
	this.r.pos.x = this.s.x;
	this.r.pos.y = this.s.y;
	ve.updateText = true;
	ve.dirty = true;
    }
}

class Entity extends Drawable {
    constructor(entity, stage) {
	super(stage);
	this.e = entity;
	this.bounds = new createjs.Shape();
	this.g = this.bounds.graphics;
	this.addDrawable(this.bounds);
	this.g.setStrokeStyle(2);
	this.g.beginStroke("#0000ff");
	this.g.drawRect(0, 0, entity.nargs[2], entity.nargs[3]);
	this.g.endStroke();
	this.bounds.x = entity.nargs[0];
	this.bounds.y = entity.nargs[1];
    }
    endMove(o) {
	markDirty();
	this.e.nargs[0] = this.bounds.x;
	this.e.nargs[1] = this.bounds.y;
    }
}

class Generic extends Entity {
    constructor(entity, stage) {
	super(entity, stage);
	this.img = new createjs.Bitmap("art/entity/" + entity.sargs[0]);
	this.addDrawable(this.img, true);
	this.img.sourceRect = new createjs.Rectangle(0, 0, entity.nargs[2],
						     entity.nargs[3]);
	this.img.x = entity.nargs[0];
	this.img.y = entity.nargs[1];
    }
    endMove(o) {
	if (o.target == this.img) {
	    this.bounds.x = this.img.x;
	    this.bounds.y = this.img.y;
	} else {
	    this.img.x = this.bounds.x;
	    this.img.y = this.bounds.y;
	}
	super.endMove(o);
    }
}

let ENTITIES = {
    "generic": Generic,
};
