import numpy as np
import copy
import networkx as nx

class individual:
    def __init__(self , genes, fitness):
        self.genes = genes
        self.fitness = fitness
        #self.gene_length = gene_length
        pass
    pass



def new_individual():
    
    genes=[]
    fitness=0
    i = individual(genes,fitness)
    return i

def get_fitness(individual,g):
    #arr=numpy.array(adjacency_matrix)
    #g=nx.from_numpy_array(arr)
    #print(type(g))
    
    fitness=nx.algorithms.community.modularity(g,individual.genes)
    individual.fitness=fitness
    pass

def mutate(child,node_count):

    for x in range(len(child.genes)):

        for y in range(len(child.genes[x])):
            
            r=np.random.randint(1,11)
            if r==5:          #10 percent chance of it happening
                a=np.random.randint(0,len(child.genes))
                b=np.random.randint(0,len(child.genes[a]))
                temp=child.genes[x][y]
                child.genes[x][y]=child.genes[a][b]
                child.genes[a][b]=temp
                pass
        pass


    get_fitness(child,g)
    return child
    pass

def find_least_fit(pop):
    least=pop[0]
    for x in range(1,len(pop)):
        if pop[x].fitness<least.fitness:
            least=pop[x]
            pass
        pass
    return least

def most_fit(pop):
    fittest=pop[0];
    for x in range(1,len(pop)):
        if pop[x].fitness>fittest.fitness:
            fittest=pop[x]
            pass
        pass
    return fittest

def two_most_fit(pop):
    pop_copy=copy.deepcopy(pop)
    mother = most_fit(pop_copy)
    pop_copy.remove(mother)
    father = most_fit(pop_copy)
    parents=[mother,father]
    return parents



def find_missing(lst):
    res=[]

    for x in range(len(lst)-1):
        
        if lst[x+1]-lst[x]>1:
            
            for y in range(lst[x]+1,lst[x+1]):
                
                res.append(y)

                pass
            
            pass
        
        pass


    return res


def make_child(mother,father,node_count,g):
    child=new_individual()
    r=np.random.randint(1,len(mother.genes))
    for x in range(r):
        child.genes.append(mother.genes[x])
        pass

    for x in range(len(father.genes)-r):
        if x+r<=len(father.genes):
            child.genes.append(father.genes[x+r])
            pass
        pass

    add_remaining=[]


    for x in range(len(child.genes)):
        
        for y in range(len(child.genes[x])):
            
            for k in range((x+1),len(child.genes)):
                
                if child.genes[x][y] in child.genes[k]:
                    child.genes[k] = list(filter((child.genes[x][y]).__ne__, child.genes[k]))
                    pass
                
                pass

            add_remaining.append(child.genes[x][y])

            pass


        pass


    add_remaining=sorted(add_remaining)
    remaining=copy.deepcopy(add_remaining)
    remaining=find_missing(sorted(remaining))


    if 0 not in add_remaining: 
       remaining.append(0)
       pass

    if node_count not in add_remaining: 
       remaining.append(node_count)
       pass



    child.genes.append(remaining)

    child.genes = list(filter(None, child.genes))

    child=mutate(child,node_count)
    get_fitness(child,g)
    return child
    pass

def populate(pop,node_count,g):
    nodes=[]
    for x in range(node_count+1):
        nodes.append(x)
        pass

    for x in range(len(pop)):
        
        np.random.shuffle(nodes)
        #print(nodes)
        count=node_count
        index=0
        #community_count=np.random.randint(1,node_count)
        while True:
            l=[]
            r=np.random.randint(0,node_count+1)
            if (r-index)>=0:
                l=nodes[index:index+r]
                index=index+r
                pop[x].genes.append(l)
                pass
            else:
                l=nodes[index:]
                pop[x].genes.append(l)
                break 
            pass
        pop[x].genes = list(filter(None, pop[x].genes))
        #print(pop[x].genes)
        pass

     
    for x in range(len(pop)):
        get_fitness(pop[x],g)
        pass

    pass

def read_file(f_name):
    arr=[]
    f = open(f_name+".txt", "r")
    for x in f:
        res = [int(i) for i in x.split() if i.isdigit()]
        arr.append(res)
        pass
    return arr

def adjacency_matrix(data,node_count):

    rows, cols = (node_count+1,node_count+1)
    matrix = [[0 for i in range(cols)] for j in range(rows)]
    #print(matrix)
    #print("\n\n\n")
    for x in range(len(data)):
        i=data[x][0]
        j=data[x][1]
        matrix[i][j]=1
        pass
    return matrix

def find_community(pop,node_count,g):
    
    populate(pop,node_count,g)
    
    for x in range(1000):
        parents=two_most_fit(pop)
        child = make_child(parents[0],parents[1],node_count,g)
        least = find_least_fit(pop)
        pop.remove(least)
        pop.append(child)
        print(x)
        pass

    #for x in range(len(pop)):
    #    if pop[x].fitness>0.27:
    #        print(pop[x].genes)
    #        pass        
    #    pass
    fittest=most_fit(pop)
    print("most fit")
    print(fittest.genes)
    print(fittest.fitness)
    pass


data = read_file("facebook_edge_list")

node_count=(max(max(data)[0],max(data)[1]))

matrix = adjacency_matrix(data,node_count)
#print(len(matrix))

arr=np.array(matrix)

g=nx.to_networkx_graph(arr,create_using=nx.DiGraph)

pop=[]
r=np.random.randint(10,101)

for x in range(r):
    i=new_individual()
    pop.append(i)
    pass


find_community(pop,node_count,g)































