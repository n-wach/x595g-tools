import by7efile
import disassembler
from readorc import orc

o = orc.Orc("chall1.exe")

info = o.to_dict()

text = info["segment_table"]["segments"][1]

exe = o.o.contents[text["offset"]:text["offset"] + text["size"]]

disassembler.disassemble(exe)

# read disassembly for the flag

