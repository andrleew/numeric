#include "lab1.3.h"
#include <opts.h>
#include <run_solution.h>
#include <solution.h>
#include <vector.h>
#include <matrix.h>

#include <fstream>

namespace NNumeric {

    enum EOutputIndexes {
        OI_STANDART
    };

    class TIterations : public NGeneral::TSolution {
    public:
        void Start(NGeneral::TReader& reader) {
            size_t row_count, column_count;
            reader.GetInput() >> row_count >> column_count >> epsilon >> max_iteration;
            Matrix.Resize(row_count, column_count);
            Vec.Resize(row_count);
            Result.Resize(row_count);
            Matrix.ForEach([&reader](auto& el) {reader.GetInput() >> el;});
            Vec.ForEach([&reader](auto& el) {reader.GetInput() >> el;});
        }

        void Do(NGeneral::TReader&, NGeneral::TWriter&) {
            for (size_t i = 0; i < Matrix.RowsCount(); ++i) {
                for (size_t j = 0; j < Matrix.ColumnsCount(); ++j) {
                    if (i == j) continue;
                    else Matrix[i][j] /= - Matrix[i][i];
                }
                Vec[i] /= Matrix[i][i];
                Matrix[i][i] = 0;
            }

            TVector<double> currentIteration = Vec, lastIteration;
            iterations = 0;
            do {
                lastIteration = currentIteration;
                MakeIteration(currentIteration);
            } while (Diff(currentIteration, lastIteration) > epsilon
                && max_iteration != ++iterations);
            Result = currentIteration;
        }

        void Finish(NGeneral::TWriter& writer) {
            Result.ForEach([&writer](const auto& el) {
                writer.GetOutput(OI_STANDART) << el << " ";
            });
            writer.GetOutput(OI_STANDART) << "\n > iterations: " << iterations << "\n";
        }

    private:
        void MakeIteration(TVector<double>& v) {
            v = Matrix.Mult(v);
            v.Sum(Vec);
        }

        double Diff(const TVector<double>& v1, const TVector<double>& v2) {
            double max_diff = 0;
            for (size_t i = 0; i < v1.Size(); ++i) {
                max_diff = std::max(std::abs(v1[i] - v2[i]), max_diff);
            }
            return max_diff;
        }

        TMatrix<double> Matrix;
        TVector<double> Vec, Result;
        double epsilon;
        size_t max_iteration, iterations;
    };

    int Iterations(const std::vector<std::string>& argv) {
        NGeneral::TOpts opts;
        opts.AddOpt("--config", "config file with sizes", true)
            .AddOpt("--matrix", "file with matrix", true)
            .AddOpt("--vector", "file with vector", true)
            .AddOpt("--output", "output file");
        if (!opts.Parce(argv)) {
            opts.Help();
            return -1;
        }

        std::fstream
            config(opts.Get("--config")),
            matrix(opts.Get("--matrix")),
            vector(opts.Get("--vector")),
            output;

        if (opts.Has("--output")) output.open(opts.Get("--output"));

        NGeneral::TRunSolution<TIterations>()
            .Input(config)
            .Input(matrix)
            .Input(vector)
            .Output(output.is_open() ? output : std::cout)
            .Do();
        return 0;
    }
}