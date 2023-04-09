from flask import Flask
app = Flask(__name__)
@app.route('/')
def index():
    return "<h1>hello word<h1>"
app.run()