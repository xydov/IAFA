# Display htrees with dot using no particular library, by putting together gv strings

from htrees import *

# v: float, c: char, node_id: int, dt: gv.Graph
def print_leaf_dot (v, c, node_id, dt):
    if c.isalnum():
        c_code = c
    else:
        c_code = "[" + str(ord(c)) + "]"
    dt.append(str(node_id) + " [label=\"(" + str(v) + "," + c_code + ")\"]")

# v: float, node_id: int, dt: gv.Graph
def print_node_dot (v, node_id, dt):
    dt.append(str(node_id) + " [label=\"" + str(v) + "\"]")

# start: int, lab: int, target: int, dt: gv.Graph
def print_edge_dot (start, lab, target, dt):
    dt.append(str(start) + " -- " + str(target) + " [label=" + str(lab) + "]")

def print_htree_dot (ht, node_id, dt):
    if isinstance(ht, Leaf):
        print_leaf_dot(ht.val, ht.code, node_id, dt)
        return node_id
    else:
        node_id_low = print_htree_dot(ht.low, node_id+1, dt)
        node_id_high = print_htree_dot(ht.high, node_id_low+1, dt)
        print_node_dot(ht.val, node_id, dt)
        print_edge_dot(node_id, 0, node_id + 1, dt)
        print_edge_dot(node_id, 1, node_id_low + 1, dt)
        return node_id_high

def display_htree (ht):
    dt = []
    print_htree_dot(ht, 0, dt)
    print("graph {")
    for s in dt:
        print(s)
    print("}")


