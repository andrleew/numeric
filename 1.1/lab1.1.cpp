#include "lab1.1.h"
#include <matrix.h>
#include <vector.h>
#include <opts.h>
#include <solution.h>
#include <run_solution.h>

#include <fstream>

namespace NNumeric {

    enum EOutputIndexes {
        OI_STANDART
    };

    class TLUSolution : public NGeneral::TSolution{
    public:
        void Start(NGeneral::TReader& reader) {
            size_t rowCount, columnCount;
            reader.GetInput() >> rowCount >> columnCount;
            Matrix.Resize(rowCount, columnCount);
            Vector.Resize(rowCount);
            Result.Resize(rowCount);
            Matrix.ForEach([&reader](auto& t) {reader.GetInput() >> t;} );
            Vector.ForEach([&reader](auto& t) {reader.GetInput() >> t;} );
        }

        void Do(NGeneral::TReader&, NGeneral::TWriter&) {
            TMatrix<double> L (Matrix.RowsCount(), Matrix.ColumnsCount());
            TMatrix<double> U = Matrix;

            for(size_t i = 0; i < Matrix.RowsCount(); i++)
                for(size_t j = i; j < Matrix.ColumnsCount(); j++)
                    L[j][i]=U[j][i]/U[i][i];
            
            for(size_t k = 1; k < Matrix.RowsCount(); k++) {
                for(size_t i = k-1; i < Matrix.RowsCount(); i++)
                    for(size_t j = i; j < Matrix.ColumnsCount(); j++)
                        L[j][i] = U[j][i]/U[i][i];

                for(size_t i = k; i < Matrix.RowsCount(); i++)
                    for(size_t j = k-1; j < Matrix.ColumnsCount(); j++)
                        U[i][j] -= L[i][k-1]*U[k-1][j];
            }
            Result = Gauss_U(U, Gauss_L(L, Vector));
        }

        void Finish(NGeneral::TWriter& writer) {
            Result.ForEach([&writer] (const auto& t) {writer.GetOutput(OI_STANDART) << t << " ";} );
            writer.GetOutput(OI_STANDART) << "\n";
        }

    private:
        TMatrix<double> Matrix;
        TVector<double> Vector, Result;

    private:
        TVector<double> Gauss_L(const TMatrix<double>& matr, TVector<double> vec) { 
            for (size_t i = 0; i < matr.RowsCount(); ++i) {
                for (size_t j = 0; j < i; ++j) {
                    vec[i] -= matr[i][j] * vec[j];
                }
            }
            return vec;
        }

        TVector<double> Gauss_U(const TMatrix<double>& matr, TVector<double> vec) { 
            for (size_t i = matr.RowsCount() - 1; static_cast<int>(i) >= 0; --i) {
                for (size_t j = matr.ColumnsCount() - 1; j > i; --j) {
                    vec[i] -= matr[i][j] * vec[j];
                }
                vec[i] /= matr[i][i];
            }
            return vec;
        }
    };

    int LU(const std::vector<std::string>& argv) {
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

        NGeneral::TRunSolution<TLUSolution>()
            .Input(config)
            .Input(matrix)
            .Input(vector)
            .Output(output.is_open() ? output : std::cout)
            .Do();
        return 0;
    }
}