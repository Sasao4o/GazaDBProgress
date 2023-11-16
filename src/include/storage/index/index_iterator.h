//===----------------------------------------------------------------------===//
//
//                         CMU-DB Project (15-445/645)
//                         ***DO NO SHARE PUBLICLY***
//
// Identification: src/include/index/index_iterator.h
//
// Copyright (c) 2018, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//
/**
 * index_iterator.h
 * For range scan of b+ tree
 */
#pragma once
#include "storage/page/b_plus_tree_leaf_page.h"

namespace bustub {

#define INDEXITERATOR_TYPE IndexIterator<KeyType, ValueType, KeyComparator>

INDEX_TEMPLATE_ARGUMENTS
class IndexIterator {
 public:
  // you may define your own constructor based on your member variables
  IndexIterator();
  IndexIterator(int pageId, BufferPoolManager* buffer_pool_manager_, int index);
  ~IndexIterator();  // NOLINT

  auto IsEnd() -> bool;

  auto operator*() -> const MappingType &;

  auto operator++() -> IndexIterator &;

  auto operator==(const IndexIterator &itr) const -> bool { return this->currentPageId == itr.currentPageId && this->currentIndex == currentIndex; }

  auto operator!=(const IndexIterator &itr) const -> bool {  return this->currentPageId != itr.currentPageId || this->currentIndex != currentIndex; }

 private:
  // add your own private member variables here
  int currentPageId;
  int currentIndex;
  BufferPoolManager* buffer_pool_manager_;
};

}  // namespace bustub
