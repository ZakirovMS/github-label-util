#ifndef PARCECONFIG_HPP
#define PARCECONFIG_HPP

#include <vector>
#include <string>
#include <fstream>
namespace data
{
  using Dict = std::pair< std::string, std::string >;

  struct Student
  {
    std::pair< std::string, std::string > fullRealName;
    std::string githubName;
    std::string groupLabel;
  };

  class namingRules
  {
    namingRules(std::string rule);
    //todo
  };

  class configCollector
  {
  public:

  private:
    std::vector< Student > students;
    std::vector< Dict > labLabels;
    std::vector< Dict > groupLabels;
    std::string badPRLabel;
    std::string badBranchLabel;
    std::string badIssueLabel;
    std::string fineLabel;
    namingRules namingPR;
    namingRules namingBranch;

    void readStudents(std::ifstream & ifs);
    void readLabels(std::ifstream & ifs);

  };
}

#endif
