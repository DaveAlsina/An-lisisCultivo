#ifdef _cultivo_v1_hpp_
//#ifdef _list_hpp_

template <typename VT>
BigTable<VT>::BigTable(){
  tableSize = TABLE_SIZE;
  count = 0;
  table = new HourMinute<VT>*[tableSize];
  for (int i=0; i<tableSize; i++){
    table[i] = nullptr;
  }
}

template <typename VT>
BigTable<VT>::~BigTable(){
}

//#endif











#endif
