// CSC Latin America 2026 - Event Processor implementation
// STUDENT VERSION: incorrect parallel implementation to debug & fix

#include "EventProcessor.hpp"
#include <cmath>

#ifdef CSC2026_USE_OPENMP
#include <omp.h>
#endif

namespace csc2026 {
double Particle::energy() const {
    // E = sqrt(p^2 + m^2)
    const double p2 = px * px + py * py + pz * pz;
    return std::sqrt(p2 + mass * mass);
}

void EventProcessor::processEvent(const Event& event) {
    for (const auto& particle : event.particles) {
        m_totalTracks++;
        m_totalEnergy += particle.energy();
    }
}

void EventProcessor::processEvents(const std::vector<Event>& events) {
    // Intentionally incorrect: race conditions + false sharing
    int tracks = 0;
    double energy = 0.0;

struct Totals { int tracks; double energy; };
std::vector<Totals> totals(omp_get_max_threads(), Totals{0, 0.0});

#pragma omp parallel
{
  const int tid = omp_get_thread_num();
  #pragma omp for
  for (size_t i = 0; i < events.size(); ++i) {
    for (const auto& p : events[i].particles) {
      totals[tid].tracks += 1;
      totals[tid].energy += p.energy();
    }
  }
}

for (const auto& t : totals) {
  tracks += t.tracks;
  energy += t.energy;
  struct alignas(64) Totals { int tracks; double energy; };
}


    m_totalTracks += tracks;
    m_totalEnergy += energy;
}

void EventProcessor::reset() {
    m_totalTracks = 0;
    m_totalEnergy = 0.0;
}

std::vector<Event> EventProcessor::generateSampleEvents(size_t nEvents) {
    std::vector<Event> events;
    events.reserve(nEvents);

    for (size_t i = 0; i < nEvents; ++i) {
        Event e;
        e.id = static_cast<int>(i);

        // Create a fixed number of particles per event
        e.particles.resize(10000);
        for (size_t p = 0; p < e.particles.size(); ++p) {
            Particle part;
            part.px = 0.1 * static_cast<double>(p);
            part.py = 0.2 * static_cast<double>(p);
            part.pz = 0.3 * static_cast<double>(p);
            part.mass = 0.511; // MeV-ish dummy
            e.particles[p] = part;
        }

        events.push_back(e);
    }

    return events;
}

} // namespace csc2026

