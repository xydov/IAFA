# conversion of character strings to bitstrings (lists of 0 and 1)

from htrees import *

# convert a character with code in the range 0 .. 255 to a single byte, 
# represented as list of 0 and 1
# see http://stackoverflow.com/questions/31063552/python-convert-hex-string-to-boolean-array
def char_to_bit_list(c):
    binary_byte = bin(ord(c))
    # Use zfill to pad the string with zeroes
    bits_string = binary_byte[2:].zfill(8)
    return [int(bit) for bit in bits_string]

def string_to_bit_list (str):
    bl = []
    for c in str:
        bl.extend(char_to_bit_list(c))
    return bl

def chop8 (bl, pos):
    blc = bl[pos:pos+8]
    blc.extend([0 for x in range(8 - len(blc))])
    return blc

# inverse of char_to_bit_string: bl is a list of 0 and 1 of length at most 8
def bit_list_to_char(bl):
    binary_string = ""
    for i in bl:
        binary_string = binary_string + str(i)
    return(chr(int(binary_string, base=2)))

def bit_list_to_string(bl):
    str = ""
    pos = 0
    bl_maxpos = len(bl)
    while pos < bl_maxpos:
        str = str + bit_list_to_char(chop8(bl, pos))
        pos = pos + 8
    return str
