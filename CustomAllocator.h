#include <cstddef>
class AllocationInformation
{
  public:
    AllocationInformation(size_t size, AllocationInformation* preivous = nullptr,
                          AllocationInformation* next = nullptr);

    size_t size() const;
    AllocationInformation* getNext() const;
    AllocationInformation* getPrevious() const;

    void setPrevious(AllocationInformation* previous);
    void setNext(AllocationInformation* next);

    /** Return the first address of the allocated block. */
    void* getAddress() const;

  private:
    size_t m_size;
    AllocationInformation* m_previous;
    AllocationInformation* m_next;
};