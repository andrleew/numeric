#include "lab1.5.h"
#include <opts.h>
#include <run_solution.h>
#include <solution.h>
#include <vector.h>
#include <matrix.h>
#include <logger.h>

#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

namespace NNumeric {

    // NGeneral::TLogger logger;

    enum EOutputIndexes {
        OI_STANDART
    };

    class TQRValues : public NGeneral::TSolution {
    public:
        void Start(NGeneral::TReader& reader) {
            iterations = 0;
            size_t row_count, column_count;
            reader.GetInput() >> row_count >> column_count >> epsilon;
            Matrix.Resize(row_count, column_count);
            Matrix.ForEach([&reader](auto& el) {reader.GetInput() >> el;});
        }

        void Do(NGeneral::TReader&, NGeneral::TWriter&) {
            while (MaxLowDiagonale() >= epsilon) {
                QR();
                ++iterations;
            }
        }

        void Finish(NGeneral::TWriter& writer) {
            for (size_t i = 0; i < Matrix.RowsCount(); ++i)
                writer.GetOutput(OI_STANDART) << Matrix[i][i] << "\n";
            writer.GetOutput(OI_STANDART) << "iterations: " << iterations << "\n";
        }

    private:
        inline double constexpr Sqr(double a) const noexcept {
            return a * a;
        }

        double MaxLowDiagonale() {
            double _max = std::numeric_limits<double>::min();
            for (size_t i = 1; i < Matrix.RowsCount(); ++i)
                for (size_t j = 0; j < i; ++j) 
                    _max = std::max(_max, std::abs(Matrix[i][j]));
            return _max;
        }

        void QR() {
            auto Q = Matrix;
            Orthogonized(Q);
            auto R = Q.GetTransposed().Mult(Matrix);
                for (const auto& v : R) {
                    for (const auto& el: v) {
                        std::cout << el << " ";
                    }
                    std::cout << "\n";
                }
                std::cout << "--------------------\n";
            Matrix = Q.Mult(R);
        }

        void Orthogonized(TMatrix<double> & matr) {
            auto tmp = matr.GetTransposed();
            TMatrix<double> res = tmp;
            for (size_t i = 0; i < res.RowsCount(); ++i) {
                for (size_t j = 0; j < i; ++j) {
                    res[i].Minus(tmp[i].GetMulted(tmp[i].Mult(res[j]) / res[j].Mult(res[j])));
                }
            }

            // res.GetTransposed().WriteMatrix();

            for (size_t i = 0; i < res.RowsCount(); ++i) {
                double avgsqr = res[i].AvgSqr();
                for (size_t j = 0; j < res.ColumnsCount(); ++j)
                    res[i][j] /= avgsqr;
            }
            
            // for (size_t i = 0; i < res.RowsCount(); ++i) {
            //     TVector<double> tmp_vec (res.RowsCount(), 0);
            //     for (size_t j = 0; j <= i; ++j) {
            //         tmp_vec.Sum(res[j].GetMulted(res[j].Mult(tmp[i])));
            //     }
            // }
            matr = res.GetTransposed();
        }

    private:
        TMatrix<double> Matrix;
        double epsilon;
        size_t iterations;
    };

    int QR(const std::vector<std::string>& argv) {
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

        NGeneral::TRunSolution<TQRValues>()
        .Input(config)
        .Input(matrix)
        .Output(output.is_open() ? output : std::cout)
        .Do();

        return 0;
    }
}