#include "Population.hpp"
#include <fstream>

int main() {
    // destination simulation parameters
    double Tr = 1.0;
    double Os = 0.1;
    double T5s = 10.0;
    int population_size = 100;

    double max_kp = 10.0;
    double max_kd = 1.0;
    double max_ki = 2.0;

    Population p(Tr, Os, T5s, population_size, max_kp, max_kd, max_ki, dt, Ts);
    int iter = 50;     // number of finding iterations

    std::vector<double> mean_cost;
    std::vector<double> best_cost;
    std::vector<std::vector<double>> kp_v(iter);
    std::vector<std::vector<double>> kd_v(iter);
    std::vector<std::vector<double>> ki_v(iter);

    p.simulate_population();
    for (int i = 0; i < iter; i++) {
        double J = p.find_solution(60, 0.2);
        double mean = p.get_mean_adaptation();
        std::cout << "iter: " << iter << "mean adapt: " << mean << std::endl;
        mean_cost.push_back(mean);

        for (const auto& entity : p.population) {
            kp_v[i].push_back(entity.get_kp());
            kd_v[i].push_back(entity.get_kd());
            ki_v[i].push_back(entity.get_ki());
        }
    }

    std::ofstream file;
    file.open("mean_cost.csv");
    for (const auto& cost : mean_cost) {
        file << cost << ",";
    }
    file.close();

    file.open("kp_values.csv");
    for (const auto& iter_kp : kp_v) {
        for (const auto& kp : iter_kp) {
            file << kp << ",";
        }
        file << "\n";
    }
    file.close();

    file.open("kd_values.csv");
    for (const auto& iter_kd : kd_v) {
        for (const auto& kd : iter_kd) {
            file << kd << ",";
        }
        file << "\n";
    }
    file.close();

    file.open("ki_values.csv");
    for (const auto& iter_ki : ki_v) {
        for (const auto& ki : iter_ki) {
            file << ki << ",";
        }
        file << "\n";
    }
    file.close();

    return 0;
}
