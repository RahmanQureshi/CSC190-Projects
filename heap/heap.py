class Heap:
    
    # At each level there are 2^n elements (starting from 0)
    

    def __init__(self, initial_capacity=100, element_set={}):
        self.heap = [0 for i in range(initial_capacity)]
        self.size = len(element_set) + 0

        # testing get_child_indices
        self.heap = [i for i in range(0, 15)]
        
        l = self.get_child_indices(5)
        print(l) # expect 11, 12

    def insert(self, element):
        pass

    def pop(self):
        pass

    def get_child_indices(self, parent_index):
        # let k = the kth element of the level n, where k=0 corresponds to the left most node of level n and k=2^n is the right most
        # it can be shown that the first child if element (n, k) is: (2^n - k - 1 ) + (2k) + 1 and the second is: (2^n - k - 1) + (2k) + 2
        # how to show: there are 2^n-k-1 elements infront of the kth element on level n and 2*k elements on level n+1 by virtue that all the elements before have children
        # To find k given index i, i -  the sum of 2^k from k = 1 to n-1
        # to find n given index i, while the sum of 2^k < index+1, we are above level 'k' 
        sum = 0;
        k = 0;
        n = 0;

        while(True):
            sum += 2**n
            if(not sum<parent_index+1):
                k = parent_index - (sum - 2**n)
                break
            n+=1
        
        return([ (2**n - k - 1 + 2*k + 1) , (2**n - k - 1 + 2*k + 2) ]) # will simplify - kept for future debugging purposes

    def get_parent_index():
        pass


if __name__ == "__main__":
    my_heap = Heap()
