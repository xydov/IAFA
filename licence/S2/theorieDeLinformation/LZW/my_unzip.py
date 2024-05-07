#! /usr/bin/env python
import sys
from lzw import read_file, write_file, decompress, string_to_compressed_code


def main():
    fn_in = sys.argv[1]
    fn_out = sys.argv[2]
    print("Decompressing from " + fn_in + " to " + fn_out)
    compr = string_to_compressed_code(read_file(fn_in))
    write_file(fn_out, decompress(compr))

main()
