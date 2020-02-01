from readorc import ksy_orc
from by7efile import By7eFile


class Orc:
    def __init__(self, path):
        self.file = By7eFile(path)
        self.o = ksy_orc.KsyOrc.from_bytes(self.file.data)

    def __repr__(self):
        return "\n".join([
            "Header: " + str(self.o.header),
            "File Type: " + self.o.file_type.name,
            "Entry Point: " + (self.o.entry_point if self.o.has_entry_point else "None"),
            "Symbol Table: ",
        ])
