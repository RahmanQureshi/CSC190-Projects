public Class LinkedList<E> {

    Element first_in_list;
    Element last_in_list;

    public LinkedList(){
	first_in_list = null;
	last_in_list = null;
    }

    public void insert(E e) {
	first_in_list = new Element(e, first_in_list);
    }

    public E pop_front(){
	Element front_element = first_in_list;
	first_in_list = first_in_list.pointer_to_last;
	return front_element;
    }


    class Element {
    
	public Element pointer_to_last;
	public E myself;
	
	public Element(E myself, Element pointer_to_last){
	
	    this.myself = myself;
	    this.pointer_to_last = pointer_to_last;

	}
    }

}
