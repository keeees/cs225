/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  clear();
  length_ = 0;
  head_ = NULL;
  tail_ = NULL;

}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
  ListNode* temp;
  ListNode* current = head_;
  while(current != NULL){
      temp = current;
      current = current->next;
      delete temp;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode* temp = new ListNode(ndata);
  temp->next = head_;
  head_ = temp;
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode* temp = new ListNode(ndata);
  if(tail_ == NULL){
      head_ = temp;
      tail_ = temp;
      length_++;
  }else{
      tail_->next = temp;
      temp->prev = tail_;
      tail_ = temp;
      length_++;
}

}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1
  ListNode *temp = startPoint;
  ListNode *next_end = endPoint->next;
  ListNode  *next_node;
 // cout<<"line99"<<endl;
  //cout<<head_<<endl;
 // cout<<tail_<<endl;

  //cout<<temp<<endl;
  //cout<<startPoint<<endl;
  //cout<<startPoint->next<<endl;
  //cout<<startPoint->next->next<<endl;
  //cout<<startPoint->next->next->next<<endl;


  //cout<<endPoint<<endl;


  while(temp->next != next_end){
          //cout<<"a"<<endl;
          next_node = temp->next;
          //cout<<"b"<<endl;

          temp->next = temp->prev;
         // cout<<"c"<<endl;

          temp->prev = next_node;
         // cout<<"d"<<endl;

          temp = next_node;
          //cout<<"e"<<endl;
         //cout<<temp<<endl;
  }
  next_node = temp->next;
  //cout<<"b"<<endl;

  temp->next = temp->prev;
  // cout<<"c"<<endl;

  temp->prev = next_node;
  // cout<<"d"<<endl;

  temp = next_node;
  //cout<<"finish loop"<<startPoint<<endl;
  //cout<<startPoint->prev->prev<<endl;
  //cout<<startPoint->prev->prev->prev<<endl;

  //cout<<temp<<endl;

  temp = endPoint->prev;
  //cout<<temp<<endl;

  if(startPoint->next != NULL){
      endPoint->prev = startPoint->next;
      startPoint->next->next = endPoint;
  }else{
      endPoint->prev = NULL;
  }
  if(temp != NULL){
      startPoint->next = temp;
      temp->prev = startPoint;
  }else{
      startPoint->next = NULL;
  }
  swap(startPoint,endPoint);
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  if(n>=size()){
      reverse();
  }else{
      ListNode *previous_head = head_->next;
      ListNode *temp = head_;
      while(1){
          for(int i = 0;i<n-1;i++){
              if(temp->next != NULL)
                temp = temp->next;
          }
          if(temp->next == NULL){
              reverse(previous_head,tail_);
              break;
          }
          if(previous_head == head_->next){
              reverse(head_,temp);
          }
          else{
              reverse(previous_head,temp);
          }
          previous_head = temp->next;
          temp = temp->next;
      }
  }

}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  if(size() == 0){
      return;
  }
  ListNode *temp = head_;
  while (temp->next != NULL && temp != NULL && temp->next->next != NULL) {
      temp = temp->next;
      temp->prev->next = temp->next;
      temp->next->prev = temp->prev; // connect two ListNodes
      ListNode *temp2 = temp->next;
      temp->next = NULL;
      temp->prev = tail_;
      tail_->next = temp; // manipulate tail_
      tail_ = temp;
      temp = temp2;
  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  if(start->next == NULL){
    return start;
  }
  ListNode*temp = start;
  for(int i = 0;i<splitPoint;i++){
    if(temp->next == NULL){
      return temp;
    }
     temp = temp->next;

  }
  temp->prev->next = NULL;
  temp->prev = NULL;
  return temp;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode* temp1 = first;
  ListNode* temp2 = second;
  ListNode* second_next;
  ListNode* first_next;
  ListNode* h;
  if(temp1->data  < temp2->data){
      h = temp1;
      //temp1->prev = h;
      if(temp1->next == NULL){
        h->next = temp2;
        temp2->prev = h;
        return h;
      }
      temp1 = temp1->next;
  }else{
      h = temp2;
      //temp2->prev = h;
      if(temp2->next == NULL){
        h->next = temp1;
        temp1->prev = h;
        return h;
      }
      temp2 = temp2->next;
  }
  ListNode* result = h;
  //h = h->next;
  while(temp2 != NULL && temp1 != NULL){
      //cout<<temp1<<"  temp1 data"<<endl;
      //cout<<temp2<<"  temp2 data"<<endl;
      //cout<<h<<"  h data"<<endl;
      //cout<<"               "<<endl;



      if(temp1->data  < temp2->data){
          h->next = temp1;
          temp1->prev = h;
          temp1 = temp1->next;
          //temp2->next = first_next;
          //first_next->prev = temp2;
      }else{
          h->next = temp2;
          temp2->prev = h;
          temp2 = temp2->next;
      }
      h = h->next;
      if(temp1 == NULL){
          h->next = temp2;
          temp2->prev = h;
      }else if(temp2 == NULL){
          h->next = temp1;
          temp1->prev = h;
      }
  }

  return result;
  /*while(temp2 != NULL){
      //cout<<temp2<<"  temp2 data"<<endl;
      second_next = temp2->next;
      //cout<<temp2->next<<"  temp2 next"<<endl;
      //cout<<temp2->prev<<"  temp2 prev"<<endl;

      while(temp1 != NULL){
          //cout<<temp1<<"  temp2sadfadsf prev"<<endl;

          first_next = temp1->next;
          //cout<<temp1<<"  aaaaaaa prev"<<endl;

          if(temp1 == first && (temp2->data < temp1->data)){
              //cout<<temp1->data.l<<"  temp1 head"<<endl;

              temp1->prev = temp2;
              temp2->next = temp1;
              temp2->prev = NULL;
              result = temp2;
              break;
          }else if(temp1->next == NULL){
              cout<<"1";
              temp1->next = temp2;
              temp2->prev = temp1;
              temp2->next = first_next;
              break;
          }else if(temp1->data == temp2->data){
              //cout<<"2";

              temp1->next = temp2;
              temp2->prev = temp1;
              temp2->next = first_next;
              first_next->prev = temp2;
              break;
          }else if(temp1->data  < temp2->data && temp2->data < temp1->next->data){
              cout<<"3";

              temp1->next = temp2;
              temp2->prev = temp1;
              temp2->next = first_next;
              first_next->prev = temp2;
              break;
          }
          temp1 = first_next;
      }
      temp2 = second_next;
  }
  return result;*/
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(start == NULL || chainLength ==1||start->next == NULL){
      return start;
  }else{
      int len = chainLength/2;
      ListNode * temp = split(start, len);

      ListNode* temp1;
      ListNode* temp2;
      temp1 = mergesort(temp,chainLength-len);
      temp2 = mergesort(start,len);
      return merge(temp2,temp1);
  }

}
