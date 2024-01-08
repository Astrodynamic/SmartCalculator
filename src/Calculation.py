import ctypes
from PySide6.QtCore import QObject, Slot


class Calculation(QObject):
    def __init__(self, path, parent=None):
        super().__init__(parent)

        self.lib = ctypes.CDLL(path)
        self.instance = None

        self.lib.__create.argtypes = [ctypes.c_void_p]
        self.lib.__create.restype = ctypes.c_void_p

        self.lib.__remove.argtypes = [ctypes.c_void_p]

        self.lib.__load.argtypes = [ctypes.c_void_p, ctypes.c_char_p]

        self.lib.__calc.argtypes = [ctypes.c_void_p, ctypes.c_double]
        self.lib.__calc.restype = ctypes.c_double

        self.lib.__empty.argtypes = [ctypes.c_void_p]
        self.lib.__empty.restype = ctypes.c_bool

        self.instance = self.lib.__create(None)


    def __del__(self):
        self.lib.__remove(self.instance)
        

    @Slot(str)
    def load(self, expression):
        self.lib.__load(self.instance, expression.encode())


    @Slot(float, result=float)
    def calc(self, value) -> float:
        return self.lib.__calc(self.instance, ctypes.c_double(value))


    @Slot(result=bool)
    def empty(self) -> bool:
        return self.lib.__empty(self.instance)
