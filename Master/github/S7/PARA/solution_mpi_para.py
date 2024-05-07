import math
from mpi4py import MPI

def split(x, size):
	n = math.ceil(len(x) / size)
	return [x[n*i:n*(i+1)] for i in range(size-1)]+[x[n*(size-1):len(x)]]

def read_documents(i):
        if i==0:
                return "aaaajaadaaapdalazknaaakahdazadajaoaajaadaaz"
        else:
                return "dak zy lk scnvle cqs zjd hdladklv e zfo fed"

def count_letters(text):
    result = [0]*26
    for letter in text:
        if letter >= 'a' and letter <= 'z':
            result[ord(letter)-ord('a')]+=1
    return result

def add_lists(l1, l2):
    res = l1[:]
    for i in range(len(res)):
        res[i] += l2[i]
    return res

def get_max_letter(l):
    m = max(l)
    pos = l.index(m)
    return(chr(ord('a')+pos))

def keep_only(secret, document, letter):
        res = ''
        for i in range(len(secret)):
                if secret[i] == letter:
                        res += document[i]
        return res

def get_signature(text, binf, bsup):
        nb = 0
        for pos in range(binf, bsup):
                if res.count(res[pos]) > 2:
                        nb += 1
        return nb

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

###############################   Start of the part to provide

if rank == 0:
    # Contains the crypted key
    secret = split(read_documents(0), size)
    # Contains the crypted data
    document = split(read_documents(1), size)
else:
    secret = None
    document = None

# Distributes the crypted key
l_secret = comm.scatter(secret, root=0)

# Counts occurences of each letters
# Retuns an array of 26 numbers on for each letter
l_count = count_letters(l_secret)

all_counts = comm.gather(l_count, root=0)

# On node rank=0 merges all list and 
# get the letter with the highest count (the key)
if rank==0:
        final_count = all_counts[0]
        for local_count in all_counts[1:]:
                final_count = add_lists(final_count, local_count)
        max_letter = get_max_letter(final_count)
else:
        max_letter = None

# Distributes the max letter to all nodes
max_letter = comm.bcast(max_letter, root=0)

# Distributes the actual document
l_doc = comm.scatter(document, root=0)

# Decrypt the document using the secret and the max letter
# Retuns a string. It keeps in document only places where in
# secret the letter is max_letter
# keep_only('abca', 'ghjk', 'a') -> 'gk'
res = keep_only(l_secret, l_doc, max_letter)

# To use get_signature we need to have the whole document on
# all nodes. We also change the boundaries to balance the work
# on all nodes
res = comm.allreduce(res, op=MPI.SUM)
binf = rank * (len(res)//size)
bsup = (rank+1) * (len(res)//size)
if rank == size-1:
        bsup += len(res)%size
        
# Check if there is no problem. Counts the sum ofrepetition of
# letters, if 'a' is present 2 times, adds 2, if it is present
# 10 times, add 10.
nb = get_signature(res, binf, bsup)

final = comm.reduce(nb, op=MPI.SUM, root=0)
if rank==0:
        print(final)

###############################   End of the part to provide
