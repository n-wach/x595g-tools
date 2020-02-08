import by7efile
import disassembler

file = by7efile.By7eFile("chall1.exe")

disassembler.disassemble(file.data)

