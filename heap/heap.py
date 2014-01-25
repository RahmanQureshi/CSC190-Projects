class Heap:
    
    # At each level there are 2^n elements (starting from 0)
    

    def __init__(self, initial_capacity=100, element_set={}):
        self.heap = [0 for i in range(initial_capacity)]
        self.size = len(element_set) + 0

        # testing get_child_indices
        self.heap = [i for i in range(0, 15)]
        
        l = self.child_indices(2)
        print(l) # expect 11, 12
        l = self.child_indices(0)
        print(l)
        l = self.parent_index(13)
        print(l)
        l = self.parent_index(14)
        print(l)

    def insert(self, element):
        pass

    def pop(self):
        pass

    def child_indices(self, parent_index):
        """This function returns the indices of the child nodes of the node at parent_index
        (int(parent_index)) -> list
        """

        # let k = the kth element of the level n, where k=0 corresponds to the left most node of level n and k=2^n is the right most
        # it can be shown that the first child if element (n, k) is: (2^n - k - 1 ) + (2k) + 1 infront of the parent index and the second is: (2^n - k - 1) + (2k) + 2
        # how to show: there are 2^n-k-1 elements infront of the kth element on level n and 2*k elements on level n+1 by virtue that all the elements before have children
        
        current_position = self.calculate_position(parent_index);
        n = current_position[0]
        k = current_position[1]
        
        return([ (parent_index + 2**n - k - 1 + 2*k + 1) , (parent_index + 2**n - k - 1 + 2*k + 2) ]) # will simplify - kept for future debugging purposes

    def parent_index(self, child_index):
        # Suppose k is the kth element of level n, where k=0 corresponds to the left most node of the level and k=2^n is the right most
        # For every two elements infront of at index k, there is one level infront of it's parent on level n-1. There are 2^n-k-1 elements infront.
        # Note that the case of 5 elements, there are still only two pairs of two elements. There are still only two elements infront of the parent on level n-1
        # There are also k elements behind it by definition
        # It follows that the parent is: child_index - k - the number of pairs of two
        # the number of pairs of two: there are floor(2^n-k-1/2)
        current_position = self.calculate_position(child_index)
        n = current_position[0]
        k = current_position[1]
        
        return child_index - k  - 1 - int( (2**n-k-1)/2 ) # -1 infront of k for itself
    
    def calculate_position(self, index):
        """This function calculates the level n and position k of the node at index.
        """
        # to find n given index i, while the sum of 2^n < index+1, we are above level 'n'
        # To find k given index i, i -  the sum of 2^k from k = 1 to n-1

        sum = 0
        k = 0
        n = 0
        while(True):
            sum += 2**n
            if(not sum<index+1): # index + 1 because first element is at index 0, but the sum of elements is not 0 (basic case - extends for the rest or else it is OBOB)
                k = index - (sum - 2**n)
                break
            n+=1
        
        print("n:{0}, k:{1}".format(n, k))
        
        return ([n, k])


if __name__ == "__main__":
    my_heap = Heap()
