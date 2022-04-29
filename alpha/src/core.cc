#include "alpha/alpha.h"

using namespace alpha;

template <typename T, typename AT = AccumulatorTrait<T>> void accumulate();

std::vector<int> twoSum(const std::vector<int> &array_, int target) {
  std::vector<int> ivec;
  auto sz = (int)array_.size();
  auto i1 = 0;
  auto i2 = sz - 1;
  for (int i = 0; i < sz; ++i) {
    if (array_[i1] + array_[i2] == target) {
      ivec.insert(ivec.begin(), {i1, i2});
      return ivec;
    }
    if (array_[i1] + array_[i2] > target)
      --i2;
    if (array_[i1] + array_[i2] < target)
      ++i1;
  }
  return ivec;
}

GenericComponent::GenericComponent(const std::string &_name) : m_name(_name) {}

GenericComponent::GenericComponent(const GenericComponent &component) {
  this->m_name = component.m_name;
  this->_type = component._type;
}

std::string GenericComponent::name() const { return m_name; }

void GenericComponent::setName(std::string _name) { m_name = _name; }

CType GenericComponent::type() const { return _type; }

void GenericComponent::setType(CType tp) { _type = tp; }

ComponentAssembly::ComponentAssembly(const std::vector<std::string> &_list)
    : cmp_list(_list) {

  coll = new ItemQueue<Component *>(10);
  processIndex = 0;
  done = false;
}

void ComponentAssembly::next() {

  if (processIndex < (int)cmp_list.size())
    ++processIndex;
  if (processIndex == (int)cmp_list.size())
    done = true;
}

ItemQueue<Component*>* ComponentAssembly::generateComponents() {
  std::lock_guard<std::mutex> _lock(g_mutex);
  while (!done) {
    auto data = ComponentFactory::create(cmp_list[processIndex]);
    {
      coll->insert(data);
      next();
    }
  }
  return coll;
}

void ComponentAssembly::processComponents() {
  while (true) {
    std::unique_lock<std::mutex> _lock(g_mutex);
    _cnd.wait(_lock, [this] { return !coll->empty(); });
    auto citem = coll->remove();
    std::cout << "Processing " << citem->name() << ".\n";
    _lock.unlock();
    if (done) {
      std::cout << "Finished processing components.\n";
      break;
    }
  }
}