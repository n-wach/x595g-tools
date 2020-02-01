# This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

from pkg_resources import parse_version
from kaitaistruct import __version__ as ks_version, KaitaiStruct, KaitaiStream, BytesIO
from enum import Enum


if parse_version(ks_version) < parse_version('0.7'):
    raise Exception("Incompatible Kaitai Struct Python API: 0.7 or later is required, but you have %s" % (ks_version))

class KsyOrc(KaitaiStruct):

    class FileType(Enum):
        exe = 0
        obj = 1

    class Bool(Enum):
        false = 0
        true = 1

    class SegmentType(Enum):
        note = 1
        progbits = 2
    def __init__(self, _io, _parent=None, _root=None):
        self._io = _io
        self._parent = _parent
        self._root = _root if _root else self
        self._read()

    def _read(self):
        self.header = self._io.ensure_fixed_contents(b"\x6F\x72\x63\x00")
        self.file_type = self._root.FileType(self._io.read_u1())
        self.has_entry_point = self._root.Bool(self._io.read_u1())
        if self.has_entry_point == self._root.Bool.true:
            self.entry_point = self._io.read_u1()

        self.symbol_table = self._root.SymbolTable(self._io, self, self._root)
        self.relocation_table = self._root.RelocationTable(self._io, self, self._root)
        self.section_table = self._root.SectionTable(self._io, self, self._root)
        self.segment_table = self._root.SegmentTable(self._io, self, self._root)
        self.contents = []
        i = 0
        while not self._io.is_eof():
            self.contents.append(self._io.read_u1())
            i += 1


    class Word28(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.unpacked = self._io.read_u4le()

        @property
        def v(self):
            if hasattr(self, '_m_v'):
                return self._m_v if hasattr(self, '_m_v') else None

            self._m_v = (((((self.unpacked & (255 << 0)) << 0) | ((self.unpacked & (255 << 8)) >> 1)) | ((self.unpacked & (255 << 16)) >> 2)) | ((self.unpacked & (255 << 24)) >> 3))
            return self._m_v if hasattr(self, '_m_v') else None


    class Section(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.permissions = self._io.read_u1()
            self.offset = self._root.Word28(self._io, self, self._root)
            self.name = (self._io.read_bytes_term(0, False, True, True)).decode(u"ascii")
            self.size = self._root.Word28(self._io, self, self._root)


    class Segment(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.name = (self._io.read_bytes_term(0, False, True, True)).decode(u"ascii")
            self.offset = self._root.Word28(self._io, self, self._root)
            self.base = self._root.Word28(self._io, self, self._root)
            self.permissions = self._root.Word28(self._io, self, self._root)
            self.type = self._root.SegmentType(self._io.read_u1())


    class RelocationTable(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.num_entries = self._root.Word28(self._io, self, self._root)
            self.relocations = [None] * (self.num_entries.v)
            for i in range(self.num_entries.v):
                self.relocations[i] = self._root.Relocation(self._io, self, self._root)



    class Symbol(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.name = (self._io.read_bytes_term(0, False, True, True)).decode(u"ascii")
            self.is_defined = self._root.Bool(self._io.read_u1())
            if self.is_defined == self._root.Bool.true:
                self.section = self._root.Word28(self._io, self, self._root)

            if self.is_defined == self._root.Bool.true:
                self.offset = self._root.Word28(self._io, self, self._root)



    class SectionTable(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.num_entries = self._root.Word28(self._io, self, self._root)
            self.sections = [None] * (self.num_entries.v)
            for i in range(self.num_entries.v):
                self.sections[i] = self._root.Section(self._io, self, self._root)



    class Relocation(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.offset = self._root.Word28(self._io, self, self._root)
            self.section = self._root.Word28(self._io, self, self._root)
            self.symbol = (self._io.read_bytes_term(0, False, True, True)).decode(u"ascii")
            self.plus = self._root.Word28(self._io, self, self._root)


    class SegmentTable(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.num_entries = self._root.Word28(self._io, self, self._root)
            self.segments = [None] * (self.num_entries.v)
            for i in range(self.num_entries.v):
                self.segments[i] = self._root.Segment(self._io, self, self._root)



    class SymbolTable(KaitaiStruct):
        def __init__(self, _io, _parent=None, _root=None):
            self._io = _io
            self._parent = _parent
            self._root = _root if _root else self
            self._read()

        def _read(self):
            self.num_entries = self._root.Word28(self._io, self, self._root)
            self.symbols = [None] * (self.num_entries.v)
            for i in range(self.num_entries.v):
                self.symbols[i] = self._root.Symbol(self._io, self, self._root)




