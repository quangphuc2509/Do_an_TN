from PyQt5 import QtWidgets, uic
from PyQt5.QtWidgets import QMessageBox
from PyQt5.QtCore import *
from PyQt5.QtGui import *

import cv2
import pandas as pd
import os
import tkinter as tk
import configparser

from App_Scanning import Worker1
from BarcodeGenerator import BarcodeGeneratorApp

# Load config file
config = configparser.ConfigParser()
config.read('config.ini')

# Load the UI file
ui_file = config.get('FILES', 'ui_file')
Ui_MainWindow, QtBaseClass = uic.loadUiType(ui_file)

app_directory = config.get('DIR', 'app_directory')

class App_UI(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.initUI()
        
    def initUI(self):
        self.setWindowTitle("BarcodeScanner Application")
        self.initCamera()
        self.initButtons()
        self.initIcons()
        self.loadData()
        self.worker1.Datetime_scan.connect(self.update_datetime_label)

    def initCamera(self):
        self.worker1 = Worker1(self)
        self.worker1.ImageUpdate.connect(self.ImageUpdateSlot)
        self.camera = cv2.VideoCapture(1, cv2.CAP_DSHOW)
        # self.camera = cv2.VideoCapture(0)

    def initButtons(self):
        self.ui.Start.clicked.connect(self.StartFeed)
        self.ui.Barcode_Create.clicked.connect(self.CreateBarcode)
        self.ui.Excel.clicked.connect(self.ExportExcel)
        self.ui.Import.clicked.connect(self.switch_to_import_mode)
        self.ui.Export.clicked.connect(self.switch_to_export_mode)

    def initIcons(self):
        self.setIcon(self.ui.Start, r'Resources\image\scan_logo.png')
        self.setIcon(self.ui.Barcode_Create, r"Resources\image\barcode.jpg")
        self.setIcon(self.ui.Excel, r"Resources\image\excel.png")
        self.setIcon(self.ui.Import, r"Resources\image\product.jpg")
        self.setIcon(self.ui.Export, r"Resources\image\product.jpg")

    def setIcon(self, widget, icon_path):
        icon = QIcon(icon_path)
        pixmap = icon.pixmap(36, 36)
        widget.setIcon(QIcon(pixmap))
        widget.setIconSize(pixmap.size())

    def loadData(self):
        self.product_data = pd.read_csv(config.get('FILES', 'product_data_file')).dropna(subset=['SKU'])
        self.product_data.reset_index(drop=True, inplace=True)

    def CreateBarcode(self):
        root = tk.Tk()
        BarcodeGeneratorApp(root)
        root.mainloop()
    
    def switch_to_import_mode(self):
        QMessageBox.information(self, "Mode Changed", "Switch to Import Mode")
        self.current_mode = 'Import'

    def switch_to_export_mode(self):
        QMessageBox.information(self, "Mode Changed", "Switch to Export Mode")
        self.current_mode = 'Export'

    @pyqtSlot(QImage)
    def ImageUpdateSlot(self, Image):
        self.ui.camera.setPixmap(QPixmap.fromImage(Image))

    @pyqtSlot(str)
    def update_datetime_label(self, scanned_datetime):
        self.ui.datetime.setText(scanned_datetime)

    def StartFeed(self):
        if not self.worker1.isRunning():
            self.worker1.start()

    def ExportExcel(self):
        try:
            file = config.get('FILES', 'output_file')
            path = os.path.join(app_directory,file)
            os.startfile(path)
            QMessageBox.information(self, "Export Success", "Data exported to Excel successfully.")
        except Exception as e:
            QMessageBox.critical(self, "Export Error", f"Error exporting data to Excel: {e}")