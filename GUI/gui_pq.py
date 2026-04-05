import PyQt5
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QMainWindow, QHBoxLayout, QVBoxLayout, QLabel, QApplication, QPushButton, QWidget


class mainWindow(QMainWindow):
    def __init__(self):
        super().__init__()


        #Layout erstellen
        layout = QHBoxLayout()
        layoutRight = QVBoxLayout()

        #Linkes Platzhalter Widget
        layout.addWidget(self.makeLabel("Platzhalter Radar"))

        #Rechtes Platzhalter Widget
        layoutRight.addWidget(self.makeLabel("Platzhalter Abstand:"))
        layoutRight.addWidget(self.makeLabel("Winkel"))
        layoutRight.addWidget(QPushButton("Start"))
        layoutRight.addWidget(QPushButton("Stop"))

        #Rechtes Layout anhägen
        layout.addLayout(layoutRight)

        #Center Widget für Fenster
        container = QWidget()
        container.setLayout(layout)
        self.setCentralWidget(container)


    def makeLabel(self, text):
        label = QLabel(text)
        label.setAlignment(Qt.AlignCenter)
        return label

app = QApplication([])
window = mainWindow()
window.show()
app.exec_()


