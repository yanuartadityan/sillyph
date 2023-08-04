#include <chrono>
#include <iostream>

#include "sph/app.h"
#include "sph/sph_common.h"
#include "sph/sph_particle.h"

using namespace std;
using namespace sph;
using namespace app;

int main() {
  auto start = chrono::high_resolution_clock::now();

  SPHSystem simulation = SPHSystem();
  App app = App(common::WINDOW_WIDTH, common::WINDOW_HEIGHT);
  app.render_simulation(simulation);

  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
  cout << "Simulation was live for " << duration.count() << " ms." << endl;

  return 0;
}
