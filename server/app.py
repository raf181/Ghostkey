# app.py
from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_login import LoginManager
from flask_migrate import Migrate
from routes import blueprint_name
from models import db, User

app = Flask(__name__)
app.config['SECRET_KEY'] = 'your_secret_key'  # Replace with a strong secret key
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///c2_framework.db'
app.config['SQLALCHEMY_BINDS'] = {
    'backup': 'sqlite:///c2_framework_backup.db'
}
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False

db.init_app(app)  # Initialize db with the app
migrate = Migrate(app, db)

login_manager = LoginManager()
login_manager.init_app(app)
login_manager.login_view = 'blueprint_name.login'

@login_manager.user_loader
def load_user(user_id):
    return User.query.get(int(user_id))

# Register blueprint
app.register_blueprint(blueprint_name)

if __name__ == '__main__':
    app.run(host="0.0.0.0")
