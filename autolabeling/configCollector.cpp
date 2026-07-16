#include "configCollector.hpp"
#include <limits>

data::configCollector::configCollector(std::ifstream & ifs)
{
  ifs.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  ifs.ignore(std::numeric_limits< std::streamsize >::max(), ',');
  readStudent(ifs);
  readLabLabel(ifs);
  readSpecialLabel(ifs);
  readNamingRule(ifs, namingPR_);
  readNamingRule(ifs, namingBranch_, '\n');
  for (size_t i = 0; i < labCount_ - 1; ++i)
  {
    ifs.ignore(std::numeric_limits< std::streamsize >::max(), ',');
    readStudent(ifs);
    readLabLabel(ifs);
    ifs.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  while (ifs.peek() != EOF)
  {
    ifs.ignore(std::numeric_limits< std::streamsize >::max(), ',');
    readStudent(ifs);
    ifs.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}

const std::vector< data::Student > & data::configCollector::getStudents() const
{
  return students_;
}

const std::string & data::configCollector::getStudentsGrLabel(std::pair< std::string, std::string > realName, std::string githubName) const
{
  for (size_t i = 0; i < students_.size(); ++i)
  {
    if (students_[i].fullRealName == realName && students_[i].githubName == githubName)
    {
      return students_[i].groupLabel;
    }
  }

  return badIssueLabel_;
}

const std::vector< data::Dict > & data::configCollector::getLabLabels() const
{
  return labLabels_;
}

const std::string & data::configCollector::getLabLabel(std::string lab) const
{
  for (size_t i = 0; i < labLabels_.size(); ++i)
  {
    if (labLabels_[i].first == lab)
    {
      return labLabels_[i].second;
    }
  }

  return badPRLabel_;
}

size_t data::configCollector::getLabCount() const
{
  return labCount_;
}

const std::string & data::configCollector::getTokenGitHub() const
{
  return tokenGitHub_;
}

const std::string & data::configCollector::getOwnerGitHub() const
{
  return ownerGitHub_;
}

const std::string & data::configCollector::getReposGitHub() const
{
  return reposGitHub_;
}

const std::string & data::configCollector::getBadPRLabel() const
{
  return badPRLabel_;
}

const std::string & data::configCollector::getBadBranchLabel() const
{
  return badBranchLabel_;
}

const std::string & data::configCollector::getBadIssueLabel() const
{
  return badIssueLabel_;
}

const std::string & data::configCollector::getFineLabel() const
{
  return fineLabel_;
}

const data::namingRule & data::configCollector::getNamingPRRule() const
{
  return namingPR_;
}

const data::namingRule & data::configCollector::getNamingBranchRule() const
{
  return namingBranch_;
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
  std::string stub;
  std::getline(ifs, stub, ',');
  labCount_ = std::stoull(stub);

  std::getline(ifs, tokenGitHub_, ',');
  std::getline(ifs, ownerGitHub_, ',');
  std::getline(ifs, reposGitHub_, ',');

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

void data::configCollector::readNamingRule(std::ifstream & ifs, data::namingRule & nr, char del)
{
  std::string rule;
  std::getline(ifs, rule, del);
  nr.setRule(rule);
}

void data::namingRule::setRule(const std::string & rule)
{
  rule_ = rule;
}

const std::string & data::namingRule::getRule() const
{
  return rule_;
}
