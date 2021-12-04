#include <iostream>
#include <vector>
#include <sstream>
#include <memory>

struct HtmlElement {
  std::string name, text;
  std::vector<HtmlElement> elements;
  const size_t indent_size = 2;
  HtmlElement() {}
  HtmlElement(const std::string &name, const std::string &text) : name(name), text(text) {}

  std::string str(int indent = 0) const {
	std::ostringstream oss;
	std::string i(indent_size * indent, ' ');
	oss << i << "<" << name << '>' << std::endl;
	if (text.size() > 0) {
	  oss << std::string(indent_size * (indent + 1), ' ') << text << std::endl;
	}
	for (const auto &e: elements) {
	  oss << e.str(indent + 1);
	}
	oss << i << "</" << name << ">" << std::endl;
	return oss.str();
  }
};

int main() {
  std::cout << "Hello, World!" << std::endl;
  return 0;
}
