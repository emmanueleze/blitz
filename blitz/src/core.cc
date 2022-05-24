
#include "blitz/blitz.hpp"

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

blitz::GenericComponent::GenericComponent(const std::string &_name)
    : m_name(_name) {}

blitz::GenericComponent::GenericComponent(const GenericComponent &component) {
  this->m_name = component.m_name;
  this->_type = component._type;
}

std::string blitz::GenericComponent::name() const { return m_name; }

void blitz::GenericComponent::setName(std::string _name) { m_name = _name; }

blitz::CType blitz::GenericComponent::type() const { return _type; }

void blitz::GenericComponent::setType(blitz::CType tp) { _type = tp; }

blitz::concurrent::ComponentAssembly::ComponentAssembly(
    const std::vector<std::string> &_list)
    : cmp_list(_list) {

  coll = std::make_shared<blitz::concurrent::ItemQueue<GenericComponent>>(10);
  processIndex = 0;
  done = false;
}

void blitz::concurrent::ComponentAssembly::next() {

  if (processIndex < (int)cmp_list.size())
    ++processIndex;
  if (processIndex == (int)cmp_list.size())
    done = true;
}

void blitz::concurrent::ComponentAssembly::generateComponents() {

  while (!done) {
    {
      auto data = blitz::cfactory::create(cmp_list[processIndex]);
      std::lock_guard<std::mutex> _lock(g_mutex);
      coll->insert(data);
      next();
      _cnd.notify_one();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}

void blitz::concurrent::ComponentAssembly::processComponents() {
  while (true) {
    std::unique_lock<std::mutex> _lock(g_mutex);
    _cnd.wait(_lock, [this] { return !coll->empty(); });
    const auto item = coll->remove();
    std::cout << "Processing " << item.name() << ".\n";
    _lock.unlock();
    if (done) {
      std::cout << "Finished processing components.\n";
      break;
    }
  }
}

blitz::name::name() {}

blitz::name::name(const name &_name) : m_names(_name.m_names) {}

blitz::name::name(name &&_name) : m_names(std::move(_name.m_names)) {}

std::shared_ptr<blitz::concurrent::ItemQueue<std::string>>
blitz::concurrent::generateNames() {
  std::vector<std::string> coll{"Eodire", "MaxToll", "SubSys", "Quartz"};
  auto ret = std::make_shared<ItemQueue<std::string>>(4);
  throw std::runtime_error("self gen error");
  for (const auto &e : coll)
    ret->insert(e);

  return ret;
}
double blitz::random_generator(const double &min, const double &max) {
  std::uniform_real_distribution<double> distr(min, max);
  std::default_random_engine re;
  return distr(re);
}
