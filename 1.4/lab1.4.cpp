#include "lab1.4.h"
#include <opts.h>
#include <run_solution.h>
#include <solution.h>
#include <vector.h>
#include <matrix.h>
#include <logger.h>

#include <fstream>
#include <vector>
#include <cmath>

namespace NNumeric {

    enum EOutputIndexes {
        OI_STANDART
    };

//    NGeneral::TLogger logger;

    class TRotations : public NGeneral::TSolution {
    public:
        void Start(NGeneral::TReader& reader) {
            iterations = 0;
            size_t row_count, column_count;
            reader.GetInput() >> row_count >> column_count >> epsilon;
            Matrix.Resize(row_count, column_count);
            Matrix.ForEach([&reader](auto& el) {reader.GetInput() >> el;});
        }

        void Do(NGeneral::TReader&, NGeneral::TWriter&) {
            auto [i, j] = FindMaxAbs();
            while (Matrix[i][j] >= epsilon) {
                Jakobi(i, j);
                auto [_i, _j] = FindMaxAbs();
                i = _i, j = _j;
                ++iterations;
            }
        }

        void Finish(NGeneral::TWriter& writer) {
            for (size_t i = 0; i < Matrix.RowsCount(); ++i)
                writer.GetOutput(OI_STANDART) << Matrix[i][i] << "\n";
            writer.GetOutput(OI_STANDART) << "iterations: " << iterations << "\n";
        }

    private:
        inline double MakePhi(size_t i, size_t j) {
            return atan((2 * Matrix[i][j]) / (Matrix[i][i] - Matrix[j][j])) / 2;
        }

        inline auto MakeSinCos(double phi) -> std::tuple<double, double> {
            return {sin(phi), cos(phi)};
        }

        auto FindMaxAbs() -> std::tuple<size_t, size_t> {
            auto p = std::make_tuple(static_cast<size_t>(0), static_cast<size_t>(0));
            double _max = std::numeric_limits<double>::min();
            for (size_t i = 0; i < Matrix.RowsCount(); ++i)
                for (size_t j = i + 1; j < Matrix.ColumnsCount(); ++j) {
                    if (_max < std::abs(Matrix[i][j])) {
                        _max = std::abs(Matrix[i][j]);
                        p = {i, j};
                    }
                }
            return p;
        }

        void Jakobi(size_t i, size_t j) {
            auto [s, c] = MakeSinCos(MakePhi(i, j));
            TMatrix<double> b = Matrix;
            b[i][i] = c*c*Matrix[i][i] + s*s*Matrix[j][j] + 2*c*s*Matrix[i][j];
            b[j][j] = s*s*Matrix[i][i] + c*c*Matrix[j][j] - 2*c*s*Matrix[i][j];
            for (size_t m = 0; m < Matrix.RowsCount(); ++m) {
                if (m == i || m == j) continue;
                b[i][m] = b[m][i] = c*Matrix[m][i] + s*Matrix[m][j];
            }
            for (size_t m = 0; m < Matrix.RowsCount(); ++m) {
                if (m == i || m == j) continue;
                b[j][m] = b[m][j] = -s*Matrix[m][i] + c*Matrix[m][j];
            }
            b[i][j] = b[j][i] = 0;
            Matrix = b;
        }

        TMatrix<double> Matrix;
        double epsilon;
        size_t iterations;
    };

    int Rotations(const std::vector<std::string>& argv) {
        NGeneral::TOpts opts;
        opts.AddOpt("--config", "config file with sizes", true)
            .AddOpt("--matrix", "file with matrix", true)
            .AddOpt("--logger", "log file")
            .AddOpt("--output", "output file");
        if (!opts.Parce(argv)) {
            opts.Help();
            return -1;
        }

        std::fstream
            config(opts.Get("--config")),
            matrix(opts.Get("--matrix")),
            output, log;

        if (opts.Has("--output")) output.open(opts.Get("--output"));
        if (opts.Has("--logger")) log.open(opts.Get("--logger"), std::ios::out);

        // NGeneral::TLogger::Open(log.is_open() ? log : std::cout);

        NGeneral::TRunSolution<TRotations>()
        .Input(config)
        .Input(matrix)
        .Output(output.is_open() ? output : std::cout)
        .Do();

        return 0;
    }
}