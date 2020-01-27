
class By7eFile:
    def __init__(self, path):
        self.file = open(path, "rb")
        self.by7es = self.file.read()
        self.data = split_by7es(self.by7es)

    def print(self):
        print(self.data.decode())


def split_by7es(by7es: bytes) -> bytes:
    data = []
    masks = [
        0b00000000,
        0b00000001,
        0b00000011,
        0b00000111,
        0b00001111,
        0b00011111,
        0b00111111,
        0b01111111,
    ]
    place = 1
    extra = 0
    for i in range(len(by7es)):
        c = by7es[i]
        data.append(((extra << (8 - place)) & 0b11111111) + (c >> place))
        extra = c & masks[place]
        place += 1

        if place == 8:
            data.append(extra)
            extra = 0
            place = 1
            # print("".join('{:08b} '.format(b) for b in by7es[0: 7]))
            # print("".join('{:07b}0 '.format(b) for b in data[-8:]))

    return bytes(reverse_bits_arr(data))


def reverse_bits_arr(arr):
    for i in range(len(arr)):
        arr[i] = int('{:07b}0'.format(arr[i])[::-1], 2)
    return arr

