import by7efile
import struct


class ORCFile:
    HEAD = "4scc"

    def __init__(self, path):
        self.file = by7efile.By7eFile(path)
        self.head = unpack(ORCFile.HEAD, self.file.data)
        self.header = self.head[0]
        self.file_type = self.head[1]
        self.has_entry_point = self.head[2]
        # ...


def unpack(fmt, data):
    return struct.unpack(fmt, data[0:struct.calcsize(fmt)])


