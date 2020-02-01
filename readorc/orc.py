from readorc import ksy_orc
from by7efile import By7eFile
import pprint


class Orc:
    def __init__(self, path):
        self.file = By7eFile(path)
        self.o = ksy_orc.KsyOrc.from_bytes(self.file.data)

    def __repr__(self):
        return pprint.pformat(self.to_dict(), indent=2)

    def to_dict(self):
        return {
            "header": str(self.o.header),
            "filetype": self.o.file_type.name,
            "entrypoint": (self.o.entry_point if self.o.has_entry_point else "None"),
            "symbol_table": {
                "num_entries": self.o.symbol_table.num_entries.v,
                "symbols": [
                    {
                        "name": symbol.name,
                        "section": symbol.section.v if symbol.is_defined else "Undefined",
                        "offset": symbol.offset.v if symbol.is_defined else "Undefined",
                    } for symbol in self.o.symbol_table.symbols
                ]
            },
            "relocation_table": {
                "num_entries": self.o.relocation_table.num_entries.v,
                "relocations": [
                    {
                        "offset": relocation.offset.v,
                        "section": relocation.section.v,
                        "symbol": relocation.symbol,
                        "plus": relocation.plus.v
                    } for relocation in self.o.relocation_table.relocations
                ]
            },
            "section_table": {
                "num_entries": self.o.section_table.num_entries.v,
                "sections": [
                    {
                        "permissions": bin(section.permissions),
                        "offset": section.offset.v,
                        "name": section.name,
                        "size": section.size.v,
                    } for section in self.o.section_table.sections
                ]
            },
            "segment_table": {
                "num_entries": self.o.segment_table.num_entries.v,
                "segments": [
                    {
                        "name": segment.name,
                        "offset": segment.offset.v,
                        "base": segment.base.v,
                        "permissions": bin(segment.permissions),
                        "type": segment.type.name,
                    } for segment in self.o.segment_table.segments
                ]
            }
        }

