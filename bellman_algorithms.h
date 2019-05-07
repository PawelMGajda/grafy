#pragma once

#include <chrono>
#include <string>

#include "list_graph.h"
#include "matrix_graph.h"


double bellmanFord(std::shared_ptr<ListGraph> t_graph, int startowy, bool czy_wypisac);

double bellmanFord(std::shared_ptr<MatrixGraph> t_graph, int startowy, bool czy_wypisac);