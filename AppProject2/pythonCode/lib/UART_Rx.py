import serial  # pip install pyserial  or conda install pyserial


def RxChar(self) -> None:
    ## OPEN SERIAL PORT N CAPTURE FIXED NUMBER OF BYTES
    ser = serial.Serial(port= "COM4", baudrate = 9600, bytesize = 8, timeout =2, stopbits = serial.STOPBITS_ONE)

    s=ser.read(1)  # reads incoming 100 serial bytes n store as string in s
    ser.close()
    sChar = s.decode('Ascii')  #convert bytes to ascii

    ## DATA CLEAN UP
    sChar = sChar.strip()  # removes any spaces or \n or \r from beginning and end of string
    sChar = sChar.upper() # make sure the character is in uppercase

    return sChar[0] # return the first, if there is a string of characters

if __name__ == "__main__":
    RxChar()

