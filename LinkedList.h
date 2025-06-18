#include <memory>

template <typename T>
class Node
{
  public:
    Node(const T& value);

    std::shared_ptr<Node<T>> getPrevious();
    std::shared_ptr<Node<T>> getNext();
    void setPrevious(std::shared_ptr<Node<T>> previous);
    void setNext(std::shared_ptr<Node<T>> next);

  private:
    T m_value;
    std::shared_ptr<Node<T>> m_previous, m_next;
};

template <typename T>
class LinkedList
{
  public:
    LinkedList();

    void push(const T& value);
    std::shared_ptr<Node<T>> getHead();
    std::shared_ptr<Node<T>> getTail();

  private:
    std::shared_ptr<Node<T>> m_head, m_tail;
};