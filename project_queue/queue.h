enum Error_code { success , underflow , overflow };
const int maxqueue = 10;
typedef double Queue_entry;
class Queue {
public:
    Queue();
    bool empty() const;
    Error_code append(const Queue_entry &x);
    Error_code serve();
    Error_code retrieve(Queue_entry &x) const;
protected:
    int count;
    int front,rear;
    Queue_entry entry[maxqueue];
};
