// p2queue.h
// FIFO : first in, first out
// wrapping queue
// reset head to zero index when array grows

template <typename QueueType>
struct Queue
{
    // hold data in an array,
    int head;
    int tail;
    QueueType* data;  // pointer to array (to hold values)
    int size;   // size of current array
    
    // constructor : initialize values
    Queue()
    {
        size = 2;
        data = new QueueType[size];
        head = 0;
        tail = 0;
    }
    
    // destructor : destroy things
    ~Queue()
    {
        delete [] data;
    }
    
    bool isEmpty()
    {
        return ( head == tail );
    }
    
    int getSize()
    {
//        if( tail > head ) // not wrapped around
//            return tail - head;
//        // wrapped around
//        return (size-head) + tail;
        return ( tail > head ? tail-head : size-head + tail );
    }
    
    void push(QueueType value)
    {
        // if array is full (allowing for one blank space), needs to grow
        if( getSize()+1 == size )
        {
            QueueType* tmp = new QueueType[size*2];
            // if array is NOT wrapped around currently
            if( head < tail )
            {
                for( int i = head; i < tail; i++ )
                    tmp[i-head] = data[i];
            }
            else // array IS wrapped around currently
            {
                // copy from head to end of array
                for( int i = head; i < size; i++ )
                    tmp[i-head] = data[i];
                // copy fromm beginning of array to the tail
                for( int j = 0; j < tail; j++ )
                    tmp[j+(size-head)] = data[j];
            }
            head = 0; // head reset to zero index
            tail = size-1; // new tail value
            delete [] data; // delete old array
            data = tmp; // point to new (larger) array
            size *= 2;  // remember size has doubled

        }
        data[tail] = value;
        tail = ( tail+1 == size ? 0 : tail+1 );
    }
    
    QueueType pop()
    {
        QueueType value = data[head];
        head = ( head + 1 == size ? 0 : head+1 );
        return value;
    }

};
