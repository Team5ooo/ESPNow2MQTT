
import serial
import json
import time
from serial import Serial

#ser = serial.Serial('COM4', baudrate = 9600, timeout=1)
ser = serial.Serial('/dev/ttyUSB0', 115200)
while 1:

    data = (ser.readline().decode('ascii')) #split('\r\n')
#    data.reset_input_buffer()
    try:
        dict_json = json.loads(data)
#        print(dict_json)
        ID = dict_json.get("ID")

        print(ID)
    except json.JSONDecodeError as e:
        print("JSON:", e)
    #j = json.loads(data)


#    file = "C:/Users/Mike/Desktop/test.json"

 #   my_data_file = open(file, 'w')

  #  with open(file1, "w") as my_data_file :
  #      json.dump(data, my_data_file)

