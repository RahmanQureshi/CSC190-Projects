public class LinkedList<E> {

    public Element front; //The newest element added to the list
    public Element back; //The oldest element added to the list
    public int size = 0;
    
    public LinkedList(){
    	front = null;
    	back = null;
    }

    public void insert(E e) {
    	size+=1;
    	Element temp = new Element(e, front, null); // The new front. The element behind it is the old front (null if empty). Being infront, there is no element infrnt of it (therefore null)
		if(size==1) {
			back = temp; //previously front (which was null). Now temp
		}else{
			front.infront = temp; // The element infront of the old front is temp
		}
			front = temp;
    }

    public E pop_front(){
		if(front==null) return null;
		//Store the front in temporary variable
		//Assign front to the element the old front was pointing at
		//return front
		size-=1;
		Element temp = front;
		front = front.behind;
		return temp.myself;
    }

    public E pop_back(){
		Element temp = back; //to return
		if(temp==null) return null;
		size-=1;
		back = back.infront; //equivalently, temp.infront. The element infront of the back is the new back
		return temp.myself;
    }


    class Element {
    
		public Element behind; // The next older element
		public Element infront; // The next newer element
	
		public E myself;
		
		public Element(E myself, Element behind, Element infront){
		
		    this.myself = myself;
		    this.behind = behind;
		    this.infront = infront;
	
		}
    }

}
