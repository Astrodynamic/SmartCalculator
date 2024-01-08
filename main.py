import sys
from pathlib import Path

from PySide6.QtGui import QGuiApplication
from PySide6.QtQml import QQmlApplicationEngine

from data import resource_rc
from src.Calculation import Calculation


if __name__ == "__main__":
    app = QGuiApplication(sys.argv)

    calculation = Calculation(Path(__file__).resolve().parent / "lib/calculation/libCalculation.so")

    engine = QQmlApplicationEngine()
    engine.rootContext().setContextProperty("Calculation", calculation)

    qml = Path(__file__).resolve().parent / "view/main.qml"
    engine.load(qml)

    if not engine.rootObjects():
        sys.exit(-1)

    sys.exit(app.exec())
