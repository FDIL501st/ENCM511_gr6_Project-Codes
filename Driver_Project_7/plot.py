import numpy as np
import math
import csv
import serial
import time
import pandas as pd
import plotly.express as px

import plotly.io as pio
pio.renderers.default = '' # plots plotly graph on the terminal window

# OPEN SERIAL PORT
ser = serial.Serial(port= "COM4", baudrate = 9600, bytesize = 8, timeout =2, stopbits = serial.STOPBITS_ONE)


## INITIALIZATIONS
rxNumsStr = ''      #string to store received 1 or 0 
rxNumsList = []      #List to store received 1 or 0 in int form 
rxTimesList = []   #list to store time stamps of received 1 or 0
startTime = time.time()   

## UART DATA CAPTURE OVER TIME INTERVAL
timeInterval = 30
while(time.time() - startTime < timeInterval):  #record data for 30 sec
    line = ser.readline() # reads 1 or 0 as single bytes till \n n stores in string
    if ((line != b' \n') and (line != b'\n')) : #removes and '\n' without num captures
        rxNumsStr = rxNumsStr + line.decode('Ascii')  # Converts string of received 1 or 0 to ASCII and combines Rx nums into 1 string
        timeMeas = time.time() - startTime # Time stamp received number
        rxTimesList.append(timeMeas) #save time stamps in a list
        
## CLOSE SERIAL PORT
ser.close()  # close any open serial ports

##rxStr = rxNumsStr #checka

### Rx DATA CLEANUP AND STRING TO INT CONVERSION
rxNumsStr = rxNumsStr.strip() # remove unwanted chars and spaces 
rxNumsList = rxNumsStr.split(' \n ')  # split string by \n n store in list
rxNumsList = [int(elem) for elem in rxNumsList]  # convert char in List into int

### CONVERT Rx DATA INTO DATA FRAME
dF = pd.DataFrame()
dF['Rx Time (sec)'] = rxTimesList
dF['Power-supply Status (1 = over-supply, 0 = normal)'] = rxNumsList


### DATA STATISTICS
dF.describe()


### COPY RX DATA AND RX TIME IN CSV AND XLS FILES
dF.to_csv('Group6.csv', index = True)
dF.to_excel('Group6.xlsx', sheet_name='New Sheet')



### PLOT Rx DATA VS Rx TIME
fig = px.line(dF, x='Rx Time (sec)', y='Power-supply Status (1 = over-supply, 0 = normal)', title = 'Group 6')
fig.show()
