import os

from flask import *

app = Flask(__name__)

APP_DIR = os.path.dirname(__file__)
BASE_DIR = os.getcwd()

@app.after_request
def add_header(r):
        r.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        return r

@app.route("/")
def hello():
        return send_file(os.path.join(APP_DIR, "index.html"))

@app.route("/art/<path:path>")
def send_art(path):
        return send_from_directory(os.path.join(BASE_DIR, "art"), path)

@app.route("/pb/<path:path>")
@app.route("/pb/pb/<path:path>")
def send_pb(path):
        return send_file(os.path.join(BASE_DIR, "pb/" + path))

@app.route("/static/<path:path>")
def send_static(path):
        return send_from_directory(os.path.join(APP_DIR, "static"), path)

@app.route("/room/<path:path>")
def send_room(path):
        fn = os.path.join(BASE_DIR, "rooms/" + path + ".dat")
        if os.path.isfile(fn):
                return send_file(fn, attachment_filename=path + ".dat",
                                 as_attachment=True)
        else:
                abort(404)
