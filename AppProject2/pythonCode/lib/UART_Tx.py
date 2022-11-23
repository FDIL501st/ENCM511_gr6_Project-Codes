import serial

def TxChar(char:str) -> None:
    """
    Transmit the char into the USB port.
    """
    # Make sure char is just 1 character
    # Done by just sending the first character of char
    #   if char is already one character, nothing happens then
    
    char = char[0]

    PORT: str = "COM4" #Changed depending on name of port need to write to
    BAUDRATE: int = 9600    #Changed depending on clock speed of 
    # 9600 for 8MHz clock
    ser = serial.Serial(PORT = PORT, baudrate = BAUDRATE, bytesize = 8, write_timeout =1, stopbits = serial.STOPBITS_ONE)

    ser.write(char.encode('Ascii')) #transmit char as ascii code

    ser.close()


if __name__ == "__main__":
    TxChar('1')