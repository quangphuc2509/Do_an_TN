import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QPushButton, QWidget, QLabel, QHBoxLayout
from PyQt5.QtCore import QPropertyAnimation, QRect

class App(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Giao Diện Chính")
        self.setGeometry(100, 100, 800, 600)

        # Tạo widget chính
        self.central_widget = QWidget()
        self.setCentralWidget(self.central_widget)

        # Layout chính
        self.main_layout = QHBoxLayout(self.central_widget)

        # Khung bên trái
        self.sidebar = QWidget()
        self.sidebar.setFixedWidth(200)
        self.sidebar_layout = QVBoxLayout(self.sidebar)
        self.sidebar.setStyleSheet("background-color: lightgrey;")
        self.main_layout.addWidget(self.sidebar)

        # Các tùy chọn trong sidebar
        self.create_sidebar_content()

        # Nút ẩn/hiện sidebar
        self.toggle_button = QPushButton("☰")
        self.toggle_button.clicked.connect(self.toggle_sidebar)
        self.toggle_button.setFixedSize(30, 30)
        self.main_layout.addWidget(self.toggle_button)

        self.sidebar_visible = True

    def create_sidebar_content(self):
        label1 = QLabel("Tính năng 1")
        label2 = QLabel("Tính năng 2")
        label3 = QLabel("Tính năng 3")
        self.sidebar_layout.addWidget(label1)
        self.sidebar_layout.addWidget(label2)
        self.sidebar_layout.addWidget(label3)

    def toggle_sidebar(self):
        animation = QPropertyAnimation(self.sidebar, b"geometry")
        animation.setDuration(300)
        current_geometry = self.sidebar.geometry()

        if self.sidebar_visible:
            end_geometry = QRect(current_geometry.x(), current_geometry.y(), 0, current_geometry.height())
        else:
            end_geometry = QRect(current_geometry.x(), current_geometry.y(), 200, current_geometry.height())

        animation.setStartValue(current_geometry)
        animation.setEndValue(end_geometry)
        animation.start()
        self.sidebar_visible = not self.sidebar_visible

if __name__ == "__main__":
    app = QApplication(sys.argv)
    main_window = App()
    main_window.show()
    sys.exit(app.exec_())
