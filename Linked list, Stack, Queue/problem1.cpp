/*
 * Problem 1: Polynomial f(x) = 6.7x^4 + 3.2x^3 - x^2 + x - 2
 *            for x in [-10, 10]
 *
 * - Compute f(x) using a dedicated function
 * - Plot graph using gnuplot (via popen pipe)
 * - Find root(s) where f(x) = 0  → bisection method
 * - Find minimum of f(x)         → golden-section search
 *
 * Requirements:
 *   gnuplot must be installed.
 *   Linux/macOS: gnuplot is called via popen().
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdio>
#include <vector>

// ─── 1. Polynomial function ───────────────────────────────────────────────────
double f(double x) {
    return 6.7*x*x*x*x + 3.2*x*x*x - x*x + x - 2.0;
}

// ─── 2. Plot with gnuplot ─────────────────────────────────────────────────────
void plotGraph(double xMin, double xMax, int samples) {
    // Step 1: write data file
    const char* dataFile = "fx_data.dat";
    std::ofstream ofs(dataFile);
    if (!ofs) {
        std::cerr << "[ERROR] Cannot open " << dataFile << " for writing.\n";
        return;
    }
    ofs << "# x        f(x)\n";
    double dx = (xMax - xMin) / (samples - 1);
    for (int i = 0; i < samples; i++) {
        double x = xMin + i * dx;
        ofs << std::fixed << std::setprecision(6) << x << "  " << f(x) << "\n";
    }
    ofs.close();

    // Step 2: open gnuplot pipe and send commands
    FILE* gp = popen("gnuplot -persistent", "w");
    if (!gp) {
        std::cerr << "[ERROR] gnuplot not found. Install gnuplot first.\n";
        return;
    }

    fprintf(gp, "set title 'f(x) = 6.7x^4 + 3.2x^3 - x^2 + x - 2'\n");
    fprintf(gp, "set xlabel 'x'\n");
    fprintf(gp, "set ylabel 'f(x)'\n");
    fprintf(gp, "set xrange [%g:%g]\n", xMin, xMax);
    fprintf(gp, "set grid\n");
    fprintf(gp, "set zero\n");
    // draw y=0 reference line
    fprintf(gp, "set arrow from %g,0 to %g,0 nohead lc rgb 'black' lw 1 dt 2\n", xMin, xMax);
    // plot from data file
    fprintf(gp, "plot '%s' using 1:2 with lines lw 2 lc rgb 'blue' title 'f(x)'\n", dataFile);

    pclose(gp);

    // Step 3: also save a gnuplot script for re-use
    std::ofstream script("plot_fx.plt");
    script << "# gnuplot script for f(x)\n";
    script << "# Run with:  gnuplot plot_fx.plt\n";
    script << "set title 'f(x) = 6.7x^4 + 3.2x^3 - x^2 + x - 2'\n";
    script << "set xlabel 'x'\n";
    script << "set ylabel 'f(x)'\n";
    script << "set xrange [" << xMin << ":" << xMax << "]\n";
    script << "set grid\n";
    script << "set arrow from " << xMin << ",0 to " << xMax << ",0 nohead lc rgb 'black' lw 1 dt 2\n";
    script << "plot '" << dataFile << "' using 1:2 with lines lw 2 lc rgb 'blue' title 'f(x)'\n";
    script << "pause -1 'Press Enter to close'\n";
    script.close();

    std::cout << "  [Graph] gnuplot window opened.\n";
    std::cout << "  [Graph] Data saved to: " << dataFile << "\n";
    std::cout << "  [Graph] Script saved to: plot_fx.plt  (re-run: gnuplot plot_fx.plt)\n\n";
}

// ─── 3. Root finding via bisection method ────────────────────────────────────
void findRoots(double xMin, double xMax, int steps) {
    std::cout << "=== Root Finding (Bisection Method) ===\n";
    double dx = (xMax - xMin) / steps;
    bool found = false;

    for (int i = 0; i < steps; i++) {
        double a = xMin + i * dx;
        double b = a + dx;
        double fa = f(a), fb = f(b);

        if (fa * fb <= 0.0) {
            for (int k = 0; k < 60; k++) {
                double mid = (a + b) / 2.0;
                double fm  = f(mid);
                if (std::abs(fm) < 1e-12) { a = b = mid; break; }
                if (fa * fm < 0.0) { b = mid; fb = fm; }
                else               { a = mid; fa = fm; }
            }
            double root = (a + b) / 2.0;
            std::cout << "  f(x) = 0  at  x = " << std::fixed << std::setprecision(8)
                      << root << "  (f(x) = " << f(root) << ")\n";
            found = true;
        }
    }
    if (!found)
        std::cout << "  No root found in [" << xMin << ", " << xMax << "]\n";
    std::cout << "\n";
}

// ─── 4. Minimum via golden-section search ────────────────────────────────────
void findMinimum(double xMin, double xMax) {
    std::cout << "=== Minimum Finding (Golden-Section Search) ===\n";
    const double phi = (std::sqrt(5.0) - 1.0) / 2.0;
    double a = xMin, b = xMax;
    double c = b - phi * (b - a);
    double d = a + phi * (b - a);

    for (int k = 0; k < 300; k++) {
        if (f(c) < f(d)) b = d;
        else             a = c;
        c = b - phi * (b - a);
        d = a + phi * (b - a);
        if (std::abs(b - a) < 1e-10) break;
    }
    double xOpt = (a + b) / 2.0;
    std::cout << "  Minimum at x = " << std::fixed << std::setprecision(8)
              << xOpt << "  f(x) = " << f(xOpt) << "\n\n";
}

// ─── main ─────────────────────────────────────────────────────────────────────
int main() {
    std::cout << "============================================================\n";
    std::cout << "  Problem 1: Polynomial f(x) = 6.7x^4 + 3.2x^3 - x^2 + x - 2\n";
    std::cout << "============================================================\n\n";

    // Print sample values
    std::cout << "--- Sample values ---\n";
    std::cout << std::setw(8) << "x" << std::setw(20) << "f(x)" << "\n";
    std::cout << std::string(28, '-') << "\n";
    for (int x = -10; x <= 10; x += 2)
        std::cout << std::setw(8) << x
                  << std::setw(20) << std::fixed << std::setprecision(4) << f(x) << "\n";
    std::cout << "\n";

    // Plot graph via gnuplot
    std::cout << "=== Graph (gnuplot) ===\n";
    plotGraph(-5.0, 5.0, 500);

    // Root finding
    findRoots(-10.0, 10.0, 1000);

    // Minimum
    findMinimum(-10.0, 10.0);

    return 0;
}
