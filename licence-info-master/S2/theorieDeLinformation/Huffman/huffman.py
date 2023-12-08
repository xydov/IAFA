from htrees import *
from htree_dot_noviz import display_htree

from htree_construct import *
from bitstring import *

# Boolean constant determining whether trees are displayed with graphviz-dot
display_tree_constant = True

# name suffix for file containing coded/ decoded text
fn_cod_suffix_constant = "_coded"
fn_dec_suffix_constant = "_decoded"


def read_file_latin1(filename):
    with open(filename + ".txt", encoding='ISO-8859-1') as fn:
        return (fn.read())


def write_file_latin1(filename, suffix, contents):
    with open(filename + suffix + ".txt", "w+", encoding='ISO-8859-1') as fn:
        fn.write(contents)


def test_construct_huffman_tree(filename):
    # read input data
    source_str = read_file_latin1(filename)

    # construct and display Huffman tree
    chd = ch_distrib(source_str)
    display_htree(construct_huffman_tree(chd))


def huffman(filename):

    # read input data
    source_str = read_file_latin1(filename)

    # construct Huffman tree and corresponding coding tab
    chd = ch_distrib(source_str)
    ht = construct_huffman_tree(chd)
    if display_tree_constant:
        display_htree(ht)
    ct = htree_to_coding_tab(ht)

    # code input string and write it to file
    code_bl = code_source_string_to_bit_list(source_str, ct)
    code_bl_len = len(code_bl)
    code_str = bit_list_to_string(code_bl)
    write_file_latin1(filename, fn_cod_suffix_constant, code_str)

    # decode string.
    # The decoded string can be longer than code_bl due to bit stuffing
    # in bit_list_to_string; therefore limit to code_bl_len
    decode_bl = (string_to_bit_list(code_str))[:code_bl_len]
    decode_str = decode_bit_list_to_string(decode_bl, ht)
    write_file_latin1(filename, fn_dec_suffix_constant, decode_str)

### testing the construct_huffman_tree() function with miserables.txt graphviz.it
#test_construct_huffman_tree('miserables')