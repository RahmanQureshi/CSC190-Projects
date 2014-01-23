public Class LinkedList<E> {

    // Bad coding practice to make everything public. Only for debugging purposes

    public Element front; //The newest element added to the list
    public Element back; //The oldest element added to the list
    int size = 0;
    
    public LinkedList(){
	front = null;
	back = null;
    }

    public void insert(E e) {
	//Re-assign the front, have the front point to the last front (which is behind it). Being infront, there is no element infront of it
	//But the last front now has an element infront of it too
	size+=1;
	temp = new Element(e, front, null); // The new front. The element behind it is the old front (null if empty). Being infront, there is no element infrnt of it (therefore null)
	if(size==1) {
	    back = front;
	}else{
	    front.infront = temp; // The element infront of the old front is temp
	}
	front = temp;
    }

    //Remember to check if empty
    public E pop_front(){
	if(front==null) return null;
	//Store the front in temporary variable
	//Assign front to the element the old front was pointing at
	//return front
	Element front_element = front;
	front = front.behind;
	return front_element;
    }

    public E pop_back(){
	temp = back; //to return
	back = back.infront; //equivalently, temp.infront. The element infront of the back is the new back
	return temp;
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