#include <fstream>
#include <memory>
#include <stdexcept>

extern std::unique_ptr<std::ifstream> g_lexer_input;

void inline lex_input(char *buf, std::size_t &bytes_read, std::size_t max_bytes_to_read) {
  bytes_read = 0;
  if (!g_lexer_input) {
    throw std::runtime_error{"g_lexer_input is not initialized"};
  }
  while (true) {
    char c = g_lexer_input->get();
    if (g_lexer_input->eof()) {
      break;
    }
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    buf[bytes_read++] = c;
    if (bytes_read == max_bytes_to_read) {
      break;
    }
  }
}
