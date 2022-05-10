#ifndef BLITZ_INCLUDE_BLITZ_CORE_ARCH_HPP
#define BLITZ_INCLUDE_BLITZ_CORE_ARCH_HPP

#include "blitz/blitz.hpp"

namespace blitz {

enum Ops { t, e, q };

enum class CType { ENGINE = 0x4d, PISTON, NONE = 0x0 };

struct Component {
  virtual std::string name() const = 0;
  virtual void setName(std::string) = 0;
  virtual CType type() const = 0;
  ~Component() {}
};

class GenericComponent : public Component {
public:
  GenericComponent() {}
  GenericComponent(const std::string &_name);
  ~GenericComponent(){}

public:
  GenericComponent(const GenericComponent &);

public:
  std::string name() const;
  void setName(std::string _name);
  CType type() const;
  void setType(CType tp);

private:
  std::string m_name;
  CType _type;
};

class Engine : public GenericComponent {
public:
  Engine() {}
  explicit Engine(std::string n) : _name(n) {}
  Engine(const Engine &engine) : GenericComponent(engine) {}
  void setName(std::string name) { _name = name; }
  std::string name() const override { return _name; }
  CType type() const override { return CType::ENGINE; }
  ~Engine() {}
  std::ostream &operator<<(std::ostream &os) {
    os << this->_name << std::endl;
    return os;
  }

private:
  std::string _name;
};

class Piston : public GenericComponent {
public:
  Piston() {}
  Piston(std::string n) : _name(n) {}
  std::string name() const override { return _name; }
  void setName(std::string name) override { _name = name; }
  CType type() const override { return CType::PISTON; }
  ~Piston() {}

private:
  std::string _name;
};

class ComponentFactory {
public:
  static GenericComponent &create(const std::string &name = std::string("Unknown"),
                           CType type = CType::NONE) {
    GenericComponent component(name);
    return std::ref(component);
  }
};

using cfactory = ComponentFactory;
using CType::ENGINE;
using CType::PISTON;

/* template<typename>
class X{
  public:
    X();
    X(const X&);  // Copy constructor.
    X(X&&);      // Move constructor.
    X& operator=(cosnt X& lvalue );   // copy assignment
    X& operator=(X&& rvalue );  // move assignment
}; */

} // namespace alpha

#endif