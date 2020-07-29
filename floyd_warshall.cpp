// Input : adjacency matrix
template <typename T, long long int FW_INF>
void floyd_warshall(std::vector <std::vector <T>>& g) {
	int n = g.size();
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (g[i][k] < FW_INF && g[k][j] < FW_INF) {
					g[i][j] = std::min(g[i][j], g[i][k] + g[k][j]);
				}
			}
		}
	}
}

