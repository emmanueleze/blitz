#include "blitz/blitz.hpp"

using namespace std;
using namespace blitz;

int main(int argc, char *argv[]) {

  vector<string> coll {"Core", "QuadEngine", "Motors", "Bus", "Sensor"};
  concurrent::ComponentAssembly assembly(coll);
  
  thread t0 (&concurrent::ComponentAssembly::generateComponents, &assembly);
  thread t1 (&concurrent::ComponentAssembly::processComponents, &assembly);

  t0.join();
  t1.join();

  
}