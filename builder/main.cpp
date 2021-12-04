#include <iostream>
#include <utility>
#include <vector>
#include <sstream>

struct HtmlElement {
  std::string name, text;
  std::vector<HtmlElement> elements;
  const size_t indent_size = 2;

  HtmlElement() = default;
  HtmlElement(std::string name, std::string text) : name(std::move(name)), text(std::move(text)) {}

  std::string str(int indent = 0) const {
	std::ostringstream oss;
	std::string i(indent_size * indent, ' ');
	oss << i << '<' << name << '>' << std::endl;
	if (!text.empty()) {
	  oss << std::string(indent_size * (indent + 1), ' ') << text << std::endl;
	}
	for (const auto &e: elements) {
	  oss << e.str(indent + 1);
	}
	oss << i << "</" << name << ">" << std::endl;
	return oss.str();
  }
};

struct HtmlBuilder {
  HtmlElement root;
  explicit HtmlBuilder(std::string root_name) {
	root.name = std::move(root_name);
  }
  void add_child(std::string child_name, std::string child_text) {
	HtmlElement e{std::move(child_name), std::move(child_text)};
	root.elements.emplace_back(e);
  }
  std::string str() const { return root.str(); }
};

int main() {
  HtmlBuilder builder{"ul"};
  builder.add_child("li", "hello");
  builder.add_child("li", "world");
  std::cout << builder.str();
  return 0;
}
