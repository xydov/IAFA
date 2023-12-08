#! /usr/bin/env python
import sys
from lzw import read_file, write_file, compress_lim, compressed_code_to_string


def main():
    fn_in = sys.argv[1]
    fn_out = sys.argv[2]
    print("Compressing from " + fn_in + " to " + fn_out)
    str = read_file(fn_in)
    compr = compress_lim(str)
    write_file(fn_out, compressed_code_to_string(compr))

main()
