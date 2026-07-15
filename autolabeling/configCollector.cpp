#include "configCollector.hpp"
#include <limits>
#include <iostream>

void data::configCollector::readStudents(std::ifstream & ifs)
{
  Student stub;
  while (!ifs.eof())
  {
    ifs.ignore(std::numeric_limits< size_t >::max(), ',');
    std::getline(ifs, stub.fullRealName.first, ',');
    std::getline(ifs, stub.fullRealName.second, ',');
    std::getline(ifs, stub.githubName, ',');
    std::getline(ifs, stub.groupLabel, ',');
    ifs.ignore(std::numeric_limits< size_t >::max(), '\n');
    students_.push_back(stub);
  }

}

void data::configCollector::readLabels(std::ifstream & ifs)
{
  ifs.ignore(std::numeric_limits< size_t >::max(), '\n');
  for (size_t i = 0; i < 5; ++i)
  {
    ifs.ignore(std::numeric_limits< size_t >::max(), ',');
  }
  Dict labLabel;
  std::getline(ifs, labLabel.first, ',');
  std::getline(ifs, labLabel.second, ',');
  labLabels_.push_back(labLabel);

  std::getline(ifs, badPRLabel_, ',');
  std::getline(ifs, badBranchLabel_, ',');
  std::getline(ifs, badIssueLabel_, ',');
  std::getline(ifs, fineLabel_, ',');
  ifs.ignore(std::numeric_limits< size_t >::max(), '\n');

  while (ifs)
  {
    for (size_t i = 0; i < 5; ++i)
    {
      ifs.ignore(std::numeric_limits< size_t >::max(), ',');
    }
    std::getline(ifs, labLabel.first, ',');
    std::getline(ifs, labLabel.second, ',');
    if (labLabel.first == "" || labLabel.second == "")
    {
      break;
    }
    labLabels_.push_back(labLabel);
  }
}

data::namingRules::namingRules(std::string & rule):
  rule_(rule)
{}

void data::namingRules::showRule()
{
  std::cout << rule_;
}
