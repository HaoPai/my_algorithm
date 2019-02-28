class Extended_queue : public Queue {
public:
    bool full() const;
    int size() const;
    void clear();
    Error_code serve_and_retrive(Queue_entry &item);
};
