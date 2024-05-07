from matplotlib import pyplot as plt
import networkx as nx


def plot_graph(graph, save=False, display=True):
    g1=graph
    plt.tight_layout()
    nx.draw_networkx(g1, arrows=True)
    if save:
        plt.savefig("graph.png", format="PNG")
    if display:
        plt.show(block=True)


#graph = nx.scale_free_graph(20).reverse()
graph = nx.gnr_graph(30, .01).reverse()
#graph = nx.random_k_out_graph(20, 2, .8).reverse()

new_elements = [0] # We start at the root (node = 0)
old_elements = []  # We initialize the already seen nodes

while len(new_elements) != 0: # as long as we have new node
    tmp = []
    for node_src in new_elements: # we take all these nodes
        for node in graph.neighbors(node_src): # we take all their descendents
            if not node in old_elements and not node in new_elements and not node in tmp:
                # If the descendent is not already seen, we keep it
                tmp.append(node)

    old_elements += new_elements # we have looked at all their descendent, so we move them to the seen nodes
    new_elements = tmp           # these are the new node, we will see them on the next iteration

print(len(old_elements) == len(graph))
plot_graph(graph, save=True, display=True)
