#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> heapvector_;
  int m_;
  PComparator c_;

  void trickleUp(int loc);
  void trickeDown(int loc);
};

// Add implementation of member functions here
  
  /*
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  template <typename T, typename PComparator>
  Heap<T, PComparator>::Heap(int m, PComparator c)
  {
    //default to 2
    if(m >= 2)
    {
      m_ = m;
    }
    else
    {
      m_ = 2;
    }
    
    c_ = c;
  }

  /**
  * @brief Destroy the Heap object
  * 
  */
  template <typename T, typename PComparator>
  Heap<T, PComparator>::~Heap()
  {

  }


  /**
   * @brief Returns true if the heap is empty
   * 
   */
  template <typename T, typename PComparator>
  bool Heap<T, PComparator>::empty() const
  {
    return heapvector_.empty();
  }

    /**
   * @brief Returns size of the heap
   * 
   */
  template <typename T, typename PComparator>
  size_t Heap<T, PComparator>::size() const
  {
    return heapvector_.size();
  }


  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  template <typename T, typename PComparator>
  void Heap<T, PComparator>::push(const T& item)
  {
    heapvector_.push_back(item);

    //calls trickleUp
    trickleUp(heapvector_.size() - 1);
  }


  template <typename T, typename PComparator>
  void Heap<T, PComparator>::trickleUp(int loc)
  {
    for(int i = loc; i > 0;)
    {
      int parent = (i - 1) / m_;
      if(c_(heapvector_[i], heapvector_[parent]))
      {
        std::swap(heapvector_[parent], heapvector_[i]);
      }
      else
      {
        break;
      }

      i = parent;
    }
  }


  template <typename T, typename PComparator>
  void Heap<T, PComparator>::trickeDown(int loc)
  {
    // if parent is 0 then the first child must be 1
    int firstchild = m_ * loc + 1;

    //no child
    if(firstchild >= heapvector_.size())
    {
      return;
    }

    int prioritychild = firstchild;
    for(int i = 1; i < m_; ++i)
    {
      int child = firstchild + i;
      if(child >= heapvector_.size())
      {
        break;
      }
      
      if(c_(heapvector_[child], heapvector_[prioritychild]))
      {
        std::swap(heapvector_[child], heapvector_[prioritychild]);
      }
    }

    if(c_(heapvector_[prioritychild], heapvector_[loc]))
    {
      std::swap(heapvector_[prioritychild], heapvector_[loc]);
      trickeDown(prioritychild);
    }

  }





// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element

  return heapvector_[0];

}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");
  }

  //switch first with last
  std::swap(heapvector_[0], heapvector_[heapvector_.size() - 1]);

  heapvector_.pop_back();

  //check if heap is still proper
  trickeDown(0);
}



#endif

