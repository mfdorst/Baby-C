#include "symbol_table.hpp"
#include <iostream>
#include <unordered_map>

std::unordered_map<std::string, std::size_t> g_symbol_table;
std::size_t g_last_symbol_location = 0;

void add_declaration(std::string symbol) {
  std::cout << "Processing declaration of " << symbol << '\n';
  g_symbol_table.emplace(std::move(symbol), g_last_symbol_location += 4);
}

bool symbol_declared(std::string const &symbol) { return g_symbol_table.count(symbol) > 0; }
