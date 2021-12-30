template <typename T, typename U>
class Iterator {
 public:
  typedef typename std::vector<T>::iterator iter_type;
  Iterator(U *p_data, bool reverse = false) : m_p_data(p_data) {
    m_it = m_p_data->m_data.begin();
  }

  void First() {
    m_it = m_p_data->m_data.begin();
  }

  void Next() {
    m_it++;
  }

  bool IsDone() {
    return (m_it == m_p_data->m_data.end());
  }

  iter_type Current() {
    return m_it;
  }

 private:
  U *m_p_data;
  iter_type m_it;
};



template <class T>
class Container {
  friend class Iterator<T, Container>;

 public:
  void Add(T a) {
    m_data.push_back(a);
  }
  T &operator[](int index){
      return m_data[index];
  }
  int size(){
      return m_data.size();
  }

  Iterator<T, Container> *CreateIterator() {
    return new Iterator<T, Container>(this);
  }

 private:
  std::vector<T> m_data;
};

