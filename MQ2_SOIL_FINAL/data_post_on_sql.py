from flask import Flask, request
from my_db import execute_select_query
from my_db import execute_query
from my_response import create_response

app = Flask(__name__)

@app.route("/readingdata", methods=["GET"])
def get_readings2():
    query = "select time,soil_moisture,MQ2 from readings2;"

    readings = execute_select_query(query)

    list_readings2 = []
    for (time ,soil_moisture,MQ2 ) in readings:
        list_readings2.append({
            #"time":time,
            "soil_moisture":soil_moisture,
            "MQ2":MQ2,
            "time":time
            
        })

    print(list_readings2)
    return create_response(list_readings2)
#-------------------------------------------------------------

@app.route("/readingdata", methods=["POST"])
def insert_readings2():
	
    soil_moisture= request.get_json().get('soil_moisture')
    MQ2 = request.get_json().get('MQ2')
    
    
    query = f"insert into readings2 (soil_moisture,MQ2) values ({soil_moisture}, {MQ2});"

    execute_query(query)

    return create_response("readings added successfully")



#------------------------------------------------------------------

app.run(host="0.0.0.0", port=3000, debug=True)
