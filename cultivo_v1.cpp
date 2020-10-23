#ifdef _cultivo_v1_hpp_

template <typename VT>
BigTable<VT>::BigTable(){
  tableSize = TABLE_SIZE;
  count = 0;
  table = new DayHour<VT>*[tableSize];
  for (int i=0; i<tableSize; i++){
    table[i] = nullptr;
  }
}

template <typename VT>
BigTable<VT>::~BigTable(){
}














#endif
