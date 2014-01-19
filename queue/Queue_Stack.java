/*
 * Queue implemented using stacks
 * Author: Abdur-Rahman Ayyaz Qureshi
 * 18 - 01 - 14
 * 
 * This is a queue implemented using Stacks. It is a logical exercise as opposed to a practical implementation.
 * http://courses.csail.mit.edu/iap/interview/Hacking_a_Google_Interview_Practice_Questions_Person_B.pdf
 */
package queue;

import java.util.List;
import java.util.Stack;

public class Queue_Stack<E> {
	
	//Instance variables
	Stack<E> incoming = new Stack<E>(); //Stack organized in LIFO
	Stack<E> outgoing = new Stack<E>(); //Stack organized in FIFO
	
	// Thought process:
	// By popping one stack and pushing to another, we can convert from LIFO to FIFO (desired state).
	// Problem: we want to queue after dequeuing.
	// The elements in outgoing are guaranteed to be older. They can only come from 'incoming.'
	// We want to maintain LIFO for 'incoming' (older at the back)
	// for queue, push outgoing before pushing the new element
	
	/*
	 * Empty constructor
	 */
	public Queue_Stack() {
		
	}
	
	/*
	 * Initialize queue with a list where element 0 (front) is the 'first-in'
	 * @param l The list to be inserted in the queue. The first element is considered to be at the front of the queue
	 */
	public Queue_Stack(List<E> l) {
		for(int i=0; i<l.size(); i++)
			incoming.push(l.get(i));
	}
	
	public void queue(E e){
		while(!outgoing.empty())
			incoming.push(e);
		incoming.push(e);
	}
	
	public E next(){
		while(!incoming.empty())
			outgoing.push(incoming.pop());
		return outgoing.pop();
	}

}
