from tkinter import Tk, StringVar
from tkinter.ttk import Label, Button
from functools import partial
from lib.UART_Tx import TxChar

class App():
    def __init__(self) -> None:
        self.win: Tk = Tk() #main window of the GUI
        # Configure main window
        self.win.title("Lighting System Control App") # title of the window
        self.win.geometry("600x400") # changes size of window 

        self.charTx: StringVar = StringVar()    #stores the character to transmit

    def run_app(self) -> None:
        """
        Adds all the buttons to the main window and runs the GUI.
        """

        self.createGrid()
        self.createConfigurationLabel()
        self.createConfigOptionButtons()
        self.createTxButton()

        self.win.mainloop() #run the GUI

    def createGrid(self) -> None:
        """Creates the grid of the main window."""
        # Divide window into 4 rows and 2 columns
        # Rows are equal height
        # Columns are equal width
        self.win.rowconfigure(index=0, weight=1)
        self.win.rowconfigure(index=1, weight=1)
        self.win.rowconfigure(index=2, weight=1)
        self.win.rowconfigure(index=3, weight=1)
        self.win.columnconfigure(index=0, weight=1)
        self.win.columnconfigure(index=1, weight=1)


    def createConfigOptionButtons(self) -> None:
        """Creates the buttons. These buttons allows to change the lighting options."""
        self.ON_Button: Button = Button(self.win, text="Keep lights on", command= partial(self.updateConfiguration, 'O'))
        self.OFF_Button: Button = Button(self.win, text="Turn lights off", command= partial(self.updateConfiguration, 'F'))
        self.ONE_Button: Button = Button(self.win, text="Blink lights every 1s", command= partial(self.updateConfiguration, '1'))
        self.TWO_Button: Button = Button(self.win, text="Blink lights every 2s", command= partial(self.updateConfiguration, '2'))
        self.THREE_Button: Button = Button(self.win, text="Blink lights every 3s", command= partial(self.updateConfiguration, '3'))

        self.ON_Button.grid(row=1, column=0)
        self.OFF_Button.grid(row=1, column=1)
        self.ONE_Button.grid(row=2, column=0)
        self.TWO_Button.grid(row=2, column=1)
        self.THREE_Button.grid(row=3, column=0)

    def createTxButton(self) -> None:
        """Create button to transmit to microcontroller."""
        self.TxButton: Button = Button(self.win, text="Use lighting configuration", command=self.Tx)
        self.TxButton.grid(row=3, column=1)   

    def createConfigurationLabel(self) -> None:
        """Creates the label. The label shows the most recent lighting configuration selected."""
        self.lightingCongifLabel: Label = Label(self.win, text="Select a lighting configuration to set.")
        self.lightingCongifLabel.grid(row=0, column=0, columnspan=2)

    def updateConfiguration(self, char: str) -> None:
        """Sets the value of charTx and updates current selected configuration shown by label."""
        self.charTx.set(char)
        self.updateLabel()

    def updateLabel(self) -> None:
        """
        Updates the label to show the current selected configuration based off of charTx.
        """
        # Base starting text of label text for most cases
        newLabelText: str = "Lighting Configuration Selected: Lights "

        char: str = self.charTx.get()

        if char == 'O':
            newLabelText += "ON"
            
        elif char == 'F':
            newLabelText += "OFF"
            
        elif char == '1':
            newLabelText += "Blink every 1s"
            
        elif char == '2':
            newLabelText += "Blink every 2s"

        elif char == '3':
            newLabelText += "Blink every 3s"
        
        else:
            newLabelText = "Lighting Configuration Not Selected"

        self.lightingCongifLabel.config(text=newLabelText)

    def Tx(self) -> None:
        """
        Transmit charTx to USB port. This lets the char later be recieved.
        """
        char: str = self.charTx.get()
        if char != '':
            TxChar(char)

if __name__ == "__main__":
    app = App()
    app.run_app()