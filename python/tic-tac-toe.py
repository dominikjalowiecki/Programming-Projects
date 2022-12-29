from tkinter import *
from tkinter import messagebox
import random
import numpy

class TicTacToe:
    hor = ' | '
    ver = '--- '

    def __init__(self, boardSize=3):
        self.boardSize = boardSize
        self.player = random.choice((0, 1))
        self.playerSym = ['X', 'O']
        self.breakStatus = False
        self.drawStatus = False

        self.matrix = numpy.full((self.boardSize, self.boardSize), ' ')

        self.tk = Tk()
        self.tkGene()
        self.tk.mainloop()

    def tkGene(self):
        self.tk.geometry(str(100 * self.boardSize) + 'x' + str(100 * self.boardSize))
        self.tk.resizable(0, 0)

        self.labels = numpy.empty((self.boardSize, self.boardSize), dtype=object)
        for r in range(self.boardSize):
            for c in range(self.boardSize):
                fr = Frame(self.tk, width=100, height=100)
                fr.grid(row=r, column=c)
                fr.pack_propagate(False)

                self.labels[r][c] = Label(fr, text=' ', font=('Arial', 15), bd=2, relief='raised')
                self.labels[r][c].place(relx=0.5, rely=0.5, anchor=CENTER, relwidth=1, relheight=1)

                blablica = (lambda r1, c1: lambda e: self.gameCore(r1, c1))(r, c)
                self.labels[r][c].bind('<Button-1>', blablica)

    def gameCore(self, r, c):
        self.playerInteraction(r, c)
        self.winHandling(self.winCheck())

        if self.breakStatus: self.tk.destroy()

    def playerInteraction(self, r, c):
        try:
            # Getting input from players
            row, col = r, c

            # Updating matrix
            if self.matrix[row][col] == ' ':
                self.matrix[row][col] = self.playerSym[self.player]
                self.labels[r][c].config(text=self.playerSym[self.player])

                # Player toogle
                self.player ^= 1

        # Error handling
        except Exception as e:
            print(f'>   {e}')

    def winCheckFunc(self, l):
        l = list(l)
        if l[0] != ' ' and l.count(l[0]) == len(l):
            return True

    def winCheck(self):
        # Row check
        for row in self.matrix:
            if self.winCheckFunc(row):
                return True

        # Col check
        cl = numpy.transpose(self.matrix)
        for col in cl:
            if self.winCheckFunc(col):
                return True

        # Diagonal check
        diags = []
        for id in range(len(self.matrix)):
            diags.append(self.matrix[id][id])
        if self.winCheckFunc(diags):
            return True

        diags = []
        for idx, rev_idx in enumerate(reversed(range(len(self.matrix)))):
            diags.append(self.matrix[idx][rev_idx])
        if self.winCheckFunc(diags):
            return True

        # Draw check
        if ' ' not in self.matrix:
            self.drawStatus = True

        # Return if no condition fullfilled
        return False

    def winHandling(self, status):
        if status:
            # Win status handling
            info = messagebox.askquestion('TicTacToe', f'Player {self.player + 1} won the game!\nDo you want to play again?')
            if info == 'yes':
                self.tk.destroy()
                self.__init__()
            else:
                self.breakStatus = True
        else:
            # Draw status handling
            if self.drawStatus:
                info = messagebox.askquestion('TicTacToe', f'The game has finished with draw result!\nDo you want to play again?')
                if info == 'yes':
                    self.tk.destroy()
                    self.__init__()
                else:
                    self.breakStatus = True

if __name__ == '__main__':
    game = TicTacToe()