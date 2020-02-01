from bitarray import bitarray

b = bitarray(endian='big')
b.fromfile(open("flag.txt","rb"))
len = b.length()
arr = []
len = len // 7
place = 0
for i in range(len):
   arr.append(b[i*7:i*7 +7])
   arr[i].reverse()
   print(chr(int(arr[i].to01(),2)),end='')
