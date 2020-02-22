def decode_t1_c(b):
    op = b[0] & 0b00001111
    ds = b[1] & 0b01111000 >> 3
    cn = b[5] << 21 | b[4] << 14 | b[3] << 7 | b[2] << 0
    ops = [
        "ADD",
        "SUB",
        "MUL",
        "DIV",
        "CMP",
        "TST",
        "AND",
        "ORR",
        "XOR",
        "STR",
        "STB",
        "LOD",
    ]
    print("{} r{} {}({})".format(ops[op], ds, cn, chr(cn)))


def decode_t1_r(b):
    op = b[0] & 0b00001111
    s = b[1] & 0b01111000 >> 3
    d = b[1] & 0b00000111 << 1 | (b[2] & 0b01000000) >> 6
    ops = [
        "ADD",
        "SUB",
        "MUL",
        "DIV",
        "CMP",
        "TST",
        "AND",
        "ORR",
        "XOR",
        "STR",
        "STB",
        "LOD",
    ]
    print("{} r{} r{}".format(ops[op], d, s))


def decode_t2_c(b):
    op = b[0] & 0b000001111
    cn = b[1] << 21 | b[2] << 14 | b[3] << 7 | b[4] << 0
    ops = [
        "JMP",
        "JLT",
        "JEQ",
        "CAL",
        "PSH",
        "POP",
        "NOT",
        "OUT",
        "INP",
        "AMP",
        "ALT",
        "AEQ",
        "AAL",
    ]
    print("{} {}".format(ops[op], cn))


def decode_t2_r(b):
    op = b[0] & 0b000001111
    v = b[1] & 0b01111000 >> 3
    ops = [
        "JMP",
        "JLT",
        "JEQ",
        "CAL",
        "PSH",
        "POP",
        "NOT",
        "OUT",
        "INP",
        "AMP",
        "ALT",
        "AEQ",
        "AAL",
    ]
    print("{} r{}".format(ops[op], v))


def disassemble(stream):
    # disassemble a stream of bytes
    pos = 0
    while pos < len(stream):
        cur = stream[pos]
        leading = (cur & 0b01110000) >> 4
        if leading == 0b000:
            pos += 1
            print("UNKNOWN")
        elif leading == 0b001:
            print("UNKNOWN")
            pos += 1
        elif leading == 0b010:
            decode_t1_r(stream[pos:pos+3])
            pos += 3
        elif leading == 0b011:
            decode_t1_c(stream[pos:pos+6])
            pos += 6
        elif leading == 0b100:
            decode_t2_r(stream[pos:pos+2])
            pos += 2
        elif leading == 0b101:
            decode_t2_c(stream[pos:pos+5])
            pos += 5
        elif leading == 0b110:
            # ret
            pos += 1
            print("RET")
        elif leading == 0b111:
            # nop
            pos += 1
            print("NOP")






