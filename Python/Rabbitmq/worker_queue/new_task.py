import sys
import pika


credentials = pika.PlainCredentials('admin', 'cicloud@tencent.com')
connection = pika.BlockingConnection(pika.ConnectionParameters("10.85.0.83", credentials=credentials))
channel = connection.channel()

#no durable
#channel.queue_declare(queue='hello')

"""
message = ' '.join(sys.argv[1:]) or "Hello World!"
channel.basic_publish(exchange='',
                      routing_key='hello',
                      body=message)
"""


#durable
channel.queue_declare(queue='task_queue', durable=True, arguments={"x-max-priority" : 10})
#channel.queue_declare(queue='task_queue1', passive=True)

arg_len = len(sys.argv)

if arg_len == 1:
    message = "Hello World!"
    priority = 0
elif arg_len == 2:
    message = sys.argv[1]
    priority = 0
else:
    message = sys.argv[1]
    priority = int(sys.argv[2])

channel.basic_publish(exchange='',
                      routing_key='task_queue',
                      body=message, 
		      properties=pika.BasicProperties(
                         delivery_mode=2,
                         expiration="60000",
                         priority=priority,
                      ))


print(" [x] Sent %r" % message)

connection.close()
