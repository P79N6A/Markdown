import sys
import os
import time
import pika
import importlib

credentials = pika.PlainCredentials('guest', 'guest123456')
connection = pika.BlockingConnection(pika.ConnectionParameters("10.85.0.83", credentials=credentials))
channel = connection.channel()

#no durable
#channel.queue_declare(queue='hello')

#no ack
def callback(ch, method, properties, body):
    print(" [x] Received %r" % body)
    time.sleep(body.count(b'.'))
    print(" [x] Done")
    ch.basic_ack(delivery_tag = method.delivery_tag)

#channel.basic_qos(prefetch_count=1)
channel.basic_consume(callback,
                      queue='192.168.1.9')

channel.start_consuming()

"""

#durable 
#channel.queue_declare(queue='task_queue', durable=True)

#ack 
def callback(ch, method, properties, body):
    print " [x] Received %r" % (body,)
    time.sleep( body.count('.') )
    print " [x] Done"
    ch.basic_ack(delivery_tag = method.delivery_tag)


#if not set prefetch_count : the worker that message is derived is robin in msg queue

#if set prefetch_count     : the worker that message is derived is decided by ack and prefetch_count, then robin

channel.basic_qos(prefetch_count=1)

#start receiver
channel.basic_consume(callback,
                      queue='task_queue')


print(' [*] Waiting for messages. To exit press CTRL+C')
channel.start_consuming()

"""
