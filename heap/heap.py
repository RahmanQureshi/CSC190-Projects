""" A heap data structure

Author: Abdur-Rahman Ayyaz Qureshi

A few notes:
Although the higher level logic follows from theory, the finer implementations are of my own design (such as parent_index or position).
Vocabulary:
Index - the index of the node in the whole array
Position - the 'pseudo-index' of the node in its level (given each level is its own sub-array)
Level - The level in a binary tree given with the root at level 0
"""

class Heap:

    def __init__(self, initial_capacity=100, element_set={}):
        self.heap = [0 for i in range(initial_capacity)]
        self.size = len(element_set) + 0

    def insert(self, element):
        pass

    def pop(self):
        pass

    def child_indices(self, parent_index):
        """Return the indices of the child nodes of the node at parent_index
        """

        # Logic:
            # Define: the node at parent_index, call it parent
            # Define: level of parent, call it n
            # Define: position of parent, call it k
            # Compute child_indices:
                # Observation: for every node behind parent, there are two nodes on level n+1 that are necessarily behind the children of parent
                # Define/Thus: there are 2*k nodes on level n+1 behind parent's children, call it offset
                # The start index of level n+1 is parent_index + remainder of nodes on the level + 1, call it p
                    # i.e. if there is one node left, parent_index + 1 will move to that node, then add one more to get to the next level
                    # p = parent_index + (2**n - (k+1)) + 1 (k+1 to include parent itself)
                # The first child will occur at 2*k, the second at 2*k + 1
        
        current_position = self.position(parent_index);
        n = current_position[0]
        k = current_position[1]

        offset = 2*k
        p = parent_index + (2**n) - (k+1) + 1
        
        return([ p + offset , p + offset + 1]) # will simplify - kept for future debugging purposes

    def parent_index(self, child_index):
        """Return the index of the parent of the node at child_index
        """

        # Logic:
            # Define: the index of the parent node, call it parent_index
            # Define: node at child_index, call it child
            # Define: level of child, call it n
            # Define: position of child, call it k
            # Define: the number of nodes on any arbitrary level i, nodes(i)
            # Compute parent_index:
                # Observation: For every two nodes infront of child that are still on level, there is one node on level n-1 that is NOT child's parent
                    # This node that is NOT child's parent is NECESSARILY infront of child's parent
                # Define: number of pairs of nodes infront of child, call it p
                    # Define: number of nodes infront of child's parent as floor(p/2), call it q
                # Hence: child's parent is at index child_index - (k+1) - q
                    # Note: k+1 because the number of nodes up to and including child on level n is k+1 (because k denotes the index)

        location = self.position(child_index)
        n = location[0]
        k = location[1]

        p = 2**n - (k + 1) # number of nodes up to and including child is k+1
        q = int ( p / 2 )

        return child_index - (k+1) - q

        return child_index - k  - 1 - int( (2**n-k-1)/2 )
    
    def position(self, index):
        """Return the level and position of index in the tree

        Level denotes the level in the tree. Levels start at 0 (the root). Position denotes the ith index of the level.
        For instance: the position of the leftmost node at any level is 0, and the position of the rightmost node is 2^n - 1.
        """

        # Logic:
            # Define: level of 'index' as n
            # Define: number of nodes up to and including abitrary level i as sum(i)
            # Compute n:
                # Observe: There are index+1 nodes in [0, index]
                # Thus: If the sum of nodes up to level n is less than index+1, we are at a level less
                # By contraposition: if the sum exceeds index+1, we are at level n
            # Compute k assuming we found n:
                # Observe: if we remove sum(n-1) from index+1, we attain the number of nodes up to and including the node at index
                # Thus: position k is equal to index+1 - sum(n-1) - 1

            # Pseudo Code:
                # Follows neatly from logic



        sum = 0 # Sum of the number of nodes
        level = 0 # Level
        position = 0 # Position
        while(True):
            sum += 2**level
            if(not sum<index+1): # the current level is n
                sum = sum - 2**level # sum(n-1)
                position = index - sum
                break
            level = level + 1
        
        return ([level, position])


if __name__ == "__main__":
    my_heap = Heap()
