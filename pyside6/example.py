import sys
import PySide6.QtWidgets

class MyWidget(PySide6.QtWidgets.QWidget):
    def __init__(self):
        super().__init__()

def main():
    app = PySide6.QtWidgets.QApplication([])
    widget = MyWidget()
    widget.resize(1024,600)

    img = PySide6.QtGui.QImage('background.png')
    painter = PySide6.QtGui.QPainter()
    painter.drawImage(1,1,img,1,1,10,10)

    widget.show()
    
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()