# The class of Huffman trees, with subclasses Leaf and Node

class Htree:
    def __init__(self, val):
        self.val = val

# constructor Leaf(val, code)
class Leaf(Htree):
    def __init__(self, val, code):
        self.val = val
        self.code = code

# constructor Node(val, low, high)
class Node(Htree):
    def __init__(self, val, low,  high):
        self.val = val
        self.low = low
        self.high = high

