# Compression and decompression with LZW algorithm
# Can be used in two modes:
# small alphabet size: alpha_small = True and alpha_size between 3 and 10
#     with initialization dictionaries of the form {'a': 0, 'b': 1 ...}
#     typical use: decompress(compress("abacababac"))
# large alphabet size: alpha_small = False and alpha_size = 128
#     with initialization of large dictionaries, typically ASCII or UTF-8 character sets
#     typical use: write_file ("alice_dec.txt", decompress(compress(read_file("alice.txt"))))

# Size of the alphabet
alpha_small = False
alpha_size = 128

# Maximal size of the dictionary
dict_size = 256


# ----------------------------------------------------------------------
# Auxiliary functions
# ----------------------------------------------------------------------

# read from file with filename
def read_file(filename):
    with open(filename) as fn:
        return (fn.read())


# write str to file with filename
def write_file(filename, str):
    with open(filename, "w+") as fn:
        fn.write(str)

# ----------------------------------------------------------------------
# Compression
# ----------------------------------------------------------------------


def init_dict():  # ex1
    dico = {}
    start = 'a'
    if not alpha_small:
        start = '\x00'
    for i in range(alpha_size):
        dico[chr(ord(start) + i)] = i
    return dico


def compress(st):  # ex2
    compr = []
    dico = init_dict()
    motPartiel = ""
    for c in st:
        if (motPartiel + c) in dico:
            motPartiel += c
        else:
            compr.append(dico[motPartiel])
            dico[motPartiel + c] = len(dico)
            motPartiel = c
    compr.append(dico[motPartiel])
    # print("Taille dico: {}".format(len(dico))) # ex 7
    return compr

# print(compress("abacababac"))  # EX 3


def compress_lim(st):  # ex8
    compr = []
    dico = init_dict()
    motPartiel = ""
    for c in st:
        if (motPartiel + c) in dico:
            motPartiel += c
        else:
            compr.append(dico[motPartiel])

            if len(dico) <= dict_size:
                dico[motPartiel + c] = len(dico)

            motPartiel = c
    compr.append(dico[motPartiel])
    return compr

# ----------------------------------------------------------------------
# Decompression
# ----------------------------------------------------------------------


def init_inv_dict():  # ex 4
    dico = {}
    start = 'a'
    if not alpha_small:
        start = '\x00'
    for i in range(alpha_size):
        dico[i] = chr(ord(start) + i)
    return dico
# print(init_dict())
# print(init_inv_dict())


def decompress(compr):  # ex5
    # Build the dictionary.
    dinv = init_inv_dict()
    pos = alpha_size
    # print(dinv)
    m_act = dinv[compr[0]]
    string = m_act
    for k in compr[1:]:
        # print(k)
        # print(dinv)
        # print("string: " + string)
        m_ant = m_act
        if k in dinv:
            m_act = dinv[k]
            dinv[pos] = m_ant + m_act[0]
            pos = pos + 1
        elif k == pos:
            m_act = m_ant + m_ant[0]
            dinv[pos] = m_act
            pos = pos + 1
        else:
            raise ValueError('Bad compr k: %s' % k)
        string += m_act
    return string
# print(compress("abaabcabadaba"))
# print(decompress(compress("abaabcabadaba")))


"""  # ex 7
print(compress(read_file("alice.txt")))
print("Taille fichier original: ", len(read_file("alice.txt")))
print("Taille texte compr: ", len(compress(read_file("alice.txt"))))
"""


def compressed_code_to_string(compr):  # ex 9 working
    string = ""
    taille = len(compr)
    for i in range(taille):
        string += chr(compr[i])
    return(string)


def string_to_compressed_code(st):  # ex
    compr = []
    for c in st:
        compr.append(ord(c))
    return(compr)
