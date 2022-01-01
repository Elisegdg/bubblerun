/**
 * \file Iterator.hpp
 * \brief Declaration of the class Iterator and Container
*/


#ifndef _ITERATOR_HPP
#define _ITERATOR_HPP

/*! \class Iterator
   * \brief Class of Iterator
   *
   *  This class is built as the Design Pattern Iterator. 
   *  It enables to read a container without knowing how it is built.
   */
template <typename T, typename U>
class Iterator {
 public:
  typedef typename std::vector<T>::iterator iter_type;
  Iterator(U *p_data, bool reverse = false) : m_p_data_(p_data) {
    m_it_ = m_p_data_->m_data_.begin();
  }

  void First() {
    m_it_ = m_p_data_->m_data_.begin();
  }

  void Next() {
    m_it_++;
  }

  bool IsDone() {
    return (m_it_ == m_p_data_->m_data_.end());
  }

  iter_type Current() {
    return m_it_;
  }

 private:
  U *m_p_data_;
  iter_type m_it_;
};


/*! \class Container
   * \brief Class of Container
   *
   *  This class is built as the Design Pattern Iterator. 
   *  It enables to read a container without knowing how it is built.
   */
template <class T>
class Container {
  friend class Iterator<T, Container>;

 public:
  void Add(T a) {
    m_data_.push_back(a);
  }
  T &operator[](int index){
      return m_data_[index];
  }
  int size(){
      return m_data_.size();
  }

  Iterator<T, Container> *CreateIterator() {
    return new Iterator<T, Container>(this);
  }

 private:
  std::vector<T> m_data_;
};

#endif