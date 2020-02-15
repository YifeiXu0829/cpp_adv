#ifndef SPARSE_H
#  define SPARSE_H
#include <map>
#include <vector>
#include<utility>
#include<future>
#include<thread>
#include<algorithm>
#include<iterator>
#include<functional>
#include<numeric>
#include<stdexcept>
#ifdef PARALLEL_STL
#include<execution>
using std::execution::par_unseq;
#endif

using std::map;
using std::vector;
using std::pair;
using std::future;
using std::thread;
using std::transform;
using std::transform_reduce;
using std::back_inserter;
using std::async;
using std::ref;
using std::accumulate;
using std::out_of_range;
using std::move;

namespace mpcs {

class SparseMatrix {
public:
	void push_back(map<size_t, double> const &row) {
		values.push_back(row);
	}
#ifndef PARALLEL_STL
	inline friend vector<double> operator*(SparseMatrix const &m, vector<double> const &v) {
		vector<future<double>> futureResults;
		transform(m.values.begin(), m.values.end(), back_inserter(futureResults),
			[&v](map<size_t, double> const &row) {
			return async([&row, &v]() {
				return accumulate(row.begin(), row.end(), 0.0, [&v](double acc, pair<size_t, double> const &elt) {
					if (elt.first >= v.size())
						throw out_of_range("Vector to short to multiply by SparseMatrix");
					return acc + elt.second * v[elt.first];
				});
			});
		});
		vector<double> result;
		transform(futureResults.begin(), futureResults.end(), back_inserter(result),
			[](auto &f) { return f.get(); });
		return result;
	}
#else
	inline friend vector<double> operator*(SparseMatrix const& m, vector<double> const& v) {
		vector<double> result(m.values.size());
		transform(par_unseq, m.values.begin(), m.values.end(), result.begin(),
			[&v](map<size_t, double> row) {
				return transform_reduce(par_unseq, row.begin(), row.end(), 0.0,
					std::plus<double>(),
					[&v](pair<size_t, double> const& elt) {
						return elt.second * v[elt.first]; 
					});
			});
		return result;
	}

#endif
private:
	vector<map<size_t, double>> values;
};

}
#endif
