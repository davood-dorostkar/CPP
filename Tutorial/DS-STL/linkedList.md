### Definitions

- every element has a value and a pointer to the next item
- the list has a head pointing to the first item
- the last item points to `nullptr`
- list's capacity is only limited to memory size
- it is inefficient for large number of items

### Linked list item

```cpp
template <typename type>
class ListNode
{
    public:
    type & data;
    ListNode *next;
    ListNode(type &data): data(data), next(nullptr){}
};
```

### Linked list

```cpp
template <typename type>
class List
{
    public:
    const type & operator[](unsigned index);
    void insertAtFront(const type &data);

    private:
    ListNode *head;
    class ListNode
    {
        public:
        type & data;
        ListNode *next;
        ListNode(type &data): data(data), next(nullptr){}
    };
}
```

```cpp
template <typename type>
const type & List<type>::operator[](unsigned index)
{
    ListNode *thru = head;
    while(index > 0 && thru->next != nullptr)
    {
        thru = thru->next;
        index--;
    }
    return thru->data;
}
```

```cpp
template <typename type>
void List<type>::insertAtFront(const type &data)
{
    ListNode *node = new ListNode(data);
    node->next = head;
    head = node;
}
```

### Operations speed

| Operation                    | linked list | array    |
| ---------------------------- | ----------- | -------- |
| Access a given index         | O(n)        | O(1)     |
| Find data                    | O(n)        | O(n)     |
| Find data in sorted DS       | O(n)        | O(lg(n)) |
| Insert item after an element | O(1)        | O(n)     |
| Delete item after an element | O(1)        | O(n)     |
