from by7efile import By7eFile
from readorc import orc


def open_orc(path):
    file = By7eFile(path)
    return orc.Orc.from_bytes(file.data)



