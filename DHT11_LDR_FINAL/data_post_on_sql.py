from flask import Flask, request
from my_db import execute_select_query
from my_db import execute_query
from my_response import create_response

app = Flask(__name__)

@app.route("/readingdata", methods=["GET"])
def get_readings():
    query = "select time, temperature, humidity,ldrrd from readings;"

    readings = execute_select_query(query)

    list_readings = []
    for (time ,temperature, humidity, ldrrd ) in readings:
        list_readings.append({
            #"time":time,
            "temperature":temperature,
            "humidity":humidity,
            "ldrrd":ldrrd,
            "time":time
            
        })

    print(list_readings)
    return create_response(list_readings)
#-------------------------------------------------------------

@app.route("/readingdata", methods=["POST"])
def insert_readings():
	
    temperature = request.get_json().get('temperature')
    humidity = request.get_json().get('humidity')
    ldrrd = request.get_json().get('ldrrd')
    
    query = f"insert into readings (temperature, humidity, ldrrd) values ({temperature}, {humidity}, {ldrrd});"

    execute_query(query)

    return create_response("readings added successfully")



#------------------------------------------------------------------

app.run(host="0.0.0.0", port=3000, debug=True)
