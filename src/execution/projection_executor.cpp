#include "execution/executors/projection_executor.h"
 
namespace bustub {

ProjectionExecutor::ProjectionExecutor(ExecutorContext *exec_ctx, const ProjectionPlanNode *plan,
                                       std::unique_ptr<AbstractExecutor> &&child_executor)
    : AbstractExecutor(exec_ctx), plan_(plan), child_executor_(std::move(child_executor)) {}

void ProjectionExecutor::Init() {
  // Initialize the child executor
  child_executor_->Init();
}

auto ProjectionExecutor::Next(Tuple **tuple, RID *rid) -> bool {
 
   Tuple **child_tuple = new Tuple*[1];
    *child_tuple = nullptr;
  // Get the next tuple
  const auto status = child_executor_->Next(child_tuple, rid);

  if (!status) {
    return false;
  }

  // Compute expressions
  std::vector<Value> values{};
  values.reserve(GetOutputSchema().GetColumnCount());
  for (const auto &expr : plan_->GetExpressions()) {
    values.push_back(expr->Evaluate(*child_tuple, child_executor_->GetOutputSchema()));
  }

  *tuple = new TupleRecord(values, &GetOutputSchema());

  if (*child_tuple != nullptr) {
    delete *child_tuple;
    }
    delete []child_tuple;
  return true;
}
}  // namespace bustub
