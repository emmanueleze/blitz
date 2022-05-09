#include "asio-server.h"
#include "alpha/alpha.h"
void show_alert(){
  alpha::alert();
}

using namespace std;

int main(int argc, char *argv[]){
  show_alert();
  vector<int> coll {32, 1, 0,4,2};
  alpha::print(coll);
}
