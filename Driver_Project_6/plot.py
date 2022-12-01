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
rxNumsStr = ''      #string to store received uint16_t numbers 
rxNumsList = []      #List to store received uint16_t numbers in int form 
rxTimesList = []   #list to store time stamps of received uint16_t numbers
startTime = time.time()   

## UART DATA CAPTURE OVER TIME INTERVAL
timeInterval = 10
while(time.time() - startTime < timeInterval):  #record data for 10 sec
    line = ser.readline() # reads uint16_t nums as single bytes till \n n stores in string
    if ((line != b' \n') and (line != b'\n')) : #removes and '\n' without num captures
        rxNumsStr = rxNumsStr + line.decode('Ascii')  # Converts string of received uint16_t num to ASCII and combines Rx nums into 1 string
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
dF['Rx Data (16 bit)'] = rxNumsList


### DATA STATISTICS
dF.describe()


### COPY RX DATA AND RX TIME IN CSV AND XLS FILES
dF.to_csv('RxData.csv', index = True)
dF.to_excel('RxData.xlsx', sheet_name='New Sheet')



### PLOT Rx DATA VS Rx TIME
fig = px.line(dF, x='Rx Time (sec)', y='Rx Data (16 bit)', title = 'RS232 Data vs Time')
fig.show()
