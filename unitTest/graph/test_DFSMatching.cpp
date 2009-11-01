#include "../UnitTest.h"
#include "../../content/graph/dfs_matching.h"
#include <fstream>
#include <sstream>

class test_DFSMatching :
	public UnitTest
{
	public:
		ifstream in;
		int cases;

		test_DFSMatching() : UnitTest("test_DFSMatching") {
			in.open("Matching.in");
			in >> cases;
		}

		virtual ~test_DFSMatching() {
			in.close();
		}

		virtual void run(int subcase) {
			int n, m, k;
			in >> n >> m >> k;
			vector<vector<int> > g(n);
			for (int i = 0; i < k; i++) {
				int x, y; in >> x >> y;
				x--; y--;
				g[x].push_back(y);
			}
			int res = dfs_matching(g, n, m);
			if (subcase == 0) check(res, 2, "0");
			if (subcase == 1) check(res, 43, "1");
			if (subcase == 2) check(res, 40, "2");
			if (subcase == 3) check(res, 40, "3");
			if (subcase == 4) check(res, 47, "4");
		}

		virtual int getCount() const {
			return cases;
		}
};

KACTL_AUTOREGISTER_TEST(test_DFSMatching);