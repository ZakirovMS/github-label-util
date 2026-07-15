#include "configCollector.hpp"
#include <limits>
#include <iostream>

data::configCollector::configCollector(std::ifstream & ifs)
{
  ifs.ignore(std::numeric_limits< size_t >::max(), '\n');
  readStudent(ifs);
  readLabLabel(ifs);
  readSpecialLabel(ifs);
  readNamingRule(ifs);
  while (ifs)
  {
    readStudent(ifs);
    readLabLabel(ifs);
    ifs.ignore(std::numeric_limits< size_t >::max(), '\n');
    if (labLabels_.back().first == "")
    {
      labLabels_.pop_back();
      break;
    }
  }

  while (ifs)
  {
    readStudent(ifs);
  }
}

const std::vector< data::Student > & data::configCollector::getStudents()
{
  return students_;
}

const std::vector< data::Dict > & data::configCollector::getLabLabels()
{
  return labLabels_;
}

const std::string & data::configCollector::getLabLabel(std::string lab)
{
  for (size_t i = 0; i < labLabels_.size(); ++i)
  {
    if (labLabels_[i].first == lab)
    {
      return labLabels_[i].second;
    }
  }

  return badIssueLabel_;
}

const std::vector< data::Dict > & data::configCollector::getGroupLabels()
{
  return groupLabels_;
}

const std::string & data::configCollector::getBadPRLabel()
{
  return badPRLabel_;
}

const std::string & data::configCollector::getBadBranchLabel()
{
  return badBranchLabel_;
}

const std::string & data::configCollector::getBadIssueLabel()
{
  return badIssueLabel_;
}

const std::string & data::configCollector::getFineLabel()
{
  return fineLabel_;
}

const data::namingRule & data::configCollector::getNamingPRRule()
{

}

const data::namingRule & data::configCollector::getNamingBranchRule()
{

}

void data::configCollector::readStudent(std::ifstream & ifs)
{
  Student stub;
  std::getline(ifs, stub.fullRealName.first, ',');
  std::getline(ifs, stub.fullRealName.second, ',');
  std::getline(ifs, stub.githubName, ',');
  std::getline(ifs, stub.groupLabel, ',');
  students_.push_back(stub);
}

void data::configCollector::readSpecialLabel(std::ifstream & ifs)
{
  std::getline(ifs, badPRLabel_, ',');
  std::getline(ifs, badBranchLabel_, ',');
  std::getline(ifs, badIssueLabel_, ',');
  std::getline(ifs, fineLabel_, ',');
}

void data::configCollector::readLabLabel(std::ifstream & ifs)
{
  Dict stub;
  std::getline(ifs, stub.first, ',');
  std::getline(ifs, stub.second, ',');
  labLabels_.push_back(stub);
}

void readNamingRule(std::ifstream & ifs, data::namingRule & nr)
{
  std::string rule;
  std::getline(ifs, rule, ',');
  nr.setRule(rule);
}

void data::namingRule::setRule(const std::string & rule)
{
  rule_ = rule;
}

const std::string & data::namingRule::getRule()
{
  return rule_;
}
