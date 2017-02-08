- install python => pip => django and install nginx


### WUSGI ###

- install uwsgi

- verify uwsgi

	- test.py

			def application(env, start_response):
				start_response('200 OK', [('Content-Type','text/html')])
				return "Hello World"

	- run uwsgi

			uwsgi --http-socket :8000 --plugin python --wsgi-file test.py --process 3


- generate a uwsgi configure file

		[uwsgi]
		socket = 127.0.0.1:9090
		master = true         //主进程
		vhost = true          //多站模式
		no-site = true        //多站模式时不设置入口模块和文件
		workers = 2           //子进程数
		reload-mercy = 10     
		vacuum = true         //退出、重启时清理文件
		max-requests = 1000   
		limit-as = 512
		buffer-size = 30000
		pidfile = /var/run/uwsgi8000.pid    //pid文件，用于下面的脚本启动、停止该进程
		daemonize = /website/uwsgi8000.log
		plugins = python
	    pythonpath = /usr/local/lib/python2.7/dist-packages


- run uwsgi

		uwsgi --ini configure_path

- reload uwsgi configure file

		uwsgi --reload /var/run/uwsgi8000.pid

### nginx ###

- config nginx configure file

		server {
			listen 80;
			server_name localhost;
			location / {
				uwsgi_pass 127.0.0.1:8000;
				uwsgi_param UWSGI_SCRIPT hello.wsgi;
				uwsgi_param UWSGI_CHDIR /data/hello;
			    include uwsgi_params;
			}
		}

- reload nginx configure file

		nginx -s reload 