#include "lab1.2.h"
#include <opts.h>
#include <matrix.h>
#include <vector.h>
#include <solution.h>
#include <run_solution.h>

#include <fstream>

namespace NNumeric {
    enum EOutputIndex {
        OI_STANDART
    };

    class TRunning : public NGeneral::TSolution {
    private:
        template <class T> inline
        double Get(const T& vec, const size_t i) const {
            return i < vec.Size() ? vec[i] : 0;
        }

    public:

        void Start(NGeneral::TReader& is) {
            size_t rowCount, columnCount;
            is.GetInput() >> rowCount >> columnCount;
            Matrix.Resize(rowCount, columnCount);
            Vector.Resize(rowCount);
            VectorA.Resize(rowCount);
            VectorB.Resize(rowCount);
            Result.Resize(rowCount);
            Matrix.ForEach([&is](auto& t){is.GetInput() >> t;});
            Vector.ForEach([&is](auto& t){is.GetInput() >> t;});
        }

        void Do(NGeneral::TReader&, NGeneral::TWriter&) {
            double y;
            for (size_t i = 0; i < Vector.Size(); ++i) {
                y = GetMatrix(i, B) + GetMatrix(i, A) * GetA(i - 1);  // i ; i - 1
                VectorA[i] = -GetMatrix(i, C) / y; // i + 1
                VectorB[i] = (Vector[i] - GetMatrix(i, A) * GetB(i - 1)) / y; // i - 1
            }
            for (size_t i = Vector.Size() - 1; static_cast<int64_t>(i) >= 0; --i) {
                Result[i] = GetA(i) * Get(Result, i + 1) + GetB(i);
            }
        }

        void Finish(NGeneral::TWriter& os) {
            Result.ForEach([&os](auto& t){os.GetOutput(OI_STANDART) << t << " ";});
            os.GetOutput(OI_STANDART) << "\n";
        }

    private:
        enum EMatrixIndexes {
            A, B, C
        };

        double GetMatrix(size_t i, size_t j) {
            if (i < Matrix.RowsCount() && j < Matrix.ColumnsCount())
                return Matrix[i][j];
            else
                return 0;
        }

        inline double GetA(size_t i) const {
            return Get(VectorA, i);
        }

        inline double GetB(size_t i) const {
            return Get(VectorB, i);
        }

    private:
        TMatrix<double> Matrix;
        TVector<double> Vector, VectorA, VectorB, Result;
    };


    int Running(const std::vector<std::string>& argv) {
        NGeneral::TOpts opts;
        opts.AddOpt("--config", "config file with sizes", true)
            .AddOpt("--matrix", "file with matrix", true)
            .AddOpt("--vector", "file with vector", true);
        if (!opts.Parce(argv)) {
            opts.Help();
            return -1;
        }

        std::fstream
            config(opts.Get("--config")),
            matrix(opts.Get("--matrix")),
            vector(opts.Get("--vector"));

        NGeneral::TRunSolution<TRunning>()
            .Input(config)
            .Input(matrix)
            .Input(vector)
            .Output(std::cout)
            .Do();
        return 0;
    }
}