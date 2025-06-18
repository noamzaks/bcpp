#include <cstddef>

class AllocationInformation final
{
  public:
    AllocationInformation(size_t size);
    AllocationInformation(size_t size, AllocationInformation* preivous, AllocationInformation* next);
    ~AllocationInformation();

    size_t size() const;
    AllocationInformation* getNext() const;
    AllocationInformation* getPrevious() const;

    void setPrevious(AllocationInformation* previous);
    void setNext(AllocationInformation* next);

    /** Return the first address of the allocated block. */
    void* getAddress() const;

    /** Prints all of the current allocation information (in order of allocation). */
    static void printAllInformation();

    /** Returns the allocation information stored for the given pointer returned by `new`. */
    static AllocationInformation* getInformation(void* p);

  private:
    /** Updates the global head & tail about this new allocation information. */
    void updateGlobalListOnCreation();
    /** Updates the global head & tail about this allocation information being removed. */
    void updateGlobalListOnDeletion();
    /** Updates the next & previous about this allocation information being removed. */
    void updateNeighborsOnDeletion();

    size_t m_size;
    AllocationInformation* m_previous;
    AllocationInformation* m_next;

    static AllocationInformation* s_head;
    static AllocationInformation* s_tail;
};