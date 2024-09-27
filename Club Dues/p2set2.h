// Set data structure
template <typename NT>
struct Node {
    NT value;
    Node<NT>* next;
};

template <typename T>
struct Set {
    // Set is made up of a sequence of Nodes,
    // each pointing to the next
    // User doesn't know about Nodes
    Node<T>* head;
    bool active_return;
    
    Set()
    {
        head = NULL;
        active_return = false;
    }
    
    ~Set()
    {
        if( active_return )
        {
            // don't deallocate the memory
            // because the instance is being
            // actively returned from an operation
            // but mark this as false, for next time
            active_return = false;
            return;
        }
            
        while( head != NULL )
        {
            Node<T>* del = head;
            head = head->next;
            delete del;
        }
    }
    
    void insert(T newValue)
    {
        // handle special case for empty Set
        if( head == NULL )
        {
            // make head point to a new Node
            head = new Node<T>;
            head->value = newValue;
            head->next  = NULL;
            return; // we're done, so get out
        }
        
        // get pointer to last node in Set
        Node<T>* last = head;
        while( true )
        {
            // if newValue already in Set, don't add anything
            if( last->value == newValue )
                return;
            // if last points to last Node
            //  and we haven't seen newValue in the Set,
            //  exit loop and add newValue
            if( last->next == NULL )
                break;
            last = last->next;
        }
        
        // now we know newValue is not already in the Set
        //  and last points to the last node in the list

        // allocate memory and assign values for new Node
        Node<T>* newNode = new Node<T>;
        newNode->value = newValue;
        newNode->next  = NULL;
        
        // now append newNode to the Set
        last->next = newNode;
    }
    
    bool isEmpty()
    {
        return( head == NULL );
    }
    
    int getSize()
    {
        int count = 0;
        Node<T>* walker = head;
        while( walker != NULL )
        {
            count++;
            walker = walker->next;
        }
        return count;
    }
    
    // assume Set is non-empty
    void remove(T removeValue)
    {
        // if Set empty, nothing to remove, so just end the function
        if( head == NULL )
            return;
     
        if( ! contains(removeValue) )
            return;
        
        // special case : remove head of the Set
        if( head->value == removeValue )
        {
            Node<T>* remove = head;
            head = head->next;
            delete remove;
            return;
        }
        
        // assume that removeValue is in the Set
        //   because we use the contains function to check
        Node<T>* before = head;
        while( before->next->value != removeValue )
            before = before->next;
        Node<T>* remove = before->next;
        before->next = before->next->next; // before->next = del->next;
        delete remove;
    }
    
    bool contains(T search)
    {
        Node<T>* walker = head;
        while( walker != NULL )
        {
            if( walker->value == search )
                return true;
            walker = walker->next;
        }
        return false;
    }
    
    void printSet(std::ostream& out)
    {
        // special case : empty Set
        if( head == NULL )
        {
            out << "[empty]";
            return;
        }
        
        // Set has at least two values
        out << head->value;
        Node<T>* walker = head->next;
        while( walker != NULL )
        {
            out << ", " << walker->value;
            walker = walker->next;
        }
        
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, Set<T>& L)
{
    L.printSet(out);
    return out;
}

// given two sets A and B, return a new set C
// that is the intersection of A and B
template <typename T>
Set<T> operator&&(Set<T>& A, Set<T>& B)
{
    Set<T> C;
    // walk through the list of set A
    //  for each value in A, if that value is also in B,
    //  add it to set C
    Node<T>* walker = A.head;
    while( walker != NULL )
    {
        if( B.contains(walker->value) )
            C.insert(walker->value);
        walker = walker->next;
    }
    C.active_return = true;
    return C;
}

// given two sets A and B, return a new set C
// that is the union of A and B
template <typename T>
Set<T> operator||(Set<T>& A, Set<T>& B)
{
    Set<T> C;
    // add to C all values from sets A and B
    // trust the insert function to handle any duplicates
    Node<T>* walker;
    walker = A.head;
    while( walker != NULL )
    {
        C.insert(walker->value);
        walker = walker->next;
    }
    walker = B.head;
    while( walker != NULL )
    {
        C.insert(walker->value);
        walker = walker->next;
    }
    C.active_return = true;
    return C;
}

// given two sets A and B, return a new set C
// that is the difference of A and B
template <typename T>
Set<T> operator-(Set<T>& A, Set<T>& B)
{
    Set<T> C;
    // walk through the list of set A
    //  for each value in A, if that value is not also in B,
    //  add it to set C
    Node<T>* walker = A.head;
    while( walker != NULL )
    {
        if( ! B.contains(walker->value) )
            C.insert(walker->value);
        walker = walker->next;
    }
    C.active_return = true;
    return C;
}
