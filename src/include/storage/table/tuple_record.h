//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// tuple.h
//
// Identification: src/include/storage/table/tuple.h
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include <string>
#include <vector>

#include "catalog/schema.h"
#include "common/rid.h"
#include "type/value.h"
#include "storage/table/tuple.h"
namespace bustub {

/**
 * Tuple format:
 * ---------------------------------------------------------------------
 * | FIXED-SIZE or VARIED-SIZED OFFSET | PAYLOAD OF VARIED-SIZED FIELD |
 * ---------------------------------------------------------------------
 */
class TupleRecord : public Tuple {
  friend class TablePage;
  friend class OverFlowPage;
  friend class TableHeap;
  friend class TableIterator;

 public:
  // Default constructor (to create a dummy tuple)
  TupleRecord() = default;

  // constructor for table heap tuple
  explicit TupleRecord(RID rid) : rid_(rid) {}

  // constructor for creating a new tuple based on input value
  TupleRecord(std::vector<Value> values, const Schema *schema);

  // copy constructor, deep copy
  // TupleRecord(const TupleRecord &other);

  // assign operator, deep copy
  // auto operator=(const Tuple &other) -> Tuple &;

  ~TupleRecord() {
       if (allocated_) {
      delete[] data_;
    }
    allocated_ = false;
    data_ = nullptr;
  }
  // serialize tuple data
  void SerializeTo(char *storage) const;

  // deserialize tuple data(deep copy)
  void DeserializeFrom(const char *storage);

  // return RID of current tuple
  inline auto GetRid() const -> RID { return rid_; }

  // Get the address of this tuple in the table's backing store
  inline auto GetData() const -> char * { return Tuple::GetData(); }

  // Get length of the tuple, including varchar legth
  inline auto GetLength() const -> uint32_t { return Tuple::GetLength(); }

  // Get the value of a specified column (const)
  // checks the schema to see how to return the Value.
  auto GetValue(const Schema *schema, uint32_t column_idx) const -> Value;

  // Generates a key tuple given schemas and attributes
  auto KeyFromTuple(const Schema &schema, const Schema &key_schema, const std::vector<uint32_t> &key_attrs) -> TupleRecord;

  // Is the column value null ?
  inline auto IsNull(const Schema *schema, uint32_t column_idx) const -> bool {
    Value value = GetValue(schema, column_idx);
    return value.IsNull();
  }
  inline auto IsAllocated() const -> bool { return Tuple::IsAllocated(); }

  auto ToString(const Schema *schema) const -> std::string;
  //1 means null
  auto clearNull(int colIdx) -> void {
    int byteIndex = colIdx / 8;
    int bitOffset = colIdx % 8;
    // bitMapPtr_[byteIndex] &=  ~(1 << bitOffset);
     (bitMapPtr_ + sizeof(uint32_t) )[byteIndex] &=  ~(1 << bitOffset);
  }  
  auto setNull(int colIdx) -> void {
    int byteIndex = colIdx / 8;
    int bitOffset = colIdx % 8;
    // bitMapPtr_[byteIndex] |= (1 << bitOffset);
    (bitMapPtr_ + sizeof(uint32_t))[byteIndex] |= (1 << bitOffset);
  }  
  auto isColNull(const Schema *schema, uint32_t colIdx)  const-> bool {
   
    
    int byteIndex = (colIdx / 8) % 2;
    int bitOffset = colIdx % 8;
    return ((GetData() + sizeof(uint32_t)+  schema->GetLength())[byteIndex] & (1 << bitOffset)) != 0;

  }
  auto SetOverFlowPageId(page_id_t overFlowId) -> void;
   auto GetOverFlowPageId() const -> page_id_t;
 private:
  // Get the starting storage address of specific column
  auto GetDataPtr(const Schema *schema, uint32_t column_idx) const -> const char *;

  // bool allocated_{false};  // is allocated?
  RID rid_{};              // if pointing to the table heap, the rid is valid
  // uint32_t size_{0};
  // char *data_{nullptr};
  char *tupleData_{nullptr};
  char *bitMapPtr_{nullptr};
};

}  // namespace bustub
