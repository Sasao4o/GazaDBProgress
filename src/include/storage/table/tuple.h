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

namespace bustub {

/**
 * Tuple format:
 * ---------------------------------------------------------------------
 * | FIXED-SIZE or VARIED-SIZED OFFSET | PAYLOAD OF VARIED-SIZED FIELD |
 * ---------------------------------------------------------------------
 */
class Tuple {
  friend class TablePage;
  friend class TableHeap;
  friend class TableIterator;

 public:
 

  // constructor for table heap tuple
  // explicit Tuple(RID rid) : rid_(rid) {}

  // constructor for creating a new tuple based on input value
   Tuple(std::vector<Value> values, const Schema *schema);
   Tuple() = default;
  // copy constructor, deep copy
   
  Tuple(const Tuple &other);

  // assign operator, deep copy
  auto operator=(const Tuple &other) -> Tuple &;

  // virtual ~Tuple();

   virtual~Tuple(){
      if (allocated_) {
      delete[] data_;
    }
    allocated_ = false;
    data_ = nullptr;
  };
  // serialize tuple data
  // virtual void SerializeTo(char *storage) const;

  // deserialize tuple data(deep copy)
  // virtual void DeserializeFrom(const char *storage);

  // return RID of current tuple
     virtual const RID GetRid() {
      return  {};
     };

  // Get the address of this tuple in the table's backing store
   
  virtual  char * GetData() const {
    return data_;
  };
  // Get length of the tuple, including varchar legth
 
  virtual  uint32_t GetLength() const {
    return size_;
  };
  // Get the value of a specified column (const)
  // checks the schema to see how to return the Value.
 

 virtual  Value GetValue(const Schema *schema, uint32_t column_idx) const;
  // Generates a key tuple given schemas and attributes
  
   Tuple KeyFromTuple(const Schema &schema, const Schema &key_schema, const std::vector<uint32_t> &key_attrs);
  // Is the column value null ?
  inline auto IsNull(const Schema *schema, uint32_t column_idx) const -> bool {
    Value value = GetValue(schema, column_idx);
    return value.IsNull();
  }
 
  virtual auto IsAllocated() const -> bool { return allocated_; }
  
 virtual auto ToString(const Schema *schema) const -> std::string;
  // //1 means null
  // auto clearNull(int colIdx) -> void {
  //   int byteIndex = colIdx / 8;
  //   int bitOffset = colIdx % 8;
  //   // bitMapPtr_[byteIndex] &=  ~(1 << bitOffset);
  //    (bitMapPtr_ + sizeof(uint32_t) )[byteIndex] &=  ~(1 << bitOffset);
  // }  
  // auto setNull(int colIdx) -> void {
  //   int byteIndex = colIdx / 8;
  //   int bitOffset = colIdx % 8;
  //   // bitMapPtr_[byteIndex] |= (1 << bitOffset);
  //   (bitMapPtr_ + sizeof(uint32_t))[byteIndex] |= (1 << bitOffset);
  // }  
  // auto isColNull(const Schema *schema, uint32_t colIdx)  const-> bool {
   
    
  //   int byteIndex = (colIdx / 8) % 2;
  //   int bitOffset = colIdx % 8;
  //   return ((data_ + sizeof(uint32_t)+  schema->GetLength())[byteIndex] & (1 << bitOffset)) != 0;

  // }

  // auto SetOverFlowPageId(page_id_t overFlowId) -> void;
  //  auto GetOverFlowPageId() const -> page_id_t;
  protected:
  bool allocated_{false};
    uint32_t size_{0};
  char *data_{nullptr};
  char *tupleData_{nullptr};
  char *bitMapPtr_{nullptr}; 
 private:
  // Get the starting storage address of specific column
  virtual auto GetDataPtr(const Schema *schema, uint32_t column_idx) const -> const char *;

    // is allocated?
  // RID rid_{};              // if pointing to the table heap, the rid is valid
 
};

}  // namespace bustub
