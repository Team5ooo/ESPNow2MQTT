



# python 3.6

import random
import time
import serial
import json
from serial import Serial

from paho.mqtt import client as mqtt_client
ser = serial.Serial('/dev/ttyUSB0', 115200)


# generate client ID with pub prefix randomly
client_id = f'python-mqtt-{random.randint(0, 1000)}'
broker = '10.45.50.103'
port = 1883

ID = "987123987"
topic = "python/" + ID

#client_id = 'thebroker'
username = 'admin'
password = 'passwd'

def connect_mqtt():
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)

    client = mqtt_client.Client(client_id)
    client.username_pw_set(username, password)
    client.on_connect = on_connect
    client.connect(broker, port)
    return client


def publish(client):
    while True:



        data = (ser.readline().decode('ascii')) #split('\r\n')
#    data.reset_input_buffer()
        try:
            dict_json = json.dumps(data)
            dict_json = json.loads(json.dumps(data))
            dict_json_ID = json.loads(data)
#        print(dict_json)
            ID = dict_json_ID.get("ID")
#        print(dict_json)
            #ID = dict_json.get("ID")
            topic = "python/" + ID
            msg = str(dict_json)
            result = client.publish(topic, msg)
        # result: [0, 1]
            status = result[0]
            if status == 0:
                print(f"Send `{msg}` to topic `{topic}`")
            else:                
                print(f"Failed to send message to topic {topic}")
                print(ID)
        except json.JSONDecodeError as e:
            print("JSON:", e)

def run():
    client = connect_mqtt()
    client.loop_start()
    publish(client)


if __name__ == '__main__':
    run()


#client = mqtt.Client("mqtt-test") # client ID "mqtt-test"
#client.on_connect = on_connect
#client.on_message = on_message
#client.username_pw_set("admin", "passwd")
#client.connect('127.0.0.1', 1883)
#client.loop_forever()  # Start networking daemon

