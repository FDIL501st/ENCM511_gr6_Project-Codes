from tkinter import Tk, StringVar
from tkinter.ttk import Button, Label, Frame

class App():
    def __init__(self) -> None:
        self.win: Tk = Tk() #main window of the GUI
        # Configure main window
        self.win.title("Rock Paper Scissors") # title of the window
        self.win.geometry("600x400") # changes size of window 

        self.charTx: StringVar = StringVar()    #stores the character to transmit

    def run_app(self) -> None:
        """Adds all the buttons to the main window and runs the GUI."""
        self.createGrid()
        
        self.win.mainloop() #run the GUI

    def createGrid(self) -> None:
        """Creates the grid of the main window."""
        # Divide window into 3 rows and 2 columns
        # Rows are equal height
        # Columns are equal width
        self.win.rowconfigure(index=0, weight=1)
        self.win.rowconfigure(index=1, weight=1)
        self.win.rowconfigure(index=2, weight=1)
        self.win.columnconfigure(index=0, weight=1)
        self.win.columnconfigure(index=1, weight=1)


    def createConfigOptionButtons(self) -> None:
        """Creates the buttons. These buttons allows to change the lighting options."""
        pass    # TODO - finish function

    def createTxButton(self) -> None:
        """Create button to transmit to microcontroller."""
        self.TxButton: Button = Button(self.win, text="Select", command=self.Tx)
        self.TxButton.grid(row=2, column=1)
        pass    # TODO - finish function

    def createConfigurationLabel(self) -> None:
        """Creates the label. The label shows the most recent lighting configuration selected."""
        self.lightingCongifLabel: Label = Label(self.win, text="Select a lighting configuration to set.")
        self.lightingCongifLabel.grid(row=0, column=0, columnspan=2)
        pass    # TODO - check if function needs to be finished

    def setCharTx(self, char: str) -> None:
        pass    # TODO - finish setter

    def Tx(self) -> None:
        # This may actually be a function in a different file
        pass    # TODO - finish function to transmit charTx
