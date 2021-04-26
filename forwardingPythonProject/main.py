# This Python file uses the following encoding: utf-8

import sys
from PySide2.QtWidgets import QApplication, QWidget
import QtQuick.Extras 1.4

if __name__ == "__main__":

    app = QApplication([])

    window = QWidget()
    window.show()

    sys.exit(app.exec_())
