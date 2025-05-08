/*
 * Assignment 1 - Developing List Data Structures and Artificial Neural Networks
 * file : random_test.cpp
 * Data Structures and Algorithms
 * Author: Võ Tiến
 * Link FB : https://www.facebook.com/Shiba.Vo.Tien
 * Link Group : https://www.facebook.com/groups/khmt.ktmt.cse.bku
 * Date: 10.9.2024
 */
#include "random_test.hpp"

RandomTest::RandomTest(int from, int to) : from(from), to(to) {}

void RandomTest::runTest() {
  for (int i = from; i <= to; ++i) {
    std::string inputFilename =
        "test/random_test/input/input_" + std::to_string(i);
    std::string outputFilename =
        "test/random_test/output/output_" + std::to_string(i);
    processFile(inputFilename, outputFilename);
  }

  // compareOutputs();
}
template <class T>
void RandomTest::runtime(IList<T> &list) {}

void RandomTest::processFile(string inputFilename, string outputFilename) {
  std::ifstream file(inputFilename);
  int number_line, capacity;
  // Check if the file was successfully opened
  if (!file.is_open()) {
    cerr << "Error: Could not open file " << inputFilename << endl;
    return;
  }

  string skip, _iList, _type, _itemEqual, _deleteUserData;
  file >> number_line >> skip >> _iList >> skip >> _type;
  file >> skip >> skip >> _itemEqual;
  file >> skip >> skip >> _deleteUserData;
  file >> skip >> skip >> capacity >> skip;
  // std::map<std::string, bool (*)(Point &, Point &)> function_itemEqual;
  // function_itemEqual["null"] = 0;
  // function_itemEqual["pointEQ_X"] = &Point::pointEQ_X;
  // function_itemEqual["pointEQ_Y"] = &Point::pointEQ_Y;
  // function_itemEqual["pointEQ_Z"] = &Point::pointEQ_Z;
  // function_itemEqual["pointEQ"] = &Point::pointEQ;

  // if (_iList == "XArrayList") {
  //   if (_type == "string") {
  //     XArrayList<std::string> list(0, 0, capacity);
  //     this->runtime(list);
  //   } else if (_type == "int") {
  //     XArrayList<int> list(0, 0, capacity);
  //     this->runtime(list);
  //   } else if (_type == "bool") {
  //     XArrayList<bool> list(0, 0, capacity);
  //     this->runtime(list);
  //   } else if (_type == "Point") {
  //     XArrayList<Point> list(0, function_itemEqual[_itemEqual], capacity);
  //     this->runtime(list);
  //   } else if (_type == "Point*") {
  //     XArrayList<Point *> list(&XArrayList<Point *>::free,
  //                              function_itemEqual[_itemEqual], capacity);
  //     this->runtime(list);
  //   }
  // } else if (_iList == "XArrayList") {
  //   if (_type == "string") {
  //     XArrayList<std::string> list(0, 0, capacity);
  //     this->runtime(list);
  //   } else if (_type == "int") {
  //     XArrayList<int> list(0, 0, capacity);
  //     this->runtime(list);
  //   } else if (_type == "bool") {
  //     XArrayList<bool> list(0, 0, capacity);
  //     this->runtime(list);
  //   } else if (_type == "Point") {
  //     XArrayList<Point> list(0, function_itemEqual[_itemEqual], capacity);
  //     this->runtime(list);
  //   } else if (_type == "Point*") {
  //     XArrayList<Point *> list(&XArrayList<Point *>::free,
  //                              function_itemEqual[_itemEqual], capacity);
  //     this->runtime(list);
  //   }
}

void RandomTest::compareOutputs() {
  std::vector<std::string> fails;
  int totalTests = 0;

  for (int i = from; i <= to; ++i) {
    std::string outputFile =
        "test/random_test/output/output_" + std::to_string(i) + ".txt";
    std::string expectedFile =
        "test/random_test/expected/expected_" + std::to_string(i) + ".txt";

    try {
      bool result = compareFiles(outputFile, expectedFile);
      if (result) {
        // Print pass message if files match
        std::cout << green << "Test input_" << i << " --------------- PASS"
                  << reset << "\n";
      } else {
        // Print fail message if files don't match
        fails.push_back("input_" + std::to_string(i));
        std::cout << red << "Test input_" << i << " --------------- FAIL"
                  << reset << "\n";
      }
      ++totalTests;
    } catch (const std::runtime_error &e) {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }

  std::cout << cyan << "\nResult -------------------------" << reset
            << std::endl;
  if (fails.empty()) {
    std::cout << green << "All tests passed!" << reset << std::endl;
  } else {
    int failedTests = fails.size();
    int passedTests = totalTests - failedTests;
    double passRate =
        (totalTests > 0)
            ? (static_cast<double>(passedTests) / totalTests) * 100.0
            : 0.0;

    std::cout << red << "Some tests failed:";
    for (const auto &fail : fails) {
      std::cout << "  " << fail;
    }
    std::cout << cyan << "\nPass rate: " << passRate << "%" << reset
              << std::endl;
  }
}

bool RandomTest::compareFiles(const std::string &file1,
                              const std::string &file2) {
  std::ifstream f1(file1);
  std::ifstream f2(file2);

  if (!f1.is_open() || !f2.is_open()) {
    throw std::runtime_error("Could not open files for comparison.");
  }

  std::stringstream buffer1, buffer2;
  buffer1 << f1.rdbuf();
  buffer2 << f2.rdbuf();

  return buffer1.str() == buffer2.str();
}
