
from functools import wraps
from flask import Flask, request, render_template, redirect, url_for, flash, session

from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import and_, or_

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite://'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = True
app.secret_key = '\xc9ixnRb\xe40\xd4\xa5\x7f\x03\xd0y6\x01\x1f\x96\xeao+\x8a\x9f\xe4'

db = SQLAlchemy(app)


############################################
# 数据库
############################################

# 定义ORM
# User类把我们刚刚创建的几个字段定义为类变量。
# 字段使用db.Column类创建实例，字段的类型作为参数，另外还提供一些其他可选参数
# __repr__方法告诉Python如何打印class对象，方便我们调试使用
class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True)
    password = db.Column(db.String(80))
    email = db.Column(db.String(120), unique=True)

    def __repr__(self):
        return '<User %r>' % self.username
        

# 创建表格、插入数据
@app.before_first_request
def create_db():
    db.drop_all()  # 每次运行，先删除再创建
    db.create_all()
    
    admin = User(username='admin', password='root', email='admin@example.com')
    db.session.add(admin)

    guestes = [User(username='guest1', password='guest1', email='guest1@example.com'),
               User(username='guest2', password='guest2', email='guest2@example.com'),
               User(username='guest3', password='guest3', email='guest3@example.com'),
               User(username='guest4', password='guest4', email='guest4@example.com')]
    db.session.add_all(guestes)
    db.session.commit()
    

############################################
# 辅助函数、装饰器
############################################

# 登录检验（用户名、密码验证）
def valid_login(username, password):
    user = User.query.filter(and_(User.username == username, User.password == password)).first()
    if user:
        return True
    else:
        return False

# 查找用户
def find_user_by_username(username):
    user = User.query.filter(User.username == username).first()
    if user:
        return True
    else:
        return False

def find_user_by_email(email):
    user = User.query.filter(User.email == email).first()
    if user:
        return True
    else:
        return False

def register(username, password, email):
    new_user = User(username=username, password=password, email=email)
    db.session.add(new_user)
    db.session.commit()
    
############################################
# 路由
############################################

# 1.主页
@app.route('/')
def home():
    return render_template('home.html', username=session.get('username'))

# 2.登录
@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        if valid_login(request.form['username'], request.form['password']):
            flash("成功登录！")
            session['username'] = request.form.get('username')
            return redirect(url_for('home'))
        else:
            error = '错误的用户名或密码！'

    return render_template('login.html', error=error)

# 3.注册
@app.route('/regist', methods=['GET','POST'])
def regist():
    error = None
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password1']
        email = request.form['email']

        if password != request.form['password2']:
            error = '密码不一致'
        elif find_user_by_username(username):
            error = '该用户已被注册'
        elif find_user_by_email(email):
            error = '该邮箱已被使用'
        else:
            flash("注册成功！")
            register(username, password, email)
            return redirect(url_for('home'))
        
    return render_template('regist.html', error=error)

if __name__ == '__main__':
    app.run(debug = True, host='localhost', port=8080)
